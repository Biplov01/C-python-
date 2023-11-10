#include <WiFi.h>
#include <ThingSpeak.h>

const char* ssid = "RAMESH_NTFiber";   // your network SSID 
const char* password = "9849981596";   // your network password

unsigned long myChannelNumber = 1864319;
const char* myWriteAPIKey = "2BDPDA602WO41Z7B";

const int triggerPin = 2;   // Trigger pin of the ultrasonic sensor
const int echoPin = 3;      // Echo pin of the ultrasonic sensor
const int ledPin = 4;       // Digital pin connected to LED
const int buzzerPin = 5;    // Digital pin connected to buzzer

WiFiClient client;

void setup() {
  Serial.begin(9600);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  wifiConnect();
}

void loop() {
  long duration;
  int waterLevel;

  // Trigger ultrasonic sensor
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  // Measure echo pulse duration
  duration = pulseIn(echoPin, HIGH);

  // Convert duration to distance (water level)
  waterLevel = duration / 29 / 2;

  Serial.print("Water Level: ");
  Serial.print(waterLevel);
  Serial.println(" cm");

  // Check if water level exceeds threshold
  if (waterLevel > 10) {
    digitalWrite(ledPin, HIGH);      // Turn on the LED
    digitalWrite(buzzerPin, HIGH);   // Activate the buzzer
    Serial.println("Flood Detected!");
  } else {
    digitalWrite(ledPin, LOW);       // Turn off the LED
    digitalWrite(buzzerPin, LOW);    // Deactivate the buzzer
  }

  ThingSpeak.setField(1, waterLevel);  // Send water level to Field 1
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

  delay(2000);  // Delay between readings
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
