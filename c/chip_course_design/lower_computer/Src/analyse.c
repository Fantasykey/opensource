#include "analyse.h"
#include "uart.h"
#include "config.h"

#include "led.h"
#include "key.h"
#include "beep.h"
#include "color.h"
#include "motor.h"
#include "nixie_tube.h"

extern uint8_t USART_RX_BUF[USART_REC_LEN];

static uint8_t index = 0;

static bool analyse_string(uint8_t *str1, uint8_t *str2, uint8_t len)
{
  uint8_t i;
  for(i = 0; i < len; ++i)
  {
    if(str1[index+i] != str2[index+i]) return false;
  }
  index+=len;
  return true;
}

static uint16_t analyse_str_to_num(uint8_t *str, uint8_t in)
{
  uint16_t temp = 0;
  while(str[in] > '0' && str[in] < '9')
  {
    temp = temp*10 + str[in]-'0';
    ++in;
  }
  index = in;
  return temp;
}

static bool analyse_color(void)
{
  /************ user code ************/
  
  /*************** end ***************/
  set_color(255, 255, 255);
  return true;
}

static bool analyse_led(void)
{
  /************ user code ************/
  
  /*************** end ***************/
  set_led_status(0X01, 0);
  return true;
}

static bool analyse_key(void)
{
  /************ user code ************/
  
  /*************** end ***************/
  get_status();
  is_pressed(KEY_1_Bit);
  return true;
}

#define ProtocolMotor "Motor-Speed:"
static bool analyse_motor(void)
{
  int16_t temp = 0;
  /************ user code ************/
  if(analyse_string(USART_RX_BUF, ProtocolMotor, sizeof(ProtocolMotor)))
  {
    temp = analyse_str_to_num(USART_RX_BUF, sizeof(ProtocolMotor)-1);
    motor_set_speed(temp);
    uart_send_num(temp);
  }
  /*************** end ***************/
  motor_set_speed(50);
  return true;
}

static bool analyse_beep(void)
{
  /************ user code ************/
  
  /*************** end ***************/
  beep_set_duty(10);
  return true;
}

static bool analyse_nixie_tube(void)
{
  /************ user code ************/
  
  /*************** end ***************/
  set_number(1, 8);
  unset_number(1);
  return true;
}

void analyse_all(void)
{
  index = 0;
  while(index < get_length()) {
    bool flag = false;
    if(analyse_color()) flag = true;
    if(analyse_led()) flag = true;
    if(analyse_key()) flag = true;
    if(analyse_motor()) flag = true;
    if(analyse_beep()) flag = true;
    if(analyse_nixie_tube()) flag = true;
    
    if(flag == false) ++index;
  }
}