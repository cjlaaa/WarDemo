//
//  Bullet.hpp
//  WarDemo
//
//  Created by 常久龙 on 16/6/20.
//
//

#ifndef Bullet_hpp
#define Bullet_hpp

#include "PublicDef.h"

class Bullet : public CCLayer
{
public:
    static Bullet* CreateBullet();
    
protected:
    bool Init();
};

enum
{
    enTagClippingNodeLeft,
    enTagClippingNodeRight,
};

struct ShootData
{
    enUnitIndex shooter;
    enUnitIndex target;
    CCPoint shooterPos;
    CCPoint targetPos;
};

class BulletLayer : public CCLayer
{
public:
    static BulletLayer* CreateBulletLayer();
    void shoot(enUnitIndex shooter,enUnitIndex target, CCPoint shooterPos, CCPoint targetPos);
    void Update(float);
protected:
    bool Init();
    void moveToTargetCallback(CCNode* pObj);
    void OnHit(CCNode* pNode,void* pData);
};


#endif /* Bullet_hpp */
