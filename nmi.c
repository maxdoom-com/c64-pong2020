#include "nmi.h"
#include <peekpoke.h>

/**
 * @brief      Set a callback for the NMI (Restore-Key)
 */
void nmi_set_callback( void (*fn)() )
{
    POKE(0x0318,((unsigned short) fn)&0x00FF); // LO
    POKE(0x0319,((unsigned short) fn)>>8); // HI
}

