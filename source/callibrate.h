/*
 * callibrate.h
 *
 *  Created on: Dec 11, 2021
 *      Author: Jasan Singh
 */

#ifndef CALLIBRATE_H_
#define CALLIBRATE_H_

#include "GPIO_Interrupt.h"

/*
 *   Description: Function calibrates the accelerometer reading using the simple offset calibration
 *                method mentioned in AN4069, it takes the reading of the sensor at a position when the push
 *                button is press and calculates the offset reading and write it into the offset registers of
 *                MMA8451
 *
 *   Parameters: none
 *   returns:    none
 */
void acc_callibrate();

/*
 *   Description: Function calibrates the accelerometer using the more accurate offset and sensitivity
 *                method mentioned in AN4069, taking the acceleration values from 6 different position
 *                of the sensor namely Potrait up, Potrait Down, Landscape Left, Landscape Right, Front and Back
 *                and calculates the offsets and writes to the offset registers of MMA8451
 *   Parameter: none
 *   return: none
 */
void accurate_callibration();

/*
 *  Description: Function does the repeated reading of acceleration values and writes it down
 *               to the pointer received as parameter
 *
 *  Parameter: int16_t type Pointer to write the read acceleration values
 *  return: none
 */
void Read_ACCxyz( int16_t * acc_values);


#endif /* CALLIBRATE_H_ */
