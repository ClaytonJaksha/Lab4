/*
* main.c
* Author: CDT CLAYTON JAKSHA
* Date: 21 Oct 2014
* Description: makes the Pong game on your display
*/

#include <msp430g2553.h>
#include "pong.h"

unsigned long m = MAX_DELAY;
unsigned long i = 0;
unsigned char j = 0;


//This is the beginning of the main() loop, where the Pong program will run from. We initialize our ball (well, really, it's a block) structure in the middle of the screen with a predefined velocity. Also we initialize our paddle with random values (they will be overwritten as the program further initializes). We also define some counters, stop the watchdog timer, and we're good to go!

void main() {

    ball_t myBall={{SCREEN_WIDTH/2,SCREEN_HEIGHT/2},{INIT_VELOC_X,INIT_VELOC_Y},0}; //initialize the ball's position in the middle of the screen with a velocity of (1,1)
    paddle_t myPaddle={4,5,3,1};
    unsigned long n = 0;
    IFG1=0; /* clear interrupt flag1 */
    WDTCTL=WDTPW+WDTHOLD; /* stop WD */

//This portion of the code calls some of the assembly funcitons defined in nokia.asm to initalize the display, clear the display, and then it draws our block in the middle of the screen and actually initializes our paddle on the far left of the screen.

    init();
    initNokia();
    clearDisplay();
    drawBlock(myBall.position.y,myBall.position.x);
    myPaddle=createPaddle(SCREEN_HEIGHT/2,1);

This loop does the bulk of the work for Pong gameplay. It first polls SW5 (the up button) and SW4 (the down button) to see if they're pressed. Depending on which is pressed, it will move the paddle in the corresponding direction. If SW3 is pressed, it will do the whole "GO ARMY" thing on the screen. m is the ever decreasing amount of delay; the delay goes down by 1000 every cycle. This causes the ball movement to speed up significantly as the game progresses.

//If the user misses the ball with their paddle, it breaks from the loop, getting trapped in while(1) and displaying the Army A.

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
            drawArmyA(j);
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
                        drawArmyA(j);
                        break;
                    }
            drawBlock(myBall.position.y,myBall.position.x);
            while (n < MIN_DELAY)
            {
                n+=1;
            }
            n=0;
        }
    while(1);
}

