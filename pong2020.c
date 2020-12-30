#include <peekpoke.h>
#include "game.h"
#include "intro.h"
#include "nmi.h"


static void nmi_callback()
{
    hide_sprites();
    asm("jmp _main");
}

void main()
{
    nmi_set_callback(nmi_callback);

    init_sprites();
    for(;;)
    {
        show_intro();
        play_game();
    }
}
