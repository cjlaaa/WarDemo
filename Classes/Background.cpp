//
//  Background.cpp
//  Background
//
//  Created by 常久龙 on 16/6/17.
//
//

#include "Background.h"

Background* Background::CreateBackground()
{
    do
    {
        Background* pRet = new Background;
        if (pRet && pRet->Init())
        {
            pRet->autorelease();
            return pRet;
        }
        delete pRet;
    } while (false);
    CCLog("Function Background::CreateBackground Error!");
    return NULL;
}

bool Background::Init()
{
    do
    {
        CCNodeLoaderLibrary * ccNodeLoaderLibraryLeft = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
        CCBReader * ccbReaderLeft = new CCBReader(ccNodeLoaderLibraryLeft);
        CCNode * bgLeft = ccbReaderLeft->readNodeGraphFromFile("ccb/background.ccbi", this);
        CCBAnimationManager* animationManagerLeft = ccbReaderLeft->getAnimationManager();
        animationManagerLeft->runAnimationsForSequenceNamed("left");
        ccbReaderLeft->release();
        
        CCNodeLoaderLibrary * ccNodeLoaderLibraryRight = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
        CCBReader * ccbReaderRight = new CCBReader(ccNodeLoaderLibraryRight);
        CCNode * bgRight = ccbReaderRight->readNodeGraphFromFile("ccb/background.ccbi", this);
        CCBAnimationManager* animationManagerRight = ccbReaderRight->getAnimationManager();
        animationManagerRight->runAnimationsForSequenceNamed("right");
        ccbReaderRight->release();
        
        CCClippingNode * clippingNodeLeft = CCClippingNode::create();
        addChild(clippingNodeLeft);
        clippingNodeLeft->addChild(bgLeft);
        CCDrawNode *shapeLeft = CCDrawNode::create();
        static CCPoint triangleLeft[3];
        triangleLeft[0] = ccp(0, 0);
        triangleLeft[1] = ccp(SCREEN_WIDTH,0);
        triangleLeft[2] = ccp(0,SCREEN_HEIGHT);
        static ccColor4F green = {0, 1, 0, 1};
        shapeLeft->drawPolygon(triangleLeft, 3, green, 0, green);
        clippingNodeLeft->setStencil(shapeLeft);
        clippingNodeLeft->setInverted(false);
        
        CCClippingNode * clippingNodeRight = CCClippingNode::create();
        addChild(clippingNodeRight);
        clippingNodeRight->addChild(bgRight);
        CCDrawNode *shapeRight = CCDrawNode::create();
        static CCPoint triangleRight[3];
        triangleRight[0] = ccp(SCREEN_WIDTH, SCREEN_HEIGHT);
        triangleRight[1] = ccp(SCREEN_WIDTH,0);
        triangleRight[2] = ccp(0,SCREEN_HEIGHT);
//        static ccColor4F green = {0, 1, 0, 1};
        shapeRight->drawPolygon(triangleRight, 3, green, 0, green);
        clippingNodeRight->setStencil(shapeRight);
        clippingNodeRight->setInverted(false);
        
        return true;
    } while (false);
    CCLog("Function Background::Init Error!");
    return false;
}

SEL_MenuHandler Background::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName)
{
    
}
SEL_CCControlHandler Background::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName)
{
    
}
bool Background::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode)
{
    
}
bool Background::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, CCBValue* pCCBValue)
{
    
}
void Background::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
    
}
SEL_CallFuncN Background::onResolveCCBCCCallFuncSelector(CCObject * pTarget, const char* pSelectorName)
{
    
}

