#include "HelloWorldScene.h"
#include "Background.h"
#include "Units.h"
USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !CCLayer::init() )return false;
    
    Background* pBg = Background::CreateBackground();
    addChild(pBg,enZOrderBack,enTagBg);
    
    UnitsLayer* pUnitLayer = UnitsLayer::CreateUnitsLayer();
    addChild(pUnitLayer,enZOrderMiddle,enTagUnits);
    
    return true;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
