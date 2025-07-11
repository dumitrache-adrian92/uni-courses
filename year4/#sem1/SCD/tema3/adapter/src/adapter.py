import json
import logging

from datetime import datetime


import influxdb_client
import paho.mqtt.client as mqtt

from influxdb_client.client.write_api import SYNCHRONOUS, Point

class Adapter:
    DATETIME_FORMAT = '%Y-%m-%dT%H:%M:%S%z'

    def __init__(self, broker_address, broker_port,
                 influxdb_address, influxdb_port, influxdb_bucket,
                 influxdb_token, influxdb_org,
                 debug):
        self.__broker_address = broker_address
        self.__broker_port = broker_port
        self.__influxdb_address = influxdb_address
        self.__influxdb_port = influxdb_port
        self.__influxdb_bucket = influxdb_bucket
        self.__influxdb_token = influxdb_token
        self.__influxdb_org = influxdb_org

        self.__mqtt_client = None
        self.__influxdb_database_client = None
        self.__write_api = None

        self.__logger = logging.getLogger(__name__)
        logging.basicConfig(format='%(asctime)s  %(message)s', datefmt='%y-%b-%d %H:%M:%S')
        if debug:
            self.__logger.setLevel(logging.DEBUG)
        else:
            import sys
            logging.disable(sys.maxsize)

    def __on_connect(self, client, userdata, flags, reason_code, properties):
        self.__mqtt_client.subscribe("#")

    def __validate_topic(self, topic):
        return topic.count("/") == 1

    def __on_message(self, client, userdata, msg):
        # take timestamp as soon as message is received in case it is not provided
        timestamp = datetime.now().strftime(self.DATETIME_FORMAT)

        if not self.__validate_topic(msg.topic):
            self.__logger.error("Received message on invalid topic: %s", msg.topic)
            return

        location, station = msg.topic.split("/")
        data = None

        try:
            data = json.loads(msg.payload)
        except json.JSONDecodeError:
            self.__logger.error("Received payload that is not JSON format: %s", msg.payload)
            return

        self.__logger.debug("Received a message by topic [%s]", msg.topic)

        if 'timestamp' in data:
            timestamp = datetime.strptime(data['timestamp'], self.DATETIME_FORMAT)
            self.__logger.debug("Data timestamp is: %s", timestamp)
        else:
            self.__logger.debug("Data timestamp is NOW")

        measurements = filter(lambda item:
                                  item[0] != 'timestamp' and
                                  isinstance(item[1], (int, float)),
                              data.items())

        for measurement, value in measurements:
            data_point = Point(f"{station}.{measurement}") \
                        .tag("location", location) \
                        .tag("station", station) \
                        .field("value", value) \
                        .time(timestamp)

            self.__write_api.write(self.__influxdb_bucket, self.__influxdb_org, data_point)
            self.__logger.debug("%s.%s.%s %s", location, station, measurement, value)


    def start(self):
        self.__mqtt_client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
        self.__mqtt_client.on_connect = self.__on_connect
        self.__mqtt_client.on_message = self.__on_message
        self.__mqtt_client.connect(self.__broker_address, self.__broker_port, 60)

        self.__influxdb_database_client = influxdb_client.InfluxDBClient(
            url=f"http://{self.__influxdb_address}:{self.__influxdb_port}",
            token=self.__influxdb_token,
            org=self.__influxdb_org
        )
        self.__write_api = self.__influxdb_database_client.write_api(write_options=SYNCHRONOUS)

        self.__mqtt_client.loop_forever()
