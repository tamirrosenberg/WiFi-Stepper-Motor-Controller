# WiFi Stepper Motor Controller
Control Stepper Motor remotely using WiFI using ESP8266, DRV8825 and the Blynk App


The Project
-----------
Tuning the Magnetic loop antenna, by controling the capacitor remotely, using Wifi. 
I built a Magnetic Loop Antenna, and my idea was to control the tuning capacitor remotely.
## --> Please visit my YouTube channel to see this project in action

This project is based on:
* ESP8266 Micro Controller
* DRV8255 Stepper Motor Driver
* Bipolar stepper motor
* Blynk Application

The Blynk App
-------------
In the Blynk app, I added five virtual buttons:
  * V0 - Tune Left
  * V1 - Tune Right
  * V2 - Fine Tune Left
  * V3 - Fine Tune Right
  * V4 - Scan
  
https://blynk.io/

DRV8825 - Motor Driver
----------------------
The DRV8825 is a smart motor driver that can be used with normal steps and even with micro-steps, and that can be controlled by
the driver's pins M0, M1, M2. In my case I wanted to use the 1/32 micro-steps, and these are the speeds that you will see in the code.
More details about this driver can be found here: https://www.pololu.com/product/2133

Arduino IDE
-----------
When you are using the Arduino IDE, you will probalby need to install the Blynk library, so please follow this procedure:
From the Arduino IDE menu:
1. Go to "Sketch" --> "Include Library" --> "Manage Libraries"
2. Search for "Blynk", and install it

Download: https://www.arduino.cc/en/software

License
-------
Are you allowed to use this code anywhere? Or change the code? - Yes! You are free to do that! Enjoy!
Please feel free to change that to your own project use case.

### Design: Tamir Rosenberg, N6JJ
### YouTube Channel Name: re: Ham Radio
### YouTube Channel link: https://www.youtube.com/channel/UCHImT8lgZAWDnsUao0wHAQQ

# The best "Thank you" will be to subscribe to my channel and "like" the video - Thanks in advance!
