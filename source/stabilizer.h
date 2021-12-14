/*
 * stabilizer.h
 *
 *  Created on: Dec 11, 2021
 *      Author: Jasan Singh
 */

#ifndef STABILIZER_H_
#define STABILIZER_H_

#include "mma8451.h"


/*
 *  Description : Function Detects the Roll percentage and its direction
 *
 *  Parameters: None
 *  ReturnType: None
 *
 */
void Roll_Detector( );


/*
 *  Description: Function controls the LED brightness controlling the PWM strength driving the LED
 *
 *  Parameter:   Takes Roll percentage of PWM count along with the polarity(direction) of Roll
 *  Returns:     None
 *
 */
void Roll_Controller( int Roll, int Polarity);

/*
 * Description: Function detects the pitch value and computes its percentage along
 *              with the direction
 *
 * Parameter:   none
 * returns:     none
 *
 */
void Pitch_Detector();

/*
 *  Description: Function writes the pitch percentage on the LED
 *
 *  Parameter: pitch percentage of PWM along with the polarity
 *  returns: none
 */
void Pitch_Controller( int Pitch, int Polarity);

#endif /* STABILIZER_H_ */
