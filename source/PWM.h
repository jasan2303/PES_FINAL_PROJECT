/*
 * PWM.h
 *
 *  Created on: Dec 11, 2021
 *      Author: Jasan Singh
 */

#ifndef PWM_H_
#define PWM_H_

#include <stdint.h>
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"

#define	PWM_PERIOD	(4800)

/*
 *  Intitializes TPM0 channels to drive Red, Green and Blue colors on the LED
 */
void PWM_Init();

/*
 *  Function controls the strength of PWM signal connected to the LEDs
 *
 *  Parameters: Takes count Values to control the PWM period
 */
void Write_LED( int Red, int Green, int Blue);


#endif /* PWM_H_ */
