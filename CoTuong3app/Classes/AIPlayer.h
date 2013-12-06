#ifndef __AIPLAYER_H__
#define __AIPLAYER_H__

#include "define.h"
#include "ChoiDon.h"
#include "pthread.h"


typedef move	Move;

//class GameScene;

//void *runThread(void*);

class AIPlayer
{
	// variables need for AI
	/**/
	/**
	 * @uml.property  name="piece" multiplicity="(0 -1)" dimension="1"
	 */
	int piece[BOARD_SIZE];
	/**
	 * @uml.property  name="color" multiplicity="(0 -1)" dimension="1"
	 */
	int color[BOARD_SIZE];
	/**
	 * @uml.property  name="ply"
	 */
	int	ply;
	/**
	 * @uml.property  name="side"
	 */
	int side;
	/**
	 * @uml.property  name="xside"
	 */
	int xside;
	/**
	 * @uml.property  name="hdp"
	 */
	int hdp;
	/**
	 * @uml.property  name="follow_pv"
	 */
	bool	follow_pv;
	/**
	 * @uml.property  name="newmove"
	 * @uml.associationEnd  inverse="this$0:vn.sunnet.game.chess.computer.Computer$move"
	 */
	move newmove;
	//
	/**
	 * @uml.property  name="gen_dat"
	 * @uml.associationEnd  multiplicity="(0 -1)" inverse="this$0:vn.sunnet.game.chess.computer.Computer$gen_rec"
	 */
	gen_rec	gen_dat[MOVE_STACK];
	/**
	 * @uml.property  name="gen_begin" multiplicity="(0 -1)" dimension="1"
	 */
	int gen_begin[HIST_STACK];
	/**
	 * @uml.property  name="gen_end" multiplicity="(0 -1)" dimension="1"
	 */
    int gen_end[HIST_STACK];
	/**
	 * @uml.property  name="hist_dat"
	 * @uml.associationEnd  multiplicity="(0 -1)" inverse="this$0:vn.sunnet.game.chess.computer.Computer$hist_rec"
	 */
    hist_rec hist_dat[HIST_STACK];
	/**
	 * @uml.property  name="history" multiplicity="(0 -1)" dimension="2"
	 */
    int history[BOARD_SIZE][BOARD_SIZE];
	/**
	 * @uml.property  name="pv" multiplicity="(0 -1)" dimension="2"
	 */
    move pv[HIST_STACK][HIST_STACK];//
	/**
	 * @uml.property  name="pv_length" multiplicity="(0 -1)" dimension="1"
	 */
    int pv_length[HIST_STACK];
	/**/
	/**
	 * @uml.property  name="play"
	 * @uml.associationEnd  multiplicity="(1 1)" inverse="this$0:vn.sunnet.game.chess.computer.Computer$Play"
	 */
    
    
    
    int MAX_PLY;
    ChoiDon*	m_GameScene;
    
    pthread_t m_thread;
    
    bool m_Stop;
    
    int type;
public:
	AIPlayer(void);
	~AIPlayer(void);
    
	void stop();
	void start();
	int randomx(int max,int min);
    
	void LoadBoard(int piece1[],int color1[]);
    
	static AIPlayer* shared();
    
	void setDelegate(ChoiDon* mdelegate){m_GameScene = mdelegate;}
    
	void play();
    
	void setSide(int _side);
    
	int getSide(){return side;}
    
	void setMaxPly(int sPly);
    
	int* getAllAvaiblePos(int pos);
    
    bool IsKingFace(int pos);
    
    bool isKingSafe(int _side);
    
    int* getAttackPosForSide(int);
    int getKingPosition(int _side);
private:
    
	void movePiece(int from, int dest);
    
	//
	int AlphaBeta(int alpha, int beta, int depth);
	int Quiescence(int alpha, int beta);
	void Check_pv ();
	void Sort();
	void Quicksort(int q, int r);
	
	bool MakeMove(Move m);
	void UnMakeMove();
public:
    
	bool Gen();
	void AILog();
private:
	void Gen_push(int from, int dest);
	bool GenCapture();
	bool MoveSave (int from, int dest);
public:
	bool IsInCheck (int xside2);
	bool Attack (int pos, int side);
private:
	int Eval();
	int Bonous();
	
};

#endif // !__AIPLAYER_H__
