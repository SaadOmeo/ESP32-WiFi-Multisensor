#include <WiFi.h>
#include <EEPROM.h>
#include "DHT.h"
#include <Adafruit_Sensor.h>

const char* ssid = "REPLACE_WITH_YOUR_SSID";
const char* password = "REPLACE_WITH_YOUR_PASSWORD";

#define DHTTYPE DHT22
#define EEPROM_SIZE 4

const int DHTPin = 27;
const int output = 2;
const int redRGB = 14;
const int greenRGB = 12;
const int blueRGB = 13;
const int motionSensor = 25;
const int ldr = 33;

DHT dht(DHTPin, DHTTYPE);
WiFiServer server(80);

static char celsiusTemp[7];
static char fahrenheitTemp[7];
static char humidityTemp[7];

String outputState = "off";
String modes[4] = {"Manual", "Auto PIR", "Auto LDR", "Auto PIR and LDR"};
String valueString = "0";
String header;

long now = 0;
long lastMeasure = 0;
boolean startTimer = false;

int selectedMode = 0;
int timer = 0;
int ldrThreshold = 0;
int armMotion = 0;
int armLdr = 0;
int pos1 = 0;
int pos2 = 0;

void detectsMovement();
void configureMode();
void outputOn();
void outputOff();

void setup() {
  dht.begin();
  Serial.begin(115200);

  pinMode(motionSensor, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(motionSensor), detectsMovement, RISING);

  Serial.println("start...");

  if (!EEPROM.begin(EEPROM_SIZE)) {
    Serial.println("failed to initialise EEPROM");
    delay(1000);
  }

  Serial.println("Bytes read from Flash. Values are:");
  for (int i = 0; i < EEPROM_SIZE; i++) {
    Serial.print(byte(EEPROM.read(i)));
    Serial.print(" ");
  }
  Serial.println();

  pinMode(output, OUTPUT);
  pinMode(redRGB, OUTPUT);
  pinMode(greenRGB, OUTPUT);
  pinMode(blueRGB, OUTPUT);

  if (EEPROM.read(0) == 0) {
    outputState = "off";
    digitalWrite(output, HIGH);
  } else {
    outputState = "on";
    digitalWrite(output, LOW);
  }

  selectedMode = EEPROM.read(1);
  if (selectedMode < 0 || selectedMode > 3) selectedMode = 0;
  timer = EEPROM.read(2);
  ldrThreshold = EEPROM.read(3);
  configureMode();

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("New Client.");
    String currentLine = "";

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        header += c;

        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html; charset=utf-8");
            client.println("Connection: close");
            client.println();

            if (header.indexOf("GET /?mode=") >= 0) {
              pos1 = header.indexOf('=');
              pos2 = header.indexOf('&');
              valueString = header.substring(pos1 + 1, pos2);
              selectedMode = valueString.toInt();
              if (selectedMode < 0 || selectedMode > 3) selectedMode = 0;
              EEPROM.write(1, selectedMode);
              EEPROM.commit();
              configureMode();
            } else if (header.indexOf("GET /?state=on") >= 0) {
              outputOn();
            } else if (header.indexOf("GET /?state=off") >= 0) {
              outputOff();
            } else if (header.indexOf("GET /?timer=") >= 0) {
              pos1 = header.indexOf('=');
              pos2 = header.indexOf('&');
              valueString = header.substring(pos1 + 1, pos2);
              timer = constrain(valueString.toInt(), 0, 255);
              EEPROM.write(2, timer);
              EEPROM.commit();
            } else if (header.indexOf("GET /?ldrthreshold=") >= 0) {
              pos1 = header.indexOf('=');
              pos2 = header.indexOf('&');
              valueString = header.substring(pos1 + 1, pos2);
              ldrThreshold = constrain(valueString.toInt(), 0, 100);
              EEPROM.write(3, ldrThreshold);
              EEPROM.commit();
            }

            client.println("<!DOCTYPE html><html><head>");
            client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style>html{font-family:Helvetica;text-align:center;margin:auto}body{max-width:700px;margin:auto;padding:16px}.button{background:#4CAF50;border:0;color:white;padding:16px 40px;text-decoration:none;font-size:24px;margin:4px;cursor:pointer;border-radius:8px}.button2{background:#555}.panel{padding:12px;margin:12px;border:1px solid #ddd;border-radius:10px}select,input{font-size:16px;padding:8px}</style>");
            client.println("</head><body><h1>ESP32 Wi-Fi Multisensor</h1>");
            client.println("<div class=\"panel\"><p><strong>Selected mode:</strong> " + modes[selectedMode] + "</p>");
            client.println("<select onchange=\"setMode(this.value)\">");
            client.println("<option value=\"0\"" + String(selectedMode == 0 ? " selected" : "") + ">Manual</option>");
            client.println("<option value=\"1\"" + String(selectedMode == 1 ? " selected" : "") + ">Auto PIR</option>");
            client.println("<option value=\"2\"" + String(selectedMode == 2 ? " selected" : "") + ">Auto LDR</option>");
            client.println("<option value=\"3\"" + String(selectedMode == 3 ? " selected" : "") + ">Auto PIR and LDR</option>");
            client.println("</select></div>");

            client.println("<div class=\"panel\"><p><strong>Output state:</strong> " + outputState + "</p>");
            if (selectedMode == 0) {
              if (outputState == "off") {
                client.println("<button class=\"button\" onclick=\"outputOn()\">ON</button>");
              } else {
                client.println("<button class=\"button button2\" onclick=\"outputOff()\">OFF</button>");
              }
            }
            if (selectedMode == 1 || selectedMode == 3) {
              client.println("<p>Timer (seconds, 0-255): <input type=\"number\" value=\"" + String(timer) + "\" onchange=\"setTimer(this.value)\" min=\"0\" max=\"255\"></p>");
            }
            if (selectedMode == 2 || selectedMode == 3) {
              client.println("<p>LDR threshold (0-100%): <input type=\"number\" value=\"" + String(ldrThreshold) + "\" onchange=\"setThreshold(this.value)\" min=\"0\" max=\"100\"></p>");
            }
            client.println("</div>");

            if (header.indexOf("GET /?sensor") >= 0) {
              float h = dht.readHumidity();
              float t = dht.readTemperature();
              float f = dht.readTemperature(true);

              if (isnan(h) || isnan(t) || isnan(f)) {
                strcpy(celsiusTemp, "Failed");
                strcpy(fahrenheitTemp, "Failed");
                strcpy(humidityTemp, "Failed");
              } else {
                float hic = dht.computeHeatIndex(t, h, false);
                dtostrf(hic, 6, 2, celsiusTemp);
                float hif = dht.computeHeatIndex(f, h);
                dtostrf(hif, 6, 2, fahrenheitTemp);
                dtostrf(h, 6, 2, humidityTemp);
              }

              client.println("<div class=\"panel\"><h2>Sensor readings</h2>");
              client.println("<p>Heat index: " + String(celsiusTemp) + " &deg;C</p>");
              client.println("<p>Heat index: " + String(fahrenheitTemp) + " &deg;F</p>");
              client.println("<p>Humidity: " + String(humidityTemp) + "%</p>");
              client.println("<p><a href=\"/\"><button>Hide readings</button></a></p></div>");
            } else {
              client.println("<div class=\"panel\"><a href=\"/?sensor\"><button>View sensor readings</button></a></div>");
            }

            client.println("<script>");
            client.println("function request(path){var x=new XMLHttpRequest();x.open('GET',path,true);x.onload=function(){location.href='/';};x.send();}");
            client.println("function setMode(v){request('/?mode='+v+'&');}");
            client.println("function setTimer(v){request('/?timer='+v+'&');}");
            client.println("function setThreshold(v){request('/?ldrthreshold='+v+'&');}");
            client.println("function outputOn(){request('/?state=on');}");
            client.println("function outputOff(){request('/?state=off');}");
            client.println("</script></body></html>");
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }

    header = "";
    client.stop();
    Serial.println("Client disconnected.");
  }

  now = millis();

  if (startTimer && armMotion && !armLdr) {
    if (outputState == "off") {
      outputOn();
    } else if (now - lastMeasure > (timer * 1000L)) {
      outputOff();
      startTimer = false;
    }
  }

  if (armLdr && !armMotion) {
    int ldrValue = map(analogRead(ldr), 0, 4095, 0, 100);
    if (ldrValue > ldrThreshold && outputState == "on") {
      outputOff();
    } else if (ldrValue < ldrThreshold && outputState == "off") {
      outputOn();
    }
    delay(100);
  }

  if (startTimer && armMotion && armLdr) {
    int ldrValue = map(analogRead(ldr), 0, 4095, 0, 100);
    if (ldrValue > ldrThreshold) {
      outputOff();
      startTimer = false;
    } else if (ldrValue < ldrThreshold && outputState == "off") {
      outputOn();
    } else if (now - lastMeasure > (timer * 1000L)) {
      outputOff();
      startTimer = false;
    }
  }
}

