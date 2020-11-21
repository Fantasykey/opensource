#include "uart.h"
#include "config.h"
#include "type.h"
//#include <intrins.h>

uint8_t USART_RX_BUF[USART_REC_LEN];
static uint16_t USART_RX_STA = 0;

void uart_init(void)
{
  SCON = 0x50;                  //REN=1允许串行接受状态，串口工作模式1                      
  TMOD = 0x20;                  //定时器工作方式2                    
  PCON = 0x00;                                                          
  TH1  = 0xFD;                  //波特率9600、数据位8、停止位1。效验位无 (11.0592M)
  TL1  = 0xFD;                                                           
  ES   = 1;                     //开串口中断                  
  EA   = 1;                     //开总中断          
  TR1  = 1;                     //启动定时器
}

bool is_received(void)
{
  return (bool)(USART_RX_STA&0X8000);
}

uint8_t get_length(void)
{
  return (uint8_t)(USART_RX_STA&(~0XC000));
}

void clear_buffer(void)
{
  USART_RX_STA = 0;
}

void uart_send_ch(uint8_t dat)
{
  ES=0;
  SBUF = dat;
  while(!TI);
    TI=0;
  ES=1;
}

void uart_send_str(uint8_t *buf)
{
  while(*buf != '\0')
  {
    uart_send_ch(*buf);
    ++buf;
  }
  uart_send_ch('\r');
  uart_send_ch('\n');
}

void uart_send_arr(uint8_t *buf, uint8_t len)
{
  uint8_t i;
  
  for(i = 0; i < len; ++i)
  {
    uart_send_ch(buf[i]);
  }
}

void uart_send_num(int16_t num)
{
  uint8_t temp_arr[5] = { 0 };
  uint8_t i = 0;
  int8_t j = 0;
  
  if(num < 0) {
    uart_send_ch('-');
    num = -num;
  }
  
  while(num) {
    temp_arr[i] = num%10+'0';
    num /= 10;
    ++i;
  }
  
  for(j = i-1; j >= 0; --j)
  {
    uart_send_ch(temp_arr[j]);
   
  }
  
  uart_send_ch('\r');
  uart_send_ch('\n');
}

static void read_to_string(uint8_t buffer)
{
  if((USART_RX_STA&0x8000)==0) // judge if free
  {
    uart_send_ch('1');
    if(USART_RX_STA&0x4000) // \r
    {
      uart_send_ch('2');
      if(buffer!=0x0a) // no '\n'
        USART_RX_STA=0; // re-receive
      else // '\n'
        USART_RX_STA|=0x8000; // seccess receive data
    } else {	// detect '\r'
      if(buffer==0x0d)USART_RX_STA|=0x4000;
      else
      {
        uart_send_ch('3');
        USART_RX_BUF[USART_RX_STA&0X3FFF]=buffer;
        USART_RX_STA += 1;
        if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;	  
      }
    }		 
  }
}

void usart_interrupt() interrupt 4
{
	RI = 0;
//  uart_send_ch(SBUF);
  
  read_to_string(SBUF);
}


