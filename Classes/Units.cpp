//
//  Units.cpp
//  WarDemo
//
//  Created by 常久龙 on 16/6/17.
//
//

#include "Units.h"
#include "MainScene.h"

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
        m_nFireCd = FIRE_INTERVAL;
        
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

void Unit::Update(float fT)
{
    if(m_nFireCd<0)
    {
        m_nFireCd = FIRE_INTERVAL;
        Fire();
    }
    else
    {
        m_nFireCd -= CCRANDOM_0_1()*10;
    }
}

void Unit::Fire()
{
    enTagUnit eTarget;
    
    if(m_nTag <= enTagUnitMyPos5)
    {
//        eTarget = (enTagUnit)(m_nTag + 5);
        
        if(CCRANDOM_0_1()<0.2) eTarget = enTagUnitEnemyPos1;
        else if(CCRANDOM_0_1()<0.4) eTarget = enTagUnitEnemyPos2;
        else if(CCRANDOM_0_1()<0.6) eTarget = enTagUnitEnemyPos3;
        else if(CCRANDOM_0_1()<0.8) eTarget = enTagUnitEnemyPos4;
        else eTarget = enTagUnitEnemyPos5;
    }
    else
    {
//        eTarget = (enTagUnit)(m_nTag - 5);
        
        if(CCRANDOM_0_1()<0.2) eTarget = enTagUnitMyPos1;
        else if(CCRANDOM_0_1()<0.4) eTarget = enTagUnitMyPos2;
        else if(CCRANDOM_0_1()<0.6) eTarget = enTagUnitMyPos3;
        else if(CCRANDOM_0_1()<0.8) eTarget = enTagUnitMyPos4;
        else eTarget = enTagUnitMyPos5;
    }
    
    ((UnitsLayer*)(getParent()))->OnFire(this,eTarget);
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
        ccpVector unitsPos = GlobalData::sharedDirector()->getUnitPos();
        
        for (int i=enTagUnitMyPos1; i<enTagUnitMax; i++)
        {
            Unit* pUnit;
            if(i<enTagUnitEnemyPos1)
            {
                pUnit = Unit::CreateUnit(CCRANDOM_0_1()>0.5?enUnitTypeCarMine:enUnitTypeTroopMine);
                
            }
            else
            {
                pUnit = Unit::CreateUnit(CCRANDOM_0_1()>0.5?enUnitTypeCarEnemy:enUnitTypeTroopEnemy);
            }
            pUnit->setPosition(unitsPos[i]);
            addChild(pUnit,enZOrderFront,enTagUnitMyPos1+i);
        }

        return true;
    } while (false);
    CCLog("Function UnitsLayer::Init Error!");
    return false;
}

void UnitsLayer::OnFire(CCNode* pNode,enTagUnit eTarget)
{
    ((MainScene*)(getParent()))->OnFire((enTagUnit)(pNode->getTag()), eTarget);
}

void UnitsLayer::Update(float fT)
{
    for (int i=0; i<enTagUnitMax; i++)
    {
        Unit* pU = (Unit*)(getChildByTag(i));
        pU->Update(fT);
    }
}
