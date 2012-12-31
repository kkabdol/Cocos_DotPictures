//
//  GameScene.cpp
//  DotPictures
//
//  Created by Seonghyeon Choe on 12/31/12.
//
//

#include "GameScene.h"
#include "Dot.h"

using namespace cocos2d;

CCScene* GameScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameScene *layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    
    
    return true;
}

void GameScene::onEnter()
{
    this->initDots();


    this->registerWithTouchDispatcher();
}

void GameScene::initDots()
{
    this->addChild(Dot::dot(0, 0, 1));
}

void GameScene::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
    CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
    if (scene->getChildrenCount() > 0) {
        CCArray* array = this->getChildren();
        Dot* dot = dynamic_cast<Dot*>(array->objectAtIndex(0));
        
        unsigned int nextCol = dot->getCol()*2;
        unsigned int nextRow = dot->getRow()*2;
        unsigned int nextSeg = dot->getSegment()+1;
        
        this->addChild(Dot::dot(nextCol+0, nextRow+0, nextSeg));
        this->addChild(Dot::dot(nextCol+1, nextRow+0, nextSeg));
        this->addChild(Dot::dot(nextCol+0, nextRow+1, nextSeg));
        this->addChild(Dot::dot(nextCol+1, nextRow+1, nextSeg));
        
        dot->removeFromParentAndCleanup(true);
        
    }
}