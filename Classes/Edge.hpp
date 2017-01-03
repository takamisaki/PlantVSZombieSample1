//屏幕大小的物理边界

#ifndef Edge_hpp
#define Edge_hpp

#include <stdio.h>
#include <cocos2d.h>

USING_NS_CC;

class Edge:public Node {
    
public:
    virtual bool init();
    CREATE_FUNC(Edge);
};

#endif /* Edge_hpp */
