#ifndef NIXIE_TUBE_H__
#define NIXIE_TUBE_H__
#include "type.h"

void nixie_tube_init(void);
/*
 *@para: index-the bit of nixie-tube what you want to display 
 *       num-the number for show
*/
void set_number(uint8_t index, uint8_t num);
/*
 *@func: close the bit nixie-tube
*/
void unset_number(uint8_t index);

#endif /* NIXIE_TUBE_H__ */