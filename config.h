#ifndef TURN_OFF_AC_LED_CONFIG_H_
#define TURN_OFF_AC_LED_CONFIG_H_

enum State {
  STATE_INIT,       //初期状態
  STATE_EXIST,      //人が存在
  STATE_GONE,       //人がいなくなった
  STATE_EXIST_PENDIG, //人が存在する疑い
  STATE_SLEEP       //人が来るまでスリープ
} state;

enum Event {
  EVENT_NONE,           //初期値
  EVENT_PIR_STATE_ON,   //PIRセンサー検知
  EVENT_PIR_STATE_OFF,  //PIRセンサー不検知
  EVENT_TIME_IS_UP      //不在時間経過
} event;

#endif //TURN_OFF_AC_LED_CONFIG_H_
