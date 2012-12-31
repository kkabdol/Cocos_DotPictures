//
//  Dot.cpp
//  DotPictures
//
//  Created by Seonghyeon Choe on 12/31/12.
//
//

#include "Dot.h"
#include "CCDrawingPrimitives.h"

using namespace cocos2d;

const float kRadius = 1.0;

Dot* Dot::dot(unsigned int col, unsigned int row, unsigned int segment)
{
    Dot* pRet = new Dot;
    if (pRet && pRet->init(col, row, segment)) {
        pRet->autorelease();
        return pRet;
    } else {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool Dot::init(unsigned int col, unsigned int row, unsigned int segment)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    if ( !CCSprite::initWithFile("white_circle.png") ) {
        return false;
    }
    
    this->col = col;
    this->row = row;
    this->segment = segment;

    // set scale
    const float scale = 1.0 / powf(2.0f, (float)(segment-1));
    CCNode::setScale(scale);

    
    // set position
    const float radius = this->getContentSize().height;
    const float segmentedRadius = radius * scale;
    float x = segmentedRadius*col + segmentedRadius/2 - radius/2;
    float y = segmentedRadius*row + segmentedRadius/2 - radius/2;

    x += size.width/2;
    y += size.height/2;
    CCNode::setPosition(x, y);
    
    
    ccColor3B color = { 255, 255, 255 };
    
    this->setColor(color);
        
    return true;
}


unsigned int Dot::getCol()
{
    return this->col;
}
unsigned int Dot::getRow()
{
    return this->row;
}
unsigned int Dot::getSegment()
{
    return this->segment;
}