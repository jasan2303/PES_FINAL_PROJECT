/*
 * GPIO_Interrupt.h
 *
 *  Created on: Oct 11, 2021
 *      Author: Jasan Singh
 */

#ifndef GPIO_INTERRUPT_H_
#define GPIO_INTERRUPT_H_

#include <stdio.h>
#include <MKL25z4.h>


#define INT_Switch (7)
#define RESET (0)
extern int INT_Flag;

/*
 * Initializes the PD7 Pin to use as a interrupt
 */
void GPIO_Int_Init();

/*
 * As soon as the gpio interrupt is triggered
 * INT_Flag is updated to do the calibration
 */
void PORTD_IRQHandler();


#endif /* GPIO_INTERRUPT_H_ */
