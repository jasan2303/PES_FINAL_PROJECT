/*
 * callibrate.c
 *
 *  Created on: Dec 11, 2021
 *      Author: Jasan Singh
 */
#include "callibrate.h"
#include "mma8451.h"
#include <MKL25Z4.H>
#include "i2c.h"
#include "fsl_debug_console.h"
#include <stdint.h>

// Macro to negate the calculated offset values
#define NEGATE (-1)

//MAcro to covert 16bit values to 14bit by dividing them by 4 i.e right shift 2 times
#define BIT_14 (4)

// Macro used to Signify the calibration offset values by dividing it by 8
#define OFFSET_SIGNIFIER (8)

// MAcro to buffer range of acceleration values
#define ACC_BUFFER (1000)

/*
 *   Description: Function calibrates the accelerometer reading using the simple offset calibration
 *                method mentioned in AN4069, it takes the reading of the sensor at a position when the push
 *                button is press and calculates the offset reading and write it into the offset registers of
 *                MMA8451
 *
 *   Parameters: none
 *   returns:    none
 */
void acc_callibrate()
{

    PRINTF("Calibrating 1\n");
    uint8_t Acc_Data[6];
    int16_t Acc_Out_14bit[3];
    int16_t Xoffset, Yoffset, Zoffset;


	i2c_start();
	i2c_read_setup(MMA_ADDR , REG_XHI);


    int i;
    // Read five bytes in repeated mode
    for( i=0; i<5; i++)
    {
       Acc_Data[i] = i2c_repeated_read(0);
    }

    // Read last byte ending repeated mode
    Acc_Data[i] = i2c_repeated_read(1);

    for ( i=0; i<3; i++ )
    {
     	Acc_Out_14bit[i] = (int16_t) (((Acc_Data[2*i]<<8) | Acc_Data[2*i+1]) >>2);  //compute 14-bit X,Y,Z output values
    }



    Xoffset = Acc_Out_14bit[0] / OFFSET_SIGNIFIER * NEGATE;                        // Compute X-axis offset correction value
    Yoffset = Acc_Out_14bit[1] / OFFSET_SIGNIFIER * NEGATE;                        // Compute Y-axis offset correction value
    Zoffset = (Acc_Out_14bit[2] - COUNTS_PER_G) / OFFSET_SIGNIFIER * NEGATE;       // Compute Z-axis offset correction value

    i2c_write_byte(MMA_ADDR, REG_CTRL1, 0x00);             // Standby mode to allow writing to the offset registers
    i2c_write_byte(MMA_ADDR, OFF_X_REG, Xoffset);
    i2c_write_byte(MMA_ADDR, OFF_Y_REG, Yoffset);
    i2c_write_byte(MMA_ADDR, OFF_Z_REG, Zoffset);
    i2c_write_byte(MMA_ADDR, REG_CTRL1, 0x3D);             // ODR = 1.56Hz, Reduced noise, Active mode


}


/*
 *  Description: Function does the repeated reading of acceleration values and writes it down
 *               to the pointer received as parameter
 *
 *  Parameter: int16_t type Pointer to write the read acceleration values
 *  return: none
 */
void Read_ACCxyz( int16_t *acc_values)
{
	int i;
	uint8_t Data[6];
	int16_t temp[3];

	i2c_start();
    i2c_read_setup(MMA_ADDR , REG_XHI);

    // Read five bytes in repeated mode
    for( i=0; i<5; i++)
    {
        Data[i] = i2c_repeated_read(0);
    }

    // Read last byte ending repeated mode
    Data[i] = i2c_repeated_read(1);

    for ( i=0; i<3; i++ )
    {
       temp[i] = (int16_t) ((Data[2*i]<<8) | Data[2*i+1]);  //compute 14-bit X,Y,Z output values
    }

    //converting to 16 bit values
    acc_values[0] = temp[0]/BIT_14;
    acc_values[1] = temp[1]/BIT_14;
    acc_values[2] = temp[2]/BIT_14;

}



/*
 *   Description: Function calibrates the accelerometer using the more accurate offset and sensitivity
 *                method mentioned in AN4069, taking the acceleration values from 6 different position
 *                of the sensor namely Potrait up, Potrait Down, Landscape Left, Landscape Right, Front and Back
 *                and calculates the offsets and writes to the offset registers of MMA8451
 *   Parameter: none
 *   return: none
 */
void accurate_callibration()
{

	static int16_t PU[3], PD[3], Front[3], Back[3], LR[3], LL[3];
    int16_t Xoffset, Yoffset, Zoffset;
    PRINTF("Calibrating \n\r");

    Read_ACCxyz(Front);
    while( !((Front[0] > -ACC_BUFFER && Front[0] < ACC_BUFFER) && (Front[1] < ACC_BUFFER && Front[1] > -ACC_BUFFER) && (Front[2] > COUNTS_PER_G)) )
    Read_ACCxyz(Front);

    Read_ACCxyz(Back);
    while( !((Back[0] > -ACC_BUFFER && Back[0] < ACC_BUFFER) && (Back[1] < ACC_BUFFER && Back[1] > -ACC_BUFFER) && (Back[2] > -COUNTS_PER_G)) )
    Read_ACCxyz(Back);

    Read_ACCxyz(PU);
    while( !((-ACC_BUFFER < PU[0] && PU[0] < ACC_BUFFER) && ( PU[1] < -COUNTS_PER_G) && ( -ACC_BUFFER < PU[2] && PU[2] < ACC_BUFFER)) )
    Read_ACCxyz(PU);

    Read_ACCxyz(PD);
    while( (-ACC_BUFFER < PD[0] && PD[0] < ACC_BUFFER) && (COUNTS_PER_G > PD[1]  )   && ( -ACC_BUFFER <  PD[2] && PD[2] < ACC_BUFFER) )
    Read_ACCxyz(PD);

    Read_ACCxyz(LR);
    while( (COUNTS_PER_G < LR[0]  ) && ( 0 < LR[1] && LR[1] < ACC_BUFFER) && ( 0 < LR[2] && LR[2] < ACC_BUFFER) )
    Read_ACCxyz(LR);

    Read_ACCxyz(LL);
    while( ( LL[0] < (-COUNTS_PER_G ) ) && ( -ACC_BUFFER < LL[1] && LL[1] < ACC_BUFFER) && ( -ACC_BUFFER < LL[2] && LL[2] < ACC_BUFFER) )
    Read_ACCxyz(LL);





     Xoffset = ( PU[0] + PD[0] + Front[0] + Back[0])/BIT_14 *NEGATE;

     Yoffset = ( LL[1] + LR[1] + Front[1] + Back[1])/BIT_14* NEGATE;

     Zoffset = (PU[2] + LL[2] + PD[2] + LR[2])/BIT_14* NEGATE;

     Xoffset /= OFFSET_SIGNIFIER;
     Yoffset /= OFFSET_SIGNIFIER;
     Zoffset /= OFFSET_SIGNIFIER;

     i2c_write_byte(MMA_ADDR, REG_CTRL1, 0x00);             // Standby mode to allow writing to the offset registers
     i2c_write_byte(MMA_ADDR, OFF_X_REG, Xoffset);
     i2c_write_byte(MMA_ADDR, OFF_Y_REG, Yoffset);
     i2c_write_byte(MMA_ADDR, OFF_Z_REG, Zoffset);
     i2c_write_byte(MMA_ADDR, REG_CTRL1, 0x3D);             // ODR = 1.56Hz, Reduced noise, Active mode

}
