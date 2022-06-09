#include <WiFi.h>
#include "index.h"
#include <DNSServer.h>
#include <AsyncTCP.h>
#include "ESPAsyncWebServer.h"
#include "max6675.h" //https://github.com/adafruit/MAX6675-library
IPAddress apIP(192, 168, 1, 1);
#define LIGHT 0x0
#define MEDIUM 0x1
#define DARK 0x2
int thermoDO = 19; // SO of  MAX6675 module to D19
int thermoCS = 23; // CS of MAX6675 module to D5
int thermoCLK = 18; // SCK of MAX6675 module to D18
//int led;
int heater = 2; // assign relay pin here

int sendminutes = 0;
MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
DNSServer dnsServer;
AsyncWebServer server(80);
const byte DNS_PORT = 53;
int lightmin  = 180;
int lightmax  = 205;
int medmin    = 210;
int medmax    = 220;
int darkmin   = 225;//225;
int darkmax   = 230;//230;
const char* PARAM_INPUT_0 = "light";
const char* PARAM_INPUT_1 = "med";
const char* PARAM_INPUT_2 = "dark";
const char* PARAM_INPUT_STOP = "stop";
String inputMessage0;
String inputMessage1;
String inputMessage2;
String inputMessageStop;
int timelight = 1;
int timemedium = 13;
int timedark = 16;

