//
//  ChoiDon.cpp
//  CoTuong3
//
//  Created by ����� H���u ��i���n on 11/28/13.
//
//

#include "ChoiDon.h"
#include "define.h"
#include "Piece.h"
#include "ChoseDauTruong.h"
#include "CCSpriterX.h"

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
    CCLOG("setTouchEnabled");
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    
    //add bg
    CCSprite* pBG = CCSprite::create("ChoiDon/khung-banchoi1.png");
    pBG->setPosition(ccp(240, 350));
    this->addChild(pBG, 0);
    
    createTable();
    
//    CCSpriterX *animator = CCSpriterX::create("demochibi/7.scml");
//    animator->setPosition(ccp(200, 300));
//    animator->setScale(0.8f);
//    animator->playAnimation("NewAnimation");
//    this->addChild(animator, 0, 100);

    return true;
}

void ChoiDon::onExit() {
    CCLayer::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
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
    this->schedule(schedule_selector(ChoiDon::update),1.0f);
	AIPlayer::shared()->LoadBoard(m_Table, m_Colors);
    AIPlayer::shared()->setSide(LIGHT);
    AIPlayer::shared()->setDelegate(this);
    AIPlayer::shared()->start();
}

CCPoint ChoiDon::getPosAtIndex(int index) {
	return ccp((index % 9) * 480 / 9 + 25, (index / 9) * 500 / 10 + 125);
}

int ChoiDon::getIndexFromPos(cocos2d::CCPoint pos) {
    int pX = pos.x / 480 * 9;
    int pY = (pos.y - 95) / 500 * 10;
    if (pX < 0 || pX > 8) {
        CCLOG("vuot be ngang");
        return -1;
    }
    if (pY < 0 || pY > 9) {
        CCLOG("vuot be doc");
        return -1;
    }
    
    return (pX + pY * 9);
}


bool ChoiDon::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    CCPoint tPosition = pTouch->getLocationInView();
    tPosition = CCDirector::sharedDirector()->convertToGL(tPosition);
    int index = getIndexFromPos(tPosition);
    if (index >= 0) {
        /* Lay quan co o vi tri index neu co */
        Piece* piece = dynamic_cast<Piece*>(getChildByTag(index));
        if (!piece) {
            return false;
        }
         piece->setSelected(true);
    }
    _newmovedest = index;
    return true;
}

void ChoiDon::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    CCPoint tPosition = pTouch->getLocationInView();
    tPosition = CCDirector::sharedDirector()->convertToGL(tPosition);
    for (int i = 0; i < this->getChildren()->count() ; i++) {
        Piece *piece = dynamic_cast<Piece*>(this->getChildren()->objectAtIndex(i));
        if (piece) {
            if (piece->isSelected()){
                piece->setPosition(tPosition);
            }
        }
    }
}

void ChoiDon::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    CCPoint tPosition = pTouch->getLocationInView();
    tPosition = CCDirector::sharedDirector()->convertToGL(tPosition);
    _newmovefrom = getIndexFromPos(tPosition);
    AIPlayerRunDone(_newmovedest, _newmovefrom);
    for (int i = 0; i < this->getChildren()->count() ; i++) {
        Piece *piece = dynamic_cast<Piece*>(this->getChildren()->objectAtIndex(i));
        if (piece) {
            if (piece->isSelected()){
                piece->setSelected(false);
            }
        }
    }
//     CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.2, ChoseDauTruong::scene()));
//    AIPlayer::shared()->stop();
//    aiplayerstart();
}

void ChoiDon::AIPlayerRunDone(int newmovefrom, int newmovedest){
    
    CCLOG("tong time la: %i",sumtime);
    
    if (!this->getChildren()) {
        return;
    }
    
    for (int i = 0; i < this->getChildren()->count() ; i++) {
        Piece *piece = dynamic_cast<Piece*>(this->getChildren()->objectAtIndex(i));
        if (piece) {
            if (piece->getTag() == newmovedest) {
                piece->removeFromParent();
            }
        }
    }
    
    for (int i = 0; i < this->getChildren()->count() ; i++) {
        Piece *piece = dynamic_cast<Piece*>(this->getChildren()->objectAtIndex(i));
        if (piece) {
            if (piece->getTag() == newmovefrom) {
                piece->setTag(newmovedest);
//                piece->setPosition(getPosAtIndex(newmovedest));
                CCMoveTo *moveto = CCMoveTo::create(1.0f, getPosAtIndex(newmovedest));
                piece->runAction(CCSequence::create(moveto,CCCallFuncN::create(this,callfuncN_selector(ChoiDon::aiplayerstart)),NULL));
//                piece->runAction(moveto);
                m_Table[newmovedest] = m_Table[newmovefrom];
                m_Colors[newmovedest] = m_Colors[newmovefrom];
                m_Table[newmovefrom] = EMPTY;
                m_Colors[newmovefrom] = EMPTY;
            }
        }
    }
        
}

void ChoiDon::aiplayerstart(){
    int random = arc4random()%7;
    CCLOG("random %i",random);
    AIPlayer::shared()->LoadBoard(m_Table, m_Colors);
    if (isDARK) {
        
        isDARK = false;
        return;
//        AIPlayer::shared()->setMaxPly(7);
//        AIPlayer::shared()->setSide(LIGHT);
    }else{
        AIPlayer::shared()->setMaxPly(6);
        AIPlayer::shared()->setSide(LIGHT);
        isDARK = true;
    }
    AIPlayer::shared()->start();
    sumtime = 0;
}

void ChoiDon::update(){
    sumtime++;
}
