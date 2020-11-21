#include "color.h"
#include "config.h"

sbit LED_R =    P1^5;
sbit LED_G =    P1^6;
sbit LED_B =    P1^7;

static uint8_t s_R = 0, s_G = 0, s_B = 0;

void color_init(void)
{
  LED_R = Color_LED_Status_OFF;
  LED_G = Color_LED_Status_OFF;
  LED_B = Color_LED_Status_OFF;
  
}

void set_color(uint8_t a_r, uint8_t a_g, uint8_t a_b)
{
  assert_param(IS_Color(a_r) && IS_Color(a_g) && IS_Color(a_b));
  s_R = a_r, s_G = a_g, s_B = a_b;
}

void control_color(uint8_t a_r, uint8_t a_g, uint8_t a_b)
{
    LED_R = (a_r==Color_LED_Status_ON);
    LED_G = (a_g==Color_LED_Status_ON);
    LED_B = (a_b==Color_LED_Status_ON);
}

void task_color(void)
{
    static volatile uint8_t cnt = 0;
    control_color(s_R>=cnt, s_G>=cnt, s_B>=cnt);
    ++cnt;
}