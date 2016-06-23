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
        unitNumMap playerWeaponNum = GlobalData::sharedDirector()->getPlayerUnitNum();
        unitDataMap unitData = GlobalData::sharedDirector()->getUnitDefaultData();
        for (unitNumMap::iterator it=playerWeaponNum.begin(); it!=playerWeaponNum.end(); ++it)
        {
            m_unitData.push_back(uiUnit(unitData[it->first],it->second));
        }
        
        CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
        CCBReader * ccbReader = new CCBReader(ccNodeLoaderLibrary);
        CCNode * ccbNode = ccbReader->readNodeGraphFromFile("ccb/ui.ccbi", this);
        ccbReader->release();
        addChild(ccbNode,enZOrderFront);
        
        unitPosMap unitPos = GlobalData::sharedDirector()->getUnitPos();
        CCArray* pBtnArray = CCArray::create();
        for (int i=enUnitIndexMy1; i<enUnitIndexEnemy1; i++)
        {
            m_vecBattleFieldStatus.push_back(enUnitTypeError);
            CCMenuItemImage *pBtn = CCMenuItemImage::create("CloseNormal.png",
                                                                  "CloseSelected.png",
                                                                  this,
                                                                  menu_selector(UI::removeUnit));
            pBtn->setTag(i);
            pBtn->setScale(2);
            pBtn->setPosition(unitPos[(enUnitIndex)i]);
            pBtnArray->addObject(pBtn);
        }
        CCMenu* pMenu = CCMenu::createWithArray(pBtnArray);
        pMenu->setPosition(CCPointZero);
        this->addChild(pMenu,enZOrderFront,enTagMenuBF);
        pBtnArray->release();
        
        CCTableView* tableView = CCTableView::create(this,
                                                     ccp(m_tableViewBg->getContentSize().width*m_tableViewBg->getScaleX(),
                                                         m_tableViewBg->getContentSize().height*m_tableViewBg->getScaleY()));
        tableView->setDirection(kCCScrollViewDirectionHorizontal);
        tableView->setPosition(ccp(0,0));
        tableView->setDelegate(this);
        tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
        this->addChild(tableView,enZOrderFront,enTagTableView);
        tableView->reloadData();
//        tableView->setBounceable(false);
        
        m_startGame->setScale(0.4);
        m_startGame->setVisible(false);
        
        return true;
    } while (false);
    CCLog("Function UI::Init Error!");
    return false;
}

void UI::removeUnit(CCNode* pNode)
{
    enUnitIndex index = (enUnitIndex)(pNode->getTag());
//    CCLog("%d",index);
    
    for (int i=0; i<m_unitData.size(); i++)
    {
        if(m_unitData[i].Data.eType==m_vecBattleFieldStatus[index])
        {
            ((MainScene*)(getParent()))->removeUnit(index);
            m_unitData[i].nNum++;
            break;
        }
    }
    
    m_vecBattleFieldStatus[index] = enUnitTypeError;
    CCTableView* pList = (CCTableView*)getChildByTag(enTagTableView);
    pList->reloadData();
    
    bool bIsShowBtn = false;
    for (int i=0; i<m_vecBattleFieldStatus.size(); i++)
    {
        if(m_vecBattleFieldStatus[i]!=enUnitTypeError)
        {
            bIsShowBtn = true;
            break;
        }
    }
    m_startGame->setVisible(bIsShowBtn);
}

void UI::onEnter()
{
    CCLayer::onEnter();
    
    for (int i=enUnitIndexMy1; i<enUnitIndexMax; i++)
    {
        if (i<enUnitIndexEnemy1)
        {
//            addUnit(CCRANDOM_0_1()>0.5?enUnitTypeCarMine:enUnitTypeTroopMine, (enUnitIndex)i);
        }
        else
        {
            addUnit(CCRANDOM_0_1()>0.5?enUnitTypeCarEnemy:enUnitTypeTroopEnemy, (enUnitIndex)i);
        }
    }
}

void UI::addUnit(enUnitType eType,enUnitIndex eIndex)
{
    MainScene* pMainScene = (MainScene*)(getParent());
    pMainScene->addUnit(eType, eIndex);
}

SEL_MenuHandler UI::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "startgame", UI::onStartGame);
    
    return NULL;
}

void UI::onStartGame(CCObject * pSender)
{
    MainScene* pMainScene = (MainScene*)(getParent());
    pMainScene->OnStartGame();
    
    m_startGame->setVisible(false);
    m_tableViewBg->setVisible(false);
    CCMenu* pMenu = (CCMenu*)getChildByTag(enTagMenuBF);
    pMenu->setVisible(false);
    CCTableView* pT = (CCTableView*)getChildByTag(enTagTableView);
    pT->setVisible(false);
}

bool UI::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "tableViewBg", CCSprite*, m_tableViewBg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "startgame", CCMenuItemImage*, m_startGame);
    return true;
};

void UI::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
//    CCLog("tableCellTouched,%d",cell->getIdx());
    if(m_unitData[cell->getIdx()].nNum>0)
    {
        int nIndex = -1;
        for (int i=0; i<m_vecBattleFieldStatus.size(); i++)
        {
            if(m_vecBattleFieldStatus[i]==enUnitTypeError)
            {
                nIndex = i;
                break;
            }
        }
        
        if(nIndex>=0)
        {
            m_unitData[cell->getIdx()].nNum -= 1;
            addUnit(m_unitData[cell->getIdx()].Data.eType, (enUnitIndex)nIndex);
            m_startGame->setVisible(true);
            m_vecBattleFieldStatus[nIndex] = m_unitData[cell->getIdx()].Data.eType;
            
            CCTableView* pList = (CCTableView*)getChildByTag(enTagTableView);
            pList->reloadData();
        }
    }
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
    CCString *num = CCString::createWithFormat("%d", m_unitData[idx].nNum);
    CCTableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = new CCTableViewCell();
        cell->autorelease();
        CCSprite *sprite = CCSprite::create("ui5.png");
        sprite->setAnchorPoint(CCPointZero);
        sprite->setPosition(ccp(0, 0));
        cell->addChild(sprite);
        
        CCLabelTTF *label = CCLabelTTF::create(num->getCString(), "Helvetica", 50.0);
        label->setPosition(ccp(sprite->getContentSize().width-label->getContentSize().width,sprite->getContentSize().height/2));
        label->setAnchorPoint(CCPointZero);
        label->setTag(enTagInCellNum);
        cell->addChild(label);
        
        CCSprite* pPic = CCSprite::create(m_unitData[idx].Data.strTexture.c_str());
        cell->addChild(pPic,enZOrderFront,enTagInCellTexture);
        pPic->setScale(0.7);
        pPic->setPosition(ccp(sprite->getContentSize().width/2,sprite->getContentSize().height/2));
    }
    else
    {
        CCLabelTTF *label = (CCLabelTTF*)cell->getChildByTag(enTagInCellNum);
        label->setString(num->getCString());
        
        CCSprite* pPic = (CCSprite*)cell->getChildByTag(enTagInCellTexture);
        pPic->initWithFile(m_unitData[idx].Data.strTexture.c_str());
    }
    
    
    return cell;
}

unsigned int UI::numberOfCellsInTableView(CCTableView *table)
{
    return m_unitData.size();
}
