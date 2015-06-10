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

/*TODO this file contains horrible code,so much repeated code which need to be fixed. */ 

#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>

#include "testrisutils.h"
#include "testrisio.h"
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
    "1111    ",
    "        "
  },
  {
    "111111  ",
    "11      ",
    "        ",
    "        "
  },
  {
    "1111    ",
    "  11    ",
    "  11    ",
    "        "
  },
  {
    "    11  ",
    "111111  ",
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
    "1111    ",
    "        "
  },
  {
    "11      ",
    "111111  ",
    "        ",
    "        "
  },
  {
    "1111    ",
    "11      ",
    "11      ",
    "        "
  },
  {
    "111111  ",
    "    11  ",
    "        ",
    "        "
  }
};

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
    sprintf(message,"%d, %d",piece.direction,piece.type);

    switch (piece.type)
    {
	case 0:
	    return ;
	case 1:
    {/*piece I*/
	if (piece.direction == 1) piece.direction = 0;
	else piece.direction++;
	    
	memcpy(piece.piece, piece_i[piece.direction],(4*8)*sizeof(char) );
	gen_piece_rsize();
	break;
    }/*piece S*/
	case 2:
    {
	if (piece.direction == 1) piece.direction = 0;
	else piece.direction++;
	    
	memcpy(piece.piece, piece_s[piece.direction],(4*8)*sizeof(char) );
	gen_piece_rsize();
	break;
    }
	case 3:
    {/*piece Z*/
	if (piece.direction == 1) piece.direction = 0;
	else piece.direction++;
	    
	memcpy(piece.piece, piece_z[piece.direction],(4*8)*sizeof(char) );
	gen_piece_rsize();
	break;
    }
	case 4:
    {/*piece T*/
	if (piece.direction == 3) piece.direction = 0;
	else piece.direction++;
	    
	memcpy(piece.piece, piece_t[piece.direction],(4*8)*sizeof(char) );
	gen_piece_rsize();
	break;
    }
	case 5:
    {/*piece L*/
	if (piece.direction == 3) piece.direction = 0;
	else piece.direction++;
	    
	memcpy(piece.piece, piece_l[piece.direction],(4*8)*sizeof(char) );
	gen_piece_rsize();
	break;
    }	
	case 6:
    {/*piece J*/
	if (piece.direction == 3) piece.direction = 0;
	else piece.direction++;
	    
	memcpy(piece.piece, piece_j[piece.direction],(4*8)*sizeof(char) );
	gen_piece_rsize();
	break;
    }
    }
}

void gen_random_piece()
{
    int piece_model = 0;
    int piece_n = 7;  /* number of diferent pieces */
    int divisor = RAND_MAX/(6+1); /* divisor for get random range */

    /* random range between 0 and number of pieces */
    do {
	piece_model = rand() / divisor;
    } while (piece_model >piece_n);
    
    if (piece_model == piece_n) piece_model = 0;

    /* se piece position */
    piece.x = 10; piece.y = 0;

    switch (piece_model)
    {
	case 0:
    {/* piece O */
	memcpy(piece.piece, piece_o[0],(4*8)*sizeof(char)) ;
	piece.direction = 0;
	piece.type = 0;
	gen_piece_rsize();
	break;
    }
	case 1:
    {/* piece I */
	memcpy(piece.piece, piece_i[0],(4*8)*sizeof(char)) ;
	piece.direction = 0;
	piece.type = 1;
	gen_piece_rsize();
	break;
    }
	case 2:
    {/* piece Z */
	memcpy(piece.piece, piece_z[0],(4*8)*sizeof(char)) ;
	piece.direction = 0;
	piece.type = 2;
	gen_piece_rsize();
	break;
    }  
	case 3:
    {/* piece S */
	memcpy(piece.piece, piece_s[0],(4*8)*sizeof(char)) ;
	piece.direction = 0;
	piece.type = 3;
	gen_piece_rsize();
	break;
    }
	case 4:
    {/* piece T */
	memcpy(piece.piece, piece_t[0],(4*8)*sizeof(char)) ;
	piece.direction = 0;
	piece.type = 4;
	gen_piece_rsize();
	break;
    }
	case 5:
    {/* piece L */
	memcpy(piece.piece, piece_l[0],(4*8)*sizeof(char)) ;
	piece.direction = 0;
	piece.type = 5;
	gen_piece_rsize();
	break;
    }
	case 6:
    { /* piece J */
	memcpy(piece.piece, piece_j[0],(4*8)*sizeof(char)) ;
	piece.direction = 0;
	piece.type = 6;
	gen_piece_rsize();
	break;
    }
    }
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
