//
//  Piece.h
//  ChineseChessV2
//
//  Created by papo on 7/24/13.
//
//

#ifndef ChineseChessV2_Piece_h
#define ChineseChessV2_Piece_h

// define type


#include "cocos2d.h"

USING_NS_CC;

class Piece: public CCNode {
    int m_Type;
    int m_Side;
    CCSprite*   m_SelectedSprite;
    CCSprite*   m_PieceSprite;
    
public:
    static Piece* create(int type, int side = 0);
    bool initWithType(int type, int side = 0);
    
    // set/ get type
    void setType(int type){m_Type = type;}
    int getType(){return m_Type;}
    
    // set-get side
    int getSide(){return m_Side;}
    void setSelected(bool bSelected);
    bool isSelected(){ return m_SelectedSprite->isVisible();}
    
    void setOpacity(GLubyte opacity);
    void show(CCSequence* action, int count = 5);
    void stop();
    std::string getTypeFileName();
private:
	
    const char* getSideName();
    const char* getTypeName();
};

#endif
