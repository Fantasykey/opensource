#include "user_init.h"
#include "config.h"

void main(void)
{
  user_init(); // include all user's initial
  
//  motor_set_speed(20);
//  set_color(0,0,0);
  set_number(1, 8);
  set_number(2, 8);
  set_number(3, 8);
  set_number(4, 8);
  uart_send_str("begin:");
  uart_send_num(12345);
  while(true)
  {
    if(is_received()) // already receive data in buffer from UART
    {
      uart_send_str("have data");
      analyse_all(); // analyse the data in buffer
      clear_buffer(); // clear the data in buffer
    }
    /************ user code ************/
    
    /*************** end ***************/
  }
}     