//
//  ChonNhanVat.cpp
//  CoTuong3
//
//  Created by Đỗ Hữu Điển on 11/28/13.
//
//

#include "ChonNhanVat.h"
#include "ChoseDauTruong.h"
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
    this->setKeypadEnabled(true);
    //add bg
    CCSprite* pBG = CCSprite::create("DauTruong/2-1.png");
    pBG->setPosition(ccp(240, 400));
    this->addChild(pBG, 0);
    
    //add menu nhan vat
    CCMenuItemImage *pNhanVat1 = CCMenuItemImage::create("DauTruong/caibang.png", "DauTruong/caibang2.png", "DauTruong/caibang2.png", this,menu_selector(ChonNhanVat::menuNhanVat));
    pNhanVat1->setTag(0);
    pNhanVat1->setPosition(ccp(115, 550));
    
    CCMenuItemImage *pNhanVat2 = CCMenuItemImage::create("DauTruong/trieudinh.png", "DauTruong/trieudinh2.png", "DauTruong/trieudinh2.png", this,menu_selector(ChonNhanVat::menuNhanVat));
    pNhanVat2->setTag(1);
    pNhanVat2->setPosition(ccp(360, 530));
    
    CCMenuItemImage *pNhanVat3 = CCMenuItemImage::create("DauTruong/tieudao.png", "DauTruong/tieudao2.png", "DauTruong/tieudao2.png", this,menu_selector(ChonNhanVat::menuNhanVat));
    pNhanVat3->setTag(2);
    pNhanVat3->setPosition(ccp(115, 210));
    
    CCMenuItemImage *pNhanVat4 = CCMenuItemImage::create("DauTruong/vodang.png", "DauTruong/vodang2.png", "DauTruong/vodang2.png", this,menu_selector(ChonNhanVat::menuNhanVat));
    pNhanVat4->setTag(3);
    pNhanVat4->setPosition(ccp(360, 207));

    CCMenu* pMenu = CCMenu::create(pNhanVat1,pNhanVat2,pNhanVat3,pNhanVat4, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    //add sv
    CCSprite* pSV = CCSprite::create("DauTruong/vs2.png");
    pSV->setPosition(ccp(240, 370));
    this->addChild(pSV, 2);
    
    return true;
}

void ChonNhanVat::menuNhanVat(cocos2d::CCObject *pSender){
    switch (dynamic_cast<CCMenuItemImage*>(pSender)->getTag()) {
        case 0:
            CCLOG("cai bang");
            break;
        case 1:
            CCLOG("trieu dinh");
            break;
        case 2:
            CCLOG("tieu dao");
            break;
        case 3:
            CCLOG("vo dang");
            break;
    }
    CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.2, ChoseDauTruong::scene()));
}

void ChonNhanVat::keyBackClicked(){
     CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.2, ChoseDauTruong::scene()));
}
