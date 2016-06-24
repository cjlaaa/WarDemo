#include "MainScene.h"
#include "Background.h"
#include "Units.h"
#include "Bullet.h"
#include "UI.h"
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
    addChild(pUnitLayer,enZOrderMiddle,enTagUnitsLayer);
    
    BulletLayer* pBulletLayer = BulletLayer::CreateBulletLayer();
    addChild(pBulletLayer,enZOrderFront,enTagBullet);
    
    UI* ui = UI::CreateUI();
    addChild(ui,enZOrderFront,enTagUI);
    
    this->schedule(schedule_selector(MainScene::Update),0.03);
    
    return true;
}

void MainScene::Update(float fT)
{
    Background* pBg = (Background*)(getChildByTag(enTagBg));
    pBg->Update(fT);
    
    UnitsLayer* pUnitLayer = (UnitsLayer*)(getChildByTag(enTagUnitsLayer));
    pUnitLayer->Update(fT);
    
    BulletLayer* pBulletLayer = (BulletLayer*)(getChildByTag(enTagBullet));
    pBulletLayer->Update(fT);
}

void MainScene::OnFire(enUnitIndex shooter, enUnitIndex target, CCPoint shooterPos, CCPoint targetPos)
{
    BulletLayer* pBulletLayer = (BulletLayer*)(getChildByTag(enTagBullet));
    pBulletLayer->shoot(shooter,target,shooterPos,targetPos);
}

void MainScene::OnHit(enUnitIndex shooter, enUnitIndex target, CCPoint targetPos)
{
    UnitsLayer* pUnitLayer = (UnitsLayer*)(getChildByTag(enTagUnitsLayer));
    pUnitLayer->OnHit(shooter, target);
    
    Background* pBg = (Background*)(getChildByTag(enTagBg));
    pBg->OnHit(target,targetPos);
}

void MainScene::OnDead(enUnitIndex target, CCPoint targetPos)
{
    Background* pBg = (Background*)(getChildByTag(enTagBg));
    pBg->OnDead(target,targetPos);
}

void MainScene::addUnit(enUnitType eType,enUnitIndex eIndex)
{
    UnitsLayer* pUnitLayer = (UnitsLayer*)(getChildByTag(enTagUnitsLayer));
    pUnitLayer->addUnit(eType, eIndex);
}

void MainScene::removeUnit(enUnitIndex eIndex)
{
    UnitsLayer* pUnitLayer = (UnitsLayer*)(getChildByTag(enTagUnitsLayer));
    pUnitLayer->removeUnit(eIndex);
}

void MainScene::OnStartGame()
{
    UnitsLayer* pUnitLayer = (UnitsLayer*)(getChildByTag(enTagUnitsLayer));
    pUnitLayer->StartGame();
}

void MainScene::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
