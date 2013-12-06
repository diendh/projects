﻿#ifndef __DEFINE_H__
#define __DEFINE_H__







#define PAWN  0
#define BISHOP 1
#define ELEPHAN  2
#define KNIGHT 3
#define CANNON	4
#define ROOK 5
#define KING  6
#define EMPTY 7
#define CHIEU  20
#define WIN  21
#define START_GAME  22

const int piecescore[6] = {
    1, 1, 1, 3, 3, 6
};


struct move
{
	int from;
	int dest;
};

struct gen_rec
{
	move m;
	int prior;
};

struct hist_rec
{
	move m;
	int capture;
	int color;
};


/******************************/
/************ Const ***********/
static const int SIZE_X = 9;
static const int SIZE_Y = 10;
static const int BOARD_SIZE = 90;

/**/

#define DARK  0
#define LIGHT  1

#define MOVE_STACK  4096
#define HIST_STACK  50
//#ifndef INFINITY
#define INFINIT  200000000
//#endif


/**
 first state
 **/
static const int FIRST_STATE[90] = {
    ROOK,   KNIGHT, ELEPHAN, BISHOP, KING,   BISHOP,   ELEPHAN,  KNIGHT, ROOK,
    EMPTY,  EMPTY,  EMPTY,   EMPTY,  EMPTY,  EMPTY,    EMPTY,    EMPTY,  EMPTY,
    EMPTY,  CANNON, EMPTY,   EMPTY,  EMPTY,  EMPTY,    EMPTY,    CANNON, EMPTY,
    PAWN,   EMPTY,  PAWN,    EMPTY,  PAWN,   EMPTY,    PAWN,     EMPTY,  PAWN,
    EMPTY,  EMPTY,  EMPTY,   EMPTY,  EMPTY,  EMPTY,    EMPTY,    EMPTY,  EMPTY,
    EMPTY,  EMPTY,  EMPTY,   EMPTY,  EMPTY,  EMPTY,    EMPTY,    EMPTY,  EMPTY,
    PAWN,   EMPTY,  PAWN,    EMPTY,  PAWN,   EMPTY,    PAWN,     EMPTY,  PAWN,
    EMPTY,  CANNON, EMPTY,   EMPTY,  EMPTY,  EMPTY,    EMPTY,    CANNON, EMPTY,
    EMPTY,  EMPTY,  EMPTY,   EMPTY,  EMPTY,  EMPTY,    EMPTY,    EMPTY,  EMPTY,
    ROOK,   KNIGHT, ELEPHAN, BISHOP, KING,   BISHOP,   ELEPHAN,  KNIGHT, ROOK,
};
static const bool FIRST_STATE_COLOR[90] = {
    DARK,   DARK,   DARK,    DARK,   DARK,   DARK,     DARK,     DARK,  DARK,
    EMPTY,  EMPTY,  EMPTY,   EMPTY,  EMPTY,  EMPTY,    EMPTY,    EMPTY,  EMPTY,
    EMPTY,  DARK,   EMPTY,   EMPTY,  EMPTY,  EMPTY,    EMPTY,    DARK,  EMPTY,
    DARK,   EMPTY,  DARK,    EMPTY,  DARK,   EMPTY,    DARK,     EMPTY,  DARK,
    EMPTY,  EMPTY,  EMPTY,   EMPTY,  EMPTY,  EMPTY,    EMPTY,    EMPTY,  EMPTY,
    EMPTY,  EMPTY,  EMPTY,   EMPTY,  EMPTY,  EMPTY,    EMPTY,    EMPTY,  EMPTY,
    LIGHT,   EMPTY,  LIGHT,    EMPTY,  LIGHT,   EMPTY,    LIGHT,     EMPTY,  LIGHT,
    EMPTY,  LIGHT, EMPTY,   EMPTY,  EMPTY,  EMPTY,    EMPTY,    LIGHT, EMPTY,
    EMPTY,  EMPTY,  EMPTY,   EMPTY,  EMPTY,  EMPTY,    EMPTY,    EMPTY,  EMPTY,
    LIGHT,   LIGHT,  LIGHT,   LIGHT,  LIGHT,  LIGHT,    LIGHT,     LIGHT,   LIGHT,
};
/*Bang uoc luong gia tri cac quan co theo vi tri*/
/**
 * @uml.property  name="pointtable" multiplicity="(0 -1)" dimension="3"
 */
