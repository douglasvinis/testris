/*==========================================================================*\
*|
*|   author: Douglas Knowman
*|   email : douglasknowman@gmail.com
*|
*|   Copyright(C) Douglas Knowman, 2015
*|
\===========================================================================*/

#include <stdint.h>

#ifndef TESTRISUTILS_H
#define TESTRISUTILS_H

#define PIECE_WIDTH 8
#define PIECE_HEIGHT 4

typedef struct piece Piece
{
    uint8_t piece[ PIECE_HEIGHT ][ PIECE_WIDTH ]; 
    uint8_t direction;
    int x,y; 
};

/* --util functions */
void clear_board(uint8_t**  board);

void rotate_piece();
void get_random_piece();

/* get real width and height of the piece */
uint8_t get_piece_rsize(Piece* piece);


#endif
