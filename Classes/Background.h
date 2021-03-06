//
//  Background.hpp
//  Background
//
//  Created by 常久龙 on 16/6/17.
//
//

#ifndef Background_h
#define Background_h

#include "PublicDef.h"

enum
{
    enTagBgLeft,
    enTagBgRight,
};

class Background : public CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
{
public:
    static Background* CreateBackground();
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName){};
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName){};
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
    virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue){};
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader){};
    virtual SEL_CallFuncN onResolveCCBCCCallFuncSelector(CCObject * pTarget, const char* pSelectorName){};
    
    void Update(float);
    void OnHit(enUnitIndex target,CCPoint targetPos);
    void OnDead(enUnitIndex target, CCPoint targetPos);
protected:
    bool Init();
    CCSprite* m_backgroundLeft;
    CCSprite* m_backgroundRight;
    void onExit();
    CCArray* m_CraterArrayLeft;
    CCArray* m_CraterArrayRight;
    CCArray* m_CraterArrayLeftDeleted;
    CCArray* m_CraterArrayRightDeleted;
};

#endif /* ListNode_hpp */
