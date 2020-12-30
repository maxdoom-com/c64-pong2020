#ifndef SPRITES_H
#define SPRITES_H

struct SpriteBitField
{
    int sprite0:1;
    int sprite1:1;
    int sprite2:1;
    int sprite3:1;
    int sprite4:1;
    int sprite5:1;
    int sprite6:1;
    int sprite7:1;
};

struct SpritesBanks
{
    unsigned char sprite0;
    unsigned char sprite1;
    unsigned char sprite2;
    unsigned char sprite3;
    unsigned char sprite4;
    unsigned char sprite5;
    unsigned char sprite6;
    unsigned char sprite7;
};

struct SpriteColors
{
    int sprite0:4;
    int sprite0_unused:4;
    int sprite1:4;
    int sprite1_unused:4;
    int sprite2:4;
    int sprite2_unused:4;
    int sprite3:4;
    int sprite3_unused:4;
    int sprite4:4;
    int sprite4_unused:4;
    int sprite5:4;
    int sprite5_unused:4;
    int sprite6:4;
    int sprite6_unused:4;
    int sprite7:4;
    int sprite7_unused:4;
};

struct SpritePositions
{
    unsigned char sprite0x;
    unsigned char sprite0y;
    unsigned char sprite1x;
    unsigned char sprite1y;
    unsigned char sprite2x;
    unsigned char sprite2y;
    unsigned char sprite3x;
    unsigned char sprite3y;
    unsigned char sprite4x;
    unsigned char sprite4y;
    unsigned char sprite5x;
    unsigned char sprite5y;
    unsigned char sprite6x;
    unsigned char sprite6y;
    unsigned char sprite7x;
    unsigned char sprite7y;
};

extern struct SpriteBitField  *sprites_enabled;
extern struct SpriteBitField  *sprites_double_width;
extern struct SpriteBitField  *sprites_double_height;
extern struct SpritesBanks    *sprites_bank;
extern struct SpriteColors    *sprite_colors;
extern struct SpritePositions *sprite_positions;
extern struct SpriteBitField  *sprite_positions_high;

#endif // SPRITES_H
