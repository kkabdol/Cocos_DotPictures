//
//  Dot.cpp
//  DotPictures
//
//  Created by Seonghyeon Choe on 12/31/12.
//
//

#include "Dot.h"
#include "CCDrawingPrimitives.h"
#include "Picture.h"

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
    std::stringstream ss;
    ss << "white_circle " << segment << ".png";
    
    std::cout << ss.str() << std::endl;
    
    if ( !CCSprite::initWithSpriteFrameName(ss.str().c_str()) ) {
        return false;
    }
    
    this->col = col;
    this->row = row;
    this->segment = segment;

    // set position
    const float radius = this->boundingBox().size.width;
    float x = radius*col + radius/2 - Dot::cWidth/2;
    float y = -radius*row - radius/2 + Dot::cHeight/2;

    const CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCNode::setPosition(x+size.width/2, y+size.height/2);
    

    
    // color
    unsigned long long r = 0;
    unsigned long long g = 0;
    unsigned long long b = 0;
    
    Picture* picture = Picture::sharedPicture();
    const int pWidth = picture->getWidth();
    const int pHeight = picture->getHeight();
    
    unsigned int count = 0;
    for (int sy = y-radius/2; sy<y+radius/2; ++sy) {
        for (int sx = x-radius/2; sx<x+radius/2; ++sx) {
            const CCPoint point = CCPoint(sx+pWidth/2, -sy+pHeight/2);
            r += picture->getPixelRColor(point);
            g += picture->getPixelGColor(point);
            b += picture->getPixelBColor(point);
            
            ++count;
        }
    }
    
    ccColor3B color = { (GLubyte)(r/count), (GLubyte)(g/count), (GLubyte)(b/count) };
    
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

bool Dot::isTouched(cocos2d::CCTouch* touch)
{
    if (this->numberOfRunningActions() > 0) {
        return false;
    }
    
    const unsigned int maxSeg = Picture::sharedPicture()->getMaxSegment();
    
    CCPoint pos = touch->getLocation();
    if ( this->getSegment() < maxSeg && this->boundingBox().containsPoint(pos) ) {
        return true;
    } else {
        return false;
    }
}

