#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <M5Stack.h>
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <ir_Mitsubishi.h>

const uint16_t kIrLed = 21;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).
IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.

uint16_t rawData_MitsubishiAC1[375] = {3432, 1690,  452, 1250,  480, 1220,  452, 396,  450, 398,  450, 394,  452, 1246,  450, 396,  452, 398,  452, 1248,  452, 1246,  452, 398,  448, 1248,  452, 394,  452, 392,  452, 1246,  454, 1250,  454, 394,  452, 1246,  452, 1250,  452, 394,  450, 396,  452, 1254,  478, 368,  452, 396,  452, 1248,  450, 396,  450, 394,  452, 394,  452, 394,  452, 394,  450, 396,  450, 396,  452, 394,  448, 398,  450, 396,  450, 396,  450, 396,  450, 394,  452, 396,  450, 396,  450, 13124,  3418, 1714,  452, 1246,  452, 1246,  450, 396,  450, 392,  450, 392,  450, 1248,  450, 392,  450, 396,  450, 1246,  450, 1248,  452, 402,  448, 1248,  452, 394,  448, 394,  450, 1246,  452, 1250,  452, 394,  450, 1248,  450, 1248,  450, 394,  448, 396,  448, 1248,  448, 396,  448, 398,  448, 1248,  452, 394,  448, 392,  450, 394,  450, 394,  450, 392,  450, 394,  448, 400,  448, 394,  448, 398,  446, 396,  450, 394,  446, 396,  450, 392,  448, 396,  448, 396,  448, 394,  450, 394,  448, 396,  446, 396,  448, 394,  448, 396,  446, 396,  448, 398,  448, 1248,  450, 394,  448, 396,  446, 1250,  450, 1246,  450, 396,  450, 1248,  448, 398,  448, 396,  446, 1250,  450, 396,  446, 1248,  450, 398,  446, 394,  450, 398,  448, 398,  448, 398,  446, 1250,  450, 1248,  448, 398,  446, 396,  448, 394,  446, 396,  448, 400,  446, 398,  446, 398,  446, 396,  448, 398,  446, 396,  448, 398,  446, 396,  444, 400,  448, 1248,  450, 1258,  446, 398,  444, 1254,  446, 398,  444, 398,  446, 1254,  448, 400,  444, 398,  446, 398,  444, 400,  444, 398,  444, 398,  444, 400,  442, 402,  444, 402,  444, 398,  444, 400,  444, 400,  444, 400,  442, 400,  446, 398,  442, 400,  444, 404,  444, 400,  440, 400,  446, 406,  444, 400,  442, 400,  442, 402,  444, 400,  444, 402,  442, 402,  444, 398,  444, 398,  416, 428,  442, 1254,  444, 400,  416, 426,  442, 404,  440, 1256,  444, 1256,  416, 428,  412, 432,  414, 428,  416, 428,  416, 430,  438, 408,  414, 430,  414, 426,  444, 400,  440, 402,  440, 404,  414, 428,  416, 428,  414, 432,  442, 400,  442, 402,  414, 1282,  416, 1282,  416, 1282,  416, 428,  414, 1284,  416, 1284,  416};

void setupIRSend() {
  // IRSend
  irsend.begin();
}

void displayStatus() {
  M5.Lcd.setCursor(0, 25);
  M5.Lcd.print("Status: ");
  M5.Lcd.setCursor(0, 45); M5.Lcd.print("Value: ");

  M5.Lcd.fillRect(95, 25, 200, 25, BLACK);
  M5.Lcd.fillRect(95, 45, 200, 25, BLACK);

  if (PIRIsSensed()) {
    M5.Lcd.setCursor(95, 25); M5.Lcd.print("Sensing");
    M5.Lcd.setCursor(95, 45); M5.Lcd.print("1");
    Serial.println("PIR Status: Sensing");
    Serial.println(" value: 1");
  }
  else {
    M5.Lcd.setCursor(95, 25); M5.Lcd.print("Not Sensed");
    M5.Lcd.setCursor(95, 45); M5.Lcd.print("0");
    Serial.println("PIR Status: Not Sensed");
    Serial.println(" value: 0");
  }

  M5.Lcd.setCursor(220, 25); M5.Lcd.print("rTime");
  M5.Lcd.setCursor(220, 45); M5.Lcd.printf("%d", RemainTime);
  Serial.print("RemainTime: ");
  Serial.println(RemainTime);

  M5.update();

}

void startTimer() {
  RemainTime = SettingTime;
  StartTime = millis();
}

void stopTimer() {
  RemainTime = SettingTime;
}

void updateTimer() {
  RemainTime = SettingTime + StartTime - millis();
}

// NEC照明をOFFにする
void turnOffNECLight() {
  // 常夜灯
  irsend.sendNEC(0x41B63DC2);
  delay(100);
  // ONOFFボタン
  irsend.sendNEC(0x41B6D52A);
}

// 三菱エアコンをOFFにする
void turnOffMitsubishiAC() {
  irsend.sendRaw(rawData_MitsubishiAC1, 375, 38);  // Send a raw data capture at 38kHz.
}
