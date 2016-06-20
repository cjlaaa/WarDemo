#include "MainScene.h"
#include "Background.h"
#include "Units.h"
#include "Bullet.h"
USING_NS_CC;

CCScene* MainScene::scene()
{
    CCScene *scene = CCScene::create();
    
    MainScene *layer = MainScene::create();

    scene->addChild(layer);

    return scene;
}

bool MainScene::init()
{
    if ( !CCLayer::init() )return false;
    
    Background* pBg = Background::CreateBackground();
    addChild(pBg,enZOrderBack,enTagBg);
    
    UnitsLayer* pUnitLayer = UnitsLayer::CreateUnitsLayer();
    addChild(pUnitLayer,enZOrderMiddle,enTagUnits);
    
    BulletLayer* pBulletLayer = BulletLayer::CreateBulletLayer();
    addChild(pBulletLayer,enZOrderFront,enTagBullet);
    
    return true;
}


void MainScene::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
