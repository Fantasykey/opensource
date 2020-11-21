#ifndef UART_H__
#define UART_H__
#include "type.h"
#define USART_REC_LEN  			30

void uart_init(void);
//judge if data is received
bool is_received(void);
//get data length
uint8_t get_length(void);
//clear buffer whar received data
void clear_buffer(void);

void uart_send_ch(uint8_t dat);

void uart_send_str(uint8_t *buf);

void uart_send_arr(uint8_t *buf, uint8_t len);

void uart_send_num(int16_t num);

#endif /* UART_H__ */