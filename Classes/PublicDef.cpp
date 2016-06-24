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
    m_UnitPos[enUnitIndexMy1] = ccp(SCREEN_WIDTH*0.106,SCREEN_HEIGHT*0.666);
    m_UnitPos[enUnitIndexMy2] = ccp(SCREEN_WIDTH*0.112,SCREEN_HEIGHT*0.514);
    m_UnitPos[enUnitIndexMy3] = ccp(SCREEN_WIDTH*0.149,SCREEN_HEIGHT*0.370);
    m_UnitPos[enUnitIndexMy4] = ccp(SCREEN_WIDTH*0.208,SCREEN_HEIGHT*0.244);
    m_UnitPos[enUnitIndexMy5] = ccp(SCREEN_WIDTH*0.296,SCREEN_HEIGHT*0.161);
    m_UnitPos[enUnitIndexMy6] = ccp(SCREEN_WIDTH*0.410,SCREEN_HEIGHT*0.120);
    
    m_UnitPos[enUnitIndexEnemy1] = ccp(SCREEN_WIDTH*0.494,SCREEN_HEIGHT*0.759);
    m_UnitPos[enUnitIndexEnemy2] = ccp(SCREEN_WIDTH*0.614,SCREEN_HEIGHT*0.730);
    m_UnitPos[enUnitIndexEnemy3] = ccp(SCREEN_WIDTH*0.719,SCREEN_HEIGHT*0.678);
    m_UnitPos[enUnitIndexEnemy4] = ccp(SCREEN_WIDTH*0.797,SCREEN_HEIGHT*0.592);
    m_UnitPos[enUnitIndexEnemy5] = ccp(SCREEN_WIDTH*0.850,SCREEN_HEIGHT*0.476);
    m_UnitPos[enUnitIndexEnemy6] = ccp(SCREEN_WIDTH*0.876,SCREEN_HEIGHT*0.341);
}

void GlobalData::setGamePreUnitPos()
{
    m_UnitPos[enUnitIndexMy1] = ccp(SCREEN_WIDTH*0.112,SCREEN_HEIGHT*0.693);
    m_UnitPos[enUnitIndexMy2] = ccp(SCREEN_WIDTH*0.137,SCREEN_HEIGHT*0.579);
    m_UnitPos[enUnitIndexMy3] = ccp(SCREEN_WIDTH*0.174,SCREEN_HEIGHT*0.484);
    m_UnitPos[enUnitIndexMy4] = ccp(SCREEN_WIDTH*0.235,SCREEN_HEIGHT*0.390);
    m_UnitPos[enUnitIndexMy5] = ccp(SCREEN_WIDTH*0.320,SCREEN_HEIGHT*0.323);
    m_UnitPos[enUnitIndexMy6] = ccp(SCREEN_WIDTH*0.428,SCREEN_HEIGHT*0.285);
    
    m_UnitPos[enUnitIndexEnemy1] = ccp(SCREEN_WIDTH*0.570,SCREEN_HEIGHT*0.767);
    m_UnitPos[enUnitIndexEnemy2] = ccp(SCREEN_WIDTH*0.679,SCREEN_HEIGHT*0.738);
    m_UnitPos[enUnitIndexEnemy3] = ccp(SCREEN_WIDTH*0.777,SCREEN_HEIGHT*0.700);
    m_UnitPos[enUnitIndexEnemy4] = ccp(SCREEN_WIDTH*0.845,SCREEN_HEIGHT*0.627);
    m_UnitPos[enUnitIndexEnemy5] = ccp(SCREEN_WIDTH*0.871,SCREEN_HEIGHT*0.500);
    m_UnitPos[enUnitIndexEnemy6] = ccp(SCREEN_WIDTH*0.865,SCREEN_HEIGHT*0.360);
}

