/*==========================================================================*\
*|
*|   author: Douglas Knowman
*|   email : douglasknowman@gmail.com
*|
*|   Copyright(C) Douglas Knowman, 2015
*|
\===========================================================================*/

/*
* this file contains all the multiplatform code of the testris game 
* all input and output multiplatform functions there are here.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifdef __WIN32__
#  include <conio.h>
#  define TIME_USLEEP 1000
#else
#  include <termios.h>
#  include <unistd.h>
#  define TIME_USLEEP 10000
#endif


#ifndef TESTRISIO_H
#define TESTRISIO_H

#ifndef __WIN32__
/* structures for change input type of unix systems*/
static struct termios settings;
static struct termios start_settings;
#endif

/* 
* if not in Windows system, implement conio.h function to send back
* true or false if has keyboard input. 
*/
#ifndef __WIN32__
uint8_t kbhit();
#endif

void	input_init();
void	input_stop();

void	clear_screen();
char get_keyhit();
void	show();	/* show all game on console */

#endif
