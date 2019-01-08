/*! 
* @file dac121c085.h
*
* @brief Library for the TI DAC121C085 with I2C interface.
*
* @author Xavier Garcia Herrera.
*
* @par
* Version 1.0 2014
*/
#ifndef _LIBDAC121C085_H
#define _LIBDAC121C085_H

#include <stdint.h> //generic typedefs
#include <stdbool.h> //bool typedef

/*! @name Communication defines
** @{
*/
#define SLAVE_ADDR	0b0001100  /*!< See datasheet for different values */
#define SLAVE_READ  1
#define SLAVE_WRITE 0
/** @} */


/* Function prototypes*/
void 
dac121c085_i2c_init (void);
void 
dac121c085_init (void);
uint16_t
dac121c085_read (void);
void 
dac121c085_write (uint16_t dac_value);
void
dac121c085_burst_write (uint16_t *dac_value, uint8_t len)


#endif /* _LIBDAC121C085_H */
