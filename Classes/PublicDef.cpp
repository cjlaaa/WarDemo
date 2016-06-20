//
//  PublicDef.cpp
//  WarDemo
//
//  Created by 常久龙 on 16/6/20.
//
//

#include "PublicDef.h"

static GlobalData *s_GlobalData = NULL;
GlobalData* GlobalData::sharedDirector(void)
{
    if (!s_GlobalData)
    {
        s_GlobalData = new GlobalData();
        s_GlobalData->init();
    }
    return s_GlobalData;
}

bool GlobalData::init()
{
    m_UnitPos.push_back(ccp(SCREEN_WIDTH*0.15,SCREEN_HEIGHT*0.6));
    m_UnitPos.push_back(ccp(SCREEN_WIDTH*0.2,SCREEN_HEIGHT*0.45));
    m_UnitPos.push_back(ccp(SCREEN_WIDTH*0.25,SCREEN_HEIGHT*0.3));
    m_UnitPos.push_back(ccp(SCREEN_WIDTH*0.4,SCREEN_HEIGHT*0.25));
    m_UnitPos.push_back(ccp(SCREEN_WIDTH*0.55,SCREEN_HEIGHT*0.2));
    
    m_UnitPos.push_back(ccp(SCREEN_WIDTH*0.35,SCREEN_HEIGHT*0.7));
    m_UnitPos.push_back(ccp(SCREEN_WIDTH*0.5,SCREEN_HEIGHT*0.65));
    m_UnitPos.push_back(ccp(SCREEN_WIDTH*0.65,SCREEN_HEIGHT*0.6));
    m_UnitPos.push_back(ccp(SCREEN_WIDTH*0.7,SCREEN_HEIGHT*0.45));
    m_UnitPos.push_back(ccp(SCREEN_WIDTH*0.75,SCREEN_HEIGHT*0.3));
    
    return true;
}