/*==========================================================================*\
*|
*|   author: Douglas Knowman
*|   email : douglasknowman@gmail.com
*|
*|   Copyright(C) 2015 Douglas Knowman
*|
*|Testris is  distributed under the terms of the GNU General Public License
*|
\===========================================================================*/

#include <time.h>

#include "testris.h"
#include "testrisio.h"
#include "testrisutils.h"


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



void col_detection(uint8_t* state)
{
    register char x,y;
    
    /* 
    * look every part of the piece and verify if in there have a 
    * collision in each side, 2 cordnates of distance.
     */
    for (y = 0; y < piece.r_h; y++)
    {
	for (x = 0; x < piece.r_w; x++)
	{
	    if (piece.piece[y][x] == '1') /* detect only if is a valid block*/
	    {
		if (board[piece.y + y] [(piece.x + x) - 1] == '1'){
		    state[0] = COL_LEFT;  /* left collision */

		}else if (board[piece.y + y] [(piece.x + x) + 1] == '1'){
		   state[1] = COL_RIGHT;  /* right collision */

		}if (board[(piece.y + y) + 1] [piece.x + x] == '1'){
		    state[2] = COL_DOWN;  /* fall collision */
		}
	    }
	}
    }

    /* if has collision with board borders.. */
    if (piece.x - 1 <= 0){
	state[0] = COL_LEFT;
    }else if ((piece.x + piece.r_w) + 1 >= BOARD_WIDTH){
	state[1] = COL_RIGHT;
    }if (piece.y+piece.r_h >= BOARD_HEIGHT) state[2] = COL_DOWN;

}

void col_handler()
{
    register char x,y;
    /* simple copy the piece on the board*/
    for (y = 0; y < PIECE_HEIGHT; y++)
    {
	for (x = 0; x < PIECE_WIDTH; x++)
	{
	    if (piece.piece[y][x] != ' '){
		board[piece.y + y][piece.x + x] = piece.piece[y][x];
	    }
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
	    if (board[y][x] != ' ')
	    {
		if(!pile_height){
		    pile_height = y;
		}
		cnt++;
	    }
	}
	if (cnt == BOARD_WIDTH){
	    cnt = 0;
	    state = 1;
	    row_y = y;
	    rows++; 
	    break;
	}else cnt = 0;
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
	for (h = row_y; h >= pile_height ; h--){
	    board[h][x] = board[h - 1][x];
	} 
    }
}


void start()
{
    uint8_t is_running = 1;
    char command = 0;
    int time_f = 0; /* count how many times to piece fall*/
    int time_l = 0; /* count time to leave the piece when is collide on pile*/
    int time_l_max = 50; /* max time to leve the piece on pile */
    fall_maxt = 60;

    level = 1;
    

    srand(time(NULL));
    input_init();
    clear_board();
    gen_random_piece();

    while (is_running)
    {
	uint8_t collision[3] = {0,0,0};
	uint8_t row_full;
	/* wait a little time*/
	usleep(TIME_USLEEP); clear_screen();

	col_detection(collision);
	row_full = row_detection();
	if (collision[2] == COL_DOWN || time_l)
	{ 
	    if (time_l ==0) time_l =1;
	    else time_l++;
	    /* only reset the piece to de beginning again if time to level piece
	    * is past.
	    */
	    if ( time_l > time_l_max){
		time_l = 0;
		col_handler();
		gen_random_piece();
	    }
	}
	if (row_full){
	     row_handler();
	}
	
	time_f++;
	/* fall only when piece not are collided */
	if (time_f > (fall_maxt-(level*5)) && !time_l)
	{
	    time_f = 0;
	    piece.y += 1;
	} 

	/* get input from player to move the piece */
	if(kbhit()){
	    command = get_keyhit();
	    if (command == 'a' && collision[0] != COL_LEFT){
		piece.x -= 2;
	    }
	    if (command == 'd' && collision[1] != COL_RIGHT){
		piece.x += 2;
	    }
	    if (command == 's' && collision[2] != COL_DOWN){
		piece.y += 1;
	    }
	    if (command == 'q'){
		rotate_piece();
	    }
	}
	/* each +10 in row the level is encreased and velocity too */
	if (rows == level*10) level++;
	show();
    }

    input_stop();
}
