#include "beep.h"
#include "config.h"
sbit BEEP =     P2^7;

static uint8_t duty = 0;

void beep_init(void)
{
  BEEP = 0;
}

void beep_set_duty(uint8_t du)
{
  duty = du;
}

void task_beep(void)
{
  static volatile uint8_t cnt = 0;
  if(cnt <= duty) BEEP = 1;
  else BEEP = 0;

  ++cnt;
}