void detectsMovement() {
  if (armMotion) {
    startTimer = true;
    lastMeasure = millis();
  }
}

void configureMode() {
  if (selectedMode == 0) {
    armMotion = 0;
    armLdr = 0;
    digitalWrite(redRGB, LOW);
    digitalWrite(greenRGB, HIGH);
    digitalWrite(blueRGB, HIGH);
  } else if (selectedMode == 1) {
    outputOff();
    armMotion = 1;
    armLdr = 0;
    digitalWrite(redRGB, HIGH);
    digitalWrite(greenRGB, LOW);
    digitalWrite(blueRGB, HIGH);
  } else if (selectedMode == 2) {
    armMotion = 0;
    armLdr = 1;
    digitalWrite(redRGB, HIGH);
    digitalWrite(greenRGB, HIGH);
    digitalWrite(blueRGB, LOW);
  } else if (selectedMode == 3) {
    outputOff();
    armMotion = 1;
    armLdr = 1;
    digitalWrite(redRGB, LOW);
    digitalWrite(greenRGB, HIGH);
    digitalWrite(blueRGB, LOW);
  }
}

void outputOn() {
  outputState = "on";
  digitalWrite(output, LOW);
  EEPROM.write(0, 1);
  EEPROM.commit();
}

void outputOff() {
  outputState = "off";
  digitalWrite(output, HIGH);
  EEPROM.write(0, 0);
  EEPROM.commit();
}
