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

#ifndef TESTRISUTILS_H
#define TESTRISUTILS_H

#define PIECE_WIDTH 8
#define PIECE_HEIGHT 4

struct Piece
{
    char piece[ PIECE_HEIGHT ][ PIECE_WIDTH ]; 
    uint8_t direction;
    uint8_t type;
    uint8_t r_w, r_h; /* real width and height of piece */
    int x,y; 
}piece;


/* util functions */
void clear_board();

void rotate_piece();
void gen_random_piece();
void piece_copy(char **from,char (*to)[8]);

/* generate real width and height of the piece */
void gen_piece_rsize();

/* wait until the frame is in correct time. */
void frame_sleep();

#endif
