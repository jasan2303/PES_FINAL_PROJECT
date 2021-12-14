/*
 *  mma8451.c
 *
 *  Details  : functions accessing MMa851 sensor
 *  Created on: Dec 11, 2021
 *      Author: Jasan Singh
 */
#include "mma8451.h"

#define LOG_TIME (1000)

#define AVOID_FLOAT (1000)

int16_t acc_X=0, acc_Y=0, acc_Z=0;
int roll=0, pitch=0;

/*
 *
 *   Description: initializes mma8451 sensor using details from dataSheet
 *                 i2c has to already be enabled
 *
 */
int init_mma()
{
	//set active mode, 14 bit samples and 800 Hz ODR 
	i2c_write_byte(MMA_ADDR, REG_CTRL1, 0x01);
	return 1;
}

/*
 *  Description: Using I2C repeated mode reads the registers containing X,Y,Z counts
 *               related to acceleration
 *
 *  Parameters: None
 *  Return Type: None
 *
 */
void read_full_xyz()
{
	int i;
	uint8_t data[6];
	int16_t temp[3];
	
	i2c_start();
	i2c_read_setup(MMA_ADDR , REG_XHI);
	
	// Read five bytes in repeated mode
	for( i=0; i<5; i++)	{
		data[i] = i2c_repeated_read(0);
	}

	// Read last byte ending repeated mode
	data[i] = i2c_repeated_read(1);
	
	for ( i=0; i<3; i++ ) {
		temp[i] = (int16_t) ((data[2*i]<<8) | data[2*i+1]);
	}

	// Align for 14 bits
	acc_X = temp[0]/4;
	acc_Y = temp[1]/4;
	acc_Z = temp[2]/4;

}




/*
 * Description : Uses Cartesian geometry to calculate Roll and Pitch angles
 *               from the acceleration counts read from I2C
 *
 * Parameters: Null
 * Return Type: Null
 *
 */
void convert_xyz_to_roll_pitch(void) {

	//Converting the counts to the actual acceleration values
	int   ax = (acc_X/COUNTS_PER_G) *AVOID_FLOAT,
		  ay = (acc_Y/COUNTS_PER_G)*AVOID_FLOAT,
		  az = (acc_Z/COUNTS_PER_G)*AVOID_FLOAT;
	static int count;

	roll = atan2(ay, az)*180/M_PI;                      // Roll angle calculation
	pitch = atan2(ax, sqrt(ay*ay + az*az))*180/M_PI;    // Pitch angle calculation

	count++;
	if(count == LOG_TIME)
	{
		count=0;
	    PRINTF( "roll = %d pitch = %d \n\r ", roll, pitch);
	}
}

