//
//  ChoseDauTruong.h
//  CoTuong3
//
//  Created by Đỗ Hữu Điển on 11/26/13.
//
//

#ifndef __CoTuong3__ChoseDauTruong__
#define __CoTuong3__ChoseDauTruong__

#include "cocos2d.h"
USING_NS_CC;

class ChoseDauTruong : public CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    void menuDauDon();
    
    void menuChienDich();

    virtual void keyBackClicked();
    // implement the "static node()" method manually
    CREATE_FUNC(ChoseDauTruong);
};

#endif /* defined(__CoTuong3__ChoseDauTruong__) */
