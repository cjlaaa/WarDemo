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

typedef vector<CCPoint> ccpVector;

class GlobalData
{
public:
    static GlobalData* sharedDirector(void);
    virtual bool init(void);
    ccpVector getUnitPos() {return m_UnitPos;}
private:
    ccpVector m_UnitPos;
};

enum
{
    enTagBg,
    enTagUnitsLayer,
    enTagBullet,
};

enum
{
    enZOrderBack,
    enZOrderMiddle,
    enZOrderFront,
};

enum enTagUnit
{
    enTagUnitMyPos1 = 0,
    enTagUnitMyPos2,
    enTagUnitMyPos3,
    enTagUnitMyPos4,
    enTagUnitMyPos5,
    enTagUnitEnemyPos1,
    enTagUnitEnemyPos2,
    enTagUnitEnemyPos3,
    enTagUnitEnemyPos4,
    enTagUnitEnemyPos5,
    enTagUnitMax,
};

struct FireMsg
{
    enTagUnit shooter;
    enTagUnit target;
};

#endif /* PublicDef_h */