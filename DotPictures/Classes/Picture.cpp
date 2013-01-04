//
//  Picture.cpp
//  DotPictures
//
//  Created by Seonghyeon Choe on 1/2/13.
//
//

#include "Picture.h"

using namespace cocos2d;

const unsigned int kMaxSegment = 7;

static Picture s_sharedPicture;
static bool s_bFirstRun = true;


Picture* Picture::sharedPicture(void)
{
	if (s_bFirstRun)
	{
		s_sharedPicture.init();
	}
    
	return &s_sharedPicture;
}

bool Picture::init(void)
{
    CCArray* pictures = CCArray::createWithContentsOfFile("Pictures.plist");

    this->pictureIndex = rand() % pictures->count();
    CCDictionary* curPicture = dynamic_cast<CCDictionary*>(pictures->objectAtIndex(this->pictureIndex));
    const char* filename = curPicture->valueForKey("file")->getCString();
    if ( !CCImage::initWithImageFile(filename))  {
        return false;
    }
    
    s_bFirstRun = false;
    
    pictures->release();
    
    
    // max score = sum(4^(n-1)*n)*c n : 1~(maxSegment-1)
    this->score = 10000000;
    this->minusScorePerPop = 1;
    
    return true;
}

unsigned int Picture::getMaxSegment()
{
    return kMaxSegment;
}


unsigned char Picture::getPixelRColor(const cocos2d::CCPoint& point)
{
    if (point.x < 0 || point.x >= this->getWidth() ||
        point.y < 0 || point.y >= this->getHeight()) {
        return 255;
    } else {
        
        const unsigned char* data = this->getData();
        const int index = point.y*this->getWidth() + point.x;
        
        return data[index*4 + 0];
    }
}

unsigned char Picture::getPixelGColor(const cocos2d::CCPoint& point)
{
    if (point.x < 0 || point.x >= this->getWidth() ||
        point.y < 0 || point.y >= this->getHeight()) {
        return 255;
    } else {
        
        const unsigned char* data = this->getData();
        const int index = point.y*this->getWidth() + point.x;
        
        return data[index*4 + 1];
    }
    
}
unsigned char Picture::getPixelBColor(const cocos2d::CCPoint& point)
{
    
    if (point.x < 0 || point.x >= this->getWidth() ||
        point.y < 0 || point.y >= this->getHeight()) {
        return 255;
    } else {
        
        const unsigned char* data = this->getData();
        const int index = point.y*this->getWidth() + point.x;
        
        return data[index*4 + 2];
    }
}

void Picture::addPop(unsigned int seg)
{
    if (this->score <= 1000) {
        return;
    }
    
    this->score -= this->minusScorePerPop;
    this->score = (this->score > 1000) ? this->score : 1000;
    
    this->minusScorePerPop *= 1.05;
    
}

long long Picture::getScoreCanGet() {
    return this->score;
}