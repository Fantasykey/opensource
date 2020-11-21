#include "motor.h"
#include "config.h"

sbit Motor_P =  P3^6;
sbit Motor_N =  P3^7;

static uint8_t s_left = 0, s_right = 0;

void motor_init(void)
{
  Motor_P = 0;
  Motor_N = 0;
}

void motor_set_speed(int8_t speed)
{
  assert_param(IS_SPEED(speed));
  
  (speed>0)?(s_left=0,s_right=speed):(s_left=-speed,s_right=0);
}

void task_motor(void)
{
  static volatile uint8_t cnt = 0;
  
  if(cnt <= s_left) Motor_P = 1;
  else Motor_P = 0;
  if(cnt <= s_right) Motor_N = 1;
  else Motor_N = 0;
  
  if(cnt > 100) cnt = 0;
  ++cnt;
}