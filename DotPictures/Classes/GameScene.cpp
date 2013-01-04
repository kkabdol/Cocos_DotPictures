//
//  GameScene.cpp
//  DotPictures
//
//  Created by Seonghyeon Choe on 12/31/12.
//
//

#include "GameScene.h"
#include "Dot.h"
#include "Picture.h"

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
    const CCSize size = CCDirector::sharedDirector()->getWinSize();

    // batch node sprite
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("white_circles.plist");
    this->batchNode = CCSpriteBatchNode::create("white_circles.png");;
    this->addChild(batchNode);
    
    // score label;
    this->scoreLabel = CCLabelTTF::create("Score : 0", "Thonburi", 34);
    this->scoreLabel->setPosition( ccp(0, size.height) );
    this->addChild(this->scoreLabel);
    this->scoreLabel->setAnchorPoint(CCPoint(0.0f, 1.0f));

    // button
    CCMenuItemImage *pResetItem = CCMenuItemImage::create("CloseNormal.png",
                                                          "CloseSelected.png",
                                                          this,
                                                          menu_selector(GameScene::resetCallback) );
    
    pResetItem->setPosition( ccp(size.width - 20, 20) );
    CCMenu* pMenu = CCMenu::create(pResetItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);
    
    return true;
}

void GameScene::onEnter()
{
    CCLayer::onEnter();
    
    this->registerWithTouchDispatcher();
    this->resetGame();
}


void GameScene::addOriginDot()
{
    batchNode->addChild(Dot::dot(0, 0, 1));
}

void GameScene::updateScoreLabel()
{
    // pop count
    long long score = Picture::sharedPicture()->getScoreCanGet();
    std::stringstream scoreSS;
    scoreSS << "Score : " << score;
    
    this->scoreLabel->setString(scoreSS.str().c_str());
}

void GameScene::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
    this->processTouchesOnDots(touches, event);
}

void GameScene::ccTouchesMoved(CCSet* touches, CCEvent* event)
{
    this->processTouchesOnDots(touches, event);
}

void GameScene::processTouchesOnDots(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
    
    std::vector<Dot*> dotsTouched;
    
    for(CCSetIterator it = touches->begin(); it != touches->end(); ++it) {
        CCTouch* touch = static_cast<CCTouch*>(*it);
        
     
        CCArray* array = batchNode->getChildren();
        for (unsigned int i=0; i<array->count(); ++i) {
            Dot* dot = dynamic_cast<Dot*>(array->objectAtIndex(i));
            
            if (dot->isTouched(touch)) {
                dotsTouched.push_back(dot);
                
            }
        }
    }
    
    
    while (dotsTouched.size() > 0) {
        Dot* dot = dotsTouched.back();
        dotsTouched.pop_back();
        
        Picture::sharedPicture()->addPop(dot->getSegment());
        
        const CCPoint originalPos = dot->getPosition();
        unsigned int nextCol = dot->getCol()*2;
        unsigned int nextRow = dot->getRow()*2;
        unsigned int nextSeg = dot->getSegment()+1;
        dot->removeFromParentAndCleanup(true);
        
        for (int j=0; j<2; ++j) {
            for (int i=0; i<2; ++i) {
                Dot* newDot = Dot::dot(nextCol+i, nextRow+j, nextSeg);
                
                const CCPoint nextPos = newDot->getPosition();
                
                newDot->setPosition(originalPos);
                newDot->runAction( CCEaseIn::create(CCMoveTo::create(0.3f, nextPos), 2.0f) );

                batchNode->addChild(newDot);
            }
        }
        
        
    }
    
    this->updateScoreLabel();
    
}

void GameScene::resetGame()
{
    batchNode->removeAllChildrenWithCleanup(true);
    Picture::sharedPicture()->init();
    addOriginDot();
    
    this->updateScoreLabel();
}

void GameScene::resetCallback(CCObject* pSender)
{
    this->resetGame();
}