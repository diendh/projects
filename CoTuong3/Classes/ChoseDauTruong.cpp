//
//  ChoseDauTruong.cpp
//  CoTuong3
//
//  Created by Đỗ Hữu Điển on 11/26/13.
//
//

#include "ChoseDauTruong.h"
#include "MenuGame.h"
#include "ChonNhanVat.h"
#include "ChoiDon.h"
#include "AppDelegate.h"

CCScene* ChoseDauTruong::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    ChoseDauTruong *layer = ChoseDauTruong::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ChoseDauTruong::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    this->setKeypadEnabled(true);
    //add bg
    CCSprite* pBG = CCSprite::create("CheDoChoi/chedochoi1.png");
    pBG->setPosition(ccp(240, 400));
    this->addChild(pBG, 0);
    
    CCMenuItemImage *pItemChoidon = CCMenuItemImage::create("CheDoChoi/choidon.png", "CheDoChoi/choidon2.png", "CheDoChoi/choidon2.png", this,menu_selector(ChoseDauTruong::menuDauDon));
    pItemChoidon->setPosition(130,250);
    
    CCMenuItemImage *pItemchiendich = CCMenuItemImage::create("CheDoChoi/chiendich.png", "CheDoChoi/chiendich2.png", "CheDoChoi/chiendich2.png", this,menu_selector(ChoseDauTruong::menuChienDich));
    pItemchiendich->setPosition(360,250);
    
    CCMenu* pMenuPlay = CCMenu::create(pItemChoidon,pItemchiendich, NULL);
    pMenuPlay->setPosition(CCPointZero);
    this->addChild(pMenuPlay, 1);

    return true;
}

void ChoseDauTruong::menuDauDon(){
    AppDelegate::musicButton();
    CCDirector::sharedDirector()->replaceScene(CCTransitionTurnOffTiles::create(0.2, ChoiDon::scene()));
}

void ChoseDauTruong::menuChienDich(){
    AppDelegate::musicButton();
    CCDirector::sharedDirector()->replaceScene(CCTransitionFlipAngular::create(0.2, ChonNhanVat::scene()));
}

void ChoseDauTruong::keyBackClicked(){
    CCDirector::sharedDirector()->replaceScene(CCTransitionFlipAngular::create(0.2, MenuGame::scene()));
}