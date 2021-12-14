/*
 * GPIO_Interrupt.c
 *
 *  Created on: Oct 11, 2021
 *      Author: Jasan Singh
 */


#include "GPIO_Interrupt.h"


int INT_Flag;

/*
 * Initializes the PD7 Pin to use as a interrupt
 */
void GPIO_Int_Init()
{
	SIM ->SCGC5 |= SIM_SCGC5_PORTD_MASK;           // Sourcing clock to port D
	PORTD->PCR[INT_Switch] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[INT_Switch] |= PORT_PCR_MUX(1);     // multiplexing the pin to GPIO
	PORTD->PCR[INT_Switch] |= PORT_PCR_IRQC(10);   // Setting the configuration to falling edge
	PORTD->PCR[INT_Switch] |= PORT_PCR_PE_MASK;    // Enabling pull up resistor configuration
	PORTD->PCR[INT_Switch] |= PORT_PCR_ISF_MASK;   // Setting the interrupt flag
	PORTD->PCR[INT_Switch] |= PORT_PCR_PS_MASK;    // Enabling Pull select

	NVIC_EnableIRQ(PORTD_IRQn);

}

/*
 * As soon as the gpio interrupt is triggered
 * execution transfers to Handler() and gets into the Crosswalk
 */
void PORTD_IRQHandler()
{
	NVIC_DisableIRQ(PORTD_IRQn);
	INT_Flag=1;
	PORTD->PCR[INT_Switch] |= PORT_PCR_ISF_MASK;
	NVIC_EnableIRQ(PORTD_IRQn);

}
