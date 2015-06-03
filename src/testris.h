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

#ifndef TESTRIS_H
#define TESTRIS_H

#define BOARD_WIDTH 20
#define BOARD_HEIGHT 20

/* declare the game board which will be store all piled game pieces*/
static uint8_t board[ BOARD_HEIGHT ][ BOARD_WIDTH ];

static uint32_t score;
static uint16_t rows;
static uint16_t level;

/* get basic information about the game */
uint32_t get_score();
uint16_t get_rows();
uint16_t get_level();

/* important function to the game mechanics. 
* collision and complete rows detectors & handles.
*/
uint8_t col_detection();
void	col_handler(uint8_t col_direction);
uint8_t row_detection();
void	row_handler();

/* main function of the game */
void start();

#endif
