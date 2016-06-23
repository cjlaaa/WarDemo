//
//  UI.hpp
//  WarDemo
//
//  Created by 常久龙 on 16/6/22.
//
//

#ifndef UI_hpp
#define UI_hpp

#include "PublicDef.h"

enum
{
    enTagTableView,
    enTagMenuBF,
};

enum
{
    enTagInCellNum,
    enTagInCellTexture,
};

struct uiUnit
{
    uiUnit(UnitData data, int num)
    {
        nNum = num;
        Data = data;
    }
    
    int nNum;
    UnitData Data;
};
typedef  vector<uiUnit> uiUnitVector;

class UI : public CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
, public cocos2d::extension::CCTableViewDataSource
, public cocos2d::extension::CCTableViewDelegate
{
public:
    static UI* CreateUI();
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName){};
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
    virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue){};
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader){};
    virtual SEL_CallFuncN onResolveCCBCCCallFuncSelector(CCObject * pTarget, const char* pSelectorName){};
    void onStartGame(CCObject * pSender);
    
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
    virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    virtual cocos2d::CCSize tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
    void tableViewSubBtnCallback(CCObject* pSender);
protected:
    bool Init();
    void onEnter();
    void addUnit(enUnitType eType,enUnitIndex eIndex);
    void removeUnit(CCNode* pNode);
    
    CCSprite* m_tableViewBg;
    CCMenuItemImage* m_startGame;
    uiUnitVector m_unitData;
    vector<enUnitType> m_vecBattleFieldStatus;
};

#endif /* UI_hpp */
