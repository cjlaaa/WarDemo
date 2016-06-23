//
//  Background.cpp
//  Background
//
//  Created by 常久龙 on 16/6/17.
//
//

#include "Background.h"

Background* Background::CreateBackground()
{
    do
    {
        Background* pRet = new Background;
        if (pRet && pRet->Init())
        {
            pRet->autorelease();
            return pRet;
        }
        delete pRet;
    } while (false);
    CCLog("Function Background::CreateBackground Error!");
    return NULL;
}

bool Background::Init()
{
    do
    {
        CCNodeLoaderLibrary * ccNodeLoaderLibraryLeft = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
        CCBReader * ccbReaderLeft = new CCBReader(ccNodeLoaderLibraryLeft);
        CCNode * bgLeft = ccbReaderLeft->readNodeGraphFromFile("ccb/background.ccbi", this);
        CCBAnimationManager* animationManagerLeft = ccbReaderLeft->getAnimationManager();
        animationManagerLeft->runAnimationsForSequenceNamed("left");
        ccbReaderLeft->release();
        
        CCNodeLoaderLibrary * ccNodeLoaderLibraryRight = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
        CCBReader * ccbReaderRight = new CCBReader(ccNodeLoaderLibraryRight);
        CCNode * bgRight = ccbReaderRight->readNodeGraphFromFile("ccb/background.ccbi", this);
        CCBAnimationManager* animationManagerRight = ccbReaderRight->getAnimationManager();
        animationManagerRight->runAnimationsForSequenceNamed("right");
        ccbReaderRight->release();
        
        CCClippingNode * clippingNodeLeft = CCClippingNode::create();
        addChild(clippingNodeLeft);
        clippingNodeLeft->addChild(bgLeft,enZOrderBack,enTagBgLeft);
        CCDrawNode *shapeLeft = CCDrawNode::create();
        static CCPoint triangleLeft[3];
        triangleLeft[0] = ccp(0, 0);
        triangleLeft[1] = ccp(SCREEN_WIDTH,0);
        triangleLeft[2] = ccp(0,SCREEN_HEIGHT);
        static ccColor4F green = {0, 1, 0, 1};
        shapeLeft->drawPolygon(triangleLeft, 3, green, 0, green);
        clippingNodeLeft->setStencil(shapeLeft);
        clippingNodeLeft->setInverted(false);
        
        CCClippingNode * clippingNodeRight = CCClippingNode::create();
        addChild(clippingNodeRight);
        clippingNodeRight->addChild(bgRight,enZOrderBack,enTagBgRight);
        CCDrawNode *shapeRight = CCDrawNode::create();
        static CCPoint triangleRight[3];
        triangleRight[0] = ccp(SCREEN_WIDTH, SCREEN_HEIGHT);
        triangleRight[1] = ccp(SCREEN_WIDTH,0);
        triangleRight[2] = ccp(0,SCREEN_HEIGHT);
//        static ccColor4F green = {0, 1, 0, 1};
        shapeRight->drawPolygon(triangleRight, 3, green, 0, green);
        clippingNodeRight->setStencil(shapeRight);
        clippingNodeRight->setInverted(false);
        
        m_CraterArrayLeft = CCArray::create();
        m_CraterArrayLeft->retain();
        m_CraterArrayRight = CCArray::create();
        m_CraterArrayRight->retain();
        m_CraterArrayLeftDeleted = CCArray::create();
        m_CraterArrayLeftDeleted->retain();
        m_CraterArrayRightDeleted = CCArray::create();
        m_CraterArrayRightDeleted->retain();
        
        
        return true;
    } while (false);
    CCLog("Function Background::Init Error!");
    return false;
}

void Background::onExit()
{
    CCLayer::onExit();
    m_CraterArrayLeft->release();
    m_CraterArrayRight->release();
    m_CraterArrayLeftDeleted->release();
    m_CraterArrayRightDeleted->release();
}

