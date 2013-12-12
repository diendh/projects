//
//  Piece.cpp
//  ChineseChessV2
//
//  Created by papo on 7/24/13.
//
//

#include "Piece.h"
#include "define.h"

Piece* Piece::create(int type, int side)
{
    Piece* p = new Piece;
    if (p && p->initWithType(type, side)) {
        p->autorelease();
        return p;
    }
    CC_SAFE_DELETE(p);
    p = NULL;
    return NULL;
}

bool Piece::initWithType(int type, int side)
{
    m_Type = type;
    m_Side = side;
    if (this->init()) {
        m_SelectedSprite = CCSprite::create("Banchoi/quanco/chon-quan.png");
		CCRotateBy* rotate = CCRotateBy::create(0.5, 180);
		CCRepeatForever* repeat = CCRepeatForever::create(rotate);
        m_SelectedSprite->setVisible(false);
		m_SelectedSprite->runAction(repeat);
		if (getSide() == LIGHT)
		{
			m_SelectedSprite->setColor(ccGREEN);
		}
        addChild(m_SelectedSprite);
        
		m_PieceSprite = CCSprite::create(getTypeFileName().c_str());
        addChild(m_PieceSprite);
        return true;
    }
    return false;
}

std::string Piece::getTypeFileName()
{
    std::string fileName = "Banchoi/quanco/";
	fileName += getTypeName();
    fileName += "_";
    fileName += getSideName();
    fileName += ".png";
    
    return fileName;
}

const char* Piece::getSideName()
{
    if (getSide() == DARK) {
        return "dark";
    }
    
    return "red";
}

const char* Piece::getTypeName()
{
    switch (getType()) {
        case BISHOP:
            return "bishop";
            break;
        case CANNON:
            return "cannon";
        case ELEPHAN:
            return "elephan";
        case KING:
            return "king";
        case KNIGHT:
            return "knight";
        case PAWN:
            return "pawn";
        case ROOK:
            return "rook";
            
        default:
            break;
    }
    return "";
}

void Piece::setSelected(bool bSelected)
{
    m_SelectedSprite->setVisible(bSelected);
    if (bSelected) {
        this->setZOrder(500);
        this->runAction(CCScaleTo::create(0.1, 1.15));
    }
    else{
        this->setZOrder(90);
        this->runAction(CCScaleTo::create(0.1, 1.0));
    }
}

void Piece::setOpacity(GLubyte opacity)
{
    m_PieceSprite->setOpacity(opacity);
    m_SelectedSprite->setOpacity(opacity);
}

void Piece::show(CCSequence* action, int count)
{
//    CCSpriteBatchNode;
    for (int i = 0; i < count; ++i) {
        CCSprite* sprite = CCSprite::create(getTypeFileName().data());
        sprite->setOpacity(70);
        sprite->setScale(1.15);
        sprite->setPosition(this->getPosition());
        CCSequence* ac = (CCSequence*)action->copy();
        CCCallFunc* callback = CCCallFunc::create(sprite, callfunc_selector(CCSprite::removeFromParent));
        sprite->runAction(CCSequence::create(CCDelayTime::create(0.1 + 0.1 * i), ac, callback, NULL));
        this->getParent()->addChild(sprite, this->getOrderOfArrival() + 2, 1200 + i);
        CCUserDefault::sharedUserDefault()->setBoolForKey("dshdj", true);
        CCUserDefault::sharedUserDefault()->flush();
    }
}

void Piece::stop()
{
    for (int i = 0; i < 5; ++i) {
        this->getParent()->removeChildByTag(1200 + i);
    }
}
