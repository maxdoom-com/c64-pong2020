#include "game.h"

#include "sprites.h"
#include "colors.h"
#include "sounds.h"
#include "screen.h"
#include "timing.h"
#include "joystick.h"

#include <peekpoke.h>
#include <conio.h>


/***********************************************************************
 * Globals
 */

struct Player player1;
struct Player player2;
struct Ball ball;


/***********************************************************************
 * Procedures
 */

signed short random_ball_dx()
{
    return PEEK(0xA2)%2 ? BALL_DX : -BALL_DX;
}

signed short random_ball_dy()
{
    return PEEK(0xA2)%2 ? BALL_DX>>2 : -BALL_DX>>2;
}


void update_ball()
{
    sprite_positions->sprite2x = ball.x >> 4;
    sprite_positions->sprite2y = ball.y >> 4;
    sprite_positions_high->sprite2 = ball.x > 255*16 ? 1:0;
}


void update_paddles()
{
    sprite_positions->sprite0y = player1.y >> 4;
    sprite_positions->sprite1y = player2.y >> 4;
}


void set_initial_positions()
{
    ball.x = BALL_INITIAL_X;
    ball.y = BALL_INITIAL_Y;
    ball.dx = random_ball_dx();
    ball.dy = 0;
    
    if( player1.type == WALL && player2.type == WALL )
    {
        ball.dy = random_ball_dy();
    }

    update_ball();

    player1.y = PADDLE_INITIAL_Y;
    player2.y = PADDLE_INITIAL_Y;
    update_paddles();

    // x-positions of the paddles
    sprite_positions->sprite0x = PADDLE_LEFT_INITIAL_X  % 256;
    sprite_positions->sprite1x = PADDLE_RIGHT_INITIAL_X % 256;
    sprite_positions_high->sprite0 = PADDLE_LEFT_INITIAL_X_HI;
    sprite_positions_high->sprite1 = PADDLE_RIGHT_INITIAL_X_HI;
}


void init_sprites()
{
    unsigned char b;

    // setting the sprites bank to use
    sprites_bank->sprite0 = 13;
    sprites_bank->sprite1 = 13;
    sprites_bank->sprite2 = 14;

    // sprites 0, 1
    for(b=0; b<=62; b++)
    {
        POKE(sprites_bank->sprite0 * 64 + b, 0);
    }
    for(b=0; b<=62; b+=3)
    {
        POKE(sprites_bank->sprite0 * 64 + b, 255);
    }

    // sprite 2
    for(b=0; b<=62; b++)
    {
        POKE(sprites_bank->sprite2 * 64 + b, 0);
    }
    for(b=0; b<=8*3; b+=3)
    {
        POKE(sprites_bank->sprite2 * 64 + b, 255);
    }

    // double size
    sprites_double_height->sprite0 = 1;
    sprites_double_height->sprite1 = 1;
    sprites_double_height->sprite2 = 0;

    // position the sprites
    set_initial_positions();

    // colors
    sprite_colors->sprite0 = WHITE;
    sprite_colors->sprite1 = WHITE;
    sprite_colors->sprite2 = YELLOW;
}


void show_sprites()
{
    sprites_enabled->sprite0 = (player1.type != WALL);
    sprites_enabled->sprite1 = (player2.type != WALL);
    sprites_enabled->sprite2 = 1;
}


void hide_sprites()
{
    sprites_enabled->sprite0 = 0;
    sprites_enabled->sprite1 = 0;
    sprites_enabled->sprite2 = 0;
}




void draw_board()
{
    bordercolor(BLACK);
    bgcolor(BLACK);
    textcolor(WHITE);
    clrscr();

    printcline( 0,  1, 40, 1, BLANK_INVERSE_BLOCK, BLUE);
    printcline( 0, 24, 40, 1, BLANK_INVERSE_BLOCK, BLUE);

    printcline( 19, 2, 22, 40, 7*16+6, LIGHTBLUE);
    printcline( 20, 2, 22, 40, 7*16+5, LIGHTBLUE);

    if( player1.type == WALL )
    {
        printcline( 0, 2, 22, 40, BLANK_INVERSE_BLOCK, BLUE);
    }
    if( player2.type == WALL )
    {
        printcline( 39, 2, 22, 40, BLANK_INVERSE_BLOCK, BLUE);
    }

    cputsxy(0, 0, "pong 2020");

    if( player1.type == WALL && player2.type == WALL )
    {
        cputsxy(14, 24, "fire to exit");
    }
}


void draw_score()
{
    gotoxy(17, 0); cprintf("%02i", player1.points);
    gotoxy(21, 0); cprintf("%02i", player2.points);
}


