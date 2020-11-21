#ifndef USER_INIT_H__
#define USER_INIT_H__

#include "led.h"
#include "key.h"
#include "beep.h"
#include "color.h"
#include "motor.h"
#include "nixie_tube.h"
#include "uart.h"
#include "timer0.h"
#include "analyse.h"

/*
 * initial all module
 * user can self extra-add
*/
void user_init(void)
{
  led_init();
  key_init();
  beep_init();
  color_init();
  motor_init();
  nixie_tube_init();
  uart_init();
//  timer0_init();
}

#endif /* USER_INIT_H__ */