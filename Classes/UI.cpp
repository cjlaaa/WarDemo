//
//  UI.cpp
//  WarDemo
//
//  Created by 常久龙 on 16/6/22.
//
//

#include "UI.h"

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
        
        return true;
    } while (false);
    CCLog("Function UI::Init Error!");
    return false;
}