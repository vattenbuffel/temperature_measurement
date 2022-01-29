# Temperature_measurement
All files needed for the temperature measurement projct at Lollo's.


# Raspberry pi
The raspberry pi hosts [node-red](https://nodered.org/docs/getting-started/raspberrypi) and [mqtt-broker](https://pimylifeup.com/raspberry-pi-mosquitto-mqtt-server/). To access node-red outside of lan, forward node-red(port 1880) to [ngrok](https://www.techcoil.com/blog/how-to-put-your-raspberry-pi-server-on-the-internet-with-ngrok/). Import src/flow.json into node-red to get the "website".
