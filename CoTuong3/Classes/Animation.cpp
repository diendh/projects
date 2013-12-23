//
//  Animation.cpp
//  CoTuong3
//
//  Created by Tr���n Anh Tu���n on 12/13/13.
//
//tot 0
//si 1
//tuong 2
//ma 3
//phao 4
//xe 5
//tuong 6
//
//
//


#include "Animation.h"

Animation::Animation(int type, int typebidanh,  std::string  phaidanh,  std::string  phaibidanh)
{
    //setType(type,typebidanh,phaidanh,phaibidanh);
    _typedanh = type;
    _typebidanh = typebidanh;
    _phaidanh = phaidanh;
    _phaibidanh = phaibidanh;
     refresh();
    delegate = NULL;
}

Animation::~Animation()
{
    CCLOG("loddd");
    //delete this;
}

CCSprite* Animation::sprite(int typedanh,int typebidanh,  std::string  phaidanh,  std::string  phaibidanh){
    Animation* b = new Animation(typedanh,typebidanh,phaidanh,phaibidanh);
    //b->autorelease();
    return b;
}

void Animation::setType(int type,int typebd,  std::string  phaidanh,  std::string  phaibidanh){
    refresh();
}

void Animation::refresh(){
    this->initWithFile("animation/khungplay.png");
    this->setScaleY(0);
    CCScaleTo * scale = CCScaleTo::create(0.6f,1);
    CCFiniteTimeAction* scaleDone = CCCallFuncN::create(this, callfuncN_selector(Animation::scaledone));
    this->runAction(CCSequence::create(scale,scaleDone,NULL));
    CCLOG("so  %s    %i",_phaidanh.c_str(),_typedanh);
    
    
      
}
/*
CCAnimation* Animation::getanimation(CCString* ah,int soluong){
    
    auto cacher = CCSpriteFrameCache::sharedSpriteFrameCache();
    cacher->addSpriteFramesWithFile(CCString::createWithFormat("animation/%s.plist",ah->getCString())->getCString());   
    const int kNumberOfFrames = soluong;
    CCArray* frames = new CCArray;
    frames->initWithCapacity(kNumberOfFrames);
    for( int i = 1; i <= kNumberOfFrames; i++ )
    {
        CCString* filename =
        CCString::createWithFormat("slice0%i_0%i.png", i,i);
        frames->addObject(cacher->spriteFrameByName(filename->getCString()));
    }
    // play the animation
    CCAnimation* anim = new CCAnimation;
    anim->initWithSpriteFrames(frames);
    anim->setDelayPerUnit(2.8f / 14.0f);
    anim->setRestoreOriginalFrame(true);
    return anim;
}

*/
void Animation::rundone(CCObject* node){
    if (delegate!=NULL) {
         delegate->AnimationRunDone();
    }
    this->removeFromParent();  
}
void Animation::scaledone(CCObject *node){
	
    CCSprite* spriterdanh = new CCSprite;
     CCSpriteFrameCache* cacher = CCSpriteFrameCache::sharedSpriteFrameCache();
    spriterdanh->initWithSpriteFrameName(CCString::createWithFormat("%i.png",_typedanh)->getCString());
    CCSpriteFrame* frame =  cacher->spriteFrameByName(CCString::createWithFormat("%i.png",_typedanh)->getCString());
    spriterdanh->setDisplayFrame(frame);
   
    
    CCArray* frames = new CCArray;
    frames->initWithCapacity(20);
    for( int i = 1;; i++ )
    {
        CCLOG("so  %i",i);
        if (cacher->spriteFrameByName(CCString::createWithFormat("%i_%i.png",_typedanh,i)->getCString())) {
            CCString* filename = CCString::createWithFormat("%i_%i.png",_typedanh,i);
            frames->addObject(cacher->spriteFrameByName(filename->getCString()));
        }else break;
    }
    //CCString* filename = CCString::createWithFormat("%i_0.png",_typedanh);
    //frames->addObject(cacher->spriteFrameByName(filename->getCString()));
    // play the animation
    CCAnimation* anim = new CCAnimation;
    anim->initWithSpriteFrames(frames);
    anim->setDelayPerUnit(2.8f / 14.0f);
    anim->setRestoreOriginalFrame(true);
    spriterdanh->setPosition(ccp(this->getContentSize().width/2-spriterdanh->getContentSize().width/4,this->getContentSize().height/2));
    spriterdanh->setTag(1010);
    //cacher->removeSpriteFrames();
    
    //bi danh
    
    
    //auto cacher = CCSpriteFrameCache::sharedSpriteFrameCache();
    CCLOG("so  %s    %i",_phaidanh.c_str(),_typedanh);
//    CCString* plitbidanh = CCString::createWithFormat("animation/%s/%s.plist",_phaibidanh.c_str(),_phaibidanh.c_str());
//    cacher->addSpriteFramesWithFile(plitbidanh->getCString());
    CCSprite* spriterbidanh = new CCSprite;
    spriterbidanh->initWithSpriteFrameName(CCString::createWithFormat("%i_0.png",_typebidanh)->getCString());
    CCSpriteFrame* framebidanh =  cacher->spriteFrameByName(CCString::createWithFormat("%i_0.png",_typebidanh)->getCString());
    spriterbidanh->setDisplayFrame(framebidanh);
    spriterbidanh->setFlipX(true);
    
    
    
//    CCArray* frames = new CCArray;
//    frames->initWithCapacity(20);
//    for( int i = 1;; i++ )
//    {
//        CCLOG("so  %i",i);
//        if (cacher->spriteFrameByName(CCString::createWithFormat("%i_%i.png",_typebidanh,i)->getCString())) {
//            CCString* filename = CCString::createWithFormat("%i_%i.png",_typebidanh,i);
//            frames->addObject(cacher->spriteFrameByName(filename->getCString()));
//        }else break;
//    }
//    // play the animation
//    CCAnimation* anim = new CCAnimation;
//    anim->initWithSpriteFrames(frames);
//    anim->setDelayPerUnit(2.8f / 14.0f);
//    anim->setRestoreOriginalFrame(true);
    
    spriterbidanh->setPosition(ccp(this->getContentSize().width/2+spriterbidanh->getContentSize().width/5,this->getContentSize().height/2));
    spriterbidanh->setTag(2010);
    this->addChild(spriterbidanh,10);
    

    
    //bi danh
    
    
    
    CCParticleSystem* thang = CCParticleSystemQuad::create("animation/gio.plist");
    thang->setPosition(ccp(spriterdanh->getContentSize().width/2,spriterdanh->getContentSize().height/2));
    thang->setTag(100);
    spriterdanh->addChild(thang, 999 );
    
    CCMoveTo* movedanh  = CCMoveTo::create(0.1f,ccp(this->getContentSize().width/2,this->getContentSize().height/2));
    CCMoveTo* movelui  = CCMoveTo::create(0.1f,ccp(this->getContentSize().width/2-spriterdanh->getContentSize().width/4,this->getContentSize().height/2));
    CCMoveTo* dungyen  = CCMoveTo::create(0.4f,ccp(this->getContentSize().width/2-spriterdanh->getContentSize().width/4,this->getContentSize().height/2));
    CCFiniteTimeAction* actionDone = CCCallFuncN::create(this, callfuncN_selector(Animation::scaledelete));
    
    CCFiniteTimeAction* deletegioDone = CCCallFuncN::create(this, callfuncN_selector(Animation::deletegio));
    CCFiniteTimeAction* addgioDone = CCCallFuncN::create(this, callfuncN_selector(Animation::addgio));
    CCFiniteTimeAction* dayluidich = CCCallFuncN::create(this, callfuncN_selector(Animation::daylui));
    spriterdanh->runAction(CCSequence::create(movedanh,deletegioDone,CCSpawn::create(CCAnimate::create(anim),dayluidich),addgioDone,movelui,deletegioDone,dungyen,actionDone,NULL));
    this->addChild(spriterdanh,15);
    //cacher->removeSpriteFrames();
    
}
void Animation::daylui(cocos2d::CCObject *node){
    if (_typebidanh==6) {
        
    }else{
        CCSprite* spritebidah = (CCSprite*)this->getChildByTag(2010);
        if (spritebidah) {
             CCMoveTo* movedanh  = CCMoveTo::create(0.1f,ccp(this->getContentSize().width/2+spritebidah->getContentSize().width/3,this->getContentSize().height/2));
            spritebidah->runAction(movedanh);
            CCParticleSystem* thang = CCParticleSystemQuad::create("animation/toemau.plist");
            thang->setPosition(ccp(spritebidah->getContentSize().width/2,spritebidah->getContentSize().height/2));
            thang->setTag(100);
            spritebidah->addChild(thang, 999 );
            
        }
    }
}
void Animation::addgio(cocos2d::CCObject *node){
    CCSprite* spriterdanh = (CCSprite*)this->getChildByTag(1010);
    CCParticleSystem* thang = CCParticleSystemQuad::create("animation/gio.plist");
    thang->setPosition(ccp(spriterdanh->getContentSize().width/2,spriterdanh->getContentSize().height/2));
    thang->setTag(100);
    spriterdanh->addChild(thang, 999 );
    CCParticleSystem *sp = dynamic_cast<CCParticleSystem*>(spriterdanh->getChildByTag(100));
    //spriterdanh->getChildByTag(100);
    if (sp) {
        CCLOG("da add gio");
    }
}
void Animation::deletegio(cocos2d::CCObject *node){
    CCSprite* spriterdanh = (CCSprite*)this->getChildByTag(1010);
    spriterdanh->removeChildByTag(100,true);
     //  CC_SAFE_DELETE(spriterdanh->getChildByTag(100));
    CCParticleSystem *sp = dynamic_cast<CCParticleSystem*>(spriterdanh->getChildByTag(100));
    //spriterdanh->getChildByTag(100);
    if (!sp) {
        CCLOG("da xoa gio");
    }
    delete sp;
}
void Animation:: scaledelete(CCObject* node){
    
      CCScaleTo * scale = CCScaleTo::create(0.08f,1,0);
      CCFiniteTimeAction* actionDone = CCCallFuncN::create(this, callfuncN_selector(Animation::rundone));
      this->runAction(CCSequence::create(scale,actionDone,NULL));
}
void Animation::setDelegate(AnimationDelegate *tt){
    delegate = tt;
}
void AnimationDelegate:: AnimationRunDone(){
    
}

