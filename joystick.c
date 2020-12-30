#include <peekpoke.h>
#include "joystick.h"

/**
 * @brief      Gets the joystick port 1 status.
 */
struct Joystick joystick1()
{
    return (struct Joystick) ((~PEEK(0xDC01)) & 0b00011111);
}


/**
 * @brief      Gets the joystick port 2 status.
 */
struct Joystick joystick2()
{
    return (struct Joystick) ((~PEEK(0xDC00)) & 0b00011111);
}


/**
 * @brief      Gets both joystick stati.
 */
struct Joystick both_joysticks()
{
    struct Joystick j1, j2;
    j1 = joystick1();
    j2 = joystick2();
    return (struct Joystick)(((unsigned char)j1)|((unsigned char)j2));
}


/**
 * @brief      Waits for a button press of any of the joysticks.
 */
void wait_any_fire()
{
    struct Joystick j1, j2;
    for(;;)
    {
        j1 = joystick1();
        j2 = joystick2();

        if(j1.fire) return;
        if(j2.fire) return;
    }
}
