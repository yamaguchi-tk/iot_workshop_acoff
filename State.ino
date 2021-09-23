#include <M5Stack.h>

enum State handleEvent(enum State s, enum Event e) {
  enum State ret = s;
  switch (s) {
    case STATE_INIT:                    // 初期状態
      Serial.println("handleEvent:STATE_INIT");
      if (e == EVENT_PIR_STATE_ON) {    // 人を検知
        Serial.println("handleEvent ret:STATE_EXIST");
        ret = STATE_EXIST;
      } else {
        ret = STATE_SLEEP;
      }
      break;
    case STATE_EXIST:                   // 人を検知した状態
      Serial.println("handleEvent:STATE_EXIST");
      if (e == EVENT_PIR_STATE_OFF) {   // 人がいなくなったら
        Serial.println("handleEvent ret:STATE_GONE");
        startTimer();
        ret = STATE_GONE;
      }
      break;
    case STATE_GONE:                    // 人を不検知となった状態
      Serial.println("handleEvent:STATE_GONE");
      if (e == EVENT_TIME_IS_UP) {      // 人がいなくなってから設定時間経過
        Serial.println("handleEvent:turnOffNECLight");
        turnOffNECLight();
        delay(100);
        Serial.println("handleEvent:turnOffMitsubishiAC");
        turnOffMitsubishiAC;
        Serial.println("handleEvent ret:STATE_SLEEP");
        stopTimer();
        ret = STATE_SLEEP;
      } else if (e == EVENT_PIR_STATE_ON) { // 再度人を検知 タイマーリセットしない
        Serial.println("handleEvent ret:STATE_EXIST_PENDIG");
        ret = STATE_EXIST_PENDIG;
      } else {
        Serial.println("handleEvent:other");
        updateTimer();
      }
      break;
    case STATE_EXIST_PENDIG:
      Serial.println("handleEvent:STATE_EXIST_PENDIG");
      if (e == EVENT_PIR_STATE_ON) { // 再度人を検知 タイマーリセット
        Serial.println("handleEvent ret:STATE_EXIST");
        ret = STATE_EXIST;
        stopTimer();
      } else if (e == EVENT_PIR_STATE_OFF) {   // 人がいなくなったら タイマーリセットしない
        Serial.println("handleEvent ret:STATE_GONE");
        ret = STATE_GONE;
      }
      break;
    case STATE_SLEEP:                   // 人を不検知となって一定時間経過後、照明・ACオフした状態
      Serial.println("handleEvent:STATE_SLEEP");
      if (e == EVENT_PIR_STATE_ON) {    // 人を検知
        Serial.println("handleEvent ret:STATE_EXIST");
        ret = STATE_EXIST;
      }
      break;
  }
  return ret;
}
