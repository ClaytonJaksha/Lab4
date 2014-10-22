#include <msp430g2553.h>
#include "pong.h"

extern void init();
extern void initNokia();
extern void clearDisplay();
extern void drawBlock(unsigned char row, unsigned char col);
extern void drawLine(unsigned char row, unsigned char col);

#define     TRUE            1
#define     FALSE           0
#define     UP_BUTTON       (P2IN & BIT5)
#define     DOWN_BUTTON     (P2IN & BIT4)
#define     AUX_BUTTON      (P2IN & BIT3)
#define     LEFT_BUTTON     (P2IN & BIT2)
#define     RIGHT_BUTTON    (P2IN & BIT1)

void main() {

    ball_t myBall={{SCREEN_WIDTH/2,SCREEN_HEIGHT/2},{INIT_VELOC_X,INIT_VELOC_Y},0}; //initialize the ball's position in the middle of the screen with a velocity of (8,5) and a radius of 3
    paddle_t myPaddle={4,5,3,1};
    unsigned long n = 0;
    unsigned long i = 0;
    unsigned char j = 0;
    IFG1=0; /* clear interrupt flag1 */
    WDTCTL=WDTPW+WDTHOLD; /* stop WD */


    init();
    initNokia();
    clearDisplay();
    drawBlock(myBall.position.y,myBall.position.x);
    myPaddle=createPaddle(SCREEN_HEIGHT/2,1);




    for (i=0;i<50;i++)
    {
        if (UP_BUTTON == 0) {
            myPaddle=createPaddle(myPaddle.y-1,myPaddle.radius);
        } else if (DOWN_BUTTON == 0) {
            myPaddle=createPaddle(myPaddle.y+1,myPaddle.radius);
        } else if (AUX_BUTTON == 0) {
            clearDisplay();
            while(AUX_BUTTON==0){
                for (j=1;j<7;j++){
                    drawBlock(j,0);
                }
                for (j=1;j<7;j++){
                    drawBlock(j,6);
                }
                for (j=1;j<7;j++){
                    drawBlock(j,10);
                }
                for (j=1;j<4;j++){
                    drawBlock(7,j);
                }
                for (j=7;j<10;j++){
                    drawBlock(7,j);
                }
                for (j=1;j<4;j++){
                    drawBlock(0,j);
                }
                for (j=7;j<10;j++){
                    drawBlock(0,j);
                }
                for (j=5;j<8;j++){
                    drawBlock(j,3);
                }
                for (j=2;j<5;j++){
                    drawBlock(5,j);
                }
            }
            clearDisplay();
            j=0;
            drawBlock(j,1);
            drawBlock(j,4);
            drawBlock(j,5);
            drawBlock(j,6);
            j=1;
            drawBlock(j,0);
            drawBlock(j,2);
            drawBlock(j,4);
            drawBlock(j,6);
            j=2;
            drawBlock(j,0);
            drawBlock(j,1);
            drawBlock(j,2);
            drawBlock(j,4);
            drawBlock(j,5);
            j=3;
            drawBlock(j,0);
            drawBlock(j,2);
            drawBlock(j,4);
            drawBlock(j,6);
            j=5;
            drawBlock(j,3);
            drawBlock(j,5);
            drawBlock(j,8);
            drawBlock(j,10);
            for (j=6;j<8;j++){
            drawBlock(j,2);
            drawBlock(j,4);
            drawBlock(j,6);
            drawBlock(j,9);
            }
            for (i=0; i<2000000; i++);
        }
        clearDisplay();
        for (j=0; j<11; j++)
        {
            drawBlock(j,PONG_WALL);
        }
        drawLine(myPaddle.y-myPaddle.radius,0);
        drawLine(myPaddle.y+myPaddle.radius,0);
        drawLine(myPaddle.y,0);
        myBall=moveBall(myBall,myPaddle); //infinite loop continuously moving the ball
        if (myBall.position.x>9000)
        {
            clearDisplay();
            j=0;
            drawBlock(j,2);
            drawBlock(j,3);
            drawBlock(j,4);
            drawBlock(j,5);
            drawBlock(j,6);
            drawBlock(j,7);
            j=1;
            drawBlock(j,3);
            drawBlock(j,4);
            drawBlock(j,5);
            drawBlock(j,6);
            drawBlock(j,7);
            j=2;
            drawBlock(j,4);
            drawBlock(j,6);
            drawBlock(j,7);
            drawBlock(j,8);
            j=3;
            drawBlock(j,3);
            drawBlock(j,4);
            drawBlock(j,7);
            drawBlock(j,8);
            j=4;
            drawBlock(j,2);
            drawBlock(j,3);
            drawBlock(j,4);
            drawBlock(j,5);
            drawBlock(j,6);
            drawBlock(j,7);
            drawBlock(j,8);
            drawBlock(j,9);
            j=5;
            drawBlock(j,2);
            drawBlock(j,3);
            drawBlock(j,4);
            drawBlock(j,5);
            drawBlock(j,6);
            drawBlock(j,7);
            drawBlock(j,8);
            drawBlock(j,9);
            j=6;
            drawBlock(j,1);
            drawBlock(j,2);
            drawBlock(j,3);
            drawBlock(j,7);
            drawBlock(j,8);
            drawBlock(j,9);
            drawBlock(j,10);
            j=7;
            drawBlock(j,0);
            drawBlock(j,1);
            drawBlock(j,2);
            drawBlock(j,8);
            drawBlock(j,9);
            drawBlock(j,10);
            while(1);
        }
        drawBlock(myBall.position.y,myBall.position.x);
        while (n < 250000)
        {
            n+=1;
        }
        n=0;
    }
    for (i=0;i<50;i++)
        {
            if (UP_BUTTON == 0) {
                myPaddle=createPaddle(myPaddle.y-1,myPaddle.radius);
            } else if (DOWN_BUTTON == 0) {
                myPaddle=createPaddle(myPaddle.y+1,myPaddle.radius);
            }  else if (AUX_BUTTON == 0) {
                clearDisplay();
                while(AUX_BUTTON==0){
                    for (j=1;j<7;j++){
                        drawBlock(j,0);
                    }
                    for (j=1;j<7;j++){
                        drawBlock(j,6);
                    }
                    for (j=1;j<7;j++){
                        drawBlock(j,10);
                    }
                    for (j=1;j<4;j++){
                        drawBlock(7,j);
                    }
                    for (j=7;j<10;j++){
                        drawBlock(7,j);
                    }
                    for (j=1;j<4;j++){
                        drawBlock(0,j);
                    }
                    for (j=7;j<10;j++){
                        drawBlock(0,j);
                    }
                    for (j=5;j<8;j++){
                        drawBlock(j,3);
                    }
                    for (j=2;j<5;j++){
                        drawBlock(5,j);
                    }
                }
                clearDisplay();
                j=0;
                drawBlock(j,1);
                drawBlock(j,4);
                drawBlock(j,5);
                drawBlock(j,6);
                j=1;
                drawBlock(j,0);
                drawBlock(j,2);
                drawBlock(j,4);
                drawBlock(j,6);
                j=2;
                drawBlock(j,0);
                drawBlock(j,1);
                drawBlock(j,2);
                drawBlock(j,4);
                drawBlock(j,5);
                j=3;
                drawBlock(j,0);
                drawBlock(j,2);
                drawBlock(j,4);
                drawBlock(j,6);
                j=5;
                drawBlock(j,3);
                drawBlock(j,5);
                drawBlock(j,8);
                drawBlock(j,10);
                for (j=6;j<8;j++){
                drawBlock(j,2);
                drawBlock(j,4);
                drawBlock(j,6);
                drawBlock(j,9);
                }
                for (i=0; i<2000000; i++);
            }
            clearDisplay();
            for (j=0; j<11; j++)
            {
                drawBlock(j,PONG_WALL);
            }
            drawLine(myPaddle.y-myPaddle.radius,0);
            drawLine(myPaddle.y+myPaddle.radius,0);
            drawLine(myPaddle.y,0);
            myBall=moveBall(myBall,myPaddle); //infinite loop continuously moving the ball
            if (myBall.position.x>9000)
                    {
                        clearDisplay();
                        j=0;
                        drawBlock(j,2);
                        drawBlock(j,3);
                        drawBlock(j,4);
                        drawBlock(j,5);
                        drawBlock(j,6);
                        drawBlock(j,7);
                        j=1;
                        drawBlock(j,3);
                        drawBlock(j,4);
                        drawBlock(j,5);
                        drawBlock(j,6);
                        drawBlock(j,7);
                        j=2;
                        drawBlock(j,4);
                        drawBlock(j,6);
                        drawBlock(j,7);
                        drawBlock(j,8);
                        j=3;
                        drawBlock(j,3);
                        drawBlock(j,4);
                        drawBlock(j,7);
                        drawBlock(j,8);
                        j=4;
                        drawBlock(j,2);
                        drawBlock(j,3);
                        drawBlock(j,4);
                        drawBlock(j,5);
                        drawBlock(j,6);
                        drawBlock(j,7);
                        drawBlock(j,8);
                        drawBlock(j,9);
                        j=5;
                        drawBlock(j,2);
                        drawBlock(j,3);
                        drawBlock(j,4);
                        drawBlock(j,5);
                        drawBlock(j,6);
                        drawBlock(j,7);
                        drawBlock(j,8);
                        drawBlock(j,9);
                        j=6;
                        drawBlock(j,1);
                        drawBlock(j,2);
                        drawBlock(j,3);
                        drawBlock(j,7);
                        drawBlock(j,8);
                        drawBlock(j,9);
                        drawBlock(j,10);
                        j=7;
                        drawBlock(j,0);
                        drawBlock(j,1);
                        drawBlock(j,2);
                        drawBlock(j,8);
                        drawBlock(j,9);
                        drawBlock(j,10);
                        while(1);
                    }
            drawBlock(myBall.position.y,myBall.position.x);
            while (n < 150000)
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
                    for (j=1;j<7;j++){
                        drawBlock(j,0);
                    }
                    for (j=1;j<7;j++){
                        drawBlock(j,6);
                    }
                    for (j=1;j<7;j++){
                        drawBlock(j,10);
                    }
                    for (j=1;j<4;j++){
                        drawBlock(7,j);
                    }
                    for (j=7;j<10;j++){
                        drawBlock(7,j);
                    }
                    for (j=1;j<4;j++){
                        drawBlock(0,j);
                    }
                    for (j=7;j<10;j++){
                        drawBlock(0,j);
                    }
                    for (j=5;j<8;j++){
                        drawBlock(j,3);
                    }
                    for (j=2;j<5;j++){
                        drawBlock(5,j);
                    }
                }
                clearDisplay();
                j=0;
                drawBlock(j,1);
                drawBlock(j,4);
                drawBlock(j,5);
                drawBlock(j,6);
                j=1;
                drawBlock(j,0);
                drawBlock(j,2);
                drawBlock(j,4);
                drawBlock(j,6);
                j=2;
                drawBlock(j,0);
                drawBlock(j,1);
                drawBlock(j,2);
                drawBlock(j,4);
                drawBlock(j,5);
                j=3;
                drawBlock(j,0);
                drawBlock(j,2);
                drawBlock(j,4);
                drawBlock(j,6);
                j=5;
                drawBlock(j,3);
                drawBlock(j,5);
                drawBlock(j,8);
                drawBlock(j,10);
                for (j=6;j<8;j++){
                drawBlock(j,2);
                drawBlock(j,4);
                drawBlock(j,6);
                drawBlock(j,9);
                }
                for (i=0; i<2000000; i++);
            }
            clearDisplay();
            for (j=0; j<11; j++)
            {
                drawBlock(j,PONG_WALL);
            }
            drawLine(myPaddle.y-myPaddle.radius,0);
            drawLine(myPaddle.y+myPaddle.radius,0);
            drawLine(myPaddle.y,0);
            myBall=moveBall(myBall,myPaddle); //infinite loop continuously moving the ball
            if (myBall.position.x>9000)
                    {
                        clearDisplay();
                        j=0;
                        drawBlock(j,2);
                        drawBlock(j,3);
                        drawBlock(j,4);
                        drawBlock(j,5);
                        drawBlock(j,6);
                        drawBlock(j,7);
                        j=1;
                        drawBlock(j,3);
                        drawBlock(j,4);
                        drawBlock(j,5);
                        drawBlock(j,6);
                        drawBlock(j,7);
                        j=2;
                        drawBlock(j,4);
                        drawBlock(j,6);
                        drawBlock(j,7);
                        drawBlock(j,8);
                        j=3;
                        drawBlock(j,3);
                        drawBlock(j,4);
                        drawBlock(j,7);
                        drawBlock(j,8);
                        j=4;
                        drawBlock(j,2);
                        drawBlock(j,3);
                        drawBlock(j,4);
                        drawBlock(j,5);
                        drawBlock(j,6);
                        drawBlock(j,7);
                        drawBlock(j,8);
                        drawBlock(j,9);
                        j=5;
                        drawBlock(j,2);
                        drawBlock(j,3);
                        drawBlock(j,4);
                        drawBlock(j,5);
                        drawBlock(j,6);
                        drawBlock(j,7);
                        drawBlock(j,8);
                        drawBlock(j,9);
                        j=6;
                        drawBlock(j,1);
                        drawBlock(j,2);
                        drawBlock(j,3);
                        drawBlock(j,7);
                        drawBlock(j,8);
                        drawBlock(j,9);
                        drawBlock(j,10);
                        j=7;
                        drawBlock(j,0);
                        drawBlock(j,1);
                        drawBlock(j,2);
                        drawBlock(j,8);
                        drawBlock(j,9);
                        drawBlock(j,10);
                        while(1);
                    }
            drawBlock(myBall.position.y,myBall.position.x);
            while (n < 60000)
            {
                n+=1;
            }
            n=0;
        }
}
