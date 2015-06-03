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

uint8_t row_detection()
{
    uint8_t cnt; /* count for every horizontal valid space on board*/
    uint8_t state = 0;
    register char x,y;

    pile_height = 0; 
    /*
    * detect if have a complete row and the pile height  and store
    * them on 2 variables to use on row_handler(). here is se the
    * score and how many rows are made by player.
    */
    for (y = 0; y < BOARD_HEIGHT; y++)
    {
	for (x = 0; x < BOARD_WIDTH; x++)
	{
	    if (board[y][x])
	    {
		if(!pile_height){
		    pile_height = y;
		}
		cnt++;
	    }
	}
	if (cnt == BOARD_WIDTH){
	    state = 1;
	    row_y = y;
	    rows++ 
	}
    }
    return state;
}

void row_handler()
{
    uint8_t x, h;
    /*
    * this function take every horizontal location in a complete row 
    * detected in row_detection() and replace along the hight of pile
    * recreating a fall in board frozen pieces.
    */
    for (x = 0; x < BOARD_WIDTH; x++){	
	for (h = row_y; h < pile_height + ; h--){
	    board[h][x] = board[h - 1][x];
	} 
    }
}


void start()
{
    
}
