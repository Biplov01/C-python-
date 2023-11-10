#include <WiFi.h>

WiFiServer server(80);

const char* ssid = "RAMESH_NTFiber";
const char* password = "9849981596";

int leftMotorForward = 14;     // GPIO4(D4) -> IN3
int rightMotorForward = 32;   // GPIO15(D8) -> IN1
int leftMotorBackward = 33;    // GPIO2(D3) -> IN4
int rightMotorBackward = 13;  // GPIO13(D7) -> IN2

void setup()
{
  Serial.begin(115200);
  
  pinMode(leftMotorForward, OUTPUT);
  pinMode(rightMotorForward, OUTPUT);
  pinMode(leftMotorBackward, OUTPUT);
  pinMode(rightMotorBackward, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();

  Serial.println("Server started");
}

void loop()
{
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  while (!client.available()) {
    delay(1);
  }

  String request = client.readStringUntil('\r');
  client.flush();

  Serial.print("Client connected - Request: ");
  Serial.println(request);

  if (request.indexOf("forward") != -1) {
    MotorForward();
  } else if (request.indexOf("backward") != -1) {
    MotorBackward();
  } else if (request.indexOf("left") != -1) {
    TurnLeft();
  } else if (request.indexOf("right") != -1) {
    TurnRight();
  } else if (request.indexOf("stop") != -1) {
    MotorStop();
  }

  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/plain");
  client.println();
  client.println("Command received.");
  delay(10);
  client.stop();
}

void MotorForward()
{
  digitalWrite(leftMotorForward, HIGH);
  digitalWrite(rightMotorForward, HIGH);
  digitalWrite(leftMotorBackward, LOW);
  digitalWrite(rightMotorBackward, LOW);
}

void MotorBackward()
{
  digitalWrite(leftMotorBackward, HIGH);
  digitalWrite(rightMotorBackward, HIGH);
  digitalWrite(leftMotorForward, LOW);
  digitalWrite(rightMotorForward, LOW);
}

void TurnLeft()
{
  digitalWrite(leftMotorForward, LOW);
  digitalWrite(rightMotorForward, HIGH);
  digitalWrite(rightMotorBackward, LOW);
  digitalWrite(leftMotorBackward, HIGH);
}

void TurnRight()
{
  digitalWrite(leftMotorForward, HIGH);
  digitalWrite(rightMotorForward, LOW);
  digitalWrite(rightMotorBackward, HIGH);
  digitalWrite(leftMotorBackward, LOW);
}

void MotorStop()
{
  digitalWrite(leftMotorForward, LOW);
  digitalWrite(leftMotorBackward, LOW);
  digitalWrite(rightMotorForward, LOW);
  digitalWrite(rightMotorBackward, LOW);
}
