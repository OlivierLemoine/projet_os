/* i2c.h
 *
 * I2C Bus driver
 *
 * UM10139.pdf p. 206-244
 */
 
#ifndef _I2C_H_
#define _I2C_H_

#include "board.h"

/**** Status Errors ****/
#define I2C_BUSY				1  		// transfer busy
#define I2C_OK					0		// transfer ended No Errors
#define I2C_ERROR				-1  	// err: general error
#define I2C_DEVICE_NOT_PRESENT	-5  	// err: Device not present
#define I2C_ARBITRATION_LOST	-6  	// err: Arbitration lost
#define I2C_TIME_OUT			-7  	// err: Time out occurred
#define I2C_SLAVE_ERROR			-8  	// err: Slave mode error

/* i2c_master_init
 *
 * i2c interface initialized in master mode
 */
int i2c_master_init();

/* i2c_write : write n bytes from buf to slave identified by addr
 *
 */
int i2c_write(uint8 addr, uint8* buf, uint32 n);

/* i2c_read : read n bytes from slave identified by addr to buf
 *
 */
int i2c_read(uint8 addr, uint8* buf, uint32 n);

/* i2c_write_read : write nwr bytes from buf to slave identified by addr,
 *                  then read nrd bytes to buf
 *
 */
int i2c_write_read(uint8 addr, uint8* buf, uint32 nwr, uint32 nrd);

#endif
