Lab 4
====
#### Clayton Jaksha | ECE 382 | Dr. York | M2A

## Objective and Purpose
### Objective

The objective of this lab is to manipulate the Nokia 1202 display with the MSP430 microcontroller by use of its front-panel buttons. We must create first an "etch-a-sketch" and then the Pong game on the display.

### Purpose

This lab practices looping, delay, external device interface, and polling in C.

## Preliminary Design

#### Etch-A-Sketch

Design for this lab consisted only of planning to remove the `clearDisplay()` function from the given code and then adding new variable `color` to determine whether we're adding or erasing blocks.

#### Pong

I designed this code by continuously checking the ball structure's position against the boundary of the screen and then changing (or maintaining) the velocity to suit that particular case. Futhermore, I added a paddle structure and edited the function which checks for a bounce against the left screen so a bounce would only register if it hit the location of the paddle. After meeting "A" functionality, I built some ARMY spirit into my design. If, during normal gameplay, the user presses `SW3`, the screen will flash the word "GO". Upon release, it displays "ARMY" and, after some delay, will return the user to gameplay. Futhermore, if the user loses, it will display the [Army A](http://upload.wikimedia.org/wikipedia/commons/thumb/4/4b/Army_A.svg/661px-Army_A.svg.png) on the screen. These are accomplished by polling the buttons each time the ball moves. Additionally, the ball's speed increases with time (i.e. the delay decreases over time).

## Code Walkthrough
We need to first include our microprocessor's library and the header file `pong.h` in order to include the functions we will reference in the `main()` loop. Also, we will declare and define the global variables `m`,`i`,`j` since they are used in all parts of the code.
#### Etch-A-Sketch
This first portion calls the MSP430 library and declares the functions found in `nokia_basic.asm`. Then it goes on to declare constants that wil be useful throughout the code.
```
#include <msp430g2553.h>

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
```
We begin the main loop here by defining some variables for the cursor and the color (black or clear) of the block we are drawing.
```
void main() {

	unsigned char	x, y, button_press;
	unsigned char   color=1;
```
Then, we initialize the MSP430 some more my stopping the watchdog timer and ensuring the button is unpressed at the beginning.
```
	// === Initialize system ================================================
	IFG1=0; /* clear interrupt flag1 */
	WDTCTL=WDTPW+WDTHOLD; /* stop WD */
	button_press = FALSE;
```
We then initialize the Nokia display, clear it, and call our two block drawing functions at x=4, y=4 before entering the infinite loop.
```
	init();
	initNokia();
	clearDisplay();
	x=4;		y=4;
	drawBlock(y,x);
	drawBlankBlock(y,x);
```
The first part of this infinite loop polls for button presses. If it finds one, it will move the x,y cursor in the appropriate direction and declare that a button has been pressed. `SW3` toggles the color with an `xor` command.
```
	while(1) {

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
				color=color ^ 1; // toggles color
			}
```
If we see that a button has been pressed, we will write a block at the new cursor location. Whether the block is black or white depends on the value of `color`, which is toggled earlier by `SW3`. We continue looping this infinitely.
```
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
```
#### Pong
```
#include <msp430g2553.h>
#include "pong.h"

unsigned long m = MAX_DELAY;
unsigned long i = 0;
unsigned char j = 0;
```

