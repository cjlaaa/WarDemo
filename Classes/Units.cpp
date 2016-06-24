//
//  Units.cpp
//  WarDemo
//
//  Created by 常久龙 on 16/6/17.
//
//

#include "Units.h"
#include "MainScene.h"

Unit* Unit::CreateUnit(enUnitType eType, enUnitIndex eIndex)
{
    do
    {
        Unit* pRet = new Unit;
        if (pRet && pRet->Init(eType,eIndex))
        {
            pRet->autorelease();
            return pRet;
        }
        delete pRet;
    } while (false);
    CCLog("Function Unit::CreateBackground Error!");
    return NULL;
}

bool Unit::Init(enUnitType eType, enUnitIndex eIndex)
{
    do
    {
        unitDataMap unitData = GlobalData::sharedDirector()->getUnitDefaultData();
        m_unitData = unitData[eType];
        
        m_nFireCd = m_unitData.nFireCD;
        m_eUnitType = m_unitData.eType;
        m_eUnitStatus = enUnitStatusPre;
        m_nHp = m_unitData.nHp;
        m_eUnitIndex = eIndex;
        
        CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
        CCBReader * ccbReader = new CCBReader(ccNodeLoaderLibrary);
        CCNode * ccbNode = ccbReader->readNodeGraphFromFile(m_unitData.strCCBI.c_str(), this);
        m_animationManager = ccbReader->getAnimationManager();
        m_animationManager->runAnimationsForSequenceNamed("run");
        m_animationManager->setAnimationCompletedCallback(this, callfunc_selector(Unit::AnimationCallBack));
        ccbReader->release();
        
        addChild(ccbNode);
        return true;
    } while (false);
    CCLog("Function Unit::Init Error!");
    return false;
}

void Unit::Update(float fT)
{
    if(m_eUnitStatus==enUnitStatusFight)
    {
        if(m_nFireCd<0)
        {
            m_nFireCd = m_unitData.nFireCD;
            Fire();
        }
        else
        {
            m_nFireCd -= 1 + CCRANDOM_0_1()*2;
        }
    }
}

void Unit::AnimationCallBack()
{
    m_animationManager->runAnimationsForSequenceNamed("run");
}

void Unit::SetStatus(enUnitStatus eStatus)
{
    m_eUnitStatus = eStatus;
}

void Unit::OnHit(enUnitIndex shooter)
{
    if(m_unitData.eType==enUnitTypeTroopMine ||
       m_unitData.eType==enUnitTypeTroopEnemy)
    {
        m_animationManager->runAnimationsForSequenceNamed("hit");
    }

    unitDataMap unitData = GlobalData::sharedDirector()->getUnitDefaultData();
    m_nHp -= unitData[GlobalData::sharedDirector()->getUnitTypeByIndex(shooter)].nDC;
    if(m_nHp<=0)
    {
        ((UnitsLayer*)(getParent()))->OnDead(m_eUnitIndex);
        ((UnitsLayer*)(getParent()))->removeUnit(m_eUnitIndex);
    }
    
//    CCLog("%d %d",m_eUnitIndex,m_nHp);
}

void Unit::Fire()
{
    enUnitIndex eTarget = getTarget();
    
    if(eTarget!=enUnitIndexMax)
    {
        m_animationManager->runAnimationsForSequenceNamed("fire");

        ((UnitsLayer*)(getParent()))->OnFire(this,eTarget);
    }
}

enUnitIndex Unit::getTarget()
{
    enUnitIndex eTarget = enUnitIndexMax;
    
    UnitExpect unitExpect = GlobalData::sharedDirector()->getUnitExpectByIndex(m_eUnitIndex);
    if(GlobalData::sharedDirector()->getUnitTypeByIndex(unitExpect.primary)!=enUnitTypeNone) eTarget=unitExpect.primary;
    else if(GlobalData::sharedDirector()->getUnitTypeByIndex(unitExpect.secondary)!=enUnitTypeNone) eTarget=unitExpect.secondary;
    else if(GlobalData::sharedDirector()->getUnitTypeByIndex(unitExpect.third)!=enUnitTypeNone) eTarget=unitExpect.third;
    else if(GlobalData::sharedDirector()->getUnitTypeByIndex(unitExpect.fourth)!=enUnitTypeNone) eTarget=unitExpect.fourth;
    else if(GlobalData::sharedDirector()->getUnitTypeByIndex(unitExpect.fifth)!=enUnitTypeNone) eTarget=unitExpect.fifth;
    else if(GlobalData::sharedDirector()->getUnitTypeByIndex(unitExpect.sixth)!=enUnitTypeNone) eTarget=unitExpect.sixth;
    
    return eTarget;
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
        m_eUnitStatus = enUnitStatusPre;
        return true;
    } while (false);
    CCLog("Function UnitsLayer::Init Error!");
    return false;
}

