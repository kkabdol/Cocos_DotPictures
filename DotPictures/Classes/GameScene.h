//
//  GameScene.h
//  DotPictures
//
//  Created by Seonghyeon Choe on 12/31/12.
//
//

#ifndef DotPictures_GameScene_h
#define DotPictures_GameScene_h

#include "cocos2d.h"

class GameScene : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(GameScene);
    
    void resetCallback(CCObject* pSender);

    
private:
    virtual void onEnter();
    virtual void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    virtual void ccTouchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    
    void processTouchesOnDots(cocos2d::CCSet* touches, cocos2d::CCEvent* event);

    void addOriginDot();
    
    void resetGame();
    void updateScoreLabel();
    
    
    cocos2d::CCLabelTTF* scoreLabel;
    cocos2d::CCSpriteBatchNode* batchNode;
};

#endif
