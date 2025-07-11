import paho.mqtt.client as mqtt
import time

# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, reason_code, properties):
    print(f"Connected with result code {reason_code}")
    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe("scd/chat/#")


# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    print(msg.topic+ " " + str(msg.payload))

mqttc = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
mqttc.on_connect = on_connect
mqttc.on_message = on_message
mqttc.user_data_set([])

mqttc.connect("mqtt.dfilip.xyz", 1883)

mqttc.loop_start()

time.sleep(2)

while True:
    string = input("Enter message:")
    mqttc.publish("scd/chat/adi", string)

# client.loop_stop()
# client.disconnect()

