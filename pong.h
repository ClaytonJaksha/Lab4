/*
 * pong.h
 * Author: CDT CLAYTON JAKSHA
 * Date: 10 Oct 2014
 * Description: Header file for pong. Declares functions and defines the ball structure.
 */

#ifndef 	_PONG_H
#define 	_PONG_H

#define 	TRUE 			1 //will be used for our collision flag
#define 	FALSE 			0 //same as above
#define 	SCREEN_WIDTH 	10 //screen parameters inserted here
#define 	SCREEN_HEIGHT 	8
#define 	INIT_VELOC_X 	1
#define 	INIT_VELOC_Y 	1
#define 	PONG_WALL 		11
#define     TRUE            1
#define     FALSE           0
#define     UP_BUTTON       (P2IN & BIT5)
#define     DOWN_BUTTON     (P2IN & BIT4)
#define     AUX_BUTTON      (P2IN & BIT3)
#define     LEFT_BUTTON     (P2IN & BIT2)
#define     RIGHT_BUTTON    (P2IN & BIT1)
#define		MIN_DELAY		50000
#define		MAX_DELAY		150000

//declare the functions from the Nokia display assembly file
extern void init();
extern void initNokia();
extern void clearDisplay();
extern void drawBlock(unsigned char row, unsigned char col);
extern void drawLine(unsigned char row, unsigned char col);

//used to build our velocity and position structure types
typedef struct {
    int x;
    int y;
} vector2d_t;

//ball structure type defined here
typedef struct {
    vector2d_t position;
    vector2d_t velocity;
    unsigned char radius;
} ball_t;

//paddle structure defined here
typedef struct {
    int y;
    int top;
    int bottom;
    int radius;
} paddle_t;

//here we declare all of our wonderful functions
ball_t createBall(int xPos, int yPos, int xVel, int yVel, unsigned char radius);

ball_t moveBall(ball_t ballToMove, paddle_t paddlePos);

paddle_t createPaddle(int yPos, int radius);

unsigned char collisionDetectTop(ball_t ball);

unsigned char collisionDetectBottom(ball_t ball);

unsigned char collisionDetectLeft(ball_t ball, paddle_t paddle);

unsigned char collisionDetectRight(ball_t ball);

void drawGo(unsigned long i, unsigned char j);

void drawArmy(unsigned long i, unsigned char j);

void drawArmyA(unsigned char j);

#endif
