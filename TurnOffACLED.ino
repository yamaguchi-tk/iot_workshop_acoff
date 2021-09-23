#include <M5Stack.h>
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include "config.h"

long SettingTime;   //長整数型 設定時間
long StartTime;     //長整数型 カウントダウン開始時間
long RemainTime;    //長整数型 残り時間


void setup() {
  setupDevice();
  setupIRSend();
  
  SettingTime = 120000L; // 120s
  StartTime = 0L;
  RemainTime = SettingTime;

  state = STATE_INIT;
  event = EVENT_NONE;
}

void loop() {
  displayStatus();
  event = receiveEvent();
  Serial.print("before:");
  Serial.println(state);
  state = handleEvent(state, event);
  Serial.print("after:");
  Serial.println(state);
  delay(1000);
}
