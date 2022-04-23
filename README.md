# Temperature_measurement
All files needed for the temperature measurement projct at Lollo's.


# Raspberry pi
The raspberry pi hosts [node-red](https://nodered.org/docs/getting-started/raspberrypi) and [mqtt-broker](https://pimylifeup.com/raspberry-pi-mosquitto-mqtt-server/). To access node-red outside of lan, use [zerotier](https://www.zerotier.com/). Import src/flow.json into node-red to get the "website".

Mosquitto runs on port 1880 and node-red on 1883.

# Zerotier
## Raspberry pi
install: ```curl -s https://install.zerotier.com | sudo bash```

join network: ```zerotier-cli join 233ccaac2713da94```

It will automatically join on reboot

## Mobile
Install zero tier app and join network ```233ccaac2713da94```, you can now enter 192.168.193.107:1880/ui to see the "website". Make sure to accept the mobile and raspberry, Noa. 