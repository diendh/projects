//
//  ChoiDon.h
//  CoTuong3
//
//  Created by ����� H���u ��i���n on 11/28/13.
//
//

#ifndef __CoTuong3__ChoiDon__
#define __CoTuong3__ChoiDon__

#include <iostream>
#include "cocos2d.h"
#include "AIPlayer.h"
using namespace std;
USING_NS_CC;

class AIPlayer;
class ChoiDon : public CCLayer,public AIPlayerDelegate
{
private:
    int m_Table[90];
	int m_Colors[90];
    
    AIPlayer *computerAI;
    
    int	m_AvaibleMoves[20];
    
    bool arrayAtPos[90];
    
    int sumtime;
    
    bool isDARK;

public:
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    void onExit();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    void ReadFilePlist();
    void createTable();
    
    CCPoint getPosAtIndex(int index);
    int getIndexFromPos(cocos2d::CCPoint pos);
    int _newmovefrom; int _newmovedest;
    
    void aiplayerstart();
    
    void addShowPointAtPos(CCPoint pos);
    void removePointAtpos();
    void isNewmovedestInAtPos();
    
    void doAfterMoveDone();
    
    void update();
    // touches events
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

    void menuBack();
    void AIPlayerRunDone(int newmovefrom,int newmovedest);
    
    virtual void keyBackClicked();
    
    void chieutuong();
    void thang();
    void thua();
    
    CREATE_FUNC(ChoiDon);
};
#endif /* defined(__CoTuong3__ChoiDon__) */
