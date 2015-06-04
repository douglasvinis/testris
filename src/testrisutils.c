/*==========================================================================*\
*|
*|   author: Douglas Knowman
*|   email : douglasknowman@gmail.com
*|
*|   Copyright(C) Douglas Knowman, 2015
*|
\===========================================================================*/

#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include "testrisutils.h"
#include "testris.h"


void clear_board()
{
    register char x,y;
    
    for (y = 0; y < BOARD_HEIGHT; y++)
    {
	for (x  = 0;x < BOARD_WIDTH; x++)
	{
	    board[y][x] = '\0';
	}
    }
}

void rotate_piece()
{
    /* if is a O piece */
    if (piece.type == 0) return;
}

void gen_random_piece()
{
    /* TODO random number here.. */ 
    uint8_t piece_model = 0; /* kind of piece will be generate now.*/

    if (piece_model == 0)
    {
	/* O piece */
	piece.piece[0] = "1111\0\0\0\0";
	piece.piece[1] = "1111\0\0\0\0";
	piece.piece[2] = "\0\0\0\0\0\0\0\0";
	piece.piece[3] = "\0\0\0\0\0\0\0\0";
	piece.direction = 0;
	piece.type = 0;
	piece.x = 4; piece.y = -2;
	gen_piece_rsize();
    }

}

void gen_piece_rsize()
{
    register char x,y;
    uint8_t p_w, p_h;
    
    /* find the real width and height of piece */

    for (y = 0;y < PIECE_HEIGHT; y++)
    {
	for (x = 0;x < PIECE_WIDTH; x++)
	{
	    if (piece.piece[y][x])
	    {
		if(x > p_w) p_w = x;
		if(y > p_h) p_h = y;
	    }
	}
    }
    piece.r_w = p_w;
    piece.r_h = p_h;
}
