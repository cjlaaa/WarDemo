#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "PublicDef.h"

class MainScene : public cocos2d::CCLayer
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    void menuCloseCallback(CCObject* pSender);
    CREATE_FUNC(MainScene);
    
    void OnFire(enTagUnit shooter, enTagUnit target);
    void OnHit(enTagUnit shooter, enTagUnit target);
private:
    void Update(float);
};

#endif // __HELLOWORLD_SCENE_H__