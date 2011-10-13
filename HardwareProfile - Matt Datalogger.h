/********************************************************************
 FileName:     	HardwareProfile - Matt Datalogger.h
 Dependencies:  See INCLUDES section
 Processor:     PIC18 USB Microcontrollers
 Hardware:      Matts Datalogger
 Compiler:      Microchip C18
 Company:       Microchip Technology, Inc.

 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the “Company”) for its PIC® Microcontroller is intended and
 supplied to you, the Company’s customer, for use solely and
 exclusively on Microchip PIC Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

********************************************************************
 File Description:

 Change History:
  Rev   Date         Description
  1.0   11/19/2004   Initial release
  2.1   02/26/2007   Updated for simplicity and to use common
                     coding style
  2.3   09/15/2008   Broke out each hardware platform into its own
                     "HardwareProfile - xxx.h" file
  3.0	21/05/2009	Changed for Matt Datalogger hardware
********************************************************************/

#ifndef HARDWARE_PROFILE_MATT_DATALOGGER_H
#define HARDWARE_PROFILE_MATT_DATALOGGER_H

    /*******************************************************************/
    /******** USB stack hardware selection options *********************/
    /*******************************************************************/
    //This section is the set of definitions required by the MCHPFSUSB
    //  framework.  These definitions tell the firmware what mode it is
    //  running in, and where it can find the results to some information
    //  that the stack needs.
    //These definitions are required by every application developed with
    //  this revision of the MCHPFSUSB framework.  Please review each
    //  option carefully and determine which options are desired/required
    //  for your application.

    //The PICDEM FS USB Demo Board platform supports the USE_SELF_POWER_SENSE_IO
    //and USE_USB_BUS_SENSE_IO features.  Uncomment the below line(s) if
    //it is desireable to use one or both of the features.
    //#define USE_SELF_POWER_SENSE_IO
    #define tris_self_power     TRISAbits.TRISA2    // Input
    #if defined(USE_SELF_POWER_SENSE_IO)
    #define self_power          PORTAbits.RA2
    #else
    #define self_power          1
    #endif

    //#define USE_USB_BUS_SENSE_IO
    #define tris_usb_bus_sense  TRISAbits.TRISA1    // Input
    #if defined(USE_USB_BUS_SENSE_IO)
    #define USB_BUS_SENSE       PORTAbits.RA1
    #else
    #define USB_BUS_SENSE       1
    #endif

    //Uncomment the following line to make the output HEX of this  
    //  project work with the MCHPUSB Bootloader    
    #define PROGRAMMABLE_WITH_USB_MCHPUSB_BOOTLOADER
	
    //Uncomment the following line to make the output HEX of this 
    //  project work with the HID Bootloader
    //#define PROGRAMMABLE_WITH_USB_HID_BOOTLOADER		

    /*******************************************************************/
    /******** MDD File System selection options ************************/
    /*******************************************************************/
    #define USE_PIC18

    #define ERASE_BLOCK_SIZE        64
    #define WRITE_BLOCK_SIZE        32

    /*******************************************************************/
    /*******************************************************************/
    /*******************************************************************/
    /******** Application specific definitions *************************/
    /*******************************************************************/
    /*******************************************************************/
    /*******************************************************************/

    /** Board definition ***********************************************/
    //These defintions will tell the main() function which board is
    //  currently selected.  This will allow the application to add
    //  the correct configuration bits as wells use the correct
    //  initialization functions for the board.  These defitions are only
    //  required in the stack provided demos.  They are not required in
    //  final application design.
    #define DEMO_BOARD MATT_DAQ
    #define MATT_DAQ
    #define CLOCK_FREQ 20000000

    /** LED ************************************************************/
    #define mInitAllLEDs()      LATC &= 0x3F; TRISC &= 0x3F; LATB &= 0x70; TRISB &= 0x70;
    
    #define mLED_1              LATCbits.LATC6	// LED to show USB status
    #define mLED_2              LATCbits.LATC7	// LED to show USB status
//    #define mLED_OUT_1          LATBbits.LATB0	// B0 and B1 are used for SPI bus
//    #define mLED_OUT_2          LATBbits.LATB1
    #define mLED_OUT_1          LATBbits.LATB2
    #define mLED_OUT_2          LATBbits.LATB3
    #define mBUZZ          		LATBbits.LATB7	// Buzzer output

    
    #define mGetLED_1()         mLED_1
    #define mGetLED_2()         mLED_2
    #define mGetLED_OUT_1()     mLED_OUT_1
    #define mGetLED_OUT_2()     mLED_OUT_2
//    #define mGetLED_OUT_3()     mLED_OUT_3
//    #define mGetLED_OUT_4()     mLED_OUT_4


    #define mLED_1_On()         mLED_1 = 1;
    #define mLED_2_On()         mLED_2 = 1;
    #define mLED_OUT_1_On()     mLED_OUT_1 = 1;
    #define mLED_OUT_2_On()     mLED_OUT_2 = 1;
