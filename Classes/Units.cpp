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
            case enUnitTypeCar1:
                ccbNode = ccbReader->readNodeGraphFromFile("ccb/car1.ccbi", this);
                break;
            case enUnitTypeCar2:
                ccbNode = ccbReader->readNodeGraphFromFile("ccb/car2.ccbi", this);
                break;
            default:
                break;
        }
        CCBAnimationManager* animationManagerLeft = ccbReader->getAnimationManager();
        animationManagerLeft->runAnimationsForSequenceNamed("run");
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
        
        unitsPos[5] = ccp(SCREEN_WIDTH*0.45,SCREEN_HEIGHT*0.8);
        unitsPos[6] = ccp(SCREEN_WIDTH*0.6,SCREEN_HEIGHT*0.75);
        unitsPos[7] = ccp(SCREEN_WIDTH*0.75,SCREEN_HEIGHT*0.7);
        unitsPos[8] = ccp(SCREEN_WIDTH*0.8,SCREEN_HEIGHT*0.55);
        unitsPos[9] = ccp(SCREEN_WIDTH*0.85,SCREEN_HEIGHT*0.4);
        
        for (int i=enTagUnitMyPos1; i<enTagUnitMax; i++)
        {
            if(i<5)
            {
                Unit* pUnit = Unit::CreateUnit(enUnitTypeCar1);
                pUnit->setPosition(unitsPos[i]);
                addChild(pUnit,enZOrderFront,enTagUnitMyPos1+i);
            }
            else
            {
                Unit* pUnit = Unit::CreateUnit(enUnitTypeCar2);
                pUnit->setPosition(unitsPos[i]);
                addChild(pUnit,enZOrderFront,enTagUnitMyPos1+i);
            }
        }

        return true;
    } while (false);
    CCLog("Function UnitsLayer::Init Error!");
    return false;
}
