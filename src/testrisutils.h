/*==========================================================================*\
*|
*|   author: Douglas Knowman
*|   email : douglasknowman@gmail.com
*|
*|   Copyright(C) Douglas Knowman, 2015
*|
\===========================================================================*/

#ifndef TESTRISUTILS_H
#define TESTRISUTILS_H

#define PIECE_WIDTH 8
#define PIECE_HEIGHT 4

struct 
{
    uint8_t piece[ PIECE_HEIGHT ][ PIECE_WIDTH ]; 
    uint8_t direction;
    uint8_t type;
    uint8_t r_w, r_h; /* real width and height of piece */
    int x,y; 
} piece;

/* util functions */
void clear_board(uint8_t**  board);

void rotate_piece();
void gen_random_piece();

/* generate real width and height of the piece */
void gen_piece_rsize();

#endif
