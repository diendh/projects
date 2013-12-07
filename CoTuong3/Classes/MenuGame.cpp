/*
 * MenuGame.cpp
 *
 *  Created on: Nov 25, 2013
 *      Author: dohuudien
 */

#include "MenuGame.h"
#include "ChoseDauTruong.h"
#include "SimpleAudioEngine.h"
#include "UserDataEncrypt.h"
#include "AppDelegate.h"

using namespace CocosDenshion;

CCScene* MenuGame::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();

    // 'layer' is an autorelease object
    MenuGame *layer = MenuGame::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool MenuGame::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    //add background
    CCSprite* pBG = CCSprite::create("MenuChinh/bg-menu.png");
    pBG->setPosition(ccp(240, 400));
    this->addChild(pBG, 0);
    
    scheduleOnce(schedule_selector(MenuGame::showdauan), 0.2);

    //add vang sang
    CCSprite* pAvangsang = CCSprite::create("MenuChinh/domsangchay.png");
    pAvangsang->setPosition(ccp(55, 630));
    pAvangsang->setScale(1.2);
    this->addChild(pAvangsang,1,20);
    CCSprite* pAvangsang2 = CCSprite::create("MenuChinh/domsangchay.png");
    pAvangsang2->setPosition(ccp(425, 630));
    pAvangsang2->setScale(1.2);
    this->addChild(pAvangsang2,1,20);
    schedule(schedule_selector(MenuGame::updatethis));
    
    //add menu play
    CCSprite* spMenuPlay = CCSprite::create("MenuChinh/choi1.png");
    spMenuPlay->setPosition(ccp(240, 150));
    pBG->addChild(spMenuPlay,1,20);
    CCSprite* spXMenuplay = CCSprite::create("MenuChinh/vong1.png");
    spXMenuplay->setPosition(ccp(90, 52));
    CCRotateBy *rota1 = CCRotateBy::create(1, -120);
    spXMenuplay->runAction(CCRepeatForever::create(rota1));
    spMenuPlay->addChild(spXMenuplay,0);
    
    CCMenuItemImage *pItemPlay = CCMenuItemImage::create("MenuChinh/choi.png", "MenuChinh/choi2.png", "MenuChinh/choi2.png", this,menu_selector(MenuGame::menuPlay));
    pItemPlay->setPosition(90,52);
    CCMenu* pMenuPlay = CCMenu::create(pItemPlay, NULL);
    pMenuPlay->setPosition(CCPointZero);
    spMenuPlay->addChild(pMenuPlay, 1);

    //add menu info, download, share
     CCMenuItemImage *pItemInfo = CCMenuItemImage::create("MenuChinh/info.png", "MenuChinh/info2.png", "MenuChinh/info2.png", this,menu_selector(MenuGame::menuInfo));
    pItemInfo->setPosition(ccp(100, 50));
    
    CCMenuItemImage *pItemshare = CCMenuItemImage::create("MenuChinh/sher.png", "MenuChinh/sher2.png", "MenuChinh/sher2.png", this,menu_selector(MenuGame::menuShare));
    pItemshare->setPosition(ccp(200, 50));
    
    CCMenuItemImage *pItemDownload = CCMenuItemImage::create("MenuChinh/nut-downpng.png", "MenuChinh/nut-downpng2.png", "MenuChinh/nut-downpng2.png", this,menu_selector(MenuGame::menuDownload));
    pItemDownload->setPosition(ccp(300, 50));
    
    CCMenuItemImage *pItemExit = CCMenuItemImage::create("MenuChinh/nut-thoat.png", "MenuChinh/nut-thoat2.png", "MenuChinh/nut-thoat2.png", this,menu_selector(MenuGame::menuExit));
    pItemExit->setPosition(ccp(400, 50));
    if (!DataEncrypt::share()->getBoolForKey("music", true))
        pItemExit->selected();
    
    CCMenu* pMenu = CCMenu::create(pItemInfo,pItemshare,pItemDownload,pItemExit, NULL);
    pMenu->setPosition(CCPointZero);
    pBG->addChild(pMenu, 1);
    
    //am thanh game
     SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Sound/2/Binh-thuong.mp3", true);
     if (!DataEncrypt::share()->getBoolForKey("music", true))
        SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    
    CCParticleSystem* lua = CCParticleSystemQuad::create("lua.plist");
    lua->setPosition(ccp(400, 170));
    this->addChild( lua, 5 );
