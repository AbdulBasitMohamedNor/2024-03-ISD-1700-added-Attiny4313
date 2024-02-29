
#include <avr/io.h>
#include <avr/power.h>
#include <avr/sleep.h>
#include <inttypes.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>

#ifndef MBED_MCP4261_H
#define MBED_MCP4261_H

//=============================================================================
// All The Addresses
//=============================================================================

#define TCON_ADDR       0x04       // Controls the state of each resistor network terminal connection.   
#define STATUS_ADDR     0x05       // Status (STATUS) Register, This register contains 5 status bits. WiperLock bits, Shutdown bit, Write Protect bit, EEPROM write cycle.
#define VW0_ADDR        0x02       // Volatile Wiper 0
#define VW1_ADDR        0x03       // Volatile Wiper 1
#define NVW0_ADDR       0x04       // Non Volatile Wiper 0	
#define NVW1_ADDR       0x05       // Non Volatile Wiper 1

// DATA EEPROM locations has the address from 0x06 to 0x0F 

//=============================================================================
// Declaration of variables & custom #defines
//=============================================================================

#define CB_WRITE        0x00       // Device commad bit for WRITE
#define CB_INCR         0x01       // Device commad bit for INCREMENT
#define CB_DECR         0x02       // Device commad bit for DECREMENT
#define CB_READ         0x03       // Device commad bit for READ

//=============================================================================
// Functions Declaration
//=============================================================================

/** Interface to the 7/8-Bit Single/Dual SPI Digital POT with Non-Volatile Memory
 *
  *  Using the driver:
 *   - remenber to setup SPI in main routine or use pins instance.
 *
 *  Defaults in this driver on start up:
 *   - as default is HARDWARE WRITE PROTECT PIN "Off".
 *   - as default is HARDWARE SHUTDOWN PIN  "Off".
 *
 */

    /** Read an Address.
     *
     * @param address The selected register to read from.
     * @return The 16 bits read.
     */
    int read(char address);

    /** Write to Address.
     *
     * @param address The selected register to write to.
     * @param data The 16 bits to write to the register
     */
    void write(char address, int data);
    
    /** Increment wiper.
     *
     * @param number The selected wiper to increment.
     */
    void inc(bool number);
    
    /** Decrement wiper.
     *
     * @param number The selected wiper to decrement.
     */
    void dec(bool number);
    
    /** Read the Status register.
     *
     * @return The 16 bits read.
     */
    int status();
    
    /** Read the tcon register.
     *
     * @return The 16 bits read.
     */
    int tcon();
    
    /** write to tcon register.
     *
     * @param data The 16 bits to write to the register
     */
    void tcon(int data);
    
    /** Read the Volatile Wiper.
     *
     * @param number The wiper number = '0' or '1'
     * @return The 16 bits read.
     */
    int wiper(bool number);
    
    /** write to Volatile Wiper.
     *
     * @param number The wiper number = '0' or '1'
     * @param data The 16 bits to write to the register
     */
    void wiper(bool number, int data);
    
    /** Read the non-volatile wiper (Power On Reset start value).
     *
     * @param number The wiper number = '0' or '1'
     * @return The 16 bits read.
     */
    int nvwiper(bool number);
    
    /** write to non-volatile wiper (Power On Reset start value).
     *
     * @param number The wiper number = '0' or '1'
     * @param data The 16 bits to write to the register
     */
    void nvwiper(bool number, int data);
    
    /** HARDWARE SHUTDOWN PIN (SHDN)
     *
     * @param act SHDN is Active = true and Inactive = false
     */
    void shdn(bool act);
    
    /** HARDWARE WRITE PROTECT PIN (WP)
     *
     * @param act WP is Active = true and Inactive = false
     */
    void wp(bool act);
  
   unsigned char _spi_write(unsigned char val);
   
  
    //DigitalOut _nWP;
    //DigitalOut _nSHDN;		 +
	 
    //char SS;
        														
//char _command_byte1;
    
    char _make_command_byte(int com, char address, int data);
    int _read(char address);                          
    void _write(char address, int data);             



#endif