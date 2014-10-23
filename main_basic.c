#include <msp430g2553.h>

//This first portion calls the MSP430 library and declares the functions found in nokia_basic.asm. Then it goes on to declare constants that wil be useful throughout the code.
extern void init();
extern void initNokia();
extern void clearDisplay();
extern void drawBlock(unsigned char row, unsigned char col);

#define		TRUE			1
#define		FALSE			0
#define		UP_BUTTON		(P2IN & BIT5)
#define		DOWN_BUTTON		(P2IN & BIT4)
#define		AUX_BUTTON		(P2IN & BIT3)
#define		LEFT_BUTTON		(P2IN & BIT2)
#define		RIGHT_BUTTON	(P2IN & BIT1)
#define		BLACK			1
#define		WHITE			0

//We begin the main loop here by defining some variables for the cursor and the color (black or clear) of the block we are drawing.

void main() {

	unsigned char	x, y, button_press;
	unsigned char   color=1;

//Then, we initialize the MSP430 some more my stopping the watchdog timer and ensuring the button is unpressed at the beginning
	
	IFG1=0; /* clear interrupt flag1 */
	WDTCTL=WDTPW+WDTHOLD; /* stop WD */
	button_press = FALSE;

// initialize screen display
	init();
	initNokia();
	clearDisplay();
	x=4;		y=4;
	drawBlock(y,x);
	drawBlankBlock(y,x);

	while(1) {
			//these conditionals check for button presses and then move the cursor
			if (UP_BUTTON == 0) {
				while(UP_BUTTON == 0);
				if (y>=1) y=y-1;
				button_press = TRUE;
			} else if (DOWN_BUTTON == 0) {
				while(DOWN_BUTTON == 0);
				if (y<=6) y=y+1;
				button_press = TRUE;
			} else if (LEFT_BUTTON == 0) {
				while(LEFT_BUTTON == 0);
				if (x>=1) x=x-1;
				button_press = TRUE;
			} else if (RIGHT_BUTTON == 0) {
				while(RIGHT_BUTTON == 0);
				if (x<=10) x=x+1;
				button_press = TRUE;
			} else if (AUX_BUTTON == 0) {
				while(AUX_BUTTON == 0);
				color=color ^ 1;
			}
			//draws the block if it needs to be drawn
			if (button_press) {
				button_press = FALSE;
				//clearDisplay();
				if (color==1)
				{
	                	drawBlock(y,x);
				} else
				{
	                	drawBlankBlock(y,x);
				}
			}
		}
}
