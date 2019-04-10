//////
//  OSC Example for ESP32, By Luke Woodbury- 9th Jan 2018
//  Tiri for Taeyoon Choi Whitney Museum
//  OSC from conductive thread via wifi
// copy and paste this on preference https://dl.espressif.com/dl/package_esp32_index.json
// into Additional Board Manager URLs field. You can add multiple URLs, separating them with commas.
//Set-up
//  A2,A3,A4,A7(pin32),A9(pin33),A12(pin13)
//////


//Wifi and OSC stuff
#include <WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>

//WIFI Settings
char ssid[] = "AFOUNDRY-2.4G"; //network SSID (name)

//char ssid[] = "SFPC"; 
//char pass[] = "since2013";    //password

WiFiUDP Udp;                                // A UDP instance to let us send and receive packets over UDP
const IPAddress outIp(192, 168, 2, 210);     // remote IP of your computer
//const IPAddress outIp(192, 168, 0, 7);     // remote IP of your computer
const unsigned int outPort = 8080;          // remote port to receive OSC
const unsigned int localPort = 8000;        // local port to listen for OSC packets (actually not used for sending)


long int now = 0;
int interval = 250; //sending every 0.25sec

int sensorPin = A0; // select the input pin for the potentiometer
int sensorValue = 0 ; // variable to store the value coming from the sensor
int sensorPins[] = {A2, A3, A4, A7, A9, A12}; // don't forget to change this

void setup() {
  //Set Serial Communication
  Serial.begin(115200);
  // Connect to WiFi network
  initWifi();
}

void loop() {
  checkOSCin();
  if (millis() - now > interval) {
    now = millis();
    readConductiveString();
  }
}


void sendOSC(char val[]) {
  OSCMessage msg(val);
  //  msg.add(val);

  Udp.beginPacket(outIp, outPort);
  msg.send(Udp); // Send the bytes to the SLIP stream
  Udp.endPacket();  // Mark the end of the OSC Packet
  msg.empty();   // Free space occupied by message
}


void checkOSCin() {
  OSCMessage msgIn;
  int size;
  if ( (size = Udp.parsePacket()) > 0) {
    //    Serial.println("here");
    while (size--)
      msgIn.fill(Udp.read());

    if (!msgIn.hasError()) {
      msgIn.dispatch("/toArduino", dispatchAddress);
    }
  }
}


void dispatchAddress(OSCMessage &msg) {
  // Even though we are classifying, wekinator sends outputs as floats
  if (msg.isFloat(0)) {
    float val = msg.getFloat(0);
    if (val == 1) {
      Serial.println("Turning LIGH1 on");
    }
    if (val == 3) {
      Serial.println("Turning lights off");
    }
  }
}