const int pointtable[2][7][2][90] =
{
    {{{0,  0,  0,  0,  0,  0,  0,  0,  0, 			/* PAWN*/
        0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,
        10,  0, 12,  0, 15,  0, 12,  0, 10,
        10,  0, 13,  0, 10,  0, 13,  0, 10,
        20, 20, 20, 20, 20, 20, 20, 20, 20,
        20, 21, 21, 22, 22, 22, 21, 21, 20,
        20, 21, 21, 23, 23, 23, 21, 21, 20,
        20, 21, 21, 23, 22, 23, 21, 21, 20,
        11, 12, 13, 14, 14, 14, 13, 12, 11},
        
        {11, 12, 13, 14, 14, 14, 13, 12, 11,          /* PAWN*/
			20, 21, 21, 23, 22, 23, 21, 21, 20,
			20, 21, 21, 23, 23, 23, 21, 21, 20,
			20, 21, 21, 22, 22, 22, 21, 21, 20,
			20, 20, 20, 20, 20, 20, 20, 20, 20,
			10,  0, 13,  0, 10,  0, 13,  0, 10,
			10,  0, 12,  0, 15,  0, 12,  0, 10,
			0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0}},
        
        {{0,  0,  0, 20,  0, 20,  0,  0,  0, 			/* BISHOP */
			0,  0,  0,  0, 22,  0,  0,  0,  0,
			0,  0,  0, 19,  0, 19,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0},
            
            {0,  0,  0,  0,  0,  0,  0,  0,  0,          /* BISHOP */
                0,  0,  0,  0,  0,  0,  0,  0,  0,
                0,  0,  0,  0,  0,  0,  0,  0,  0,
                0,  0,  0,  0,  0,  0,  0,  0,  0,
                0,  0,  0,  0,  0,  0,  0,  0,  0,
                0,  0,  0,  0,  0,  0,  0,  0,  0,
                0,  0,  0,  0,  0,  0,  0,  0,  0,
                0,  0,  0, 19,  0, 19,  0,  0,  0,
                0,  0,  0,  0, 22,  0,  0,  0,  0,
                0,  0,  0, 20,  0, 20,  0,  0,  0}},
        
        {{0,  0, 25,  0,  0,  0, 25,  0,  0, 			/* ELEPHAN */
			0,  0,  0,  0,  0,  0,  0,  0,  0,
			23,  0,  0,  0, 28,  0,  0,  0, 23,
			0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0, 22,  0,  0,  0, 22,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0},
            
            {0,  0,  0,  0,  0,  0,  0,  0,  0,          /* ELEPHAN */
                0,  0,  0,  0,  0,  0,  0,  0,  0,
                0,  0,  0,  0,  0,  0,  0,  0,  0,
                0,  0,  0,  0,  0,  0,  0,  0,  0,
                0,  0,  0,  0,  0,  0,  0,  0,  0,
                0,  0, 22,  0,  0,  0, 22,  0,  0,
                0,  0,  0,  0,  0,  0,  0,  0,  0,
                23,  0,  0,  0, 28,  0,  0,  0, 23,
                0,  0,  0,  0,  0,  0,  0,  0,  0,
                0,  0, 25,  0,  0,  0, 25,  0,  0}},
        
        {{40, 35, 40, 40, 40, 40, 40, 35, 40, 		/* KNIGHT */
			40, 41, 42, 40, 20, 40, 42, 41, 40,
			40, 42, 43, 40, 40, 40, 43, 42, 40,
			40, 42, 43, 43, 43, 43, 43, 42, 40,
			40, 43, 44, 44, 44, 44, 44, 43, 40,
			40, 43, 44, 44, 44, 44, 44, 43, 40,
			40, 43, 44, 44, 44, 44, 44, 43, 40,
			40, 43, 44, 44, 44, 44, 44, 43, 40,
			40, 41, 42, 42, 42, 42, 42, 41, 40,
			40, 40, 40, 40, 40, 40, 40, 40, 40},
            
            {40, 40, 40, 40, 40, 40, 40, 40, 40, 		/* KNIGHT */
                40, 41, 42, 42, 42, 42, 42, 41, 40,
                40, 43, 44, 44, 44, 44, 44, 43, 40,
                40, 43, 44, 44, 44, 44, 44, 43, 40,
                40, 43, 44, 44, 44, 44, 44, 43, 40,
                40, 43, 44, 44, 44, 44, 44, 43, 40,
                40, 42, 43, 43, 43, 43, 43, 42, 40,
                40, 42, 43, 40, 40, 40, 43, 42, 40,
                40, 41, 42, 40, 20, 40, 42, 41, 40,
                40, 35, 40, 40, 40, 40, 40, 35, 40}},
        
        
        {{50, 50, 50, 50, 50, 50, 50, 50, 50, 		/* CANNON */
			50, 50, 50, 50, 50, 50, 50, 50, 50,
			50, 51, 53, 53, 55, 53, 53, 51, 50,
			50, 51, 50, 50, 50, 50, 50, 51, 50,
			50, 51, 51, 51, 51, 51, 51, 51, 50,
			50, 51, 50, 50, 50, 50, 50, 51, 50,
			50, 51, 50, 50, 50, 50, 50, 51, 50,
			50, 51, 50, 50, 50, 50, 50, 51, 50,
			50, 51, 50, 50, 50, 50, 50, 51, 50,
			50, 50, 50, 50, 50, 50, 50, 50, 50},
            
            {50, 50, 50, 50, 50, 50, 50, 50, 50, 		/* CANNON */
                50, 51, 50, 50, 50, 50, 50, 51, 50,
                50, 51, 50, 50, 50, 50, 50, 51, 50,
                50, 51, 50, 50, 50, 50, 50, 51, 50,
                50, 51, 50, 50, 50, 50, 50, 51, 50,
                50, 51, 51, 51, 51, 51, 51, 51, 50,
                50, 51, 50, 50, 50, 50, 50, 51, 50,
                50, 51, 53, 53, 55, 53, 53, 51, 50,
                50, 50, 50, 50, 50, 50, 50, 50, 50,
                50, 50, 50, 50, 50, 50, 50, 50, 50}},
        
        
        {{89, 92, 90, 90, 90, 90, 90, 92, 89, 		/* ROOK */
			91, 92, 90, 93, 90, 93, 90, 92, 91,
			90, 92, 90, 91, 90, 91, 90, 92, 90,
			90, 91, 90, 91, 90, 91, 90, 91, 90,
			90, 94, 90, 94, 90, 94, 90, 94, 90,
			90, 93, 90, 91, 90, 91, 90, 93, 90,
			90, 91, 90, 91, 90, 91, 90, 91, 90,
			90, 91, 90, 90, 90, 90, 90, 91, 90,
			90, 92, 91, 91, 90, 91, 91, 92, 90,
			90, 90, 90, 90, 90, 90, 90, 90, 90},
            
            {90, 90, 90, 90, 90, 90, 90, 90, 90, 		/* ROOK */
                90, 92, 91, 91, 90, 91, 91, 92, 90,
                90, 91, 90, 90, 90, 90, 90, 91, 90,
                90, 91, 90, 91, 90, 91, 90, 91, 90,
                90, 93, 90, 91, 90, 91, 90, 93, 90,
                90, 94, 90, 94, 90, 94, 90, 94, 90,
                90, 91, 90, 91, 90, 91, 90, 91, 90,
                90, 92, 90, 91, 90, 91, 90, 92, 90,
                91, 92, 90, 93, 90, 93, 90, 92, 91,
                89, 92, 90, 90, 90, 90, 90, 92, 89}},
        
        {{0,  0,  0, 30, 35, 30,  0,  0,  0, 			/* KING */
			0,  0,  0, 15, 15, 15,  0,  0,  0,
			0,  0,  0,  1,  1,  1,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0},
            
			{0,  0,  0,  0,  0,  0,  0,  0,  0,          /* KING */
                0,  0,  0,  0,  0,  0,  0,  0,  0,
                0,  0,  0,  0,  0,  0,  0,  0,  0,
                0,  0,  0,  0,  0,  0,  0,  0,  0,
                0,  0,  0,  0,  0,  0,  0,  0,  0,
                0,  0,  0,  0,  0,  0,  0,  0,  0,
                0,  0,  0,  0,  0,  0,  0,  0,  0,
                0,  0,  0,  1,  1,  1,  0,  0,  0,
                0,  0,  0, 15, 15, 15,  0,  0,  0,
                0,  0,  0, 30, 35, 30,  0,  0,  0}}},
    
    /********* AI 2 ***********************/
    {{{0,  0,  0,  0,  0,  0,  0,  0,  0, 			/* PAWN*/
        0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,
        10,  0, 10,  0, 10,  0, 10,  0, 10,
        10,  0, 10,  0, 10,  0, 10,  0, 10,
        20, 20, 20, 20, 20, 20, 20, 20, 20,
        20, 20, 20, 20, 20, 20, 20, 20, 20,
        20, 20, 20, 20, 20, 20, 20, 20, 20,
        20, 20, 20, 20, 20, 20, 20, 20, 20,
        15, 15, 15, 15, 15, 15, 15, 15, 15},
        
        {15, 15, 15, 15, 15, 15, 15, 15, 15,          /* PAWN*/
			20, 21, 20, 20, 20, 20, 20, 20, 20,
			20, 21, 21, 23, 23, 23, 21, 21, 20,
			20, 21, 21, 22, 22, 22, 21, 21, 20,
			20, 20, 20, 20, 20, 20, 20, 20, 20,
			10,  0, 13,  0, 10,  0, 13,  0, 10,
			10,  0, 12,  0, 15,  0, 12,  0, 10,
			0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0}},
        
        {{0,  0,  0, 40,  0, 40,  0,  0,  0, 			/* BISHOP */
			0,  0,  0,  0, 42,  0,  0,  0,  0,
			0,  0,  0, 40,  0, 40,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0},
            
            {0,  0,  0,  0,  0,  0,  0,  0,  0,          /* BISHOP */
                0,  0,  0,  0,  0,  0,  0,  0,  0,
                0,  0,  0,  0,  0,  0,  0,  0,  0,
                0,  0,  0,  0,  0,  0,  0,  0,  0,
                0,  0,  0,  0,  0,  0,  0,  0,  0,
                0,  0,  0,  0,  0,  0,  0,  0,  0,
                0,  0,  0,  0,  0,  0,  0,  0,  0,
                0,  0,  0, 43,  0, 43,  0,  0,  0,
                0,  0,  0,  0, 45,  0,  0,  0,  0,
                0,  0,  0, 46,  0, 46,  0,  0,  0}},
        
        {{0,  0, 40,  0,  0,  0, 40,  0,  0, 			/* ELEPHAN */
			0,  0,  0,  0,  0,  0,  0,  0,  0,
			40,  0,  0,  0, 45,  0,  0,  0, 40,
			0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0, 40,  0,  0,  0, 40,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0},
            
            {0,  0,  0,  0,  0,  0,  0,  0,  0,          /* ELEPHAN */
                0,  0,  0,  0,  0,  0,  0,  0,  0,
                0,  0,  0,  0,  0,  0,  0,  0,  0,
                0,  0,  0,  0,  0,  0,  0,  0,  0,
                0,  0,  0,  0,  0,  0,  0,  0,  0,
                0,  0, 42,  0,  0,  0, 42,  0,  0,
                0,  0,  0,  0,  0,  0,  0,  0,  0,
                43,  0,  0,  0, 48,  0,  0,  0, 43,
                0,  0,  0,  0,  0,  0,  0,  0,  0,
                0,  0, 45,  0,  0,  0, 45,  0,  0}},
        
        {{80, 75, 80, 80, 80, 80, 80, 75, 80, 		/* KNIGHT */
			80, 81, 82, 80, 80, 80, 82, 81, 80,
			80, 82, 83, 80, 80, 80, 83, 82, 80,
			80, 81, 82, 80, 80, 80, 82, 81, 80,
			80, 82, 83, 80, 80, 80, 83, 82, 80,
			80, 81, 82, 80, 80, 80, 82, 81, 80,
			80, 82, 83, 80, 80, 80, 83, 82, 80,
			80, 81, 82, 80, 80, 80, 82, 81, 80,
			80, 82, 83, 80, 80, 80, 83, 82, 80,
			80, 80, 80, 80, 80, 80, 80, 80, 80},
            
            {80, 75, 80, 80, 80, 80, 80, 75, 80, 		/* KNIGHT */
                80, 81, 82, 80, 80, 80, 82, 81, 80,
                80, 82, 83, 80, 80, 80, 83, 82, 80,
                80, 81, 82, 80, 80, 80, 82, 81, 80,
                80, 82, 83, 80, 80, 80, 83, 82, 80,
                80, 81, 82, 80, 80, 80, 82, 81, 80,
                80, 82, 83, 80, 80, 80, 83, 82, 80,
                80, 81, 82, 80, 80, 80, 82, 81, 80,
                80, 82, 83, 80, 80, 80, 83, 82, 80,
                80, 80, 80, 80, 80, 80, 80, 80, 80}},
        
        {{90, 90, 90, 90, 90, 90, 90, 90, 90, 		/* CANNON */
			100, 100, 100, 100, 100, 100, 100, 100, 100,
			100, 100, 100, 100, 100, 100, 100, 100, 100,
			100, 100, 100, 100, 100, 100, 100, 100, 100,
			100, 100, 100, 100, 100, 100, 100, 100, 100,
			100, 100, 100, 100, 100, 100, 100, 100, 100,
			100, 100, 100, 100, 100, 100, 100, 100, 100,
			100, 100, 100, 100, 100, 100, 100, 100, 100,
			100, 100, 100, 100, 100, 100, 100, 100, 100,
			100, 100, 100, 100, 100, 100, 100, 100, 100},
            
            {100, 100, 100, 100, 100, 100, 100, 100, 100,       /* CANNON */
                100, 100, 100, 100, 100, 100, 100, 100, 100,
                100, 100, 100, 100, 100, 100, 100, 100, 100,
                100, 100, 100, 100, 100, 100, 100, 100, 100,
                100, 100, 100, 100, 100, 100, 100, 100, 100,
                100, 100, 100, 100, 100, 100, 100, 100, 100,
                100, 100, 100, 100, 100, 100, 100, 100, 100,
                100, 100, 100, 100, 100, 100, 100, 100, 100,
                100, 100, 100, 100, 100, 100, 100, 100, 100,
                90, 90, 90, 90, 90, 90, 90, 90, 90}},
        
        
        {{200, 200, 200, 200, 200, 200, 200, 200, 200, 		/* ROOK */
			200, 200, 200, 200, 200, 200, 200, 200, 200,
			200, 200, 200, 200, 200, 200, 200, 200, 200,
			200, 200, 200, 200, 200, 200, 200, 200, 200,
			200, 200, 200, 200, 200, 200, 200, 200, 200,
			200, 200, 200, 200, 200, 200, 200, 200, 200,
			200, 200, 200, 200, 200, 200, 200, 200, 200,
			200, 200, 200, 200, 200, 200, 200, 200, 200,
			200, 200, 200, 200, 200, 200, 200, 200, 200,
			200, 200, 200, 200, 200, 200, 200, 200, 200},
            
            {250, 250, 250, 250, 250, 250, 250, 250, 250, 		/* ROOK */
                250, 250, 250, 250, 250, 250, 250, 250, 250,
                240, 240, 240, 240, 240, 240, 240, 240, 240,
                240, 240, 240, 240, 240, 240, 240, 240, 240,
                250, 250, 250, 250, 250, 250, 250, 250, 250,
                240, 240, 240, 240, 240, 240, 240, 240, 240,
                240, 240, 240, 240, 240, 240, 240, 240, 240,
                250, 250, 250, 250, 250, 250, 250, 250, 250,
                240, 240, 240, 240, 240, 240, 240, 240, 240,
                240, 240, 240, 240, 240, 240, 240, 240, 240}},
        
        {{0,  0,  0, 2000, 2050, 2000,  0,  0,  0, 			/* KING */
			0,  0,  0, 2015, 2015, 2015,  0,  0,  0,
			0,  0,  0,  2000,  2000,  2000,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0},
            
			{0,  0,  0,  0,  0,  0,  0,  0,  0,          /* KING */
                0,  0,  0,  0,  0,  0,  0,  0,  0,
                0,  0,  0,  0,  0,  0,  0,  0,  0,
                0,  0,  0,  0,  0,  0,  0,  0,  0,
                0,  0,  0,  0,  0,  0,  0,  0,  0,
                0,  0,  0,  0,  0,  0,  0,  0,  0,
                0,  0,  0,  0,  0,  0,  0,  0,  0,
                0,  0,  0,  2000,  2000,  2000,  0,  0,  0,
                0,  0,  0, 2015, 2015, 2015,  0,  0,  0,
                0,  0,  0, 2030, 2035, 2030,  0,  0,  0}}}
};