//    CCParticleSystem* lua2 = CCParticleSystemQuad::create("lua.plist");
//       lua2->setPosition(ccp(80, 170));
//       this->addChild( lua2, 5 );
    
    return true;
}

void MenuGame::menuPlay(){
     AppDelegate::musicButton();
     CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.2, ChoseDauTruong::scene()));
}

void MenuGame::menuInfo(){
    
    for (int i = 0; i < this->getChildren()->count() ; i++) {
        CCNode *node = dynamic_cast<CCNode*>(getChildren()->objectAtIndex(i));
        if (node) {
            node->setVisible(false);
        }
    }
    
//    CCAlertView* alv = CCAlertView::create("tile", "mess", "cannel", "oke", this,  callfuncO_selector(MenuGame::oke), callfuncO_selector(MenuGame::can));
//    this->addChild(alv);
    
    AppDelegate::musicButton();
}
void MenuGame::menuShare(){
    AppDelegate::musicButton();
    
}
void MenuGame::menuDownload(){
   AppDelegate::musicButton();
    
}
void MenuGame::menuExit(CCObject* pSender){
     if (DataEncrypt::share()->getBoolForKey("music", true)){
        dynamic_cast<CCMenuItemImage*>(pSender)->selected();
        SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
        SimpleAudioEngine::sharedEngine()->pauseAllEffects();
         DataEncrypt::share()->setBoolForKey("music", false);
    }
    else{
        SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
        SimpleAudioEngine::sharedEngine()->resumeAllEffects();
        DataEncrypt::share()->setBoolForKey("music", true);
    }
    DataEncrypt::share()->save();
}

void MenuGame::updatethis(){
    for (int i = 0; i < this->getChildren()->count() ; i++) {
        CCSprite *sp = dynamic_cast<CCSprite*>(this->getChildren()->objectAtIndex(i));
        if (!sp) {
            CCProgressTimer *proreesstimer = dynamic_cast<CCProgressTimer*>(this->getChildren()->objectAtIndex(i));
            if (!proreesstimer) {
                break;
            }
            proreesstimer->setPercentage(proreesstimer->getPercentage() + 1);
            break;
        }
        if (sp->getTag() == 20) {
            if (sp->getPositionY() >= 630) {
                x = -2;
            }
            if (sp->getPositionY() <= 345) {
                x = 2;
            }
            sp->setPosition(ccp(sp->getPositionX(), sp->getPositionY() + x));
        }
    }
}

void MenuGame::showdauan(){
    //add bg ky tien
    CCSprite* pBGkytien = CCSprite::create("MenuChinh/antrien.png");
    pBGkytien->setPosition(ccp(240, 613));
    pBGkytien->setScale(5);
    this->addChild(pBGkytien, 1);
    CCScaleTo *scale = CCScaleTo::create(0.2f,1);
    pBGkytien->runAction(CCSequence::create(scale,CCCallFuncN::create(this, callfuncN_selector(MenuGame::showkytien)),NULL));    
}

void MenuGame::showkytien(){

    if (DataEncrypt::share()->getBoolForKey("music", true))
     SimpleAudioEngine::sharedEngine()->playEffect("Sound/2/An-quan.mp3", false);

    CCSprite* pkytien = CCSprite::create("MenuChinh/chukytien.png");
    CCProgressTimer *proreesstimer = CCProgressTimer::create(pkytien);
    proreesstimer->setType(kCCProgressTimerTypeBar);
    proreesstimer->setPosition(ccp(240, 613));
    proreesstimer->setMidpoint(ccp(1, 1));
    proreesstimer->setBarChangeRate(ccp(0,1));
    this->addChild(proreesstimer,30);
}

