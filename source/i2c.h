
#ifndef I2C_H
#define I2C_H

#include <stdint.h>
#include <MKL25Z4.H>


/*
 *  Description: Initializes i2c0 using the details from the manual
 *
 *  Parameters : None
 *  Return Type: NOne
 *
 */
void i2c_init(void);

/*
 *  Description: Signal's to send start sequence
 *
 *  Parameters : None
 *  ReturnType : None
 */
void i2c_start(void);

/*
 *  Description : Function Sets up the device from which data is read by
 *                sending device and register addresses
 *  Parameter: Device and register address from which data has to be read
 *  Return Type: None
 *
 */
void i2c_read_setup(uint8_t dev, uint8_t address);

/*
 *  Description: Function keeps reading data from the I2C bus until parameter
 *               isLAstRead signal's to stop
 *
 *  Parameter:   Flag isLastRead to indicate send stop signal
 *  return type: Returns 8 bit data read from the bus
 *
 */
uint8_t i2c_repeated_read(uint8_t);


/*
 *  Description: function for reading a single byte
 *               using 7bit addressing reads a byte from dev:address
 *  Parameter :  Takes Device and the register address
 *  Return Type: Reads 8 bit Data read from the register
 */
uint8_t i2c_read_byte(uint8_t dev, uint8_t address);

/*
 *  Description: using 7bit addressing writes a byte data to dev:address
 *
 *  Parameters : Along with the Device and register address, 8 bit data is given
 *  Return Type: Null
 */
void i2c_write_byte(uint8_t dev, uint8_t address, uint8_t data);

#endif
