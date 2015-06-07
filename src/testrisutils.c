/*==========================================================================*\
*|
*|   author: Douglas Knowman
*|   email : douglasknowman@gmail.com
*|
*|   Copyright(C) Douglas Knowman, 2015
*|
\===========================================================================*/

#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include "testrisutils.h"
#include "testris.h"

extern uint8_t board[BOARD_HEIGHT][BOARD_WIDTH];

/* pieces and they rotations */
/* TODO put this pieces on a separated file and load then.*/

/* piece O  */
char* piece_o[1][4] = 
{
  {/* this piece have only one retation form */
    "1111    ",
    "1111    ",
    "        ",
    "        "
  }
};

/* piece I */
char* piece_i[2][4] = 
{
  {
    "11      ",
    "11      ",
    "11      ",
    "11      "
  },
  {
    "11111111",
    "        ",
    "        ",
    "        "
  }
};

/* piece Z */
char* piece_z[2][4] = 
{
  {
    "1111    ",
    "  1111  ",
    "        ",
    "        "
  },
  {
    "  11    ",
    "1111    ",
    "11      ", "        "
  }
};

/* piece S */
char* piece_s[2][4] = 
{
  {
    "  1111  ",
    "1111    ",
    "        ",
    "        "
  },
  {
    "11      ",
    "1111    ",
    "  11    ",
    "        "
  }
};

/* piece T */
char* piece_t[4][4] = 
{
  {
    "  11    ",
    "111111  ",
    "        ",
    "        "
  },
  {
    "11      ",
    "1111    ",
    "11      ",
    "        "
  },
  {
    "111111  ",
    "  11    ",
    "        ",
    "        "
  },
  {
    "  11    ",
    "1111    ",
    "  11    ",
    "        "
  }
};

/* piece L */
char* piece_l[4][4] = 
{
  {
    "11      ",
    "11      ",
    "11      ",
    "1111    "
  },
  {
    "11111111",
    "11      ",
    "        ",
    "        "
  },
  {
    "1111    ",
    "  11    ",
    "  11    ",
    "  11    "
  },
  {
    "      11",
    "11111111",
    "        ",
    "        "
  }
};

/* piece J */
char* piece_j[4][4] = 
{
  {
    "  11    ",
    "  11    ",
    "  11    ",
    "1111    "
  },
  {
    "11      ",
    "11111111",
    "        ",
    "        "
  },
  {
    "1111    ",
    "11      ",
    "11      ",
    "11      "
  },
  {
    "11111111",
    "      11",
    "        ",
    "        "
  }
};

/* global variable only for test before random numbers generation*/
uint8_t piece_model = 0;

void clear_board()
{
    register char x,y;
    
    for (y = 0; y < BOARD_HEIGHT; y++)
    {
	for (x  = 0;x < BOARD_WIDTH; x++)
	{
	    board[y][x] = ' ';
	}
    }
}

void rotate_piece()
{
    if (piece.type = 0) return;
    if (piece.type = 1)
    {
	if (piece.direction == 2) piece.direction = 0;
	else piece.direction++;
	    
	memcpy(piece.piece, piece_i[piece.direction],sizeof piece_i[piece.direction]);
    }
}

void gen_random_piece()
{
    /* TODO random number here.. */ 
    /*uint8_t piece_model = 0;  kind of piece will be generate now.*/
    
    if (piece_model == 7) piece_model = 0;

    /* se piece position */
    piece.x = 10; piece.y = 0;

    if (piece_model == 0)
    {
	/* O piece */
	memcpy(piece.piece, piece_o[0],sizeof piece_o[0]);
	piece.direction = 0;
	piece.type = 0;
	gen_piece_rsize();
    }else if (piece_model == 1)
    {
	memcpy(piece.piece, piece_i[0],sizeof piece_i[0]);
	piece.direction = 0;
	piece.type = 1;
	gen_piece_rsize();
    }

    piece_model++;
}

void gen_piece_rsize()
{
    register char x,y;
    uint8_t p_w = 0, p_h = 0;
    
    /* find the real width and height of piece */

    for (y = 0;y < PIECE_HEIGHT; y++)
    {
	for (x = 0;x < PIECE_WIDTH; x++)
	{
	    if (piece.piece[y][x] == '1')
	    {
		if(x > p_w) p_w = x;
		if(y > p_h) p_h = y;
	    }
	}
    }
    piece.r_w = p_w+1;
    piece.r_h = p_h+1;
}
