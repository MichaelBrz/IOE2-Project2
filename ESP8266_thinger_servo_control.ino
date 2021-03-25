#include <ThingerESP8266.h>
#include <ESP8266WiFi.h>
#include <Servo.h>

#define USERNAME "thingerName"
#define DEVICE_ID "esp8266"
#define DEVICE_CREDENTIAL "thingerCredentials"

#define SSID "yourNetwork"
#define SSID_PASSWORD "yourPassword"

ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

//// digital pin, pin that goes to your LED
#define LED1 13
#define LED2 12
//// digital pin, pin that goes to your servo
#define SERVO_PIN 16

///// create a Servo object and give it a name
Servo servo1;

void setup() {
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(SERVO_PIN, OUTPUT);

  ////// turning on the servo
  servo1.attach(SERVO_PIN);
  ///// setting the servo to start at speed 90, 90 = stop
  ///// servos have a range of speed in one direction from  90 - 0
  ///// and 90 - 180 in the other direction with 90 at the center
  servo1.write(90);


  thing.add_wifi(SSID, SSID_PASSWORD);

  ///// pin control example (i.e. turning on/off a light, a relay, etc)
  thing["led1"] << digitalPin(LED1);
  thing["led2"] << digitalPin(LED2);
  //thing["servo"]<< servo(servo1.write((int)in));

  //////SERVO CONTROL/////////////////////////////////////////////

  ///// stop speed
  thing["stop"] << [] (pson & in) {

    if (!in.is_empty()) {

      servo1.write(90);
    }
    in = false;
  };


  ////END OF SETUP
}

//// Thinger handles everything in the loop

void loop() {
  thing.handle();

}
