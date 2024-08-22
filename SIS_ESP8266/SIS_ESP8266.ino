#define BLYNK_TEMPLATE_ID "TMPL3UJs3P6vH"         // Add your Blynk template ID here
#define BLYNK_TEMPLATE_NAME "SIS"     // Add your Blynk template name here

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "SivBY5HsPLpApQqVUmOJfHAAlXArFX1i"; // Blynk auth token
char ssid[] = "JOHN   AIR  FIBER -2.4G";           // Your WiFi SSID
char pass[] = "god$143Gvm";                       // Your WiFi password

int relayPin = 8;       // Pin connected to the relay module
int buzzerPin = 9;      // Pin connected to the buzzer module
int sensor_pin = A0;    // Pin connected to the soil moisture sensor (analog pin A0)
int output_value;       // Variable to store the sensor reading

BlynkTimer timer;

void setup() {
  Serial.begin(9600);   // Initialize serial communication

  pinMode(relayPin, OUTPUT);   // Set relay pin as an output
  pinMode(buzzerPin, OUTPUT);  // Set buzzer pin as an output
  pinMode(sensor_pin, INPUT);  // Set sensor pin as an input
  
  Blynk.begin(auth, ssid, pass); // Initialize Blynk

  timer.setInterval(1000L, sensorCheck); // Check sensor every 1 second
}

void loop() {
  Blynk.run();
  timer.run();
}

void sensorCheck() {
  output_value = analogRead(sensor_pin);
  output_value = map(output_value, 550, 10, 0, 100);
  
  Serial.print("Moisture: ");
  Serial.print(output_value);
  Serial.println("%");
  
  if (output_value < 20 || Blynk.connected()) { // Turn on pump if moisture is low or Blynk is connected
    digitalWrite(relayPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
  } else {
    digitalWrite(relayPin, LOW);
    digitalWrite(buzzerPin, LOW);
  }
}

BLYNK_WRITE(V1) { // Virtual pin 1 is for manual control from Blynk app
  int pumpState = param.asInt();
  digitalWrite(relayPin, pumpState); // Control pump based on Blynk app switch state
}
