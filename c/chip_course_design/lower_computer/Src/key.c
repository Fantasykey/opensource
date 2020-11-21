#include "key.h"
#include "config.h"

sbit KEY_1 =      P3^2;
sbit KEY_2 =      P3^3;
sbit KEY_3 =      P3^4;
sbit KEY_4 =      P3^5;
#define KEY       P3

static uint8_t Status_KEY = 0;

void key_init(void)
{
  Status_KEY = 0;
  KEY_1 = 1;
  KEY_2 = 1;
  KEY_3 = 1;
  KEY_4 = 1;
}

uint8_t get_status(void)
{
  Status_KEY = KEY;
  Status_KEY &=~(KEY_1|KEY_2|KEY_3|KEY_4);
  return Status_KEY;
}

bool is_pressed(uint8_t key_bit)
{
  assert_param(IS_KEY_BIT(key_bit));
  
  return (bool)((KEY&key_bit) == KEY_Status_Pressed);
}