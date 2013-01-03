//
//  Picture.h
//  DotPictures
//
//  Created by Seonghyeon Choe on 1/2/13.
//
//

#ifndef DotPictures_Picture_h
#define DotPictures_Picture_h

#include "cocos2d.h"

class Picture : public cocos2d::CCImage
{
public:
    virtual bool init(void);
    static Picture* sharedPicture(void);
    
    unsigned char getPixelRColor(const cocos2d::CCPoint& point);
    unsigned char getPixelGColor(const cocos2d::CCPoint& point);
    unsigned char getPixelBColor(const cocos2d::CCPoint& point);
    
    unsigned int getMaxSegment();
    
    void addPop(unsigned int seg);
    long long getScoreCanGet();
    

private:
    unsigned int pictureIndex;
    long long score;
    double minusScorePerPop;
};
#endif
