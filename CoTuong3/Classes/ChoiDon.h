//
//  ChoiDon.h
//  CoTuong3
//
//  Created by Đỗ Hữu Điển on 11/28/13.
//
//

#ifndef __CoTuong3__ChoiDon__
#define __CoTuong3__ChoiDon__

#include <iostream>
#include "cocos2d.h"
#include "AIPlayer.h"
USING_NS_CC;

class ChoiDon : public CCLayer,AIPlayerDelegate
{
public:
    
    int m_Table[90];
	int m_Colors[90];

    int sumtime;
    
    bool isDARK;
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    void onExit();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    void createTable();
    
    CCPoint getPosAtIndex(int index);
    int getIndexFromPos(cocos2d::CCPoint pos);
    int _newmovefrom; int _newmovedest;
    
    void aiplayerstart();
    
    void update();
    // touches events
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

    void AIPlayerRunDone(int newmovefrom,int newmovedest);
    
    CREATE_FUNC(ChoiDon);
};
#endif /* defined(__CoTuong3__ChoiDon__) */
