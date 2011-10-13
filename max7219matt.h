/***************************************************************
*
* Maxim-IC MAX7219 LED Display Driver - HEADER
*
****************************************************************
*
* Filename:			max7219.h
* Dependencies:		See INCLUDES if any
* Processor:		PIC18 (Tested on 18f4410)
* Compiler:			C18 3.20
*
* Notes:			Code from EE Compendium (http://ee.cleversoul.com/max7219_source.html)
*					Code was tweaked to work wih C18
*								
*/

/** Public Prototypes ***************************************************/
void MAX7219Init(void);
void MAX7219Clear(void);
void MAX7219DisplayChar(char digit, char character, int dP);
void MAX7219_Shutdown(void);
void MAX7219_Wakeup(void);
void MAX7219_SetBrightness(char brightness);
void MAX7219_StartDisplayTest(void);
void MAX7219_StopDisplayTest(void);
void MAX7219WriteValue(unsigned int value);
