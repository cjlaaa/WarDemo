#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "PublicDef.h"

enum
{
    enTagBg,
    enTagUnitsLayer,
    enTagBullet,
    enTagUI,
};

class MainScene : public cocos2d::CCLayer
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    void menuCloseCallback(CCObject* pSender);
    CREATE_FUNC(MainScene);
    
    void OnFire(enUnitIndex shooter, enUnitIndex target);
    void OnHit(enUnitIndex shooter, enUnitIndex target);
    void OnDead(enUnitIndex target);
    void addUnit(enUnitType eType,enUnitIndex eIndex);
    void removeUnit(enUnitIndex eIndex);
private:
    void Update(float);
};

#endif // __HELLOWORLD_SCENE_H__
