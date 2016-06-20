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
        CCParticleSun* pP = CCParticleSun::create();
        addChild(pP);
        pP->setPosition(ccp(0,0));
        
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
        
        return true;
    } while (false);
    CCLog("Function BulletLayer::Init Error!");
    return false;
}

void BulletLayer::Shoot(enTagUnit shooter,enTagUnit target)
{
    ccpVector unitPos = GlobalData::sharedDirector()->getUnitPos();
    
//    Bullet* pB = Bullet::CreateBullet();
//    addChild(pB);
//    pB->setPosition(unitPos[shooter]);
//    pB->runAction(CCMoveTo::create(1, unitPos[target]));
//    pB->setScale(0.3);

}