/**/
/**
 * @uml.property  name="offset" multiplicity="(0 -1)" dimension="2"
 */
const int offset[7][8] =
{{-1, 1,13, 0, 0, 0, 0, 0},		/* PAWN {for DARK side} */
    {-12,-14,12,14,0,0,0,0},		/* BISHOP */
    {-28,-24,24,28, 0, 0, 0, 0 },	/* ELEPHAN */
    {-11,-15,-25,-27,11,15,25,27},	/* KNIGHT */
    {-1, 1,-13,13, 0, 0, 0, 0},		/* CANNON */
    {-1, 1,-13,13, 0, 0, 0, 0},		/* ROOK */
    {-1, 1,-13,13, 0, 0, 0, 0}};	/* KING */

/**
 * @uml.property  name="mailbox182" multiplicity="(0 -1)" dimension="1"
 */
const int mailbox182[182] =
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8,-1,-1,
    -1,-1, 9,10,11,12,13,14,15,16,17,-1,-1,
    -1,-1,18,19,20,21,22,23,24,25,26,-1,-1,
    -1,-1,27,28,29,30,31,32,33,34,35,-1,-1,
    -1,-1,36,37,38,39,40,41,42,43,44,-1,-1,
    -1,-1,45,46,47,48,49,50,51,52,53,-1,-1,
    -1,-1,54,55,56,57,58,59,60,61,62,-1,-1,
    -1,-1,63,64,65,66,67,68,69,70,71,-1,-1,
    -1,-1,72,73,74,75,76,77,78,79,80,-1,-1,
    -1,-1,81,82,83,84,85,86,87,88,89,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

