#include "sprites.h"

struct SpriteBitField *sprites_enabled = (struct SpriteBitField *)0xD015;
struct SpriteBitField *sprites_double_width = (struct SpriteBitField *)0xD01D;
struct SpriteBitField *sprites_double_height = (struct SpriteBitField *)0xD017;

struct SpritesBanks *sprites_bank = (struct SpritesBanks *)0x07F8;

struct SpriteColors *sprite_colors = (struct SpriteColors *)0xD027;

struct SpritePositions *sprite_positions = (struct SpritePositions *)0xD000;
struct SpriteBitField *sprite_positions_high = (struct SpriteBitField *)0xD010;
