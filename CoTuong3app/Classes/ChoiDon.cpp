//
//  ChoiDon.cpp
//  CoTuong3
//
//  Created by Đỗ Hữu Điển on 11/28/13.
//
//

#include "ChoiDon.h"
#include "AIPlayer.h"
#include "define.h"
#include "Piece.h"
#include "AIPlayer.h"
CCScene* ChoiDon::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    ChoiDon *layer = ChoiDon::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ChoiDon::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    //add bg
    CCSprite* pBG = CCSprite::create("ChoiDon/khung-banchoi1.png");
    pBG->setPosition(ccp(240, 350));
    this->addChild(pBG, 0);
    isDadi = false;
    createTable();
    
    quandi = DARK;
   // AIPlayer::shared()->setDelegate(this);
  //  AIPlayer::shared()->setMaxPly(5);
    
    _mainAI = new AIPlayer;
    _mainAI->setDelegate(this);
    _mainAI->LoadBoard(m_Table, m_Colors);
    _mainAI->setSide(DARK);
    _mainAI->setMaxPly(6);
    
    
    _main2AI = new AIPlayer;
    _main2AI->setDelegate(this);
    _main2AI->LoadBoard(m_Table, m_Colors);
    _main2AI->setSide(LIGHT);
    _main2AI->setMaxPly(7);
    
    if (quandi == DARK) {
        _mainAI->start();
    }else{
        _main2AI->start();
    }
   
   // for (int i=0;i<90;i++) {
      //  CCLog(" m_Table %i  m_Clolor %i",m_Table[i],m_Colors[i]);
  //  }
    return true;
}

void ChoiDon::AINewMove(int x, int y) {
   //   _mainAI->stop();
    if (quandi==DARK)     quandi = LIGHT;
    else quandi = DARK;
    //_mainAI->setDelegate(NULL);
   //  CC_SAFE_DELETE(_mainAI);
    //    CCLOG("new move: %d %d", x, y);
	m_X = x;
	m_Y = y;
    if (x==-1 && y == -1) {
        if (quandi==DARK)CCLog("Do thua");
            //CCMessageBox("Dothua","Thong bao.");
       if (quandi==LIGHT) CCLog("Xanh thua");// CCMessageBox("Xanh thua","Thong bao.");
        _main2AI->stop();
        _mainAI->stop();
        return;
    }
         scheduleOnce(schedule_selector(ChoiDon::updateGame),2.f);
    CCLOG(" Di chuyen tu %i den %i ",x,y);
    Piece* piece = (Piece*)this->getChildByTag(x);
    if (piece!=NULL) {
        Piece* piece1 = (Piece*)this->getChildByTag(y);
        if (piece1!=NULL) {
             CCLOG("Y null ");
            this->removeChild(piece1,true);
        }
        CCMoveTo * md = CCMoveTo::create(0.5f,getPosAtIndex(y));
        piece->runAction(md);
        piece->setTag(y);
        // dao vi tri nuoc di
        m_Table[y] = m_Table[x];
        m_Colors[y] = m_Colors[x];
        m_Table[x] = EMPTY;
        m_Colors[x] = EMPTY;
    }else{
         CCLOG("X null ");
    }//
   
    /*
//	scheduleOnce(schedule_selector(ChoiDon::scheduleAIMove), 0.3);
    {
        if (m_X != -1 && m_Y != -1) {
            Piece* piece = dynamic_cast<Piece*>(this->getChildByTag(m_X));
                    piece->setSelected(true);
               
            if (piece) {

                if (m_Colors[m_X] == LIGHT ) {
                   // movePiece(piece, m_Y);
                    CCPoint dest = getPosAtIndex(m_Y);
                    
                    int index = piece->getTag();

                    reorderChild(piece, 2);
                    // change to new pos
                    piece->setTag(m_Y);
                    
                    // reset table
                    moveTable(index, m_Y);
                }
            }
        }
    }
     */
    //    scheduleAIMove(0);
}
void ChoiDon::updateGame(float t){
    CCLOG(" Lai di %i",quandi);
    if (quandi==DARK) {
        _mainAI->LoadBoard(m_Table, m_Colors);
        _mainAI->setSide(DARK);
        _mainAI->setMaxPly(2);
        _mainAI->start();
    }else{
        _main2AI->LoadBoard(m_Table, m_Colors);
        _main2AI->setSide(LIGHT);
        _main2AI->setMaxPly(1);
        _main2AI->start();
    }
}
void ChoiDon::moveTable(int from, int dest) {
    // luu lai nuoc di vao stack
//    if (!m_IsUndoing) {
//        hist_rec h;
//        move m;
//        m.dest = dest;
//        m.from = from;
//        h.capture = m_Table[dest];
//        h.color = m_Colors[dest];
//        h.m = m;
//        m_UndoStack->push(h);
//    }
    
     CCLOG(" Di chuyen tu %i den %i ",from,dest);
    Piece* piece = (Piece*)this->getChildByTag(dest);
    CCMoveTo * md = CCMoveTo::create(2.f,getPosAtIndex(dest));
    piece->runAction(md);
    // dao vi tri nuoc di
    m_Table[dest] = m_Table[from];
    m_Colors[dest] = m_Colors[from];
    
    m_Table[from] = EMPTY;
    m_Colors[from] = EMPTY;
}
void ChoiDon::createTable() {
	for (int i = 0; i < 90; ++i) {
		char type = FIRST_STATE[i];
		if (type != EMPTY) {
			Piece* piece = Piece::create(type, (i < 45 ? DARK : LIGHT));
			piece->setPosition(getPosAtIndex(i));
			piece->setTag(i);
			addChild(piece);
			m_Colors[i] = (i < 45 ? DARK : LIGHT);
		} else {
			m_Colors[i] = EMPTY;
		}
		m_Table[i] = FIRST_STATE[i];
	}
}

CCPoint ChoiDon::getPosAtIndex(int index) {
	return ccp((index % 9) * 480 / 9 + 25, (index / 9) * 500 / 10 + 125);
}