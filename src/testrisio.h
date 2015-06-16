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

/*
* this file contains all the multiplatform code of the testris game 
* all input and output multiplatform functions there are here.
*/
#include <stdlib.h>
#include <stdint.h>

#ifdef __WIN32__
#  include <conio.h>
#  include <windows.h>
#  define TIME_PER_FRAME 10000
#  define VERSION "0.2.6 [WIN32]"

/* some constants for time in game */
#  define TIME_L_MAX 10 /* max time to leave the piece on pile */
#  define TIME_F_MAX 5 /* max time to wait when is fall */
#  define LEVEL_DIFICUTY 1 /* fator for increase the fall speed of the piece */

#else
#  include <termios.h>
#  include <unistd.h>
#  define TIME_PER_FRAME 10000 
#  define VERSION "0.2.6 [GNU/LINUX]"

/* some constants for time in game */
#  define TIME_L_MAX 50 /* max time to leave the piece on pile */
#  define TIME_F_MAX 60 /* max time to wait when is fall */
#  define LEVEL_DIFICUTY 10 /* fator for increase the fall speed of the piece */
#endif


#ifndef TESTRISIO_H
#define TESTRISIO_H

#ifndef __WIN32__
/* structures for change input type of unix systems*/
static struct termios settings;
static struct termios start_settings;
#endif

char message[100];

/* 
* if not in Windows system, implement conio.h function to send back
* true or false if has keyboard input. 
*/
#ifndef __WIN32__
uint8_t tkbhit(); /* if have keyboard input */
#else
uint8_t tkbhit();
#endif

void	input_init();
void	input_stop();

void	clear_screen();
char    get_keyhit();
void    game_over(); /* show final score when the game ends */
void	show();	/* show all game on console */
int     get_time_msec(); /* return system time in miliseconds */

#endif
