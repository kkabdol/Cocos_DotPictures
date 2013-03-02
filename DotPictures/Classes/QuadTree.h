//
//  QuadTree.h
//  DotPictures
//
//  Created by Seonghyeon Choe on 3/2/13.
//
//

#ifndef DotPictures_QuadTree_h
#define DotPictures_QuadTree_h


#include "cocos2d.h"
class Dot;
class QuadTree {
public:
    enum {
        kNorthWest,
        kNorthEast,
        kSouthWest,
        kSouthEast,
        
        kMaxDirection,
    };
    
    QuadTree(Dot* rootDot);
    ~QuadTree();
    
    Dot* getDot();
    cocos2d::CCPoint getCenter();
    Dot* getDotInPoint(int x, int y);
    void addDot(Dot* parent, Dot* northWest, Dot* northEast, Dot* southWest, Dot* southEast);
    void setChildren(Dot* northWest, Dot* northEast, Dot* southWest, Dot* southEast);
    
private:
    // if dot == NULL, there are children
    Dot* dot;
    cocos2d::CCPoint center;
    
    QuadTree* northWest;
    QuadTree* northEast;
    QuadTree* southWest;
    QuadTree* southEast;
    
};
#endif
