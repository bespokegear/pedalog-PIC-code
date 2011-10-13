/***************************************************************
*
* Maxim-IC MAX7219 LED Display Driver - SOURCE
*
****************************************************************
*
* Filename:			max7219.c
*
* Dependencies:		max7219.h
*					spi.h
*
* Processor:		PIC18 (Tested on 18f4410)
*
* Compiler:			C18 3.20
*								
*/

/** INCLUDES ************************************************************************************/
#include <p18cxxx.h>		//This was my MCU change as needed
#include <spi.h>
//#include <delays.h>			//Can be omitted if you comment out the custom display test
#include "max7219matt.h"
#include <string.h>
#include <stdlib.h>

/** DEFINITIONS ********************************************************************************/
#define SPI_CS		(LATDbits.LATD2) //Chip-Select Pin (change as needed)

void MAX7219Write(unsigned char reg_address, unsigned char dataout);
void MAX7219SendByte(unsigned char dataout);
void MAX7219WriteValue(unsigned int value);
void MAX7219WriteValueDP(unsigned int value, int dp);
void MAX7219WriteStringDP(char string[5], int dp);

static unsigned char MAX7219_LookupCode(char character);

/*----------------------------------------------------------------------------------------------
Function and Routines
----------------------------------------------------------------------------------------------*/

/***********************************************************************************************
* 
* MAX7219 Display Init
*
************************************************************************************************/
void MAX7219Init(void)
{

	SPI_CS = 0; //Chip Select
	
	//Setup and open the SSP for SPI MASTER Mode 0,0
	OpenSPI(SPI_FOSC_16, MODE_00, SMPEND); 
	
	MAX7219Write(0x0B,4); 		//Set Scan limit: just 5 Digits
	
	//MAX7219Write(0x9,0x00);		//No decode
	MAX7219Write(0x9,0xFF);		//With B decode for all digits
	
	MAX7219_Wakeup();			//Normal operation
	
	MAX7219_StopDisplayTest();
	
	MAX7219Clear();				//Clear the Display
	
	MAX7219_SetBrightness(0x0f);	//Max brightness
	
}

/***********************************************************************************************
* 
* MAX7219 Write to display
*
************************************************************************************************/
void MAX7219Write(unsigned char reg_address, unsigned char dataout)
{

	SPI_CS = 0;		//send CS low to trasmit data
	
	MAX7219SendByte(reg_address);	//write register address
	MAX7219SendByte(dataout);		//write data	
	
	SPI_CS = 1;		//Send CS to high to latch in 16 bits of data
	
}

/***********************************************************************************************
* 
* MAX7219 put byte to SPI
*
************************************************************************************************/
void MAX7219SendByte(unsigned char dataout)
{

	putcSPI(dataout); //write the byte to the max7219 via SDO	
	
}

/***********************************************************************************************
* 
* MAX7219 Clear Display
*
************************************************************************************************/
void MAX7219Clear(void)
{

	char i;
	
	for(i=0;i<9;i++)
	{
	
		MAX7219Write(i,0x0F);	
		
	}	
	
}

/***********************************************************************************************
* 
* MAX7219 Character and Digit
*
************************************************************************************************/
void MAX7219DisplayChar(char digit, char character, int dP)
{

	unsigned char val;
	
	val = MAX7219_LookupCode(character);
	
	if(dP == 1)
	{
		val |= 0x80;
	}
		

	MAX7219Write(digit, val);
	
}

/***********************************************************************************************
* 
* MAX7219 Lookup routine for char to hex
*
************************************************************************************************/
static const struct {
	char   ascii;
	char   segs;
} MAX7219_Font[] = {
  {' ', 0x00},
  {'0', 0x7e},
  {'1', 0x30},
  {'2', 0x6d},
  {'3', 0x79},
  {'4', 0x33},
  {'5', 0x5b},
  {'6', 0x5f},
  {'7', 0x70},
  {'8', 0x7f},
  {'9', 0x7b},
  {'A', 0x77},
  {'B', 0x1f},
  {'C', 0x4e},
  {'D', 0x3d},
  {'E', 0x4f},
  {'F', 0x47},
  {'P', 0x67},
  {'.', 0x80},
  {'\0', 0x00}
};
static unsigned char MAX7219_LookupCode(char character)
{
  char i;
  for (i = 0; MAX7219_Font[i].ascii; i++)             // scan font table for ascii code
    if (character == MAX7219_Font[i].ascii)
      return MAX7219_Font[i].segs;                    // return segments code
  return 0;                                           // code not found, return null (blank)
}

