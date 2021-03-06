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

enum enUnitStatus
{
    enUnitStatusPre,
    enUnitStatusFight,
};

class Unit : public CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
{
public:
    static Unit* CreateUnit(enUnitType eType, enUnitIndex eIndex);
    void Update(float fT);
    void OnHit(enUnitIndex target);
    void SetStatus(enUnitStatus eStatus);
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) {};
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName){};
    virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode){};
    virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, CCBValue* pCCBValue){};
    virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader){};
    virtual SEL_CallFuncN onResolveCCBCCCallFuncSelector(CCObject * pTarget, const char* pSelectorName){};
protected:
    bool Init(enUnitType eType, enUnitIndex eIndex);
    void Fire();
    void AnimationCallBack();
    enUnitIndex getTarget();
    
    CCBAnimationManager* m_animationManager;
    int m_nFireCd;
    int m_nHp;
    enUnitStatus m_eUnitStatus;
    enUnitType m_eUnitType;
    UnitData m_unitData;
    enUnitIndex m_eUnitIndex;
};

class UnitsLayer : public CCLayer
{
public:
    static UnitsLayer* CreateUnitsLayer();
    void Update(float);
    
    void OnFire(CCNode* pNode,enUnitIndex eTarget);
    void OnHit(enUnitIndex shooter, enUnitIndex target);
    void OnDead(enUnitIndex target);
    void addUnit(enUnitType eType,enUnitIndex eIndex);
    void removeUnit(enUnitIndex eIndex);
    void StartGame();
    void StartGameUnitMoveCallback();
    void reposUnit(enUnitIndex eIndex);
    void checkGameStatus();
    void InitBattleField();
protected:
    bool Init();
    enUnitStatus m_eUnitStatus;
};


#endif /* Units_hpp */
