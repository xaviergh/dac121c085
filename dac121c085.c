/*! 
* @file dac121c085.c
*
* @brief Library for the TI DAC121C085 with I2C interface.
*
* @author Xavier Garcia Herrera.
*
* @par
* Version 1.0 2014
*/
#include "dac121c085.h"

#ifdef __XC8
#define delay_ms __delay_ms
#else
#use i2c(master,I2C1,slow) //to use with CSS PIC only
#endif


/*!
*\fn void dac121c085_i2c_init (void)
* @brief Init microcontroller I2C.
* @return nothing.
*/
void
dac121c085_i2c_init (void)
{
    //Standard Mode: 100kHz
    //Fast Mode: 400kHz
    i2c_init(100000);
}

/*!
*\fn void dac121c085_init (void)
* @brief Init dac121c085 with 0V and normal mode.
* @return nothing.
*/
void
dac121c085_init (void)
{
    i2c_start(); 
    i2c_write(SLAVE_ADDR | SLAVE_WRITE);
    i2c_write(0x00);
    i2c_write(0x00);
    i2c_stop();
}

/*!
*\fn void dac121c085_read (void)
* @brief Read dac121c085 current value.
* @return 12bit DAC value.
*/
uint16_t
dac121c085_read (void)
{
    
    uint8_t msb, lsb;
    uint16_t dac_value;

    i2c_start(); 
    i2c_write(SLAVE_ADDR | SLAVE_READ);
    msb = i2c_read(); //ACK
    lsb = i2c_read(0); //NACK
    i2c_stop();

    dac_value = make16(msb,lsb);
    dac_value = dac_value && 0x0FFF; //take only the 12bit part

    return dac_value;
}

/*!
*\fn void dac121c085_write (uint16_t dac_value)
* @brief write the desired 12bit value to the DAC in normal mode.
* @param[in] dac_value 12bit DAC value.
* @return nothing.
*/
void
dac121c085_write (uint16_t dac_value)
{
    dac_value = dac_value && 0x0FFF; //clean the 12bit part and set normal mode 0b00

    i2c_start(); 
    i2c_write(SLAVE_ADDR | SLAVE_WRITE);
    i2c_write((dac_value >> 8)); //msb
    i2c_write(dac_value); //lsb
    i2c_stop();
}

/*!
*\fn void dac121c085_burst_write (uint16_t dac_value)
* @brief Write continuous 12bit value to the DAC in normal mode.
* @param[in] dac_value pointer to the 12bit values to write.
* @param[in] len length of the array to the dac_value.
* @return nothing.
*/
void
dac121c085_burst_write (uint16_t *dac_value, uint8_t len)
{
    i2c_start(); 
    i2c_write(SLAVE_ADDR | SLAVE_WRITE);

    while (len--)
    {
        i2c_write((*dac_value >> 8)); //msb
        i2c_write(*dac_value); //lsb
        dac_value++;
    }

    i2c_stop();
}