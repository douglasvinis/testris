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

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "testrisio.h"
#include "testris.h"
#include "testrisutils.h"

char message[100];

#ifndef __WIN32__ 
uint8_t tkbhit()
{
    struct timeval tv; fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO,&fds);
    select(STDIN_FILENO+1,&fds,NULL,NULL,&tv);
    return FD_ISSET(STDIN_FILENO,&fds);
}
#else
uint8_t tkbhit()
{
    return kbhit();
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

int get_time_msec()
{
    int mtime;
    #ifdef __WIN32__
    SYSTEMTIME st;
    GetSystemTime(&st);
    mtime = (int) st.wMilliseconds;

    #else
    struct timeval tv;
    gettimeofday(&tv,NULL);
    mtime = tv.tv_usec / 1000;
    #endif
    return mtime;
}

void game_over()
{
    clear_screen();
    printf("\n\n\t***  GAME OVER  ***\n\tFINAL SCORE:\t%d\n\tROWS:\t\t%d\n\tLEVEL:\t\t%d\n\n",
           get_score(),get_rows(),get_level());
    printf("<< PRESS ENTER TO EXIT >>\n");
    getchar();
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
	/* printing score rows and level on right of board */
	switch (y)
	{
        case 1:
          printf("<< TESTRIS %s >>",VERSION);
          break;
	    case 3:
		  printf("\tSCORE: %d",get_score());
		  break;
	    case 5:
		  printf("\tROWS: %d",get_rows());
		  break;
	    case 7:
		  printf("\tLEVEL: %d",get_level());
		  break;
        case 9: /* instrucoes de controle em portugues */
          printf("  a - mover esquerda | d - mover direita"); 
          break;
        case 10:
          printf("  s - queda com velocidade | w - rodar peca"); break;
        case 11:
          printf("  q - sair do jogo | p - pausar/continuar");
          break;
        case 13:/* english control instructions */
          printf("  a - move left | d -move right");
          break;
        case 14:
          printf("  s - speed fall | w - rotate piece");
          break;
        case 15:
          printf("  q - exit | p - pause/resume");
          break;

        case 19:
          printf("\t|| %s  ||",message);
          break;
	}
	putchar('\n');
    }
}
