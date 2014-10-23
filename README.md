Lab 3
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

## Required Tables/Logic Analyzer



## Code Walkthrough



## Debugging



## Testing Methodology/Results



## Observations and Conclusion
#### Observations

* If a single step in SPI is messed up, the whole thing will not work.
* Outputting data is not as simple as writing to a port.


#### Conclusion

## Documentation

None


# GO ARMY, BEAT AIR FORCE
![alt text](http://coloradosportsreport.com/wp-content/uploads/2014/09/8157971746_51767b4c1d.jpg "GO ARMY, BEAT AIR FORCE")