//   #define mLED_OUT_3_On()     mLED_OUT_3 = 1;
//   #define mLED_OUT_4_On()     mLED_OUT_4 = 1;
    #define mBUZZ_On()         	mBUZZ = 1;

    
    #define mLED_1_Off()        mLED_1 = 0;
    #define mLED_2_Off()        mLED_2 = 0;
    #define mLED_OUT_1_Off()    mLED_OUT_1 = 0;
    #define mLED_OUT_2_Off()    mLED_OUT_2 = 0;
//    #define mLED_OUT_3_Off()    mLED_OUT_3 = 0;
//   #define mLED_OUT_4_Off()    mLED_OUT_4 = 0;
    #define mBUZZ_Off()         mBUZZ = 0;
    
    #define mLED_1_Toggle()     mLED_1 = !mLED_1;
    #define mLED_2_Toggle()     mLED_2 = !mLED_2;
    #define mLED_OUT_1_Toggle() mLED_OUT_1 = !mLED_OUT_1;
    #define mLED_OUT_2_Toggle() mLED_OUT_2 = !mLED_OUT_2;
//    #define mLED_OUT_3_Toggle() mLED_OUT_3 = !mLED_OUT_3;
//    #define mLED_OUT_4_Toggle() mLED_OUT_4 = !mLED_OUT_4;
    #define mBUZZ_Toggle() 		mBUZZ = !mBUZZ;
    
    /** SWITCH *********************************************************/
    #define mInitAllSwitches()  TRISBbits.TRISB4=1;TRISBbits.TRISB5=1;//TRISBbits.TRISB6=1;

    //#define mInitSwitch3()      TRISBbits.TRISB4=1;
    #define mInitSwitch2()      TRISBbits.TRISB5=1;
    #define mInitSwitch1()      TRISBbits.TRISB4=1;
	
    //#define sw3                 !PORTBbits.RB6
    #define sw2                 !PORTBbits.RB5		// Invert the value to make it sensible...
    #define sw1                 !PORTBbits.RB4
  
	/************LCD power and backlight****************************/	
	#define mLCD_power_init()	LATD &= 0xF0; TRISD &= 0xF0;	// Make lower nibble of PORTD an output

    //#define mLCD_power          PORTDbits.RD2		Not required
    #define mLCD_backled        PORTDbits.RD3

	//#define mLCD_power_On()  	mLCD_power=1
	#define mLCD_backled_On()	mLCD_backled=1
	#define mLCD_backled_Off()	mLCD_backled=0
	#define mLCD_backled_toggle()	mLCD_backled=!mLCD_backled;

    /** POT ************************************************************/
    #define mInitPOT()          {TRISAbits.TRISA0=1;ADCON0=0x01;ADCON2=0x3C;ADCON2bits.ADFM = 1;}

	/******** DATA ACQUISITION CHANNELS********************************/
	// This makes AN0-AN4 & AN5-AN7 inputs. Sets ADCON1 = AN0-AN3 as analogue. Sets ADCON2 for 2Tad and Fosc/32
	#define mInitDAQ()			{TRISA&=0b0001111; ADCON1=0b00001011; ADCON2=0b10001010;} 	
	#define mInitAN0()          {ADCON0=0b00000001;}
	#define mInitAN1()          {ADCON0=0b00000101;}		                           
	#define mInitAN2()          {ADCON0=0b00001001;}
	#define mInitAN3()          {ADCON0=0b00001101;}
	#define mInitAN4()          {ADCON0=0b00010001;}
	#define mInitAN5()          {ADCON0=0b00010101;}
	#define mInitAN6()          {ADCON0=0b00011001;}
	#define mInitAN7()          {ADCON0=0b00011101;}															
    
    /** SPI : Chip Select Lines ****************************************/
	/** This is set in the max7219matt.c file***************************/

//  #define tris_cs_temp_sensor TRISBbits.TRISB2    // Output
//  #define cs_temp_sensor      LATBbits.LATB2

//	#define SW_CS_PIN         	PORTCbits.RC6      // Chip Select
//	#define TRIS_SW_CS_PIN    	TRISCbits.TRISC6

    /** USB external transceiver interface (optional) ******************/
    #define tris_usb_vpo        TRISBbits.TRISB3    // Output
    #define tris_usb_vmo        TRISBbits.TRISB2    // Output
    #define tris_usb_rcv        TRISAbits.TRISA4    // Input
    #define tris_usb_vp         TRISCbits.TRISC5    // Input
    #define tris_usb_vm         TRISCbits.TRISC4    // Input
    //#define tris_usb_oe         TRISCbits.TRISC1    // Output
    
    #define tris_usb_suspnd     TRISAbits.TRISA3    // Output
    
    /** TRIS ***********************************************************/
    #define INPUT_PIN           1
    #define OUTPUT_PIN          0

	/********LCD interface*********************************************/
	/****************SEE xlcd.h IN THE LCD FOLDER**********************/
	/******************************************************************/

#endif  //HARDWARE_PROFILE_MATT_DATALOGGER_H
