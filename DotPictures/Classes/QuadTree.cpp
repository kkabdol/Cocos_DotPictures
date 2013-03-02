//
//  QuadTree.cpp
//  DotPictures
//
//  Created by Seonghyeon Choe on 3/2/13.
//
//

#include "QuadTree.h"
#include "Dot.h"

using namespace cocos2d;



QuadTree::QuadTree(Dot* rootDot) {
    assert(rootDot);
    
    this->dot = rootDot;
    this->center = rootDot->getPosition();
    
    this->northWest = NULL;
    this->northEast = NULL;
    this->southWest = NULL;
    this->southEast = NULL;
}
QuadTree::~QuadTree() {
    
    this->dot = NULL;
    
    if(this->northWest) {
        assert(this->northEast);
        assert(this->southWest);
        assert(this->southEast);
        
        delete this->northWest;
        this->northWest = NULL;
        
        delete this->northEast;
        this->northEast = NULL;
        
        delete this->southWest;
        this->southWest = NULL;
        
        delete this->southEast;
        this->southEast = NULL;
        
    }
}

Dot* QuadTree::getDot(){
    return this->dot;
}

cocos2d::CCPoint QuadTree::getCenter() {
    return this->center;
}

Dot* QuadTree::getDotInPoint(int x, int y){
    if (this->getDot()) {
        this->center = this->getDot()->getPosition();   // update
        return this->getDot();
    }
    
    QuadTree* child = NULL;
    if (x < center.x) {
        if (y >= center.y) {
            child = this->northWest;
        } else {
            child = this->southWest;
        }
    } else {
        if (y >= center.y) {
            child = this->northEast;
        } else {
            child = this->southEast;
        }
    }
    assert(child != NULL);
    
    return child->getDotInPoint(x, y);
}

void QuadTree::addDot(Dot* parent, Dot* northWest, Dot* northEast, Dot* southWest, Dot* southEast) {
    
    const CCPoint parentCenter = parent->getPosition();
    
    QuadTree* aTree = this;
    CCPoint treeCenter = aTree->getCenter();
    while (treeCenter.x != parentCenter.x ||
           treeCenter.y != parentCenter.y) {        
        
        if (parentCenter.x < treeCenter.x) {
            if (parentCenter.y >= treeCenter.y) {
                aTree = aTree->northWest;
            } else {
                aTree = aTree->southWest;
            }
        } else {
            if (parentCenter.y >= treeCenter.y) {
                aTree = aTree->northEast;
            } else {
                aTree = aTree->southEast;
            }
        }
        treeCenter = aTree->getCenter();
    }
    
    aTree->setChildren(northWest, northEast, southWest, southEast);
}

void QuadTree::setChildren(Dot* northWest, Dot* northEast, Dot* southWest, Dot* southEast) {
    this->dot = NULL;
    
    this->northWest = new QuadTree(northWest);
    this->northEast = new QuadTree(northEast);
    this->southWest = new QuadTree(southWest);
    this->southEast = new QuadTree(southEast);
    
    
}