float therm;
String statuses = "Idle";
uint8_t md = 0;
TaskHandle_t Task0, Task1;
void Idle() {
  delay(1000);
}
void bootcore() {
  xTaskCreatePinnedToCore(
    loopCore1,
    "core1",
    8192,
    NULL,
    1,
    &Task1,
    1);
  delay(500);
  xTaskCreatePinnedToCore(
    loopCore0,
    "core0",
    8192,
    NULL,
    1,
    &Task0,
    0);
  delay(500);
}
String processor(const String& var){
  Serial.println(var);
  if (var == "TEMPERATURE") {
    return readtemp();
  }
  else if (var == "et") {
    return timerValue();
  }
  else if (var == "statuses") {
    return statuses;
  }
  return String();
}
String readtemp() {
  float t = thermocouple.readCelsius();
  therm = t;
  return String(t);
}
String timerValue() {
  int et = sendminutes;
  return String(et);
}
String statusNow() {
  return statuses;
}
void setup() {
  stoproast();
  bootcore();
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(heater, OUTPUT);
//  pinMode(led, OUTPUT);
  WiFi.softAP("Automatic Coffee Roaster");
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  dnsServer.start(DNS_PORT, "*", apIP);
  //dnsServer.start(53, "*", WiFi.softAPIP());
 Serial.println(WiFi.softAPIP());
 // server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);//only when requested from AP
  //more handlers...
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", html, processor);
    request->send(response);
  });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", readtemp().c_str());
  });
  server.on("/et", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", timerValue().c_str());
  });
  server.on("/statuses", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", statusNow().c_str());
  });
  server.on("/update", HTTP_GET, [] (AsyncWebServerRequest * request) {
    String inputParam;
    // GET input1 value on <ESP_IP>/update?state=<inputMessage>
    if (request->hasParam(PARAM_INPUT_0)) {
      inputMessage0 = request->getParam(PARAM_INPUT_0)->value();
      inputParam = PARAM_INPUT_0;
      Serial.print("light = ");
      Serial.println(inputMessage0);
      if (inputMessage0.toInt() == 1) {
        md = 1;
      }
    }
    if (request->hasParam(PARAM_INPUT_1)) {
      inputMessage1 = request->getParam(PARAM_INPUT_1)->value();
      inputParam = PARAM_INPUT_1;
      Serial.print("med = ");
      Serial.println(inputMessage1);
      if (inputMessage1.toInt() == 1) {
        md = 2;
      }
    }
    if (request->hasParam(PARAM_INPUT_2)) {
      inputMessage2 = request->getParam(PARAM_INPUT_2)->value();
      inputParam = PARAM_INPUT_2;
      Serial.print("dark = ");
      Serial.println(inputMessage2);
      if (inputMessage2.toInt() == 1) {
        md = 3;
      }
    }
    if (request->hasParam(PARAM_INPUT_STOP)) {
      inputMessageStop = request->getParam(PARAM_INPUT_STOP)->value();
      inputParam = PARAM_INPUT_STOP;
      Serial.print("Stop = ");
      Serial.println(inputMessageStop);
      if (inputMessageStop.toInt() == 1) {
        stoproast();
        md = 0;
      }
    }
    else {
      inputMessage0 = "No message sent";
      inputMessage1 = "No message sent";
      inputMessage2 = "No message sent";
      inputMessageStop = "No message sent";
      inputParam = "none";
    }
    Serial.println("OK");
    request->send(200, "text/plain", "OK");
  });
  server.begin();
}
void loop() {
  Idle();
  // if(inputMessage0.toInt()==1){roast(LIGHT);}
  // if(inputMessage1.toInt()==1){roast(MEDIUM);}
  // if(inputMessage2.toInt()==1){roast(DARK);}
  // if(inputMessageStop.toInt()==1){stoproast();}
  // put your main code here, to run repeatedly:
  //    if (Serial.read() == 'l'||inputMessage0.toInt()==1){
  //      Serial.println("started light via serial");
  //      roast(LIGHT);
  //   }
  //   if (Serial.read() == 'm'||inputMessage1.toInt()==1){
  //     Serial.println("started light via serial");
  //     roast(MEDIUM);
  //   }
  //    if (Serial.read() == 'd'||inputMessage2.toInt()==1){
  //     Serial.println("started light via serial");
  //     roast(DARK);
  //   }
}
void loopCore0( void * parameter ) {
  for (;;) {
    // put your main code here, to run repeatedly:
    //readtemp();
    Idle();
     
     // dnsServer.processNextRequest();
    //  if(md==0){stoproast();}
    //ticker.attach(0.1, tick);
    // APESP32Portal();

  }
}
void loopCore1( void * parameter ) {
  for (;;) {
     //dnsServer.processNextRequest();
    // put your main code here, to run repeatedly:
    //  if(inputMessage0.toInt()==1){md=LIGHT;}
    if (md == 1) {
      roast(LIGHT);
    }
    else if (md == 2) {
      roast(MEDIUM);
    }
    else if (md == 3) {
      roast(DARK);
    }

    //  if(inputMessage0.toInt()==1){roast(LIGHT);}
    // if(inputMessage1.toInt()==1){roast(MEDIUM);}
    //  if(inputMessage2.toInt()==1){roast(DARK);}



  }
}
void roast(uint8_t a) {
  int minutes;
  int sec = 0;
  unsigned long oneSecond = 1000UL;
  unsigned long startTime;
  if (a == LIGHT) {
    minutes = timelight;
  }
  if (a == MEDIUM) {
    minutes = timemedium;
  }
  if (a == DARK) {
    minutes = timedark;
  }
  sec = sec + 60 * minutes;
  startTime = millis();
  while (1) {
    if (millis() - startTime >= oneSecond) {
      sec--;
      startTime += oneSecond;
      if (a == LIGHT) {
        startlightroast();
      }
      if (a == MEDIUM) {
        startmediumroast();
      }
      if (a == DARK) {
        startdarkroast();
      }
      int displayMin = sec / 60;
      if (displayMin < 10) Serial.print("0");
      Serial.print(displayMin);
      sendminutes = displayMin;
      Serial.print(":");
      int displaySec = sec % 60;
      if (displaySec < 10) Serial.print("0");
      Serial.println(sec % 60);
      if (Serial.read() == 'c') {
        stoproast();
        Serial.println("The roasting timer has ended forcefully via serial");
        break;
      }
      if (sec < 0) {
        stoproast();
        Serial.println("The roasting has ended");
        break;
      }
      if (inputMessageStop.toInt() == 1) {
        stoproast();
        break;
      }
      if (md == 0) {
        stoproast();
        break;
      }
    }
  }
}
void relay(int stat) {
  if (stat == 1) {
    digitalWrite(heater, HIGH);
  }
  else if (stat == 0) {
    digitalWrite(heater, LOW);
  }
}
void startlightroast() {
  statuses = "Light Roast, heating";
  if (therm < lightmin) {
    relay(1);
  }
  if (therm > lightmin) {
    statuses = "Light Roast, Roasting";
  }
  if (therm > lightmax) {
    relay(0);
  }
}
void startmediumroast() {
  statuses = "Medium Roast, heating";
  if (therm < medmin) {
    relay(1);
  }
  if (therm > medmin) {
    statuses = "Medium Roast, Roasting";
  }
  if (therm > medmax) {
    relay(0);
  }
}
void startdarkroast() {
  statuses = "Dark Roast, heating";
  if (therm <= darkmin) {
    relay(1);
  }
  if (therm >= darkmin) {
    statuses = "Dark Roast, Roasting";
  }
  if (therm >= darkmax) {
    relay(0);
  }
}
void stoproast() {
  relay(0);
  sendminutes = 0;
  statuses = "Stopped";
  delay(1000);
  statuses = "Idle";
  md = 0;
}
