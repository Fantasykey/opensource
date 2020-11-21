#ifndef COLOR_H__
#define COLOR_H__
#include "type.h"
#include "color.h"

extern void color_init(void);
// use the down of function to set color-led's color
extern void set_color(uint8_t a_r, uint8_t a_g, uint8_t a_b);

#endif /* COLOR_H__ */