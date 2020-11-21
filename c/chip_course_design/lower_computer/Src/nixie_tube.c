#include "nixie_tube.h"
#include "config.h"

#if Nixie_Tube_IS_ANODE
//common anode
unsigned char table[] =
{0xc0,0xf9,0xa4,0xb0,
0x99,0x92,0x82,0xf8,
0x80,0x90,0x88,0x83,
0xc6,0xa1,0x86,0x8e};
#else
//common cathode
unsigned char table[] =
{0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71};
#endif /* Nixie_Tube_IS_ANODE */

sbit NixieTube_1 = P2^0;
sbit NixieTube_2 = P2^1;
sbit NixieTube_3 = P2^2;
sbit NixieTube_4 = P2^3;
#define NixieTube P0

void nixie_tube_init(void)
{
  NixieTube_1 = !Nixie_Tube_IS_ANODE;
  NixieTube_2 = !Nixie_Tube_IS_ANODE;
  NixieTube_3 = !Nixie_Tube_IS_ANODE;
  NixieTube_4 = !Nixie_Tube_IS_ANODE;
  NixieTube = 0;
}

void set_number(uint8_t index, uint8_t num)
{
  switch(index)
  {
    case 1:
      NixieTube_1 = Nixie_Tube_IS_ANODE;
      break;
    case 2:
      NixieTube_2 = Nixie_Tube_IS_ANODE;
      break;
    case 3:
      NixieTube_3 = Nixie_Tube_IS_ANODE;
      break;
    case 4:
      NixieTube_4 = Nixie_Tube_IS_ANODE;
      break;
  }
  NixieTube = table[num];
}

void unset_number(uint8_t index)
{
  switch(index)
  {
    case 1:
      NixieTube_1 = !Nixie_Tube_IS_ANODE;
      break;
    case 2:
      NixieTube_2 = !Nixie_Tube_IS_ANODE;
      break;
    case 3:
      NixieTube_3 = !Nixie_Tube_IS_ANODE;
      break;
    case 4:
      NixieTube_4 = !Nixie_Tube_IS_ANODE;
      break;
  }
}