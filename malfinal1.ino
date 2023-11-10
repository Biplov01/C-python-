#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#include <SoftwareSerial.h>
SoftwareSerial espSerial(2, 3); // RX, TX
const int PulseWire = A0;
const int LED = 4;
int Threshold = 550;

const char* ssid = "Islington-College";   // your network SSID
const char* password = "I$LiNGT0N@123";   // your network password

unsigned long myChannelNumber = 2112706;
const char* myWriteAPIKey = "R8AUP1KHA41L5K0J";

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 30000;


// Create a sensor object
WiFiClient client;

PulseSensorPlayground pulseSensor;

void setup() {
	Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  wifiConnect();
  pinMode(LED, OUTPUT); // Set LED pin as OUTPUT

  pulseSensor.analogInput(PulseWire);
  pulseSensor.setThreshold(Threshold);

  if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object!");
    delay(1000);
    Serial.println("connecting to wifi...................................................................");
    delay(500);
    Serial.println("connecting to api.thingspeak");
  }
}

void loop() {
  if (pulseSensor.sawStartOfBeat()) {
    int myBPM = pulseSensor.getBeatsPerMinute();
    Serial.println("♥ A HeartBeat Happened!");
    Serial.print("BPM: ");
    Serial.println(myBPM);
    digitalWrite(LED, HIGH); // Turn on the LED when a heartbeat is detected
  } else {
    digitalWrite(LED, LOW); // Turn off the LED when there is no heartbeat
  }
 ThingSpeak.setField(1, myBPM);
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  
  delay(2000);
}

// Function to connect WiFi
void wifiConnect() {
  Serial.println("Connecting to WiFi!");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println("WiFi connected.");
}

