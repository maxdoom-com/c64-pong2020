#ifndef GAME_H
#define GAME_H

/***********************************************************************
 * Game constants.
 */

// Range a paddle may move (y direction)
#define PADDLE_MINY  66 << 4
#define PADDLE_MAXY 200 << 4

// Initial paddle positions
#define PADDLE_INITIAL_Y            130 << 4
#define PADDLE_LEFT_INITIAL_X       24
#define PADDLE_LEFT_INITIAL_X_HI    0
#define PADDLE_RIGHT_INITIAL_X      334
#define PADDLE_RIGHT_INITIAL_X_HI   1

// Paddle y move speed
#define PADDLE_DY 8

// Range the ball may move (y direction)
// - BALL_MAXY differs from PADDLY_MAXY because the paddle is taller
#define BALL_MINY  66 << 4
#define BALL_MAXY 232 << 4

// Range the ball may move (x direction)
#define BALL_MINX 24 << 4
#define BALL_MAXX 335 << 4

// Initial ball position
#define BALL_INITIAL_X 180 << 4
#define BALL_INITIAL_Y 146 << 4

// Number of points to win a game
#define POINTS_TO_WIN 10

// An inverse whitespace
#define BLANK_INVERSE_BLOCK 32+128

// Maximum delta-y of the ball
#define BALL_DY_MIN -8
#define BALL_DY_MAX  8

// Delta-x move speed of the ball.
#define BALL_DX 8


/***********************************************************************
 * Structures
 */

enum {
    HUMAN = 0,
    WALL,
};

struct Player
{
    unsigned char points;
    unsigned short y;
    unsigned char type; // HUMAN|CPU|WALL
};

struct Ball
{
    // large (16 times the real values, because we are missing floating point operations)
    unsigned short x, y;
    signed short dx, dy;
};


/***********************************************************************
 * Globals
 */

extern struct Player player1;
extern struct Player player2;


/***********************************************************************
 * Procedures
 */

void play_game();

void init_sprites();

void wait_any_fire();

void show_sprites();

void hide_sprites();



#endif // GAME_H
