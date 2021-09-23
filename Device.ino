#include <M5Stack.h>


void setupDevice() {

  M5.begin();
  M5.Power.begin();

  Serial.begin(115200);
  M5.Lcd.clear(BLACK);
  M5.Lcd.setTextColor(YELLOW);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.println("Turn Off AC & LED CH1");
  Serial.println("Turn Off AC & LED CH1");
  M5.Lcd.setCursor(65, 10);
  M5.Lcd.setTextColor(WHITE);

  // PIR
  pinMode(36, INPUT);

#if ESP8266
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
#else  // ESP8266
  Serial.begin(115200, SERIAL_8N1);
#endif  // ESP8266

}
