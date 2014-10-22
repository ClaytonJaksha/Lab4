/*
 * pong.c
 * Author: CDT CLAYTON JAKSHA
 * Date: 10 Oct 2014
 * Description: Defines the functions (all nested within moveBall) that are necessary to
 *              make the pong game ball movement and bouncing functional.
 */
#include "pong.h"

//creates a ball structure. The arguments are passed onto the ball.
ball_t createBall(int xPos, int yPos, int xVel, int yVel, unsigned char radius)
{
    ball_t newBall;
    newBall.position.x=xPos;
    newBall.position.y=yPos;
    newBall.velocity.x=xVel;
    newBall.velocity.y=yVel;
    newBall.radius=radius;
    return newBall;
}

paddle_t createPaddle(int yPos, int radius)
{
    paddle_t newPaddle;
    newPaddle.y=yPos;
    newPaddle.radius=radius;
    newPaddle.top=yPos+radius;
    newPaddle.bottom=yPos-radius;
    return newPaddle;
}
//This function is the meatiest function here. Given a ball, it will create a new ball with the ball's given parameters.
ball_t moveBall(ball_t ballToMove, paddle_t paddlePos)
{
    ball_t newBall;
    unsigned char top=collisionDetectTop(ballToMove);
    unsigned char bottom=collisionDetectBottom(ballToMove);
    unsigned char left=collisionDetectLeft(ballToMove, paddlePos);
    unsigned char right=collisionDetectRight(ballToMove);
    if (left==2)
    {
        newBall=createBall(9001,9001,9001,9001,9001);
    }
    else if ((bottom==TRUE)&&(left==FALSE||right==FALSE)) //since we just reverse the ball's vertical velocity whenever it hits the bottom or top, we'll just create a new ball with those properties
    {
        newBall=createBall(ballToMove.velocity.x+ballToMove.position.x,-INIT_VELOC_Y+ballToMove.position.y,ballToMove.velocity.x,-INIT_VELOC_Y,ballToMove.radius);
    }else if ((top==TRUE)&&(left==FALSE||right==FALSE)) //since we just reverse the ball's vertical velocity whenever it hits the bottom or top, we'll just create a new ball with those properties
    {
        newBall=createBall(ballToMove.velocity.x+ballToMove.position.x,INIT_VELOC_Y+ballToMove.position.y,ballToMove.velocity.x,INIT_VELOC_Y,ballToMove.radius);
    }else if ((top==FALSE||bottom==FALSE)&&(left==TRUE)) //same as above, just when it hits the left or right side we reverse its horizontal velocity
    {
        newBall=createBall(INIT_VELOC_X+ballToMove.position.x,ballToMove.velocity.y+ballToMove.position.y,INIT_VELOC_X,ballToMove.velocity.y,ballToMove.radius);
    }else if ((top==FALSE||bottom==FALSE)&&(right==TRUE)) //same as above, just when it hits the left or right side we reverse its horizontal velocity
    {
        newBall=createBall(-INIT_VELOC_X+ballToMove.position.x,ballToMove.velocity.y+ballToMove.position.y,-INIT_VELOC_X,ballToMove.velocity.y,ballToMove.radius);
    }else if ((top==TRUE)&&(left==TRUE)) //same as above, just when it hits the left or right side we reverse its horizontal velocity
    {
        newBall=createBall(INIT_VELOC_X+ballToMove.position.x,INIT_VELOC_Y+ballToMove.position.y,INIT_VELOC_X,INIT_VELOC_Y,ballToMove.radius);
    }else if ((top==TRUE)&&(right==TRUE)) //same as above, just when it hits the left or right side we reverse its horizontal velocity
    {
        newBall=createBall(-INIT_VELOC_X+ballToMove.position.x,INIT_VELOC_Y+ballToMove.position.y,-INIT_VELOC_X,INIT_VELOC_Y,ballToMove.radius);
    }else if ((bottom==TRUE)&&(left==TRUE)) //same as above, just when it hits the left or right side we reverse its horizontal velocity
    {
        newBall=createBall(INIT_VELOC_X+ballToMove.position.x,-INIT_VELOC_Y+ballToMove.position.y,INIT_VELOC_X,-INIT_VELOC_Y,ballToMove.radius);
    }else if ((bottom==TRUE)&&(right==TRUE)) //same as above, just when it hits the left or right side we reverse its horizontal velocity
    {
        newBall=createBall(-INIT_VELOC_X+ballToMove.position.x,-INIT_VELOC_Y+ballToMove.position.y,-INIT_VELOC_X,-INIT_VELOC_Y,ballToMove.radius);
    }else //if it doesn't hit anything, we just let it move
    {
        newBall=createBall(ballToMove.velocity.x+ballToMove.position.x,ballToMove.velocity.y+ballToMove.position.y,ballToMove.velocity.x,ballToMove.velocity.y,ballToMove.radius);
    }
    return newBall;
}
/*
 * each of the following collision detectors just looks to see if the edge of the ball (defined as the center + radius) is
 * at the edge of the screen or greater. If it is; we return a TRUE flag. IF it's not, we'll return a FALSE flag.
 */
unsigned char collisionDetectTop(ball_t ball)
{
    unsigned char collbit=FALSE;
    if (ball.position.y<=0)
    {
        collbit=TRUE;
        return collbit;
    }else
    {
        collbit=FALSE;
        return collbit;
    }
}

unsigned char collisionDetectBottom(ball_t ball)
{
    unsigned char collbit=FALSE;
        if ((ball.position.y+ball.radius)>=SCREEN_HEIGHT)
        {
            collbit=TRUE;
            return collbit;
        }else
        {
            collbit=FALSE;
            return collbit;
        }
}

unsigned char collisionDetectLeft(ball_t ball,paddle_t paddle)
{
    unsigned char collbit=FALSE;
        if ((ball.position.x-ball.radius)<=0)
        {
           if ((ball.position.y<=paddle.top)&&(ball.position.y>=paddle.bottom))
           {
               collbit=TRUE;
               return collbit;
           }
           else
           {
               collbit=2;
               return collbit;
           }
        }else
        {
            collbit=FALSE;
            return collbit;
        }
}

unsigned char collisionDetectRight(ball_t ball)
{
    unsigned char collbit=FALSE;
        if ((ball.position.x+ball.radius)>=SCREEN_WIDTH)
        {
            collbit=TRUE;
            return collbit;
        }else
        {
            collbit=FALSE;
            return collbit;
        }
}
