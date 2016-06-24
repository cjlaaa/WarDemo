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
    
    if(eTarget!=enUnitIndexError)
    {
        m_animationManager->runAnimationsForSequenceNamed("fire");

        ((UnitsLayer*)(getParent()))->OnFire(this,eTarget);
    }
}

enUnitIndex Unit::getTarget()
{
    enUnitIndex eTarget = enUnitIndexError;
    
    UnitExpect unitExpect = GlobalData::sharedDirector()->getUnitExpectByIndex(m_eUnitIndex);
    if(GlobalData::sharedDirector()->getUnitTypeByIndex(unitExpect.primary)!=enUnitTypeNone) eTarget=unitExpect.primary;
    else if(GlobalData::sharedDirector()->getUnitTypeByIndex(unitExpect.secondary)!=enUnitTypeNone) eTarget=unitExpect.secondary;
    else if(GlobalData::sharedDirector()->getUnitTypeByIndex(unitExpect.third)!=enUnitTypeNone) eTarget=unitExpect.third;
    else if(GlobalData::sharedDirector()->getUnitTypeByIndex(unitExpect.fourth)!=enUnitTypeNone) eTarget=unitExpect.fourth;
    else if(GlobalData::sharedDirector()->getUnitTypeByIndex(unitExpect.fifth)!=enUnitTypeNone) eTarget=unitExpect.fifth;
    
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
        return true;
    } while (false);
    CCLog("Function UnitsLayer::Init Error!");
    return false;
}

void UnitsLayer::StartGame()
{
    GlobalData::sharedDirector()->setGameStartUnitPos();
    unitPosMap unitPos = GlobalData::sharedDirector()->getUnitPos();
    
    for (int i=0; i<enUnitIndexEnemy1; i++)
    {
        Unit* pU = (Unit*)(getChildByTag(i));
        if(pU!=NULL)pU->runAction(CCSequence::create(CCMoveTo::create(1, unitPos[(enUnitIndex)i]),
                                                     CCCallFunc::create(this, callfunc_selector(UnitsLayer::StartGameUnitMoveCallback))));
    }
}

void UnitsLayer::StartGameUnitMoveCallback()
{
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
}

void UnitsLayer::OnFire(CCNode* pNode,enUnitIndex eTarget)
{
    ((MainScene*)(getParent()))->OnFire((enUnitIndex)(pNode->getTag()), eTarget);
}

void UnitsLayer::OnHit(enUnitIndex shooter, enUnitIndex target)
{
    Unit* pU = (Unit*)getChildByTag(target);
    if(pU!=NULL)pU->OnHit(shooter);
}

void UnitsLayer::OnDead(enUnitIndex target)
{
    ((MainScene*)(getParent()))->OnDead(target);
}

void UnitsLayer::Update(float fT)
{
    for (int i=0; i<enUnitIndexMax; i++)
    {
        Unit* pU = (Unit*)(getChildByTag(i));
        if(pU!=NULL)pU->Update(fT);
    }
}
