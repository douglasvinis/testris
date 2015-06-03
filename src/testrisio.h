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

#ifdef __WIN32__
#  include <conio.h>
#  define TIME_USLEEP 10000
#else
#  include <termios.h>
#  include <unistd.h>
#  define TIME_USLEEP 1000
#endif


#ifndef TESTRISIO_H
#define TESTRISIO_H

/* 
* if not in Windows system, implement conio.h function to send back
* true or false if has keyboard input. 
*/
#ifndef __WIN32__
uint8_t kbhit();
#endif

uint8_t get_keyhit(char t);
void	show()	/* show all game on console */

#endif
