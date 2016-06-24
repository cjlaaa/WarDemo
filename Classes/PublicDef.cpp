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

void GlobalData::setGameStartUnitPos()
{
    m_UnitPos[enUnitIndexMy1] = ccp(SCREEN_WIDTH*0.15,SCREEN_HEIGHT*0.6);
    m_UnitPos[enUnitIndexMy2] = ccp(SCREEN_WIDTH*0.2,SCREEN_HEIGHT*0.45);
    m_UnitPos[enUnitIndexMy3] = ccp(SCREEN_WIDTH*0.25,SCREEN_HEIGHT*0.3);
    m_UnitPos[enUnitIndexMy4] = ccp(SCREEN_WIDTH*0.4,SCREEN_HEIGHT*0.25);
    m_UnitPos[enUnitIndexMy5] = ccp(SCREEN_WIDTH*0.55,SCREEN_HEIGHT*0.2);
}

bool GlobalData::init()
{
    m_UnitPos.insert(pair<enUnitIndex,CCPoint>(enUnitIndexMy1,ccp(SCREEN_WIDTH*0.1,SCREEN_HEIGHT*0.7)));
    m_UnitPos.insert(pair<enUnitIndex,CCPoint>(enUnitIndexMy2,ccp(SCREEN_WIDTH*0.15,SCREEN_HEIGHT*0.55)));
    m_UnitPos.insert(pair<enUnitIndex,CCPoint>(enUnitIndexMy3,ccp(SCREEN_WIDTH*0.2,SCREEN_HEIGHT*0.4)));
    m_UnitPos.insert(pair<enUnitIndex,CCPoint>(enUnitIndexMy4,ccp(SCREEN_WIDTH*0.35,SCREEN_HEIGHT*0.35)));
    m_UnitPos.insert(pair<enUnitIndex,CCPoint>(enUnitIndexMy5,ccp(SCREEN_WIDTH*0.5,SCREEN_HEIGHT*0.3)));
                                                                                             
    m_UnitPos.insert(pair<enUnitIndex,CCPoint>(enUnitIndexEnemy1,ccp(SCREEN_WIDTH*0.45,SCREEN_HEIGHT*0.8)));
    m_UnitPos.insert(pair<enUnitIndex,CCPoint>(enUnitIndexEnemy2,ccp(SCREEN_WIDTH*0.6,SCREEN_HEIGHT*0.75)));
    m_UnitPos.insert(pair<enUnitIndex,CCPoint>(enUnitIndexEnemy3,ccp(SCREEN_WIDTH*0.75,SCREEN_HEIGHT*0.7)));
    m_UnitPos.insert(pair<enUnitIndex,CCPoint>(enUnitIndexEnemy4,ccp(SCREEN_WIDTH*0.8,SCREEN_HEIGHT*0.55)));
    m_UnitPos.insert(pair<enUnitIndex,CCPoint>(enUnitIndexEnemy5,ccp(SCREEN_WIDTH*0.85,SCREEN_HEIGHT*0.4)));
                                                                                                                                                                              
    //UnitData(string ccbi, string texture, enUnitType type, int hp, int dc, int firecd)
    m_UnitDefaultData.insert(pair<enUnitType,UnitData>(enUnitTypeCarMine,
                                                       UnitData("ccb/car1.ccbi",
                                                                "ccbResources/cars/1/ID_235_01.png",
                                                                enUnitTypeCarMine,50,3,50)));
    m_UnitDefaultData.insert(pair<enUnitType,UnitData>(enUnitTypeCarEnemy,
                                                       UnitData("ccb/car2.ccbi",
                                                                "ccbResources/cars/1/ID_236_01.png",
                                                                enUnitTypeCarEnemy,50,3,50)));
    m_UnitDefaultData.insert(pair<enUnitType,UnitData>(enUnitTypeTroopMine,
                                                       UnitData("ccb/troop1.ccbi",
                                                                "ccbResources/troop/2/001.png",
                                                                enUnitTypeTroopMine,30,1,100)));
    m_UnitDefaultData.insert(pair<enUnitType,UnitData>(enUnitTypeTroopEnemy,
                                                       UnitData("ccb/troop2.ccbi",
                                                                "ccbResources/troop/1/ID_257_TRIMd-1.png",
                                                                enUnitTypeTroopEnemy,30,1,100)));
    
    m_PlayerUnitNum.insert(pair<enUnitType,int>(enUnitTypeCarMine,3));
    m_PlayerUnitNum.insert(pair<enUnitType,int>(enUnitTypeTroopMine,3));
    
    m_UnitExpect.insert(pair<enUnitIndex, UnitExpect>(enUnitIndexMy1,UnitExpect(enUnitIndexEnemy1,
                                                                                enUnitIndexEnemy2,
                                                                                enUnitIndexEnemy3,
                                                                                enUnitIndexEnemy4,
                                                                                enUnitIndexEnemy5)));
    m_UnitExpect.insert(pair<enUnitIndex, UnitExpect>(enUnitIndexMy2,UnitExpect(enUnitIndexEnemy2,
                                                                                enUnitIndexEnemy3,
                                                                                enUnitIndexEnemy1,
                                                                                enUnitIndexEnemy4,
                                                                                enUnitIndexEnemy5)));
    m_UnitExpect.insert(pair<enUnitIndex, UnitExpect>(enUnitIndexMy3,UnitExpect(enUnitIndexEnemy3,
                                                                                enUnitIndexEnemy4,
                                                                                enUnitIndexEnemy2,
                                                                                enUnitIndexEnemy1,
                                                                                enUnitIndexEnemy5)));
    m_UnitExpect.insert(pair<enUnitIndex, UnitExpect>(enUnitIndexMy4,UnitExpect(enUnitIndexEnemy4,
                                                                                enUnitIndexEnemy3,
                                                                                enUnitIndexEnemy5,
                                                                                enUnitIndexEnemy2,
                                                                                enUnitIndexEnemy1)));
    m_UnitExpect.insert(pair<enUnitIndex, UnitExpect>(enUnitIndexMy5,UnitExpect(enUnitIndexEnemy5,
                                                                                enUnitIndexEnemy4,
                                                                                enUnitIndexEnemy3,
                                                                                enUnitIndexEnemy2,
                                                                                enUnitIndexEnemy1)));
    m_UnitExpect.insert(pair<enUnitIndex, UnitExpect>(enUnitIndexEnemy1,UnitExpect(enUnitIndexMy1,
                                                                                   enUnitIndexMy2,
                                                                                   enUnitIndexMy3,
                                                                                   enUnitIndexMy4,
                                                                                   enUnitIndexMy5)));
    m_UnitExpect.insert(pair<enUnitIndex, UnitExpect>(enUnitIndexEnemy2,UnitExpect(enUnitIndexMy2,
                                                                                   enUnitIndexMy3,
                                                                                   enUnitIndexMy1,
                                                                                   enUnitIndexMy4,
                                                                                   enUnitIndexMy5)));
    m_UnitExpect.insert(pair<enUnitIndex, UnitExpect>(enUnitIndexEnemy3,UnitExpect(enUnitIndexMy3,
                                                                                   enUnitIndexMy2,
                                                                                   enUnitIndexMy4,
                                                                                   enUnitIndexMy1,
                                                                                   enUnitIndexMy5)));
    m_UnitExpect.insert(pair<enUnitIndex, UnitExpect>(enUnitIndexEnemy4,UnitExpect(enUnitIndexMy4,
                                                                                   enUnitIndexMy3,
                                                                                   enUnitIndexMy5,
                                                                                   enUnitIndexMy2,
                                                                                   enUnitIndexMy1)));
    m_UnitExpect.insert(pair<enUnitIndex, UnitExpect>(enUnitIndexEnemy5,UnitExpect(enUnitIndexMy5,
                                                                                   enUnitIndexMy4,
                                                                                   enUnitIndexMy3,
                                                                                   enUnitIndexMy2,
                                                                                   enUnitIndexMy1)));
    return true;
}