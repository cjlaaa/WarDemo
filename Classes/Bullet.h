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

class BulletLayer : public CCLayer
{
public:
    static BulletLayer* CreateBulletLayer();
    void Shoot(enTagUnit shooter,enTagUnit target);
    
protected:
    bool Init();
};


#endif /* Bullet_hpp */
