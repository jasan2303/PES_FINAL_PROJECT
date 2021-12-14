#ifndef MMA8451_H
#define MMA8451_H
#include <stdint.h>
#include "i2c.h"
#include <math.h>
#include <stdio.h>
#include "fsl_debug_console.h"
#include <MKL25Z4.H>

#define MMA_ADDR 0x3A

/*
 *  Register address from MMA8451 datasheet
 */
#define REG_XHI 0x01
#define REG_XLO 0x02
#define REG_YHI 0x03
#define REG_YLO 0x04
#define REG_ZHI	0x05
#define REG_ZLO 0x06

#define REG_WHOAMI 0x0D
#define REG_CTRL1  0x2A
#define REG_CTRL4  0x2D

#define WHOAMI 0x1A

#define OFF_X_REG 0x2f
#define OFF_Y_REG 0x30
#define OFF_Z_REG 0x31

// Counts requires for per G(9.8 m/sec2) value
#define COUNTS_PER_G (4096.0)

// Pi value for Calculating Roll and Pitch angles
#define M_PI (3.14159265)

// Externing so that they can be accessed globally
extern int roll, pitch;
extern int16_t acc_X, acc_Y, acc_Z;

/*
 *   description : initializes MMA sensor by fur enabling I2C bus connection
 *
 *   Parameters: None
 *   Return Type: Returns 1, if initialization is successful
 */
int init_mma(void);

/*
 *  Description: Using I2C repeated mode reads the registers containing X,Y,Z counts
 *               related to acceleration
 *
 *  Parameters: None
 *  Return Type: None
 *
 */
void read_full_xyz(void);


/*
 * Description : Uses Cartesian geometry to calculate Roll and Pitch angles
 *               from the acceleration counts read from I2C
 *
 * Parameters: Null
 * Return Type: Null
 *
 */
void convert_xyz_to_roll_pitch(void);

#endif
