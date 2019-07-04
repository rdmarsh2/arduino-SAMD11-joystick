/*
 * Top panel block 1(upper buttons)
 * 4 pin connector on pins 0-3
 */
#define BUTTON_1 0
#define BUTTON_2 1
#define BUTTON_3 2
#define BUTTON_4 3

/*
 * Top panel block 2 (upper buttons)
 * 4 pin connector on pins 4-7
 */
#define BUTTON_5 4
#define BUTTON_6 5
#define BUTTON_7 6
#define BUTTON_8 7

// 8 and 9 left empty

/* 
 * Joystick block - placed here so a 5-pin block puts the neutral wire on the
 * ground pin next to pin 13
 */
#define JOYSTICK_UP   10
#define JOYSTICK_DOWN 11
// these are flipped from the "standard" order because of Sanwa JLF wire ordering
#define JOYSTICK_RIGHT 12
#define JOYSTICK_LEFT 13

/*
 * Back panel block, 4-pin connector on theanalog pins - same orientation as top panel blocks
 */
#define BUTTON_9  A5
#define BUTTON_10 A4
#define BUTTON_11 A3
#define BUTTON_12 A2
