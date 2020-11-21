#include <REGX52.H>

#define KEY_Status_Pressed  0
#define KEY_Status_Loosen   1

#define Color_LED_Status_ON	0
#define Color_LED_Status_OFF 1

#define LED_Status_ON	0
#define LED_Status_OFF 1

#define Nixie_Tube_IS_ANODE 0

// For convenient tranfer parameters
#define assert_param(expr) ((void)0)
  
#define LED_1_BIT 0X01
#define LED_2_BIT 0X02
#define LED_3_BIT 0X04
#define LED_4_BIT 0X08
#define LED_5_BIT 0X10
#define LED_6_BIT 0X20
#define LED_7_BIT 0X40
#define LED_8_BIT 0X80

#define IS_LED_BIT(INSTANCE) (((INSTANCE) == LED_1_BIT) || \
                             ((INSTANCE) == LED_2_BIT) || \
                             ((INSTANCE) == LED_3_BIT) || \
                             ((INSTANCE) == LED_4_BIT) || \
                             ((INSTANCE) == LED_5_BIT) || \
                             ((INSTANCE) == LED_6_BIT) || \
                             ((INSTANCE) == LED_7_BIT) || \
                             ((INSTANCE) == LED_8_BIT))

#define KEY_1_Bit 0X04
#define KEY_2_Bit 0X08
#define KEY_3_Bit 0X10
#define KEY_4_Bit 0X20

#define IS_KEY_BIT(INSTANCE) (((INSTANCE) == KEY_1_Bit) || \
                             ((INSTANCE) == KEY_2_Bit) || \
                             ((INSTANCE) == KEY_3_Bit) || \
                             ((INSTANCE) == KEY_4_Bit))

#define IS_Color(INSTANCE) ((INSTANCE >= 0) && \
                            (INSTANCE <= 255))

#define IS_SPEED(INSTANCE) ((INSTANCE > -100) && \
                            (INSTANCE < 100))

