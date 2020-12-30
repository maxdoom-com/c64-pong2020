#include "intro.h"

#include <peekpoke.h>
#include <conio.h>

#include "screen.h"
#include "colors.h"
#include "game.h"
#include "timing.h"
#include "joystick.h"


/***********************************************************************
 * Ressources
 */

#include "logo.xbm"



/***********************************************************************
 * Redraw the menu
 */
void redraw_menu(unsigned char option)
{
    switch(player1.type)
    {
        case HUMAN:
            print(0, 10, "player #1: human", option==0 ? WHITE:GRAY);
            break;
        case WALL:
            print(0, 10, "player #1: wall ", option==0 ? WHITE:GRAY);
            break;
    }

    switch(player2.type)
    {
        case HUMAN:
            print(0, 11, "player #2: human", option==1 ? WHITE:GRAY);
            break;
        case WALL:
            print(0, 11, "player #2: wall ", option==1 ? WHITE:GRAY);
            break;
    }

    print(0, 12, "play", option==2 ? WHITE:GRAY);

    print(0, 13, "----------------", GRAY);
    print(0, 14, "end game", option==3 ? WHITE:GRAY);
}


// wait for the release of the up-trigger
void wait_for_release_of_up()
{
    struct Joystick j;
    do {
        j = both_joysticks();
    } while(j.up);
}

// wait for the release of the down-trigger
void wait_for_release_of_down()
{
    struct Joystick j;
    do {
        j = both_joysticks();
    } while(j.down);
}

// wait for the release of the fire buttons
void wait_for_release_of_fire()
{
    struct Joystick j;
    do {
        j = both_joysticks();
    } while(j.fire);
}



/***********************************************************************
 * The game intro
 */

unsigned char option = 2;

void show_intro()
{
    struct Joystick j;

    screen_off();
    upper_case_screen();
    
    hide_sprites();

    bordercolor(BLACK);
    bgcolor(BLACK);
    textcolor(BLUE);
    clrscr();

    poke_xbm_to_screen(logo_width, logo_height, logo_bits, 1024);
    cputsxy(32, 7, "2020");
    redraw_menu(option);
    screen_on();

    for(;;)
    {
        j = both_joysticks();

        if( ! j.up && ! j.down && ! j.fire )
        {
            continue;
        }

        if( j.up && option > 0 )
        {
            --option;
            redraw_menu(option);
            wait_for_release_of_up();
        }

        if( j.down && option < 3 )
        {
            ++option;
            redraw_menu(option);
            wait_for_release_of_down();
        }

        if( j.fire )
        {
            switch(option)
            {
                case 0:
                    if(++player1.type > WALL) player1.type = HUMAN;
                    redraw_menu(option);
                    wait_for_release_of_fire();
                    break;
                case 1:
                    if(++player2.type > WALL) player2.type = HUMAN;
                    redraw_menu(option);
                    wait_for_release_of_fire();
                    break;
                case 2:
                    wait_for_release_of_fire();
                    return; // to play game...
                    break;
                case 3:
                    wait_for_release_of_fire();
                    asm("jmp $FCE2");
                    break;
            }
        }
    }
}