void play_game()
{
    unsigned char game_over;
    unsigned char playing;
    unsigned char collison;

    struct Joystick j1, j2;

    screen_off();
    draw_board();
    show_sprites();
    screen_on();

    playing = 0;
    game_over = 0;
    player1.points = 0;
    player2.points = 0;
    set_initial_positions();
    draw_score();

    for(;;)
    {

        /***************************************************************
         * Game over test
         */
        if( game_over )
        {
            unsigned char push_a_button_line_y = 20;

            cputsxy( 23, 15, "game over");

            if( player1.points > player2.points )
            {
                if( player1.type == HUMAN )
                {
                    cputsxy( 23, 17, "player 1 wins");
                }
                else
                {
                    cputsxy( 23, 17, "the left wall");
                    cputsxy( 23, 18, "wins");
                    ++push_a_button_line_y;
                }
            }
            else
            {
                if( player2.type == HUMAN )
                {
                    cputsxy( 23, 17, "player 2 wins");
                }
                else
                {
                    cputsxy( 23, 17, "the right wall");
                    cputsxy( 23, 18, "wins");
                    ++push_a_button_line_y;
                }
            }

            cputsxy( 23, push_a_button_line_y, "push a button");

            wait_any_fire();
            return;
        }

        /***************************************************************
         * Paddle movement
         */
        j1 = joystick1();
        j2 = joystick2();

        if( j1.up )
        {
            if( (player1.y-=PADDLE_DY) < PADDLE_MINY) player1.y = PADDLE_MINY;
        }
        if( j1.down )
        {
            if( (player1.y+=PADDLE_DY) > PADDLE_MAXY) player1.y = PADDLE_MAXY;
        }

        if( j2.up )
        {
            if( (player2.y-=PADDLE_DY) < PADDLE_MINY) player2.y = PADDLE_MINY;
        }
        if( j2.down )
        {
            if( (player2.y+=PADDLE_DY) > PADDLE_MAXY) player2.y = PADDLE_MAXY;
        }

        update_paddles();

        if( ! playing )
        {
            /***********************************************************
             * Stop here, if not playing ball.
             */
            draw_score();
            if( player1.points >= POINTS_TO_WIN || player2.points >= POINTS_TO_WIN )
            {
                game_over = 1;
                continue;
            }
            // bordercolor(DARKGRAY);
            
            delay(15000);
            attention();

            // bordercolor(BLACK);
            playing = 1;
        }
        else
        {
            /***********************************************************
             * If ball moves!
             */

            // Update the ball position.
            ball.x += ball.dx;
            ball.y += ball.dy;

            // Ball reflections on top and bottom border.
            if( ball.y > BALL_MAXY || ball.y < BALL_MINY )
            {
                ball.dy = -ball.dy;
                bump();
            }

            // Has the ball been missed?
            if( ball.x <= BALL_MINX )
            {
                player2.points ++;
                playing = 0;
                set_initial_positions();
                scored();
            }
            if( ball.x >= BALL_MAXX )
            {
                player1.points ++;
                playing = 0;
                set_initial_positions();
                scored();
            }

            // If the left player is a wall.
            if( player1.type == WALL )
            {
                if( ball.x <= (PADDLE_LEFT_INITIAL_X+6)<<4 )
                {
                    pong();

                    // Reflect the ball
                    ball.x -= ball.dx;
                    ball.dx = -ball.dx;
                }
            }

            // If the right player is a wall.
            if( player2.type == WALL )
            {
                if( ball.x >= (PADDLE_RIGHT_INITIAL_X-6)<<4 )
                {
                    ping();

                    // Reflect the ball
                    ball.x -= ball.dx;
                    ball.dx = -ball.dx;
                }
            }

            // Wait for a fire button, if playing with NO humans.
            if( player1.type == WALL && player2.type == WALL )
            {
                if( j1.fire || j2.fire )
                {
                    return;
                }
            }

            // If the ball collides with a paddle...
            if( (collison = PEEK(0xD01E)) )
            {
                if( collison == 0b00000110 )
                {
                    // on the right side
                    if( ball.dx > 0 )
                    {
                        signed char vertical_difference;

                        ping();

                        // Reflect the ball
                        ball.dx = -ball.dx;

                        // Change the delta-y of the ball.
                        vertical_difference = sprite_positions->sprite2y - sprite_positions->sprite1y - 16;
                        ball.dy += vertical_difference >> 1;
                        if( ball.dy < BALL_DY_MIN ) ball.dy = BALL_DY_MIN;
                        if( ball.dy > BALL_DY_MAX ) ball.dy = BALL_DY_MAX;
                    }
                }
                else
                {
                    // on the left side
                    if( ball.dx < 0 )
                    {
                        signed char vertical_difference;

                        pong();

                        // Reflect the ball
                        ball.dx = -ball.dx;
                        
                        // Change the delta-y of the ball.
                        vertical_difference = sprite_positions->sprite2y - sprite_positions->sprite0y - 16;
                        ball.dy += vertical_difference >> 1;
                        if( ball.dy < BALL_DY_MIN ) ball.dy = BALL_DY_MIN;
                        if( ball.dy > BALL_DY_MAX ) ball.dy = BALL_DY_MAX;
                    }

                }
            }

            // Update the position of the ball.
            update_ball();

            // Do a little delay.
            delay(25);
        }
    }
}