void UnitsLayer::InitBattleField()
{
    removeAllChildren();
}

void UnitsLayer::StartGame()
{
    GlobalData::sharedDirector()->setGameStartUnitPos();
    unitPosMap unitPos = GlobalData::sharedDirector()->getUnitPos();
    
    for (int i=0; i<enUnitIndexMax; i++)
    {
        Unit* pU = (Unit*)(getChildByTag(i));
        if(pU!=NULL)pU->runAction(CCSequence::create(CCMoveTo::create(1, unitPos[(enUnitIndex)i]),
                                                     CCCallFunc::create(this, callfunc_selector(UnitsLayer::StartGameUnitMoveCallback))));
    }
}

void UnitsLayer::StartGameUnitMoveCallback()
{
    m_eUnitStatus = enUnitStatusFight;
    for (int i=0; i<enUnitIndexMax; i++)
    {
        Unit* pU = (Unit*)(getChildByTag(i));
        if(pU!=NULL)pU->SetStatus(enUnitStatusFight);
    }
}

void UnitsLayer::addUnit(enUnitType eType,enUnitIndex eIndex)
{
    unitPosMap unitsPos = GlobalData::sharedDirector()->getUnitPos();
    unitTypeMap mapUnitType;
    
    enUnitType eUnitType = eType;
    Unit* pUnit = Unit::CreateUnit(eUnitType,eIndex);
    pUnit->setPosition(unitsPos[eIndex]);
    addChild(pUnit,enZOrderFront,eIndex);
    
    GlobalData::sharedDirector()->setUnitTypeByIndex(eIndex, eType);
}

void UnitsLayer::removeUnit(enUnitIndex eIndex)
{
    Unit* pUnit = (Unit*)getChildByTag(eIndex);
    if(pUnit!=NULL)removeChild(pUnit);
    
    GlobalData::sharedDirector()->setUnitTypeByIndex(eIndex, enUnitTypeNone);
    
    if(m_eUnitStatus==enUnitStatusFight)
    {
        reposUnit(eIndex);
        checkGameStatus();
    }
}

void UnitsLayer::checkGameStatus()
{
    bool bIsMeWin = true;
    bool bIsEnemyWin = true;
    
    for (int i=0; i<enUnitIndexEnemy1; i++)
    {
        if(GlobalData::sharedDirector()->getUnitTypeByIndex((enUnitIndex)i)!=enUnitTypeNone)
        {
            bIsMeWin = false;
        }
    }
    
    for (int i=enUnitIndexEnemy1; i<enUnitIndexMax; i++)
    {
        if(GlobalData::sharedDirector()->getUnitTypeByIndex((enUnitIndex)i)!=enUnitTypeNone)
        {
            bIsEnemyWin = false;
        }
    }
    
    if(bIsMeWin||bIsEnemyWin)
    {
        m_eUnitStatus = enUnitStatusPre;
        ((MainScene*)(getParent()))->OnGameOver();
    }
}

void UnitsLayer::OnFire(CCNode* pNode,enUnitIndex eTarget)
{
    ((MainScene*)(getParent()))->OnFire((enUnitIndex)(pNode->getTag()), eTarget, pNode->getPosition(),(getChildByTag(eTarget)->getPosition()));
}

void UnitsLayer::OnHit(enUnitIndex shooter, enUnitIndex target)
{
    Unit* pU = (Unit*)getChildByTag(target);
    if(pU!=NULL)pU->OnHit(shooter);
}

