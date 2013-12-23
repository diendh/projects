//
//  Animation.h
//  CoTuong3
//
//  Created by Trần Anh Tuấn on 12/13/13.
//
//

#ifndef __CoTuong3__Animation__
#define __CoTuong3__Animation__
#include "cocos2d.h"
using namespace cocos2d;
#include <iostream>

class AnimationDelegate
{
public:
	virtual void AnimationRunDone();
};

class Animation : public CCSprite,AnimationDelegate
{
public:
    AnimationDelegate * delegate;
    void setDelegate(AnimationDelegate * tt);
    void rundone(CCObject* node);
       void scaledone(CCObject* node);
    void scaledelete(CCObject* node);
     void addgio(CCObject* node);
    void deletegio(CCObject* node);
     void daylui(CCObject* node);
    int _typebidanh;
    int _typedanh;
    std::string  _phaidanh;
     std::string  _phaibidanh;
    Animation(int typedanh, int typebidanh,  std::string  phaidanh,  std::string  phaibidanh);
    ~Animation();
    static CCSprite* sprite(int typedanh,int typebidanh,  std::string  phaidanh,  std::string  phaibidanh);
    void setType(int typedanh,int typebidanh,  std::string  phaidanh,  std::string  phaibidanh);
private:
    void refresh();
};


#endif /* defined(__CoTuong3__Animation__) */
