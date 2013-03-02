//
//  Dot.h
//  DotPictures
//
//  Created by Seonghyeon Choe on 12/31/12.
//
//

#ifndef DotPictures_Dot_h
#define DotPictures_Dot_h

#include "cocos2d.h"

class Dot : public cocos2d::CCSprite
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init(unsigned int col, unsigned int row, unsigned int segment);
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static Dot* dot(unsigned int col, unsigned int row, unsigned int segment);
    
    static const int cWidth = 640;
    static const int cHeight = 640;
    
    unsigned int getCol();
    unsigned int getRow();
    unsigned int getSegment();
    
    bool isTouched(cocos2d::CCTouch* touch);
    
    
private:
    
    unsigned int col;
    unsigned int row;
    unsigned int segment;
};

#endif