void UnitsLayer::OnDead(enUnitIndex target)
{
    ((MainScene*)(getParent()))->OnDead(target,((Unit*)getChildByTag(target))->getPosition());
}

void UnitsLayer::Update(float fT)
{
    for (int i=0; i<enUnitIndexMax; i++)
    {
        Unit* pU = (Unit*)(getChildByTag(i));
        if(pU!=NULL)pU->Update(fT);
    }
}

void UnitsLayer::reposUnit(enUnitIndex eIndex)
{
    unitPosMap unitsPos = GlobalData::sharedDirector()->getUnitPos();
    
    if(eIndex==enUnitIndexMy2 || eIndex==enUnitIndexEnemy2)
    {
        if((Unit*)getChildByTag(eIndex+1)!=NULL)
        {
            Unit* pUnit = (Unit*)getChildByTag(eIndex-1);
            if(pUnit!=NULL)
            {
                pUnit->stopAllActions();
                pUnit->runAction(CCMoveTo::create(1, unitsPos[eIndex]));
            }
        }
        else
        {
            Unit* pUnit = (Unit*)getChildByTag(eIndex-1);
            if(pUnit!=NULL)
            {
                pUnit->stopAllActions();
                pUnit->runAction(CCMoveTo::create(1, unitsPos[(enUnitIndex)(eIndex+1)]));
            }
        }
    }
    
    if(eIndex==enUnitIndexMy3 || eIndex==enUnitIndexEnemy3)
    {
        Unit* pUnit1 = (Unit*)getChildByTag(eIndex-1);
        if(pUnit1!=NULL)
        {
            pUnit1->stopAllActions();
            pUnit1->runAction(CCMoveTo::create(1, unitsPos[eIndex]));
            
            Unit* pUnit2 = (Unit*)getChildByTag(eIndex-2);
            if(pUnit2!=NULL)
            {
                pUnit2->stopAllActions();
                pUnit2->runAction(CCMoveTo::create(1, unitsPos[(enUnitIndex)(eIndex-1)]));
            }
        }
        else
        {
            Unit* pUnit = (Unit*)getChildByTag(eIndex-2);
            if(pUnit!=NULL)
            {
                pUnit->stopAllActions();
                pUnit->runAction(CCMoveTo::create(1, unitsPos[(enUnitIndex)(eIndex)]));
            }
        }
    }
    
    if(eIndex==enUnitIndexMy5 || eIndex==enUnitIndexEnemy5)
    {
        if((Unit*)getChildByTag(eIndex-1)!=NULL)
        {
            Unit* pUnit = (Unit*)getChildByTag(eIndex+1);
            if(pUnit!=NULL)
            {
                pUnit->stopAllActions();
                pUnit->runAction(CCMoveTo::create(1, unitsPos[eIndex]));
            }
        }
        else
        {
            Unit* pUnit = (Unit*)getChildByTag(eIndex+1);
            if(pUnit!=NULL)
            {
                pUnit->stopAllActions();
                pUnit->runAction(CCMoveTo::create(1, unitsPos[(enUnitIndex)(eIndex-1)]));
            }
        }
    }
    
    if(eIndex==enUnitIndexMy4 || eIndex==enUnitIndexEnemy4)
    {
        Unit* pUnit1 = (Unit*)getChildByTag(eIndex+1);
        if(pUnit1!=NULL)
        {
            pUnit1->stopAllActions();
            pUnit1->runAction(CCMoveTo::create(1, unitsPos[eIndex]));
            
            Unit* pUnit2 = (Unit*)getChildByTag(eIndex+2);
            if(pUnit2!=NULL)
            {
                pUnit2->stopAllActions();
                pUnit2->runAction(CCMoveTo::create(1, unitsPos[(enUnitIndex)(eIndex+1)]));
            }
        }
        else
        {
            Unit* pUnit = (Unit*)getChildByTag(eIndex+2);
            if(pUnit!=NULL)
            {
                pUnit->stopAllActions();
                pUnit->runAction(CCMoveTo::create(1, unitsPos[(enUnitIndex)(eIndex)]));
            }
        }
    }
}
