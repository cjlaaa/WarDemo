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

class Unit : public CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
{
public:
    static Unit* CreateUnit(enUnitType eType);
    void Update(float fT);
    void OnHit();
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
    virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, CCBValue* pCCBValue);
    virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
    virtual SEL_CallFuncN onResolveCCBCCCallFuncSelector(CCObject * pTarget, const char* pSelectorName);
protected:
    bool Init(enUnitType eType);
    void Fire();
    void AnimationCallBack();
    
    CCBAnimationManager* m_animationManager;
    int m_nFireCd;
    enUnitType m_eUnitType;
    UnitData m_unitData;
};

class UnitsLayer : public CCLayer
{
public:
    static UnitsLayer* CreateUnitsLayer();
    void Update(float);
    
    void OnFire(CCNode* pNode,enTagUnit eTarget);
    void OnHit(enTagUnit shooter, enTagUnit target);
protected:
    bool Init();
};


#endif /* Units_hpp */
