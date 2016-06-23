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
    enUnitTypeError = -1,
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
    enUnitIndexEnemy1,
    enUnitIndexEnemy2,
    enUnitIndexEnemy3,
    enUnitIndexEnemy4,
    enUnitIndexEnemy5,
    enUnitIndexMax,
};

struct UnitData
{
    UnitData()
    {
        strCCBI = "";
        strTexture = "";
        eType = enUnitTypeError;
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

typedef map<enUnitIndex,CCPoint> unitPosMap;
typedef map<enUnitType,UnitData> unitDataMap;
typedef map<enUnitIndex,enUnitType> unitTypeMap;
class GlobalData
{
public:
    static GlobalData* sharedDirector(void);
    virtual bool init(void);
    unitPosMap getUnitPos() {return m_UnitPos;}
    unitDataMap getUnitDefaultData() {return m_UnitDefaultData;}
    unitTypeMap getUnitType() {return m_UnitType;}
    void setUnitTypeByIndex(enUnitIndex eIndex, enUnitType eType) {m_UnitType[eIndex] = eType;};
    enUnitType getUnitTypeByIndex(enUnitIndex eIndex) {return m_UnitType[eIndex];}
private:
    unitTypeMap m_UnitType;
    unitPosMap m_UnitPos;
    unitDataMap m_UnitDefaultData;
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