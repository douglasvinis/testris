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

extern uint8_t board[BOARD_HEIGHT][BOARD_WIDTH];


void clear_board()
{
    register char x,y;
    
    for (y = 0; y < BOARD_HEIGHT; y++)
    {
	for (x  = 0;x < BOARD_WIDTH; x++)
	{
	    board[y][x] = ' ';
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
	piece.piece[0] = "11      ";
	piece.piece[1] = "11      ";
	piece.piece[2] = "11      ";
	piece.piece[3] = "1111    ";
	piece.direction = 0;
	piece.type = 0;
	piece.x = 4; piece.y = 0;
	gen_piece_rsize();
    }

}

void gen_piece_rsize()
{
    register char x,y;
    uint8_t p_w = 0, p_h = 0;
    
    /* find the real width and height of piece */

    for (y = 0;y < PIECE_HEIGHT; y++)
    {
	for (x = 0;x < PIECE_WIDTH; x++)
	{
	    if (piece.piece[y][x] == '1')
	    {
		if(x > p_w) p_w = x;
		if(y > p_h) p_h = y;
	    }
	}
    }
    piece.r_w = p_w+1;
    piece.r_h = p_h+1;
}
