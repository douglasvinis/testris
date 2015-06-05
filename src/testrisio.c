/*==========================================================================*\
*|
*|   author: Douglas Knowman
*|   email : douglasknowman@gmail.com
*|
*|   Copyright(C) Douglas Knowman, 2015
*|
\===========================================================================*/

#include <stdio.h>
#include <stdlib.h>

#include "testrisio.h"
#include "testris.h"
#include "testrisutils.h"

#ifndef __WIN32__ 
uint8_t kbhit()
{
    struct timeval tv; fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO,&fds);
    select(STDIN_FILENO+1,&fds,NULL,NULL,&tv);
    return FD_ISSET(STDIN_FILENO,&fds);
}
#endif

void input_init()
{
    #ifndef __WIN32__
    /* init terminal input modification for unix systems. */
    tcgetattr(STDIN_FILENO,&settings);
    tcgetattr(STDIN_FILENO,&start_settings);

    settings.c_lflag &= ~(ICANON|ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &settings);
    #endif
}

void input_stop()
{
    #ifndef __WIN32__
    tcsetattr(STDIN_FILENO, TCSANOW,&start_settings);
    #endif
}

void clear_screen()
{
    #ifdef __WIN32__
    system("cls");
    #else
    printf("\e[H\e[2J");
    #endif
}

char get_keyhit()
{
    #ifdef __WIN32__
    return getch();
    #else
    return getchar();
    #endif
}

void show()
{
    register uint8_t x,y;

    for (y = 0;y < BOARD_HEIGHT; y++)
    {
	printf("|*|");	
	for (x = 0;x < BOARD_WIDTH; x++)
	{
	    if (board[y][x] ==  '1'){
		putchar(OUTPUT_CHAR);

	    }else if ((y >= piece.y && y < piece.y+PIECE_HEIGHT) &&
		(x >= piece.x && x < piece.x+PIECE_WIDTH))
	    {
		if (piece.piece[y-piece.y][x-piece.x] == '1'){
		    putchar(OUTPUT_CHAR);
		}else putchar(' '); 
	    }else putchar(' ');
	}
	printf("|*|");	
	putchar('\n');
    }
}
