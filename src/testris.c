/*==========================================================================*\
*|
*|   author: Douglas Knowman
*|   email : douglasknowman@gmail.com
*|
*|   Copyright(C) Douglas Knowman, 2015
*|
\===========================================================================*/

#include <stdint.h>

#include "testrisio.h"
#include "testrisutils.h"
#include "testris.h"

uint32_t get_score()
{
    return score;
}

uint32_t get_rows()
{
    return rows;
}

uint32_t get_level()
{
    return level;
}


uint8_t col_detection()
{
    uint8_t state = 0;
    register char x,y;
    
    /* 
    * look every part of the piece and verify if in there have a 
    * collision in each side, 2 cordnates of distance.
     */
    for (y = 0; y < PIECE_HEIGHT; y++)
    {
	for (x = 0; x < PIECE_WIDTH; x++)
	{
	    if (board[piece.y + y] [(piece.x + x) - 2]){
		state = COL_LEFT;  /* left collision */

	    }else if (board[piece.y + y] [(piece.x + x) + 2]){
		state = COL_RIGHT;  /* right collision */

	    }else if (board[(piece.y + y) + 2] [piece.x + x]){
		state = COL_DOWN;  /* fall collision */
	    }
	}
    }

    /* if has collision with board borders.. */
    if (piece.x - 1 <= 0){
	state = 1;
    }else if ((piece.x + piece.r_w) + 1 >= BOARD_WIDTH){
	state = 2;
    }

    return state;
}

void col_handler()
{
    register char x,y;
    /* simple copy the piece on the board*/
    for (y = 0; y < PIECE_HEIGHT; y++)
    {
	for (x = 0; x < PIECE_WIDTH; x++)
	{
	    board[piece.y + y][piece.x + x] = piece.piece[y][x];
	}
    }
}
