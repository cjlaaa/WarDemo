//
//  Units.cpp
//  WarDemo
//
//  Created by 常久龙 on 16/6/17.
//
//

#include "Units.h"

Unit* Unit::CreateUnit(enUnitType eType)
{
    do
    {
        Unit* pRet = new Unit;
        if (pRet && pRet->Init(eType))
        {
            pRet->autorelease();
            return pRet;
        }
        delete pRet;
    } while (false);
    CCLog("Function Unit::CreateBackground Error!");
    return NULL;
}

bool Unit::Init(enUnitType eType)
{
    do
    {
        CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
        CCBReader * ccbReader = new CCBReader(ccNodeLoaderLibrary);
        CCNode * ccbNode;
        switch (eType)
        {
            case enUnitTypeCarMine:
                ccbNode = ccbReader->readNodeGraphFromFile("ccb/car1.ccbi", this);
                break;
            case enUnitTypeCarEnemy:
                ccbNode = ccbReader->readNodeGraphFromFile("ccb/car2.ccbi", this);
                break;
            case enUnitTypeTroopMine:
                ccbNode = ccbReader->readNodeGraphFromFile("ccb/troop1.ccbi", this);
                break;
            case enUnitTypeTroopEnemy:
                ccbNode = ccbReader->readNodeGraphFromFile("ccb/troop2.ccbi", this);
                break;
            default:
                break;
        }
        m_animationManager = ccbReader->getAnimationManager();
        m_animationManager->runAnimationsForSequenceNamed("run");
        ccbReader->release();
        
        addChild(ccbNode);
        return true;
    } while (false);
    CCLog("Function Unit::Init Error!");
    return false;
}


SEL_MenuHandler Unit::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName)
{
    
}
SEL_CCControlHandler Unit::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName)
{
    
}
bool Unit::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode)
{
    
}
bool Unit::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, CCBValue* pCCBValue)
{
    
}
void Unit::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
    
}
SEL_CallFuncN Unit::onResolveCCBCCCallFuncSelector(CCObject * pTarget, const char* pSelectorName)
{
    
}

UnitsLayer* UnitsLayer::CreateUnitsLayer()
{
    do
    {
        UnitsLayer* pRet = new UnitsLayer;
        if (pRet && pRet->Init())
        {
            pRet->autorelease();
            return pRet;
        }
        delete pRet;
    } while (false);
    CCLog("Function UnitsLayer::CreateBackground Error!");
    return NULL;
}

bool UnitsLayer::Init()
{
    do
    {
        CCPoint unitsPos[10] = {};
        unitsPos[0] = ccp(SCREEN_WIDTH*0.15,SCREEN_HEIGHT*0.6);
        unitsPos[1] = ccp(SCREEN_WIDTH*0.2,SCREEN_HEIGHT*0.45);
        unitsPos[2] = ccp(SCREEN_WIDTH*0.25,SCREEN_HEIGHT*0.3);
        unitsPos[3] = ccp(SCREEN_WIDTH*0.4,SCREEN_HEIGHT*0.25);
        unitsPos[4] = ccp(SCREEN_WIDTH*0.55,SCREEN_HEIGHT*0.2);
        
        unitsPos[5] = ccp(SCREEN_WIDTH*0.35,SCREEN_HEIGHT*0.7);
        unitsPos[6] = ccp(SCREEN_WIDTH*0.5,SCREEN_HEIGHT*0.65);
        unitsPos[7] = ccp(SCREEN_WIDTH*0.65,SCREEN_HEIGHT*0.6);
        unitsPos[8] = ccp(SCREEN_WIDTH*0.7,SCREEN_HEIGHT*0.45);
        unitsPos[9] = ccp(SCREEN_WIDTH*0.75,SCREEN_HEIGHT*0.3);
        
        for (int i=enTagUnitMyPos1; i<enTagUnitMax; i++)
        {
            if(i<5)
            {
                Unit* pUnit = Unit::CreateUnit(CCRANDOM_0_1()>0.5?enUnitTypeCarMine:enUnitTypeTroopMine);
                pUnit->setPosition(unitsPos[i]);
                addChild(pUnit,enZOrderFront,enTagUnitMyPos1+i);
            }
            else
            {
                Unit* pUnit = Unit::CreateUnit(CCRANDOM_0_1()>0.5?enUnitTypeCarEnemy:enUnitTypeTroopEnemy);
                pUnit->setPosition(unitsPos[i]);
                addChild(pUnit,enZOrderFront,enTagUnitMyPos1+i);
            }
        }

        return true;
    } while (false);
    CCLog("Function UnitsLayer::Init Error!");
    return false;
}
