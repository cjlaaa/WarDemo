//
//  Bullet.cpp
//  WarDemo
//
//  Created by 常久龙 on 16/6/20.
//
//

#include "Bullet.h"


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
