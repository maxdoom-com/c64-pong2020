#ifndef SCREEN_H
#define SCREEN_H

// print a :text in a :color from [:x, :y]
void print(unsigned char x, unsigned char y, unsigned char *text, unsigned char color);

// Print a line of :characters with :color starting at [:x0, :y0]
// and increasing the position by :step bytes for :count times
// ie. printcline(2,3,10, 1,ord('a'),WHITE) ... will print a horizontal line
//     from x,y=2,3 to x,y=12,3 with the char 'a' in white
// ie. printcline(2,3,10,40,ord('a'),WHITE) ... will print a vertical line
//     from x,y=2,3 to x,y=2,13 with the char 'a' in white
void printcline(
    unsigned char x0,
    unsigned char y0,
    unsigned char count,
    unsigned char step,
    unsigned char character,
    unsigned char color
);

// poke an xml of :width and :height with :data
// herefore the *.xbm shall be directly included
// :start_at might be 1024 for the top left corner of the screen
// currently only xbms with a width of 40 are supported
void poke_xbm_to_screen(unsigned short width, unsigned short height, unsigned char *data, unsigned short start_at);

// hide the text screen
void screen_off();

// show the text screen
void screen_on();

// set text mode to capital and graphics characters
void upper_case_screen();

// set text mode to camel case characters and second graphics mode characters
void camel_case_screen();


#endif // SCREEN_H
