//
//  UI.cpp
//  WarDemo
//
//  Created by 常久龙 on 16/6/22.
//
//

#include "UI.h"
#include "MainScene.h"

UI* UI::CreateUI()
{
    do
    {
        UI* pRet = new UI;
        if (pRet && pRet->Init())
        {
            pRet->autorelease();
            return pRet;
        }
        delete pRet;
    } while (false);
    CCLog("Function UI::CreateUI Error!");
    return NULL;
}

bool UI::Init()
{
    do
    {
        CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
        CCBReader * ccbReader = new CCBReader(ccNodeLoaderLibrary);
        CCNode * ccbNode = ccbReader->readNodeGraphFromFile("ccb/ui.ccbi", this);
        ccbReader->release();
        addChild(ccbNode,enZOrderFront);
        
        CCTableView* tableView = CCTableView::create(this,
                                                     ccp(m_tableViewBg->getContentSize().width*m_tableViewBg->getScaleX(),
                                                         m_tableViewBg->getContentSize().height*m_tableViewBg->getScaleY()));
        tableView->setDirection(kCCScrollViewDirectionHorizontal);
        tableView->setPosition(ccp(0,0));
        tableView->setDelegate(this);
        tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
        this->addChild(tableView,enZOrderFront);
        tableView->reloadData();
        tableView->setBounceable(false);
        
        return true;
    } while (false);
    CCLog("Function UI::Init Error!");
    return false;
}

void UI::onEnter()
{
    CCLayer::onEnter();
    
    for (int i=enUnitIndexMy1; i<enUnitIndexMax; i++)
    {
        if (i<=enUnitIndexMy5)
        {
            addUI(CCRANDOM_0_1()>0.5?enUnitTypeCarMine:enUnitTypeTroopMine, (enUnitIndex)i);
        }
        else
        {
            addUI(CCRANDOM_0_1()>0.5?enUnitTypeCarEnemy:enUnitTypeTroopEnemy, (enUnitIndex)i);
        }
    }
}

void UI::addUI(enUnitType eType,enUnitIndex eIndex)
{
    MainScene* pMainScene = (MainScene*)(getParent());
    pMainScene->addUnit(eType, eIndex);
}

bool UI::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "tableViewBg", CCSprite*, m_tableViewBg);
    
    return true;
};

void UI::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCLog("tableCellTouched,%d",cell->getIdx());
}

CCSize UI::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
    CCSprite *sprite = CCSprite::create("ui5.png");
    CCSize size = sprite->getContentSize()*1.02;
    sprite->release();
    return size;
}

void UI::tableViewSubBtnCallback(CCObject* pSender)
{
    CCTableViewCell *cell = (CCTableViewCell*)(((CCMenuItemImage*)pSender)->getParent()->getParent());
    CCLog("tableViewSubBtnCallback,%d",cell->getIdx());
}


CCTableViewCell* UI::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCString *string = CCString::createWithFormat("%d", idx);
    CCTableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = new CCTableViewCell();
        cell->autorelease();
        CCSprite *sprite = CCSprite::create("ui5.png");
        sprite->setAnchorPoint(CCPointZero);
        sprite->setPosition(ccp(0, 0));
        cell->addChild(sprite);
        
        CCLabelTTF *label = CCLabelTTF::create(string->getCString(), "Helvetica", 20.0);
        label->setPosition(CCPointZero);
        label->setAnchorPoint(CCPointZero);
        label->setTag(123);
        cell->addChild(label);
    }
    else
    {
        CCLabelTTF *label = (CCLabelTTF*)cell->getChildByTag(123);
        label->setString(string->getCString());
    }
    
    
    return cell;
}

unsigned int UI::numberOfCellsInTableView(CCTableView *table)
{
    return 10;
}