void Background::OnHit(enUnitIndex target)
{
    unitPosMap unitsPos = GlobalData::sharedDirector()->getUnitPos();
    
    CCSprite* pCrater = CCSprite::create("keng.png");
    pCrater->setScale(0.3);
    if(target<enUnitIndexEnemy1)
    {
        m_backgroundLeft->addChild(pCrater);
        pCrater->setPosition(m_backgroundLeft->convertToNodeSpace(unitsPos[target]));
        m_CraterArrayLeft->addObject(pCrater);
    }
    else
    {
        m_backgroundRight->addChild(pCrater);
        pCrater->setPosition(m_backgroundRight->convertToNodeSpace(unitsPos[target]));
        m_CraterArrayRight->addObject(pCrater);
    }
}

void Background::OnDead(enUnitIndex target)
{
    enUnitType eType = GlobalData::sharedDirector()->getUnitTypeByIndex(target);
    unitDataMap unitData = GlobalData::sharedDirector()->getUnitDefaultData();
    unitPosMap unitsPos = GlobalData::sharedDirector()->getUnitPos();
    
    if(eType==enUnitTypeTroopMine ||
       eType==enUnitTypeTroopEnemy)
    {
        CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
        CCBReader * ccbReader = new CCBReader(ccNodeLoaderLibrary);
        CCNode * ccbNode = ccbReader->readNodeGraphFromFile(unitData[eType].strCCBI.c_str(), this);
        CCBAnimationManager* animationManager = ccbReader->getAnimationManager();
        animationManager->runAnimationsForSequenceNamed("dead");
        ccbReader->release();
        ccbNode->setScaleX(0.5);//the bg sprite in ccb is scale.
        
        if(target<enUnitIndexEnemy1)
        {
            m_backgroundLeft->addChild(ccbNode);
            ccbNode->setPosition(m_backgroundLeft->convertToNodeSpace(unitsPos[target]));
            m_CraterArrayLeft->addObject(ccbNode);
        }
        else
        {
            m_backgroundRight->addChild(ccbNode);
            ccbNode->setPosition(m_backgroundRight->convertToNodeSpace(unitsPos[target]));
            m_CraterArrayRight->addObject(ccbNode);
        }
    }
}

void Background::Update(float)
{
    m_CraterArrayLeft->removeObjectsInArray(m_CraterArrayLeftDeleted);
    m_CraterArrayLeftDeleted->removeAllObjects();
    CCObject* pObjLeft = NULL;
    CCARRAY_FOREACH(m_CraterArrayLeft,pObjLeft)
    {
        CCSprite* pCrater = (CCSprite*)(pObjLeft);
        CCPoint p = pCrater->getPosition();
        CCPoint point = m_backgroundLeft->convertToWorldSpace(p);
        if(point.x < 0 || point.y < 0 || point.x > SCREEN_WIDTH || point.y > SCREEN_HEIGHT)
        {
            m_CraterArrayLeftDeleted->addObject(pCrater);
            m_backgroundLeft->removeChild(pCrater,true);
        }
    }
    
    m_CraterArrayRight->removeObjectsInArray(m_CraterArrayRightDeleted);
    m_CraterArrayRightDeleted->removeAllObjects();
    CCObject* pObjRight = NULL;
    CCARRAY_FOREACH(m_CraterArrayRight,pObjRight)
    {
        CCSprite* pCrater = (CCSprite*)(pObjRight);
        CCPoint p = pCrater->getPosition();
        CCPoint point = m_backgroundRight->convertToWorldSpace(p);
        if(point.x < 0 || point.y < 0 || point.x > SCREEN_WIDTH || point.y > SCREEN_HEIGHT)
        {
            m_CraterArrayRightDeleted->addObject(pCrater);
            m_backgroundRight->removeChild(pCrater,true);
        }
    }
}

bool Background::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode)
{
    if(m_backgroundLeft==NULL)
    {
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "background", CCSprite*, m_backgroundLeft);
    }
    else
    {
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "background", CCSprite*, m_backgroundRight);
    }
    
    return true;
}