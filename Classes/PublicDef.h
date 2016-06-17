//
//  PublicDef.h
//  WarDemo
//
//  Created by 常久龙 on 16/6/17.
//
//

#ifndef PublicDef_h
#define PublicDef_h

#include "cocos2d.h"
USING_NS_CC;
#include "cocos-ext.h"
USING_NS_CC_EXT;
using namespace std;

#define SCREEN_WIDTH    (CCDirector::sharedDirector()->getVisibleSize().width)
#define SCREEN_HEIGHT   (CCDirector::sharedDirector()->getVisibleSize().height)

enum
{
    enTagBg,
    enTagUnits,
};

enum
{
    enZOrderBack,
    enZOrderMiddle,
    enZOrderFront,
};

#endif /* PublicDef_h */