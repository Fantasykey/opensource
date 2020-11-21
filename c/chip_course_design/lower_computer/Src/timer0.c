#include "timer0.h"
#include "config.h"
#include "task.h"

void timer0_init(void)
{
  TMOD = 0x02;
  TH0 = 256-5;
  TL0 = 256-5;
  TR0 = 1;
  EA = 1;
  ET0 = 1;
}

void timer0_ISR(void) interrupt 1
{
  task_color();
//  task_beep();
//  task_motor();
}