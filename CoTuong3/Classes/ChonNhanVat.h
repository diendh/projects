//
//  ChonNhanVat.h
//  CoTuong3
//
//  Created by Đỗ Hữu Điển on 11/28/13.
//
//

#ifndef __CoTuong3__ChonNhanVat__
#define __CoTuong3__ChonNhanVat__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class ChonNhanVat : public CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();

    void menuNhanVat(CCObject* pSender);
    
    virtual void keyBackClicked();
    // implement the "static node()" method manually
    CREATE_FUNC(ChonNhanVat);
};
#endif /* defined(__CoTuong3__ChonNhanVat__) */
