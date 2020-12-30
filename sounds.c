#include <peekpoke.h>
#include "sounds.h"
#include "timing.h"

void beep(unsigned short freq)
{
    // Reset
    unsigned short l;
    for(l=0xD400; l<0xD418; l++) POKE(l,0);

    // Make a tone
    POKE(0xD418,15);         // volume max 15
    POKE(0xD405,9);          // adsr
    // POKE(54276,17);         // wave form
    // delay(500);             // duration (blocking)
    POKE(0xD401,freq>>8);    // hi freq.
    POKE(0xD400,freq&0xFF);  // lo freq.
    POKE(0xD404,17);         // start!
    // delay(3000);            // release (blocking)
}


void scored()
{
    beep(8000);
}

void attention()
{
    beep(5000);delay(8000);
    beep(5000);delay(8000);
    beep(5000);delay(8000);
}

void ping()
{
    beep(3000);
}

void pong()
{
    beep(4000);
}

void bump()
{
    beep(2500);
}
