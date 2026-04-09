#include <WiFi.h>
#include <HTTPClient.h>

// -------- WiFi Info --------
const char* ssid = "TP-Link_4BA8";         
const char* password = "15644237"; 

// -------- Telegram Info --------
String botToken = "8584566638:AAFttc_O9Bw2nmGxVGSVvx3YJD7EFz9Sxos"; 
String chatID = "1967710649";  

// -------- HC-SR04 Pins --------
#define TRIG_PIN 26
#define ECHO_PIN 25
float distanceThreshold = 5.0; // cm

// -------- MQ-135 Pin --------
#define MQ135_PIN 34
int mq135Threshold = 450; // raw ADC threshold

void setup() {
  Serial.begin(115200);
  Serial.println("ESP32 Bin + Gas Monitor Starting...");

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(MQ135_PIN, INPUT);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected!");
}

void loop() {
  // ======== HC-SR04 Distance ========
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  float distanceCm = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distanceCm);
  Serial.println(" cm");

  // If bin is filled
  if (distanceCm < distanceThreshold) {
    sendTelegramMessage("Bin Filled");
    delay(5000); // avoid spamming
  }

  // ======== MQ-135 Gas ========
  int gasValue = analogRead(MQ135_PIN);
  Serial.print("MQ-135 ADC: ");
  Serial.println(gasValue);

  if (gasValue > mq135Threshold) {
    sendTelegramMessage("Bad Smell");
    delay(5000); // avoid spamming
  }

  delay(500); // stability delay
}

// ======== Function to Send Telegram Message ========
void sendTelegramMessage(String text) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = "https://api.telegram.org/bot" + botToken +
                 "/sendMessage?chat_id=" + chatID + "&text=" + text;
    http.begin(url);
    int httpCode = http.GET();
    if (httpCode > 0) Serial.println("Message sent to Telegram: " + text);
    else Serial.println("Error sending message");
    http.end();
  } else {
    Serial.println("WiFi disconnected!");
  }
}
