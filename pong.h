/*
 * pong.h
 * Author: CDT CLAYTON JAKSHA
 * Date: 10 Oct 2014
 * Description: Header file for pong. Declares functions and defines the ball structure.
 */

#ifndef _PONG_H
#define _PONG_H
#define TRUE 1 //will be used for our collision flag
#define FALSE 0 //same as above
#define SCREEN_WIDTH 10 //screen parameters inserted here
#define SCREEN_HEIGHT 8
#define INIT_VELOC_X 1
#define INIT_VELOC_Y 1
#define PONG_WALL 11

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

#endif
