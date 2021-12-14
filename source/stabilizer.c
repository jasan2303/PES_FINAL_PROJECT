/*
 * stabilizer.c
 *
 *  Created on: Dec 11, 2021
 *      Author: Jasan Singh
 */

#include "stabilizer.h"
#include "LEDs.h"
#include <math.h>
#include "PWM.h"

// Macro for reference to calculate pitch and roll percentage
#define OFFSET_ANGLE (90)


/*
 *  Description : Function Detects the Roll percentage and its direction
 *
 *  Parameters: None
 *  ReturnType: None
 *
 */
void Roll_Detector( )
{
	int roll_polarity=0;
	int roll_percentage;


	if( roll > 0)
		roll_polarity = 1;   //Notes the Roll Polarity

	//computing Roll percentage(fraction to reflect it as LED brightness
	roll_percentage = ((fabs(roll))/ OFFSET_ANGLE)*PWM_PERIOD;

	//Applies the roll on the LED
	Roll_Controller(roll_percentage, roll_polarity );

}


/*
 *  Description: Function controls the LED brightness controlling the PWM strength driving the LED
 *
 *  Parameter: Takes Roll percentage of PWM count along with the polarity(direction) of Roll
 *  Returns:   None
 *
 */
void Roll_Controller( int Roll, int Polarity)
{
	if(Polarity)
		Write_LED( Roll, 0, 0);  //positive roll shown using RED LED
	else
		Write_LED(0, 0, Roll ); //negative roll shown using BLUE LED

}


/*
 * Description: Function detects the pitch value and computes its percentage along
 *              with the direction
 *
 * Parameter:   none
 * returns:     none
 *
 */
void Pitch_Detector( )
{
	int pitch_polarity=0;
	int pitch_percentage;


	if( pitch > 0)
		pitch_polarity = 1;     //Notes pitch polarity

	//computes pitch percentage of PWM period
	pitch_percentage = ((fabs(pitch))/ OFFSET_ANGLE)*PWM_PERIOD;

	//Applies pitch on LED
	Pitch_Controller(pitch_percentage, pitch_polarity );

}


/*
 *  Description: Function writes the pitch percentage on the LED
 *
 *  Parameter:   pitch percentage of PWM along with the polarity
 *  returns:     none
 */
void Pitch_Controller( int Pitch, int Polarity)
{
	if(Polarity)
		Write_LED( 0, Pitch, 0);
	else
		Write_LED(Pitch, Pitch, Pitch );

}
