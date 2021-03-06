/*==========================================================================*\
*|
*|   author: Douglas Vinicius
*|   email : douglvini@gmail.com
*|
*|   Copyright(C) 2015 Douglas Vinicius
*|
*|Testris is  distributed under the terms of the GNU General Public License
*|
\===========================================================================*/

#include <time.h>
#include <string.h>

#include "testris.h"
#include "testrisio.h"
#include "testrisutils.h"

/* declare the game board which will be store all piled game pieces*/
uint8_t board[ BOARD_HEIGHT ][ BOARD_WIDTH ];


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
    /* calculating pontuation of each piece which colides */
    score += piece.type * 6;

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
    /* TODO system for calculate row points correctly*/

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
        score+= 230;
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
    char paused = 0;

    level = 1;
    

    srand(time(NULL));
    input_init();
    clear_board();
    gen_random_piece();

    while (is_running)
    {
	uint8_t collision[3] = {0,0,0};
	uint8_t row_full;

    /*sending status message */
    if (paused){
        strcpy(message,"paused");
    }else{
        strcpy(message,"playing");
    }

	/* if time to process si less than velocity */
	frame_sleep();
    clear_screen();
    
    /* if pile reach the top game over */
    if (pile_height == 1 || level == 6) is_running = 0;

	col_detection(collision);
	row_full = row_detection();
	if (collision[2] == COL_DOWN || time_l)
	{ 
	    if (time_l ==0) time_l =1;
	    else time_l++;
	    /* only reset the piece to de beginning again if time to level piece
	    * is past.
	    */
	    if ( time_l > TIME_L_MAX)
        {
		    time_l = 0;
            if ( collision[2] == COL_DOWN){ 
		        col_handler();
		        gen_random_piece();
            }
	    }
	}
	if (row_full){
	     row_handler();
	}
	
	time_f++;
	/* fall only when piece not are collided */
	if (time_f > (TIME_F_MAX - (level * LEVEL_DIFICUTY)) && !time_l && !paused)
	{
	    time_f = 0;
	    piece.y += 1;
	} 

	col_detection(collision);

	/* get input from player to move the piece */
	if(tkbhit()){
	    command = get_keyhit();
	    if (command == 'a' && collision[0] != COL_LEFT && !paused){
		piece.x -= 2;
	    }
	    if (command == 'd' && collision[1] != COL_RIGHT && !paused){
		piece.x += 2;
	    }
	    if (command == 's' && collision[2] != COL_DOWN && !paused){
		piece.y += 1;
	    }
	    if (command == 'w' && !paused){
		    rotate_piece();
	    }
        if (command == 'p')
        {
             paused = paused ? 0:1;
        }
        if (command == 'q')
        {
             is_running = 0;
        }
	}
	/* each +10 in row the level is encreased and velocity too */
	if (rows == level*10) level++;
	show();
    }
    /* game over message */
    game_over();

    input_stop();
}
