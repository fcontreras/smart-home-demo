# MQTT with Smart home
This code is based on the components for the [KEYESTUDIO ESP32](https://www.amazon.com/dp/B0B7637837) but is generic enough so it can be used with other boards with a few changes.
The idea behind this is that instead of using the App provided by the Keystudio company, all components will be exposing information and consuming commands from a MQTT server, allowing others 
to control it externally.

## How to run this
In order to run this, you need to:
1. Update the settings.h file with a unique ID for your smart home (since this example uses the public mosquitto test server).
2. Create an arduino-secrets.h file with the following content:
```
//WiFi Consts
#define wifi_ssid "YOUR WIFI SSID"
#define wifi_secret "YOUR WIFI PASSWORD"
```
3. Include all the libraries provided by the Keystudio smart home, you can download them [here](https://www.dropbox.com/scl/fo/ys76epnqdnaju8tonx55v/AJPbXisPt649xpJ25iO_toU/3.%20Arduino%20Tutorials/Libraries?dl=0&rlkey=yrljitgfxrg8z1tzfxtl0xqzx&subfolder_nav_tracking=1)

## Disclaimer
This project was made for educational proposes, use it at your own risk.

## Troubleshooting
You might find an issue with "'ledcSetup' was not declared in this scope". This is because the libraries in used for this project are very old (I might update them at some point but for now it is like this).
So, to solve it make sure that the board you installed in the board manager for the ESP32 is version 2.x. refer to someone mentioning this on github [here](https://github.com/espressif/arduino-esp32/issues/9510)
and the migration guide where the breaking changes are explained [here](https://docs.espressif.com/projects/arduino-esp32/en/latest/migration_guides/2.x_to_3.0.html#ledc)
