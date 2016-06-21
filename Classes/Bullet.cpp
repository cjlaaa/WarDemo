//
//  Bullet.cpp
//  WarDemo
//
//  Created by 常久龙 on 16/6/20.
//
//

#include "Bullet.h"

Bullet* Bullet::CreateBullet()
{
    do
    {
        Bullet* pRet = new Bullet;
        if (pRet && pRet->Init())
        {
            pRet->autorelease();
            return pRet;
        }
        delete pRet;
    } while (false);
    CCLog("Function Bullet::CreateBullet Error!");
    return NULL;
}

bool Bullet::Init()
{
    do
    {
//        CCParticleSun* pP = CCParticleSun::create();
//        addChild(pP);
//        pP->setTotalParticles(30);
//        pP->setPosition(ccp(0,0));
//        
//        setScale(0.3);
        CCSprite* pB = CCSprite::create("dandao_00000.png");
        addChild(pB);
        pB->setRotation(-30);
        pB->setScaleY(0.3);
        
        return true;
    } while (false);
    CCLog("Function Bullet::Init Error!");
    return false;
}

BulletLayer* BulletLayer::CreateBulletLayer()
{
    do
    {
        BulletLayer* pRet = new BulletLayer;
        if (pRet && pRet->Init())
        {
            pRet->autorelease();
            return pRet;
        }
        delete pRet;
    } while (false);
    CCLog("Function BulletLayer::CreateBulletLayer Error!");
    return NULL;
}

bool BulletLayer::Init()
{
    do
    {
        CCClippingNode * clippingNodeLeft = CCClippingNode::create();
        addChild(clippingNodeLeft,enZOrderFront,enTagClippingNodeLeft);
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
        addChild(clippingNodeRight,enZOrderFront,enTagClippingNodeRight);
        CCDrawNode *shapeRight = CCDrawNode::create();
        static CCPoint triangleRight[3];
        triangleRight[0] = ccp(SCREEN_WIDTH, SCREEN_HEIGHT);
        triangleRight[1] = ccp(SCREEN_WIDTH,0);
        triangleRight[2] = ccp(0,SCREEN_HEIGHT);
        shapeRight->drawPolygon(triangleRight, 3, green, 0, green);
        clippingNodeRight->setStencil(shapeRight);
        clippingNodeRight->setInverted(false);
        
        return true;
    } while (false);
    CCLog("Function BulletLayer::Init Error!");
    return false;
}

void BulletLayer::Update(float)
{
    
}

void BulletLayer::shoot(enTagUnit shooter,enTagUnit target)
{
    ccpVector unitPos = GlobalData::sharedDirector()->getUnitPos();
    float fBulletRunTime = 0.5;
    CCClippingNode * clippingNodeLeft = (CCClippingNode*)(getChildByTag(enTagClippingNodeLeft));
    CCClippingNode * clippingNodeRight = (CCClippingNode*)(getChildByTag(enTagClippingNodeRight));
    
    //begin
    Bullet* pBulletLeft = Bullet::CreateBullet();
    pBulletLeft->setPosition(unitPos[shooter]);
    CCPoint ccpTarget;
    if(shooter <= enTagUnitMyPos5) ccpTarget=ccp(SCREEN_WIDTH,SCREEN_HEIGHT);
    else ccpTarget = ccp(0,0);
    pBulletLeft->runAction(CCSequence::create(CCMoveTo::create(fBulletRunTime, ccpTarget),
                                     CCCallFuncN::create(pBulletLeft, callfuncN_selector(BulletLayer::moveToTargetCallback))));
    if(shooter<=enTagUnitMyPos5)clippingNodeLeft->addChild(pBulletLeft);
    else clippingNodeRight->addChild(pBulletLeft);
    
    
    //end
    Bullet* pBulletRight = Bullet::CreateBullet();
    pBulletRight->runAction(CCSequence::create(CCDelayTime::create(3.f),
                                               CCMoveTo::create(fBulletRunTime, unitPos[target]),
                                               CCCallFuncN::create(pBulletRight, callfuncN_selector(BulletLayer::moveToTargetCallback)),
                                               NULL));
    if(shooter>=enTagUnitEnemyPos1)
    {
        pBulletRight->setPosition(ccp(SCREEN_WIDTH,SCREEN_HEIGHT));
        clippingNodeLeft->addChild(pBulletRight);
    }
    else
    {
        pBulletRight->setPosition(ccp(0,0));
        clippingNodeRight->addChild(pBulletRight);
    }
    
}

void BulletLayer::moveToTargetCallback(CCNode* pObj)
{
    Bullet* pB = dynamic_cast<Bullet*>(pObj);
    pB->removeFromParent();
}
