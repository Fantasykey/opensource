#ifndef LED_H__
#define LED_H__
#include "type.h"

void led_init(void);
// use the down of function to change led's status
void set_led_status(uint8_t led_bit, bool status);

#endif /* LED_H__ */