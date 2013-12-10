/*
 * MenuGame.h
 *
 *  Created on: Nov 25, 2013
 *      Author: dohuudien
 */

#include "cocos2d.h"

#ifndef MENUGAME_H_
#define MENUGAME_H_

USING_NS_CC;

class MenuGame : public CCLayer
{
private:
    float x;
public:
	 // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	    virtual bool init();

	    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static CCScene* scene();
    
    void updatethis();
    
    void showdauan();
    void showkytien();
    void updatekytien();
        void menuPlay();
    
    void menuInfo();
    void menuShare();
    void menuDownload();
    void menuExit(CCObject* pSender);
    
    virtual void keyBackClicked();
    // implement the "static node()" method manually
    CREATE_FUNC(MenuGame);
};

#endif /* MENUGAME_H_ */
