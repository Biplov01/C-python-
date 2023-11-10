#include <WiFi.h>
#include <ThingSpeak.h>

const char* ssid = "RAMESH_NTFiber";   // your network SSID
const char* password = "9849981596";   // your network password

unsigned long myChannelNumber = 2194149;
const char* myWriteAPIKey = "GS86XDG4Z7L7VV9B";

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 30000;

// Variable to store the random value
int distance;

// Create a WiFi client object
WiFiClient client;

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  wifiConnect();
}

void loop() {
  // Generate a random value between 20 and 50
  distance = random(0, 40);

  Serial.print("Random Value: ");
  Serial.println(distance);

  // Send the random value to ThingSpeak
  ThingSpeak.setField(1, distance);
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

  delay(5000);
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
