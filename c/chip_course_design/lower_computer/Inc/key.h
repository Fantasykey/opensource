#ifndef KEY_H__
#define KEY_H__
#include "type.h"

extern void key_init(void);
extern uint8_t get_status(void);
// use the down of function to judge one's key is pressed
extern bool is_pressed(uint8_t key_bit);

#endif /* KEY_H__ */