/**
 * @uml.property  name="mailbox90" multiplicity="(0 -1)" dimension="1"
 */
const int mailbox90[90] =
{28, 29, 30, 31, 32, 33, 34, 35, 36,
    41, 42, 43, 44, 45, 46, 47, 48, 49,
    54, 55, 56, 57, 58, 59, 60, 61, 62,
    67, 68, 69, 70, 71, 72, 73, 74, 75,
    80, 81, 82, 83, 84, 85, 86, 87, 88,
    93, 94, 95, 96, 97, 98, 99,100,101,
    106, 107,108,109,110,111,112,113,114,
    119, 120,121,122,123,124,125,126,127,
    132, 133,134,135,136,137,138,139,140,
    145, 146,147,148,149,150,151,152,153};

/**
 * @uml.property  name="legalposition" multiplicity="(0 -1)" dimension="1"
 */
const int legalposition[90] =
{1, 1, 5, 3, 3, 3, 5, 1, 1,
    1, 1, 1, 3, 3, 3, 1, 1, 1,
    5, 1, 1, 3, 7, 3, 1, 1, 5,
    1, 1, 1, 1, 1, 1, 1, 1, 1,
    9, 1,13, 1, 9, 1,13, 1, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9};

/**
 * @uml.property  name="maskpiece" multiplicity="(0 -1)" dimension="1"
 */
