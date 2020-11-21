#include "led.h"
#include "config.h"

sbit LED_1 =    P1^0;
sbit LED_2 =    P1^1;
sbit LED_3 =    P1^2;
sbit LED_4 =    P1^3;
sbit LED_5 =    P1^4;
sbit LED_6 =    P1^5;
sbit LED_7 =    P1^6;
sbit LED_8 =    P1^7;
#define LED     P0

void led_init(void)
{
  LED_1 = LED_Status_OFF;
  LED_2 = LED_Status_OFF;
  LED_3 = LED_Status_OFF;
  LED_4 = LED_Status_OFF;
  LED_5 = LED_Status_OFF;
  LED_6 = LED_Status_OFF;
  LED_7 = LED_Status_OFF;
  LED_8 = LED_Status_OFF;
}

void set_led_status(uint8_t led_bit, bool status)
{
  assert_param(IS_LED_BIT(led_bit));

  if(status) {
    LED |= led_bit;
  } else {
    LED &=~led_bit;
  }
}