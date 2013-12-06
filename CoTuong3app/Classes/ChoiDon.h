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
USING_NS_CC;
class  AIPlayer;
class ChoiDon : public CCLayer
{
public:
    
    int m_Table[90];
	int m_Colors[90];
    AIPlayer *_mainAI;
    AIPlayer * _main2AI;
    int		m_X, m_Y;
    int quandi;
    bool isDadi;
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    void updateGame(float t);
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    void moveTable(int from, int dest) ;
    void createTable();
    void AINewMove(int x, int y);
    CCPoint getPosAtIndex(int index);
    // implement the "static node()" method manually
    CREATE_FUNC(ChoiDon);
};
#endif /* defined(__CoTuong3__ChoiDon__) */
