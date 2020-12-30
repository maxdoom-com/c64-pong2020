#include "timing.h"

/**
 * @brief      Delays execution by some cycles.
 */
void delay(unsigned short i)
{
    while( --i );
}

