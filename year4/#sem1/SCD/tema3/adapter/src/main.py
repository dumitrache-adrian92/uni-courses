import os

from adapter import Adapter

if __name__ == "__main__":
    broker_address = os.getenv("MQTT_BROKER_HOST")
    broker_port = int(os.getenv("MQTT_BROKER_PORT"))
    influxdb_address = os.getenv("INFLUXDB_HOST")
    influxdb_port = int(os.getenv("INFLUXDB_PORT"))
    influxdb_bucket = os.getenv("INFLUXDB_BUCKET")
    influxdb_database = os.getenv("INFLUXDB_DB")
    influxdb_token = os.getenv("INFLUXDB_TOKEN")
    influxdb_org = os.getenv("INFLUXDB_ORG")
    debug = os.getenv("DEBUG_DATA_FLOW", "false").lower() == "true"

    adapter = Adapter(broker_address, broker_port, influxdb_address, influxdb_port,
                      influxdb_bucket, influxdb_token, influxdb_org,
                      debug)
    adapter.start()
