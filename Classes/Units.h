//
//  Units.hpp
//  WarDemo
//
//  Created by 常久龙 on 16/6/17.
//
//

#ifndef Units_hpp
#define Units_hpp

#include "PublicDef.h"

enum enUnitType
{
    enUnitTypeCarMine,
    enUnitTypeCarEnemy,
    enUnitTypeTroopMine,
    enUnitTypeTroopEnemy,
};

class Unit : public CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
{
public:
    static Unit* CreateUnit(enUnitType eType);
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
    virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, CCBValue* pCCBValue);
    virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
    virtual SEL_CallFuncN onResolveCCBCCCallFuncSelector(CCObject * pTarget, const char* pSelectorName);
protected:
    bool Init(enUnitType eType);
    CCBAnimationManager* m_animationManager;
};

enum
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

class UnitsLayer : public CCLayer
{
public:
    static UnitsLayer* CreateUnitsLayer();
    
protected:
    bool Init();
};


#endif /* Units_hpp */