const int maskpiece[7] = {8, 2, 4, 1, 1, 1, 2};
/**
 * @uml.property  name="knightcheck" multiplicity="(0 -1)" dimension="1"
 */
const int knightcheck[8] = {1,-1,-9,-9,-1,1,9,9};
/**
 * @uml.property  name="knightcheck2" multiplicity="(0 -1)" dimension="1"
 */
const int knightcheck2 [8] = {-8,-10,-8,-10,8,10,8,10};
/**
 * @uml.property  name="elephancheck" multiplicity="(0 -1)" dimension="1"
 */
const int elephancheck[8] = {-10,-8,8,10,0,0,0,0};
/**
 * @uml.property  name="kingpalace" multiplicity="(0 -1)" dimension="2"
 */
const int kingpalace[2][9] = {{3,4,5,12,13,14,21,22,23},
    {66,67,68,75,76,77,84,85,86}};



/*************/


#define kSTARMode1	"star_key1"
#define kSTARMode3	"star_key3"
#define kSTARMode4	"star_key4"

#define kNumberWin1	"wincount1"
#define kNumberLose1	"losecount1"
#define kScore3			"score3"
#define kScore4			"score4"

#define kAILevel        "AILevel"

#define kAvatar1        "Avatar1"
#define kAvatar2        "Avatar2"

const char CAP_BAC[6][15] = {
    "Tập sự",
    "Nghiệp dư",
    "Cao cờ",
    "Kỳ thủ",
    "Kỳ tiên",
    "Kỳ thánh"
    
};

#endif


/*

${NDK_ROOT}/toolchains/arm-linux-androideabi-4.4.3/prebuilt/darwin-x86/lib/gcc/arm-linux-androideabi/4.4.3/include
*/