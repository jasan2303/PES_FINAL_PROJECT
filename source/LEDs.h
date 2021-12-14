#ifndef LEDS_H
#define LEDS_H

// Freedom KL25Z LEDs
#define RED_LED_POS (18)		// on port B
#define GREEN_LED_POS (19)	// on port B
#define BLUE_LED_POS (1)		// on port D

/*
 *  Description: Initializes RGB LEDs at port B18, B19, D1
 *
 *  Parameters: None
 *  ReturnType : None
 */
void Init_RGB_LEDs(void);

/*
 *  Description : Turns on LEDs depending on the parameters sent
 *
 *  Parameters : red_on, green_on, blue_on separate signals Turns Led ON if 1 and OFF when 0
 *  Return Type: none
 */
void Control_RGB_LEDs(unsigned int red_on, unsigned int green_on, unsigned int blue_on);


#endif
