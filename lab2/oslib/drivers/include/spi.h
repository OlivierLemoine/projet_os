#ifndef _SPI_H_
#define _SPI_H_

#include "board.h"

#define SPI_BUSY				1  		// transfer busy
#define SPI_OK					0		// transfer ended No Errors
#define SPI_ERROR				-1  	// err: general error

/* spi_init
 *   initialize SPI device
 */
void spi_init();

/* spi_write
 *   initialize SPI device
 */
void spi_write(uint8 *data, uint32 n);

/* spi_status()
 *   return SPI transmission status
 */
#endif
