#ifndef JOYSTICK_H
#define JOYSTICK_H

/***********************************************************************
 * Structures
 */

struct Joystick
{
    int up:1;
    int down:1;
    int left:1;
    int right:1;
    int fire:1;
    int _:3;
};


/***********************************************************************
 * Procedures
 */

struct Joystick joystick1();

struct Joystick joystick2();

struct Joystick both_joysticks();

void wait_any_fire();


#endif // JOYSTICK_H