bool GlobalData::init()
{
    m_UnitPos.insert(pair<enUnitIndex,CCPoint>(enUnitIndexMy1,ccp(SCREEN_WIDTH*0.112,SCREEN_HEIGHT*0.693)));
    m_UnitPos.insert(pair<enUnitIndex,CCPoint>(enUnitIndexMy2,ccp(SCREEN_WIDTH*0.137,SCREEN_HEIGHT*0.579)));
    m_UnitPos.insert(pair<enUnitIndex,CCPoint>(enUnitIndexMy3,ccp(SCREEN_WIDTH*0.174,SCREEN_HEIGHT*0.484)));
    m_UnitPos.insert(pair<enUnitIndex,CCPoint>(enUnitIndexMy4,ccp(SCREEN_WIDTH*0.235,SCREEN_HEIGHT*0.390)));
    m_UnitPos.insert(pair<enUnitIndex,CCPoint>(enUnitIndexMy5,ccp(SCREEN_WIDTH*0.320,SCREEN_HEIGHT*0.323)));
    m_UnitPos.insert(pair<enUnitIndex,CCPoint>(enUnitIndexMy6,ccp(SCREEN_WIDTH*0.428,SCREEN_HEIGHT*0.285)));
    
    m_UnitPos.insert(pair<enUnitIndex,CCPoint>(enUnitIndexEnemy1,ccp(SCREEN_WIDTH*0.570,SCREEN_HEIGHT*0.767)));
    m_UnitPos.insert(pair<enUnitIndex,CCPoint>(enUnitIndexEnemy2,ccp(SCREEN_WIDTH*0.679,SCREEN_HEIGHT*0.738)));
    m_UnitPos.insert(pair<enUnitIndex,CCPoint>(enUnitIndexEnemy3,ccp(SCREEN_WIDTH*0.777,SCREEN_HEIGHT*0.700)));
    m_UnitPos.insert(pair<enUnitIndex,CCPoint>(enUnitIndexEnemy4,ccp(SCREEN_WIDTH*0.845,SCREEN_HEIGHT*0.627)));
    m_UnitPos.insert(pair<enUnitIndex,CCPoint>(enUnitIndexEnemy5,ccp(SCREEN_WIDTH*0.871,SCREEN_HEIGHT*0.500)));
    m_UnitPos.insert(pair<enUnitIndex,CCPoint>(enUnitIndexEnemy6,ccp(SCREEN_WIDTH*0.865,SCREEN_HEIGHT*0.360)));

    
    //UnitData(string ccbi, string texture, enUnitType type, int hp, int dc, int firecd)
    m_UnitDefaultData.insert(pair<enUnitType,UnitData>(enUnitTypeCarMine,
                                                       UnitData("ccb/car1.ccbi",
                                                                "ccbResources/cars/1/ID_235_01.png",
                                                                enUnitTypeCarMine,50,10,50)));
    m_UnitDefaultData.insert(pair<enUnitType,UnitData>(enUnitTypeCarEnemy,
                                                       UnitData("ccb/car2.ccbi",
                                                                "ccbResources/cars/1/ID_236_01.png",
                                                                enUnitTypeCarEnemy,50,10,50)));
    m_UnitDefaultData.insert(pair<enUnitType,UnitData>(enUnitTypeTroopMine,
                                                       UnitData("ccb/troop1.ccbi",
                                                                "ccbResources/troop/2/001.png",
                                                                enUnitTypeTroopMine,30,5,100)));
    m_UnitDefaultData.insert(pair<enUnitType,UnitData>(enUnitTypeTroopEnemy,
                                                       UnitData("ccb/troop2.ccbi",
                                                                "ccbResources/troop/1/ID_257_TRIMd-1.png",
                                                                enUnitTypeTroopEnemy,30,5,100)));
    
    m_PlayerUnitNum.insert(pair<enUnitType,int>(enUnitTypeCarMine,6));
    m_PlayerUnitNum.insert(pair<enUnitType,int>(enUnitTypeTroopMine,6));
    
    m_UnitExpect.insert(pair<enUnitIndex, UnitExpect>(enUnitIndexMy1,UnitExpect(enUnitIndexEnemy1,
                                                                                enUnitIndexEnemy2,
                                                                                enUnitIndexEnemy3,
                                                                                enUnitIndexEnemy4,
                                                                                enUnitIndexEnemy5,
                                                                                enUnitIndexEnemy6)));
    m_UnitExpect.insert(pair<enUnitIndex, UnitExpect>(enUnitIndexMy2,UnitExpect(enUnitIndexEnemy2,
                                                                                enUnitIndexEnemy3,
                                                                                enUnitIndexEnemy1,
                                                                                enUnitIndexEnemy4,
                                                                                enUnitIndexEnemy5,
                                                                                enUnitIndexEnemy6)));
    m_UnitExpect.insert(pair<enUnitIndex, UnitExpect>(enUnitIndexMy3,UnitExpect(enUnitIndexEnemy3,
                                                                                enUnitIndexEnemy4,
                                                                                enUnitIndexEnemy2,
                                                                                enUnitIndexEnemy1,
                                                                                enUnitIndexEnemy5,
                                                                                enUnitIndexEnemy6)));
    m_UnitExpect.insert(pair<enUnitIndex, UnitExpect>(enUnitIndexMy4,UnitExpect(enUnitIndexEnemy4,
                                                                                enUnitIndexEnemy3,
                                                                                enUnitIndexEnemy5,
                                                                                enUnitIndexEnemy2,
                                                                                enUnitIndexEnemy6,
                                                                                enUnitIndexEnemy1)));
    m_UnitExpect.insert(pair<enUnitIndex, UnitExpect>(enUnitIndexMy5,UnitExpect(enUnitIndexEnemy5,
                                                                                enUnitIndexEnemy4,
                                                                                enUnitIndexEnemy6,
                                                                                enUnitIndexEnemy3,
                                                                                enUnitIndexEnemy2,
                                                                                enUnitIndexEnemy1)));
    m_UnitExpect.insert(pair<enUnitIndex, UnitExpect>(enUnitIndexMy6,UnitExpect(enUnitIndexEnemy6,
                                                                                enUnitIndexEnemy5,
                                                                                enUnitIndexEnemy4,
                                                                                enUnitIndexEnemy3,
                                                                                enUnitIndexEnemy2,
                                                                                enUnitIndexEnemy1)));
    m_UnitExpect.insert(pair<enUnitIndex, UnitExpect>(enUnitIndexEnemy1,UnitExpect(enUnitIndexMy1,
                                                                                   enUnitIndexMy2,
                                                                                   enUnitIndexMy3,
                                                                                   enUnitIndexMy4,
                                                                                   enUnitIndexMy5,
                                                                                   enUnitIndexMy6)));
    m_UnitExpect.insert(pair<enUnitIndex, UnitExpect>(enUnitIndexEnemy2,UnitExpect(enUnitIndexMy2,
                                                                                   enUnitIndexMy3,
                                                                                   enUnitIndexMy1,
                                                                                   enUnitIndexMy4,
                                                                                   enUnitIndexMy5,
                                                                                   enUnitIndexMy6)));
    m_UnitExpect.insert(pair<enUnitIndex, UnitExpect>(enUnitIndexEnemy3,UnitExpect(enUnitIndexMy3,
                                                                                   enUnitIndexMy2,
                                                                                   enUnitIndexMy4,
                                                                                   enUnitIndexMy1,
                                                                                   enUnitIndexMy5,
                                                                                   enUnitIndexMy6)));
    m_UnitExpect.insert(pair<enUnitIndex, UnitExpect>(enUnitIndexEnemy4,UnitExpect(enUnitIndexMy4,
                                                                                   enUnitIndexMy3,
                                                                                   enUnitIndexMy5,
                                                                                   enUnitIndexMy2,
                                                                                   enUnitIndexMy6,
                                                                                   enUnitIndexMy1)));
    m_UnitExpect.insert(pair<enUnitIndex, UnitExpect>(enUnitIndexEnemy5,UnitExpect(enUnitIndexMy5,
                                                                                   enUnitIndexMy4,
                                                                                   enUnitIndexMy6,
                                                                                   enUnitIndexMy3,
                                                                                   enUnitIndexMy2,
                                                                                   enUnitIndexMy1)));
    m_UnitExpect.insert(pair<enUnitIndex, UnitExpect>(enUnitIndexEnemy6,UnitExpect(enUnitIndexMy6,
                                                                                   enUnitIndexMy5,
                                                                                   enUnitIndexMy4,
                                                                                   enUnitIndexMy3,
                                                                                   enUnitIndexMy2,
                                                                                   enUnitIndexMy1)));
    return true;
}