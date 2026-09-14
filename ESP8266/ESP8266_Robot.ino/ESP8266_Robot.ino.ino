// ======================================================
// AI DIGITAL TWIN - OMNIDIRECTIONAL ROBOT
// Board: ESP8266 NodeMCU
// ======================================================

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

// -------------------- WiFi --------------------
const char* WIFI_SSID = "YOUR_WIFI_NAME";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

// -------------------- API ----------------------
const char* API_KEY = "YOUR_API_KEY";

const char* API_URL =
  "https://api.prayalabs.com/api/generate.php?api_key=";

// ---------------- Motor pins -------------------
// Motor A
#define A_IN1 D5
#define A_IN2 D6

// Motor B
#define B_IN1 D3
#define B_IN2 D4

// Motor C
#define C_IN1 D0
#define C_IN2 D1

#define MOTOR_SPEED 150

StaticJsonDocument<1024> iotDataDoc;


// ======================================================
// MOTOR CONTROL FUNCTIONS
// ======================================================

void motorStop(int in1, int in2) {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}

void motorForward(int in1, int in2) {
  analogWrite(in1, MOTOR_SPEED);
  digitalWrite(in2, LOW);
}

void motorBackward(int in1, int in2) {
  digitalWrite(in1, LOW);
  analogWrite(in2, MOTOR_SPEED);
}


// ======================================================
// STOP ALL MOTORS
// ======================================================

void stopAllMotors() {

  motorStop(A_IN1, A_IN2);
  motorStop(B_IN1, B_IN2);
  motorStop(C_IN1, C_IN2);
}


// ======================================================
// NORTH
// A = STOP
// B = BACKWARD
// C = FORWARD
// ======================================================

void moveNorth() {

  motorStop(A_IN1, A_IN2);

  motorBackward(B_IN1, B_IN2);

  motorForward(C_IN1, C_IN2);
}


// ======================================================
// SOUTH
// A = STOP
// B = FORWARD
// C = BACKWARD
// ======================================================

void moveSouth() {

  motorStop(A_IN1, A_IN2);

  motorForward(B_IN1, B_IN2);

  motorBackward(C_IN1, C_IN2);
}


// ======================================================
// NORTHWEST
// A = BACKWARD
// B = BACKWARD
// C = FORWARD
// ======================================================

void moveNorthWest() {

  motorBackward(A_IN1, A_IN2);

  motorBackward(B_IN1, B_IN2);

  motorForward(C_IN1, C_IN2);
}


// ======================================================
// SOUTHEAST
// A = FORWARD
// B = FORWARD
// C = BACKWARD
// ======================================================

void moveSouthEast() {

  motorForward(A_IN1, A_IN2);

  motorForward(B_IN1, B_IN2);

  motorBackward(C_IN1, C_IN2);
}


// ======================================================
// CLOCKWISE
// ALL FORWARD
// ======================================================

void rotateCW() {

  motorForward(A_IN1, A_IN2);

  motorForward(B_IN1, B_IN2);

  motorForward(C_IN1, C_IN2);
}


// ======================================================
// COUNTER-CLOCKWISE
// ALL BACKWARD
// ======================================================

void rotateCCW() {

  motorBackward(A_IN1, A_IN2);

  motorBackward(B_IN1, B_IN2);

  motorBackward(C_IN1, C_IN2);
}


// ======================================================
// READ BOOLEAN FROM API JSON
// ======================================================

bool readBool(const char* field) {

  if (!iotDataDoc.containsKey(field)) {
    return false;
  }

  JsonVariant value = iotDataDoc[field];

  if (value.is<bool>()) {
    return value.as<bool>();
  }

  String text = value.as<String>();
  text.trim();
  text.toLowerCase();

  return (
    text == "true" ||
    text == "1" ||
    text == "high" ||
    text == "on"
  );
}


// ======================================================
// SET ROBOT MOVEMENT
// ======================================================

void processDirection() {

  if (readBool("north")) {

    Serial.println("DIRECTION: NORTH");
    moveNorth();

  }
  else if (readBool("south")) {

    Serial.println("DIRECTION: SOUTH");
    moveSouth();

  }
  else if (readBool("northwest")) {

    Serial.println("DIRECTION: NORTHWEST");
    moveNorthWest();

  }
  else if (readBool("southeast")) {

    Serial.println("DIRECTION: SOUTHEAST");
    moveSouthEast();

  }
  else if (readBool("cw")) {

    Serial.println("DIRECTION: CLOCKWISE");
    rotateCW();

  }
  else if (readBool("ccw")) {

    Serial.println("DIRECTION: COUNTER-CLOCKWISE");
    rotateCCW();

  }
  else {

    Serial.println("DIRECTION: STOP");
    stopAllMotors();
  }
}


// ======================================================
// SETUP
// ======================================================

void setup() {

  Serial.begin(115200);

  pinMode(A_IN1, OUTPUT);
  pinMode(A_IN2, OUTPUT);

  pinMode(B_IN1, OUTPUT);
  pinMode(B_IN2, OUTPUT);

  pinMode(C_IN1, OUTPUT);
  pinMode(C_IN2, OUTPUT);

  stopAllMotors();

  Serial.println();
  Serial.println("=================================");
  Serial.println("AI DIGITAL TWIN ROBOT");
  Serial.println("ESP8266 Starting...");
  Serial.println("=================================");

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected!");

  Serial.print("ESP8266 IP: ");
  Serial.println(WiFi.localIP());
}


// ======================================================
// MAIN LOOP
// ======================================================

void loop() {

  if (WiFi.status() != WL_CONNECTED) {

    stopAllMotors();

    Serial.println("WiFi disconnected!");

    delay(1000);
    return;
  }


  WiFiClientSecure client;

  // For testing only.
  // For a final production project, certificate verification
  // should be configured instead.
  client.setInsecure();

  HTTPClient http;

  String endpoint = String(API_URL) + API_KEY;

  if (http.begin(client, endpoint)) {

    int httpCode = http.GET();

    if (httpCode > 0) {

      String payload = http.getString();

      Serial.print("HTTP Code: ");
      Serial.println(httpCode);

      Serial.print("API Response: ");
      Serial.println(payload);


      DeserializationError error =
        deserializeJson(iotDataDoc, payload);


      if (!error) {

        processDirection();

      }
      else {

        Serial.print("JSON Error: ");
        Serial.println(error.c_str());

        stopAllMotors();
      }

    }
    else {

      Serial.print("HTTP Error: ");
      Serial.println(http.errorToString(httpCode));

      stopAllMotors();
    }

    http.end();

  }
  else {

    Serial.println("Unable to connect to API.");

    stopAllMotors();
  }


  // Prevent extremely rapid API requests
  delay(200);
}