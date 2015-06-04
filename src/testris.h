/*==========================================================================*\
*|
*|   author: Douglas Knowman
*|   email : douglasknowman@gmail.com
*|
*|   Copyright(C) Douglas Knowman, 2015
*|
\===========================================================================*/

#ifndef TESTRIS_H
#define TESTRIS_H

#include <stdint.h>

#define BOARD_WIDTH 20
#define BOARD_HEIGHT 20

#define OUTPUT_CHAR 35 /* '#' in ascii */

#define COL_RIGHT 2
#define COL_LEFT 1
#define COL_DOWN 3

/* declare the game board which will be store all piled game pieces*/
static uint8_t board[ BOARD_HEIGHT ][ BOARD_WIDTH ];

static uint32_t score;
static uint32_t rows;
static uint32_t level;

static uint8_t pile_height;
static uint8_t row_y;
static uint32_t fall_maxt; /* max time until the piece fall*/

/* get basic information about the game */
uint32_t get_score();
uint32_t get_rows();
uint32_t get_level();

/* important function to the game mechanics. 
* collision and complete rows detectors & handles.
*/
uint8_t col_detection();
void	col_handler();
uint8_t row_detection();
void	row_handler();

/* main function of the game */
void start();

#endif
