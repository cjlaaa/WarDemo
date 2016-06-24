//
//  PublicDef.h
//  WarDemo
//
//  Created by 常久龙 on 16/6/17.
//
//

#ifndef PublicDef_h
#define PublicDef_h

#include "cocos2d.h"
USING_NS_CC;
#include "cocos-ext.h"
USING_NS_CC_EXT;
using namespace std;

#define SCREEN_WIDTH    (CCDirector::sharedDirector()->getVisibleSize().width)
#define SCREEN_HEIGHT   (CCDirector::sharedDirector()->getVisibleSize().height)

enum enUnitType
{
    enUnitTypeNone = -1,
    enUnitTypeCarMine,
    enUnitTypeCarEnemy,
    enUnitTypeTroopMine,
    enUnitTypeTroopEnemy,
};

enum enUnitIndex
{
    enUnitIndexError,
    enUnitIndexMy1 = 0,
    enUnitIndexMy2,
    enUnitIndexMy3,
    enUnitIndexMy4,
    enUnitIndexMy5,
    enUnitIndexMy6,
    enUnitIndexEnemy1,
    enUnitIndexEnemy2,
    enUnitIndexEnemy3,
    enUnitIndexEnemy4,
    enUnitIndexEnemy5,
    enUnitIndexEnemy6,
    enUnitIndexMax,
};

struct UnitData
{
    UnitData()
    {
        strCCBI = "";
        strTexture = "";
        eType = enUnitTypeNone;
        nHp = 0;
        nDC = 0;
        nFireCD = 0;
    }
    
    UnitData(string ccbi, string texture, enUnitType type, int hp, int dc, int firecd)
    {
        strCCBI = ccbi;
        strTexture = texture;
        eType = type;
        nHp = hp;
        nDC = dc;
        nFireCD = firecd;
    }
    
    string strCCBI;
    string strTexture;
    enUnitType eType;
    int nHp;
    int nDC;
    int nFireCD;
};

struct UnitExpect
{
    UnitExpect()
    {
    }
    UnitExpect(enUnitIndex ePrimary,enUnitIndex eSecondary,enUnitIndex eThird,enUnitIndex eFourth, enUnitIndex eFifth, enUnitIndex eSixth)
    {
        primary = ePrimary;
        secondary = eSecondary;
        third = eThird;
        fourth = eFourth;
        fifth = eFifth;
        sixth = eSixth;
    }
    
    enUnitIndex primary;
    enUnitIndex secondary;
    enUnitIndex third;
    enUnitIndex fourth;
    enUnitIndex fifth;
    enUnitIndex sixth;
};

typedef map<enUnitIndex,CCPoint> unitPosMap;
typedef map<enUnitType,UnitData> unitDataMap;
typedef map<enUnitIndex,enUnitType> unitTypeMap;
typedef map<enUnitType,int> unitNumMap;
typedef map<enUnitIndex,UnitExpect> unitExpectMap;
class GlobalData
{
public:
    static GlobalData* sharedDirector(void);
    virtual bool init(void);
    unitPosMap getUnitPos() {return m_UnitPos;}
    void setGameStartUnitPos();
    unitDataMap getUnitDefaultData() {return m_UnitDefaultData;}
    unitTypeMap getUnitType() {return m_UnitType;}
    void setUnitTypeByIndex(enUnitIndex eIndex, enUnitType eType) {m_UnitType[eIndex] = eType;};
    enUnitType getUnitTypeByIndex(enUnitIndex eIndex) {return m_UnitType[eIndex];}
    unitNumMap getPlayerUnitNum() {return m_PlayerUnitNum;}
    UnitExpect getUnitExpectByIndex(enUnitIndex eIndex){return m_UnitExpect[eIndex];}
private:
    unitTypeMap m_UnitType;
    unitPosMap m_UnitPos;
    unitDataMap m_UnitDefaultData;
    unitNumMap m_PlayerUnitNum;
    unitExpectMap m_UnitExpect;
};

enum
{
    enZOrderBack,
    enZOrderMiddle,
    enZOrderFront,
};

struct FireMsg
{
    enUnitIndex shooter;
    enUnitIndex target;
};

#endif /* PublicDef_h */