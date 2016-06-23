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
//    m_UnitPos.push_back(ccp(SCREEN_WIDTH*0.15,SCREEN_HEIGHT*0.6));
//    m_UnitPos.push_back(ccp(SCREEN_WIDTH*0.2,SCREEN_HEIGHT*0.45));
//    m_UnitPos.push_back(ccp(SCREEN_WIDTH*0.25,SCREEN_HEIGHT*0.3));
//    m_UnitPos.push_back(ccp(SCREEN_WIDTH*0.4,SCREEN_HEIGHT*0.25));
//    m_UnitPos.push_back(ccp(SCREEN_WIDTH*0.55,SCREEN_HEIGHT*0.2));
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
                                                                enUnitTypeCarMine,50,1,300)));
    m_UnitDefaultData.insert(pair<enUnitType,UnitData>(enUnitTypeCarEnemy,
                                                       UnitData("ccb/car2.ccbi",
                                                                "ccbResources/cars/1/ID_236_01.png",
                                                                enUnitTypeCarEnemy,50,1,300)));
    m_UnitDefaultData.insert(pair<enUnitType,UnitData>(enUnitTypeTroopMine,
                                                       UnitData("ccb/troop1.ccbi",
                                                                "ccbResources/troop/2/001.png",
                                                                enUnitTypeTroopMine,20,5,500)));
    m_UnitDefaultData.insert(pair<enUnitType,UnitData>(enUnitTypeTroopEnemy,
                                                       UnitData("ccb/troop2.ccbi",
                                                                "ccbResources/troop/1/ID_257_TRIMd-1.png",
                                                                enUnitTypeTroopEnemy,20,5,500)));
    
    
    return true;
}