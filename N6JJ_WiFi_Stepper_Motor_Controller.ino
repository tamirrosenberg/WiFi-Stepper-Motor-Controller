/*************************************************************************************************************************************
Project: Tuning the Magnetic loop capacitor remotely using Wifi
Details: This project is based on the ESP8266 Micro Controller, DRV8255 stepper motor driver, bipolar stepper motor and the Blynk App.
I built a Magnetic Loop Antenna, and my idea was to control the tuning capacitor remotely, using Wifi.
In the Blynk app, I added five virtual buttons:
  V0 - Tune Left
  V1 - Tune Right
  V2 - Fine Tune Left
  V3 - Fine Tune Right
  V4 - Scan
The DRV8825 is a smart motor driver that can be used with normal steps and even with micro-steps, and that can be controlled by
the driver's pins M0, M1, M2. In my case I wanted to use the 1/32 micro-steps, and these are the speeds that you will see in the code.
More details about this driver can be found here: https://www.pololu.com/product/2133
Please feel free to change that to your own project use case.
Please visit my YouTube channel to see this project in action.
Are you allowed to use this code anywhere? Or change the code? - Yes! You are free to do that! Enjoy!
Design: Tamir Rosenberg, N6JJ
YouTube Channel Name: re: Ham Radio
YouTube: https://www.youtube.com/channel/UCHImT8lgZAWDnsUao0wHAQQ
**************************************************************************************************************************************/

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_PRINT Serial

// Define pin connections
const int enablePin = 0;                            // ESP8266 digital pin 0
const int stepPin = 4;                              // ESP8266 digital pin 4
const int dirPin = 5;                               // ESP8266 digital pin 5

// Define Blynk ports
bool TuneRight = false;
bool TuneLeft = false;
bool FineTuneRight = false;
bool FineTuneLeft = false;
bool Scan = false;

// Define networking parameters
char auth[] = "your Blynk auth code here";           // set the Blynk authentication code
char ssid[] = "your WiFi SSID here";                 // set the WiFi SSID
char pass[] = "your WiFi password here";             // set the Wifi password


// -- Start of Setup ---------------------------------------------------------------------------------------------------------------------

void setup(){

  Serial.begin(115200);                               // baudrate for serial communication
  Blynk.begin(auth, ssid, pass);                      // network information 
  // Declare pins as Outputs
  pinMode(stepPin, OUTPUT);                           // step pin
  pinMode(dirPin, OUTPUT);                            // direction pin
  pinMode(enablePin, OUTPUT);                         // enable pin
  pinMode(LED_BUILTIN, OUTPUT);                       // onboard LED indicator
}

BLYNK_WRITE(V0){                                      // Blynk virtual pin V0
  TuneLeft = param.asInt();                           // turn left
}
  
BLYNK_WRITE(V1){                                      // Blynk virtual pin V1
  TuneRight = param.asInt();                          // turn right
}

BLYNK_WRITE(V2){                                      // Blynk virtual pin V2
  FineTuneLeft = param.asInt();                       // fine tuning Left
}

BLYNK_WRITE(V3){                                      // Blynk virtual pin V3
  FineTuneRight = param.asInt();                      // fine tunning Right
}

BLYNK_WRITE(V4){                                      // Blynk virtual pin V4
  Scan = param.asInt();                               // scan
}

// -- Main Tunning Function ---------------------------------------------------------------------------------

void Tunning (int Steps, int Rotation){               
  digitalWrite(enablePin, LOW);                       // enable the driver
  for (int i = 0; i < Rotation; i++){                 // loop for motor steps 
    digitalWrite(stepPin, HIGH);                      // perform a step
    digitalWrite(LED_BUILTIN, LOW);                   // turn LED indicator OFF
    delayMicroseconds(Steps);                         // wait for the steps operation
    digitalWrite(stepPin, LOW);                       // stop the step 
    digitalWrite(LED_BUILTIN, HIGH);                  // tuen LED indicator ON
    delayMicroseconds(Steps);                         // wait between steps
    Blynk.run();
  }
}

// -- Start of loop -------------------------------------------------------------------------------

void loop() {                                         
  
  Blynk.run();

  digitalWrite(enablePin, HIGH);                       // disable the driver - will save power and heat on the motor driver
  
  if (TuneRight){                                      // turn right
    digitalWrite(dirPin, LOW);                         // set direction to one side
    Tunning(1500, 320);                                // turn in normal speed
  }

  if (FineTuneRight){                                  // fine turn right
    digitalWrite(dirPin, LOW);                         // set direction to one side
    Tunning(3000, 16);                                 // turn slow, aka "Fine Tune"
  }
  
  if (TuneLeft){                                        // turn left
    digitalWrite(dirPin, HIGH);                         // set direction to the other side
    Tunning(1500, 320);                                 // turn in normal speed
  }

  if (FineTuneLeft){                                    // fine turn left 
    digitalWrite(dirPin, HIGH);                         // set direction to the other side
    Tunning(3000, 16);                                  // turn slow, aka "Fine Tune"
  }

  while (Scan) {                                        // scan as long as the App button is enable
    digitalWrite(dirPin, LOW);                          // set scan direction to one side
    Tunning(1000, 16);                                  // scan quickly, aka "Fast Tune"
  }
}

// -- End of loop ---------------------------------------------------------------------------------
