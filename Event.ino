#include <M5Stack.h>

boolean TimeIsUp() {
  if (RemainTime <= 0L) {
    return true;
  } else {
    return false;
  }
}

boolean PIRIsSensed() {
  int pir;
  pir = digitalRead(36);
  Serial.print("PIR :");
  Serial.println(pir);
  if (pir == 1) {
    return true;
  } else {
    return false;
  }
}

enum Event receiveEvent() {
  if (PIRIsSensed()) {
    Serial.println("receiveEvent:EVENT_PIR_STATE_ON");
    return EVENT_PIR_STATE_ON;
  } else {
    if (TimeIsUp()) {
      Serial.println("receiveEvent:EVENT_TIME_IS_UP");
      return EVENT_TIME_IS_UP;
    } else {
      Serial.println("receiveEvent:EVENT_PIR_STATE_OFF");
      return EVENT_PIR_STATE_OFF;
    }
  }
}
