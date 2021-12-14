/*
 *  Drone_Stabilizer.c
 *
 *  Details  : main file of the project
 *  Created on: Dec 11, 2021
 *      Author: Jasan Singh
 */

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include <math.h>
#include "LEDs.h"
#include "i2c.h"
#include "mma8451.h"
#include "PWM.h"
#include "stabilizer.h"
#include "GPIO_Interrupt.h"
#include "callibrate.h"



/*
 * @brief   Application entry point.
 */
int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

    #ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
    #endif

	Init_RGB_LEDs();
	i2c_init();								/* init i2c	*/
	PWM_Init();                             /* PWM controlled LED are initialized */
	GPIO_Int_Init();                        /* Interrupt Button at port D7 is initialized */

	if (!init_mma())
	{							     		/* init mma peripheral */
		Control_RGB_LEDs(1, 0, 0);			/* Light red error LED */
		while (1);							/* If not able to initialize mma */
	}


    INT_Flag = RESET;                       /* Resseting the interrupt flag prior to entering the while loop */

	while (1)
	{

		if(INT_Flag)
		{
			acc_callibrate(); /* Doing Offset calibration*/

			//accurate_callibration();  /* Uncomment this and comment the above */
			                            /* acc_callibrate() function call to use*/
			                            /* more accurate method of calibration */

			//resetting the interrupt flag after the interrupt is served.
			INT_Flag = RESET;

		}
		read_full_xyz();
		convert_xyz_to_roll_pitch();
		Roll_Detector( );
		Pitch_Detector( );
	}

}
