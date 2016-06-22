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
        unitDataMap unitData = GlobalData::sharedDirector()->getUnitDefaultData();
        m_unitData = unitData[eType];
        
        m_nFireCd = m_unitData.nFireCD;
        m_eUnitType = m_unitData.eType;
        m_eUnitStatus = enUnitStatusIdle;
        m_nHp = m_unitData.nHp;
        
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
    if(m_nFireCd<0)
    {
        m_nFireCd = m_unitData.nFireCD;
        Fire();
    }
    else
    {
        m_nFireCd -= CCRANDOM_0_1()*10;
    }
}

void Unit::AnimationCallBack()
{
    m_animationManager->runAnimationsForSequenceNamed("run");
}

void Unit::OnHit(enUnitIndex shooter)
{
    if(m_unitData.eType==enUnitTypeTroopMine ||
       m_unitData.eType==enUnitTypeTroopEnemy)
    {
        m_animationManager->runAnimationsForSequenceNamed("hit");
    }
    
    unitTypeVector vecUnitType = GlobalData::sharedDirector()->getUnitType();
    unitDataMap unitData = GlobalData::sharedDirector()->getUnitDefaultData();
    m_nHp -= unitData[vecUnitType[shooter]].nDC;
    if(m_nHp<=0) removeFromParent();
}

void Unit::Fire()
{
    m_animationManager->runAnimationsForSequenceNamed("fire");
    enUnitIndex eTarget;
    
    if(m_nTag <= enUnitIndexMy5)
    {
//        eTarget = (enTagUnit)(m_nTag + 5);
        
        if(CCRANDOM_0_1()<0.2) eTarget = enUnitIndexEnemy1;
        else if(CCRANDOM_0_1()<0.4) eTarget = enUnitIndexEnemy2;
        else if(CCRANDOM_0_1()<0.6) eTarget = enUnitIndexEnemy3;
        else if(CCRANDOM_0_1()<0.8) eTarget = enUnitIndexEnemy4;
        else eTarget = enUnitIndexEnemy5;
    }
    else
    {
//        eTarget = (enTagUnit)(m_nTag - 5);
        
        if(CCRANDOM_0_1()<0.2) eTarget = enUnitIndexMy1;
        else if(CCRANDOM_0_1()<0.4) eTarget = enUnitIndexMy2;
        else if(CCRANDOM_0_1()<0.6) eTarget = enUnitIndexMy3;
        else if(CCRANDOM_0_1()<0.8) eTarget = enUnitIndexMy4;
        else eTarget = enUnitIndexMy5;
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
        unitTypeVector vecUnitType;
        
        for (int i=enUnitIndexMy1; i<enUnitIndexMax; i++)
        {
            
            if(i<enUnitIndexEnemy1)
            {
                enUnitType eUnitType = CCRANDOM_0_1()>0.5?enUnitTypeCarMine:enUnitTypeTroopMine;
                Unit* pUnit = Unit::CreateUnit(eUnitType);
                vecUnitType.push_back(eUnitType);
                pUnit->setPosition(unitsPos[i]);
                addChild(pUnit,enZOrderFront,enUnitIndexMy1+i);
            }
            else
            {
                enUnitType eUnitType = CCRANDOM_0_1()>0.5?enUnitTypeCarEnemy:enUnitTypeTroopEnemy;
                Unit* pUnit = Unit::CreateUnit(eUnitType);
                vecUnitType.push_back(eUnitType);
                pUnit->setPosition(unitsPos[i]);
                addChild(pUnit,enZOrderFront,enUnitIndexMy1+i);
            }
        }
        
        GlobalData::sharedDirector()->setUnitType(vecUnitType);
        return true;
    } while (false);
    CCLog("Function UnitsLayer::Init Error!");
    return false;
}

void UnitsLayer::OnFire(CCNode* pNode,enUnitIndex eTarget)
{
    ((MainScene*)(getParent()))->OnFire((enUnitIndex)(pNode->getTag()), eTarget);
}

void UnitsLayer::OnHit(enUnitIndex shooter, enUnitIndex target)
{
    Unit* pU = (Unit*)getChildByTag(shooter);
    if(pU!=NULL)pU->OnHit(shooter);
}

void UnitsLayer::Update(float fT)
{
    for (int i=0; i<enUnitIndexMax; i++)
    {
        Unit* pU = (Unit*)(getChildByTag(i));
        if(pU!=NULL)pU->Update(fT);
    }
}