This is the beginning of the `main()` loop, where the Pong program will run from. We initialize our ball (well, really, it's a block) structure in the middle of the screen with a predefined velocity. Also we initialize our paddle with random values (they will be overwritten as the program further initializes). We also define some counters, stop the watchdog timer, and we're good to go!
```
void main() {
    ball_t myBall={{SCREEN_WIDTH/2,SCREEN_HEIGHT/2},{INIT_VELOC_X,INIT_VELOC_Y},0}; //initialize the ball's position in the middle of the screen with a velocity of (8,5)
    paddle_t myPaddle={4,5,3,1};
    unsigned long n = 0;
    IFG1=0; /* clear interrupt flag1 */
    WDTCTL=WDTPW+WDTHOLD; /* stop WD */
```
This portion of the code calls some of the assembly funcitons defined in `nokia.asm` to initalize the display, clear the display, and then it draws our block in the middle of the screen and actually initializes our paddle on the far left of the screen.
```
    init();
    initNokia();
    clearDisplay();
    drawBlock(myBall.position.y,myBall.position.x);
    myPaddle=createPaddle(SCREEN_HEIGHT/2,1);
```
This loop does the bulk of the work for Pong gameplay. It first polls `SW5` (the up button) and `SW4` (the down button) to see if they're pressed. Depending on which is pressed, it will move the paddle in the corresponding direction. If `SW3` is pressed, it will do the whole "GO ARMY" thing on the screen. `m` is the ever decreasing amount of delay; the delay goes down by 1000 every cycle. This causes the ball movement to speed up significantly as the game progresses. 

If the user misses the ball with their paddle, it breaks from the loop, getting trapped in `while(1)` and displaying the Army A.
```
    while (m > MIN_DELAY)
    {
        if (UP_BUTTON == 0) {
            myPaddle=createPaddle(myPaddle.y-1,myPaddle.radius);
        } else if (DOWN_BUTTON == 0) {
            myPaddle=createPaddle(myPaddle.y+1,myPaddle.radius);
        } else if (AUX_BUTTON == 0) {
    		clearDisplay();
        	while(AUX_BUTTON==0){
        		drawGo(i,j);
        	}
        		clearDisplay();
        		drawArmy(i,j);
        }
        clearDisplay();
        for (j=0; j<11; j++)
        {
            drawBlock(j,PONG_WALL);
        }
        for (j=myPaddle.bottom; j<=myPaddle.top; j++)
        {
        	drawLine(j,0);
        }
        myBall=moveBall(myBall,myPaddle); //infinite loop continuously moving the ball
        if (myBall.position.x>9000)
        {
            clearDisplay();
            drawArmyA(j); // draws the Army A upon losing the game
            break;
        }
        drawBlock(myBall.position.y,myBall.position.x);
        m-=1000;
        while (n < m)
        {
            n+=1;
        }
        n=0;
    }
```
At some point, it goes so fast that one can hardly react, for this reason we have a `MIN_DELAY`. If the delay tries to go below this, then we just hold at that value. This loop does the same thing as the one above.
```
    while(1)
        {
            if (UP_BUTTON == 0) {
                myPaddle=createPaddle(myPaddle.y-1,myPaddle.radius);
            } else if (DOWN_BUTTON == 0) {
                myPaddle=createPaddle(myPaddle.y+1,myPaddle.radius);
            }  else if (AUX_BUTTON == 0) {
        		clearDisplay();
            	while(AUX_BUTTON==0){
            		drawGo(i,j);
            	}
            		clearDisplay();
            		drawArmy(i,j);
            }
            clearDisplay();
            for (j=0; j<11; j++)
            {
                drawBlock(j,PONG_WALL);
            }
            for (j=myPaddle.bottom; j<=myPaddle.top; j++)
            {
            	drawLine(j,0);
            }
            myBall=moveBall(myBall,myPaddle); //infinite loop continuously moving the ball
            if (myBall.position.x>9000)
                    {
                        clearDisplay();
                        drawArmyA(j); //draws the Army A upon losing the game
                        break;
                    }
            drawBlock(myBall.position.y,myBall.position.x);
            while (n < MIN_DELAY)
            {
                n+=1;
            }
            n=0;
        }
    while(1); //trap the processor upon completion
}
```



## Debugging

Debugging was primarily done by looking at the Nokia 1202 display and the stored register and expression values within CCS-6.0's debugging feature.

## Testing Methodology/Results

#### Testing Methodology

#### Results
The code works!
##### Basic Functionality
###### I drew this spiral-looking-thing by just moving my cursors around... like an etch-a-sketch!
![alt text](http://i.imgur.com/FkbkF9i.jpg "BEAT NAVY!!!")
###### By pressing `SW3`, I toggled to the erase mode and marched diagonally from the bottom-right to the top-left of the screen, leaving a trail of destruction behind me.
![alt text](http://i.imgur.com/580j6ZV.jpg "BEAT NAVY!!!")
##### B Functionality
B functionality is required for A functionality to work. Therefore, if A functionality works, B functionality must also work. I demonstrate A functionality below.
##### A Functionality
###### We see that the ball moves through the screen, a big wall is on the right, and the paddle is on the left.
![alt text](http://i.imgur.com/z7bVnnp.jpg "It's a bird! It's a plane!")
###### We see that the ball bounced off of the top and the paddle moved downward, two important parts of A functionality. (It looks like the paddle will miss the ball though!)
![alt text](http://i.imgur.com/BTUGl2Z.jpg "It's PONG!!!")
##### Bonus Functionality
###### Here we see the "GO" functionality. When `SW3` is pressed mid-game, the display looks like it would below as long as the button is held.
![alt text](http://i.imgur.com/JOMXSLg.jpg "GO ARMY")
###### After `SW3` is released, the display switches from "GO" to "ARMY" and then delays for a short period (in order to give the user time to let the message sink in).
![alt text](http://i.imgur.com/5DsCJyo.jpg "BEAT AIR FORCE")
###### If the user loses the game (by missing the ball with the paddle), the Army A will flash on the screen, asserting its dominance over the user.
![alt text](http://i.imgur.com/DbWHULP.jpg "BEAT NAVY!!!")

## Observations and Conclusion
#### Observations

* Reusing previous .c and .h files can make coding faster and modular.
* Writing fine values onto a screen is difficult.
* Structures and fun and easy to use. They enable a group of information to be stored in an organized manner.

#### Conclusion

The etch-a-sketch and pong funcitons worked according to specs. Army is fully prepared to beat Air Force next week.

## Documentation

None


# [ON BRAVE OL' ARMY TEAM!](http://www.youtube.com/watch?v=-HNz02SNTLY)
![alt text](http://usarmy.vo.llnwd.net/e2/c/images/2011/11/07/226002/size0.jpg "GO ARMY, BEAT AIR FORCE")
