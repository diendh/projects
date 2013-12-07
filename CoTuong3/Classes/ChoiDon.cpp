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
    
    CCDictionary *pConfInfo;
    // create this dictionary object within the content of our plist configuration file
    pConfInfo = CCDictionary::createWithContentsOfFile("0.plist");
   
    int width, height;
    
    // Get data for the given key. As you can see below, you can get this data within the format you expect (string, int, float....)
    //pBackgroundFile = pConfInfo->valueForKey(keyValue)->getCString()()
    width = pConfInfo->valueForKey("WIDTH_01")->intValue();
    height= pConfInfo->valueForKey("HEIGHT_01")->intValue();
    CCLOG("%i %i",width,height);
    
    computerAI = new AIPlayer();
    computerAI->setDelegate(this);
    computerAI->setMaxPly(6);
    computerAI->setSide(LIGHT);
    
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
			Piece* piece = Piece::create(type, (FIRST_STATE_COLOR[i] ? LIGHT : DARK));
			piece->setPosition(getPosAtIndex(i));
			piece->setTag(i);
			addChild(piece);
			m_Colors[i] = FIRST_STATE_COLOR[i] ? LIGHT : DARK;
		} else {
			m_Colors[i] = EMPTY;
		}
		m_Table[i] = FIRST_STATE[i];
	}
    this->schedule(schedule_selector(ChoiDon::update),1.0f);
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
	 CCLOG("tong time la: %i",sumtime);
    if (getChildByTag(100)) {
        return false;
    }
    CCPoint tPosition = pTouch->getLocationInView();
    tPosition = CCDirector::sharedDirector()->convertToGL(tPosition);
    int index = getIndexFromPos(tPosition);
    if (index >= 0) {
        /* Lay quan co o vi tri index neu co */
        Piece* piece = dynamic_cast<Piece*>(getChildByTag(index));
        if (!piece || piece->getSide()==LIGHT) {
            AIPlayerRunDone(_newmovedest, index);
            return false;
        }
        removePointAtpos();
        
        if (piece->getSide() == DARK) {
            piece->setSelected(true);
            
            AIPlayer::shared()->LoadBoard(m_Table, m_Colors);
            int* moves = AIPlayer::shared()->getAllAvaiblePos(index);
            
            for (int i = 0; i < 20; i++) {
                m_AvaibleMoves[i] = moves[i];
                
                if (moves[i] == -1) {
                    break;
                }
                
                addShowPointAtPos(getPosAtIndex(moves[i]));
            }
            delete[] moves;
        }
            _newmovedest = index;
    }
    
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
    if (_newmovedest == _newmovefrom) {
        for (int i = 0; i < this->getChildren()->count() ; i++) {
            Piece *piece = dynamic_cast<Piece*>(this->getChildren()->objectAtIndex(i));
            if (piece) {
                if (piece->isSelected()){
                    piece->setPosition(getPosAtIndex(_newmovedest));
                }
            }
        }
        return;
    }
    AIPlayerRunDone(_newmovedest, _newmovefrom);
}

void ChoiDon::AIPlayerRunDone(int newmovefrom, int newmovedest){
    
    CCLOG("tong time la: %i",sumtime);
    
    if (!this->getChildren()) {
        return;
    }
    
    removeChildByTag(100, true);
    
    if (!isDARK){
        if (!arrayAtPos[newmovedest]) {
            for (int i = 0; i < this->getChildren()->count() ; i++) {
                Piece *piece = dynamic_cast<Piece*>(this->getChildren()->objectAtIndex(i));
                if (piece) {
                    if (piece->getTag() == newmovefrom) {
                        piece->setPosition(getPosAtIndex(newmovefrom));
                    }
                }
            }
            
            CCLOG("!arrayAtPos[%i]",newmovedest);
            return;
        }
    }
    
    computerAI->stop();
    
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
                CCMoveTo *moveto = CCMoveTo::create(0.5f, getPosAtIndex(newmovedest));
                piece->runAction(CCSequence::create(moveto,CCCallFuncN::create(this,callfuncN_selector(ChoiDon::aiplayerstart)),NULL));
//                piece->runAction(moveto);
                m_Table[newmovedest] = m_Table[newmovefrom];
                m_Colors[newmovedest] = m_Colors[newmovefrom];
                m_Table[newmovefrom] = EMPTY;
                m_Colors[newmovefrom] = EMPTY;
            }
        }
    }
    removePointAtpos();    
}

void ChoiDon::aiplayerstart(){
    if (isDARK) {
        isDARK = false;
        return;
    }
    
    CCSprite *sp = CCSprite::create("hourglass.png");
    sp->setPosition(ccp(240, 400));
    CCRotateBy *rota = CCRotateBy::create(0.2, 20);
    sp->runAction(CCRepeatForever::create(rota));
    addChild(sp,100,100);
    
    isDARK = true;
	computerAI->LoadBoard(m_Table, m_Colors);
    computerAI->start();
    sumtime = 0;
}

void ChoiDon::update(){
    sumtime++;
}

void ChoiDon::addShowPointAtPos(CCPoint pos) {    
    CCSprite* movePoint = CCSprite::create("Banchoi/quanco/goi-y-quan.png");
    movePoint->setPosition(pos);
    movePoint->runAction(CCRepeatForever::create(CCSequence::create(
                                                                    CCFadeIn::create(0.5),
                                                                    CCFadeOut::create(0.5),
                                                                    0
                                                                    )));
    
    this->addChild(movePoint, 1, 13258614);
    arrayAtPos[getIndexFromPos(pos)] = true;
}

void ChoiDon::removePointAtpos(){
    if (!getChildren()->count()) {
        return;
    }
    memset(arrayAtPos, 0, sizeof(arrayAtPos));
    
    for (int i = 0; i < getChildren()->count(); i++) {
        Piece *piece = dynamic_cast<Piece*>(this->getChildren()->objectAtIndex(i));
        if (piece) {
            if (piece->isSelected()){
                piece->setSelected(false);
            }
        }
        removeChildByTag(13258614, true);
    }
    
}