/***********************************************************************************************
* 
* MAX7219 Shutdown display(power save)
*
************************************************************************************************/
void MAX7219_Shutdown(void)
{
	
	MAX7219Write(0x0c,0); //put display in shutdown
		
}

/***********************************************************************************************
* 
* MAX7219 Wakeup display
*
************************************************************************************************/
void MAX7219_Wakeup(void)
{

	MAX7219Write(0x0c,1); //put display in normal operation mode	
	
}

/***********************************************************************************************
* 
* MAX7219 Set the display brightness 1-15 levels
*
************************************************************************************************/
void MAX7219_SetBrightness(char brightness)
{

	brightness &= 0x0f;

	MAX7219Write(0x0a, brightness); //set brightness
	
}

/***********************************************************************************************
* 
* MAX7219 Start Display Test
*
************************************************************************************************/
void MAX7219_StartDisplayTest(void)
{
	
	MAX7219Write(0x0f, 1); //Start display test
	
}
/***********************************************************************************************
* 
* MAX7219 Stop Display Test
*
************************************************************************************************/
void MAX7219_StopDisplayTest(void)
{
	
	MAX7219Write(0x0f, 0); //Stop display test	
	
}

/***********************************************************************************************
* 
* MAX7219 Write full value to display
* This takes in an integer (Value) and displays it on the display display
*
************************************************************************************************/
void MAX7219WriteValue(unsigned int value)
{


/*****************Local variables****************************/

	char string[5];		// local holder for the int to string conversion
	int lengthdisplay;		// local display length
	int blanklength;				// Counter for the display 
	char i;
/************************************************************/
	//memset(&string,'\0',5);					// This line clears the string to get rid of anything left in there...
	itoa(value, string);				// Convert int into a string
	lengthdisplay=strlen(string);		// Check the length of the data
	blanklength=5-lengthdisplay;		// Calculate the number of digits to blank

	for (i=1;i<=blanklength;i++)
	{
		MAX7219Write(i,0x0F);  			// blank this display
	}
	for (i=blanklength+1;i<=5;i++)
	{
		MAX7219Write(i,string[i-blanklength-1]);  		// write the number to the display
	}

}

/***********************************************************************************************
* 
* MAX7219 Write full value to display with decimal point
* This takes in an integer (Value) and displays it on the display display
* This will add a decimal point to the digit given in dp
************************************************************************************************/
void MAX7219WriteValueDP(unsigned int value, int dp)
{


/*****************Local variables****************************/

	char string[5];		// local holder for the int to string conversion
	int lengthdisplay;		// local display length
	int blanklength;				// Counter for the display 
	char i;
	char val;
/************************************************************/
	//memset(&string,'\0',5);					// This line clears the string to get rid of anything left in there...
	itoa(value, string);				// Convert int into a string
	lengthdisplay=strlen(string);		// Check the length of the data
	blanklength=5-lengthdisplay;		// Calculate the number of digits to blank

	for (i=1;i<=blanklength;i++)
	{
		MAX7219Write(i,0x0F);  			// blank this display
	}
	for (i=blanklength+1;i<=5;i++)
	{
		val = string[i-blanklength-1];
		if(i==dp)
		{
			// Only add the decimal point to the digit which needs it
			val |= 0x80;
		}
		//MAX7219Write(i,string[i-blanklength-1]);  		// write the number to the display
		MAX7219Write(i,val);  		// write the number to the display
	}
}


/***********************************************************************************************
* 
* MAX7219 Write full string to display with decimal point
* This takes in a string (Value) and displays it on the display 
* This will add a decimal point to the digit given in dp
************************************************************************************************/

void MAX7219WriteStringDP(char string[5], int dp)
{


/*****************Local variables****************************/

	//char string[5];		// local holder for the int to string conversion
	int lengthdisplay;		// local display length
	int blanklength;				// Counter for the display 
	char i;
	char val;
/************************************************************/
	//memset(&string,'\0',5);					// This line clears the string to get rid of anything left in there...
	//itoa(value, string);				// Convert int into a string
	lengthdisplay=strlen(string);		// Check the length of the data
	blanklength=5-lengthdisplay;		// Calculate the number of digits to blank

	for (i=1;i<=blanklength;i++)
	{
		MAX7219Write(i,0x0F);  			// blank this display
	}
	for (i=blanklength+1;i<=5;i++)
	{
		val = string[i-blanklength-1];
		if(i==dp)
		{
			// Only add the decimal point to the digit which needs it
			val |= 0x80;
		}
		//MAX7219Write(i,string[i-blanklength-1]);  		// write the number to the display
		MAX7219Write(i,val);  		// write the number to the display
	}
}