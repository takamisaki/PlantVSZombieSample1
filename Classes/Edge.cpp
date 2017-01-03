#include "Edge.hpp"

USING_NS_CC;

//初始化
bool Edge::init(){
    
    if (!Node::init()) {
        return false;
    }
    
    //设置边界的尺寸
    Size visibleSize = Director::getInstance() -> getVisibleSize();
    setPhysicsBody(PhysicsBody::createEdgeBox(visibleSize));
    setContentSize(visibleSize);
    
    return true;
}
