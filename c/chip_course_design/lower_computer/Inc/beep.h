#ifndef BEEP_H__
#define BEEP_H__
#include "type.h"

void beep_init(void);
// use the down of function to change beep' tone
void beep_set_duty(uint8_t du);

#endif /* BEEP_H__ */