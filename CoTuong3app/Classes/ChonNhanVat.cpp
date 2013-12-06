//
//  ChonNhanVat.cpp
//  CoTuong3
//
//  Created by Đỗ Hữu Điển on 11/28/13.
//
//

#include "ChonNhanVat.h"

CCScene* ChonNhanVat::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    ChonNhanVat *layer = ChonNhanVat::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ChonNhanVat::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    //add bg
    CCSprite* pBG = CCSprite::create("DauTruong/chonnv3.png");
    pBG->setPosition(ccp(240, 400));
    this->addChild(pBG, 0);
    
    return true;
}
