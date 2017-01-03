#include "CardSprite.hpp"

USING_NS_CC;


//初始化
bool CardSprite::init() {
    
    if (!Sprite::init()) {
        return false;
    }
    
    canTouch = false;
    
    //设置点击监测器，执行外界给它配置的方法
    auto touchListener = EventListenerTouchOneByOne::create();
    
    touchListener -> onTouchBegan = [ this ] (Touch *t, Event *e) {
        
        //如果不能接收点击，不执行方法
        if (!canTouch) {
            return false;
        }
        
        //区分点击的范围
        if (getBoundingBox().containsPoint(t -> getLocation())) {
            
            if (touchHandler) {
                touchHandler(t);
                return true;
            }
            return false;
        }
        
        return false;
    };
    
    //设置拖动调用的方法
    touchListener -> onTouchMoved = [ this  ] (Touch *t, Event *e) {
        
        if (dragHandler) {
            dragHandler(t);
        }
    };
    
    //设置松开调用的方法
    touchListener -> onTouchEnded = [ this ] (Touch *t, Event *e) {
        
        if (dropHandler) {
            dropHandler(t);
        }
    };
    
    //注册监测器
    Director::getInstance() -> getEventDispatcher()
                            -> addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}
