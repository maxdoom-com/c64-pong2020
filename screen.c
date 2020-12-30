#include "screen.h"

#include <peekpoke.h>
#include <conio.h>


void print(unsigned char x, unsigned char y, unsigned char *text, unsigned char color)
{
    unsigned short p, length;
    unsigned char *s;

    s = text;
    length = 0;
    while(*s++)++length;

    cputsxy(x, y, text);
    
    for(p=0xD800+40*y+x; p<0xD800+40*y+x+length; p++) POKE(p, color);
}


void printcline(
    unsigned char x0,
    unsigned char y0,
    unsigned char count,
    unsigned char step,
    unsigned char character,
    unsigned char color)
{
    unsigned short w;
    for(w=0; w<count*step; w+=step)
    {
        POKE(0x0400+y0*40+x0+w, character);
        POKE(0xD800+y0*40+x0+w, color);
    }
}


void poke_xbm_to_screen(unsigned short width, unsigned short height, unsigned char *data, unsigned short start_at)
{
    unsigned short i, j, position;

    position = start_at;

    for(i=0; i<width*height/8; i++)
    {
        for(j=0; j<8; j++)
        {
            POKE(position, ((data[i]>>j)&0b00000001) ? 32+128:32);
            position += 1;
        }
    }
}

void screen_off()
{
    POKE( 0xD011, PEEK(0xD011) & 0b11101111 );
}

void screen_on()
{
    POKE( 0xD011, PEEK(0xD011) | 0b00010000 );
}

void upper_case_screen()
{
    POKE(0xD018,21);
}

void camel_case_screen()
{
    POKE(0xD018,23);
}
