#include "SunSprite.hpp"

USING_NS_CC;

//初始化
bool SunSprite::init() {
    
    if (!Sprite::init()) {
        return false;
    }
    
    setScale(0.4);
    setTexture("Sun.png");
    setAnchorPoint(Point::ZERO);
    
    //配置点击监测器
    auto clickListener = EventListenerTouchOneByOne::create();
    
    //配置点击执行的方法
    clickListener -> onTouchBegan = [ this ] (Touch *t, Event *e) {
        
        //区分点击的范围
        if (getBoundingBox().containsPoint(t -> getLocation())) {

            if (addSunshineHandler) {
                addSunshineHandler();
            }
            
            //点击后移除自己
            removeFromParent();
        }
        return false;
    };
    
    //注册监测器
    Director::getInstance() -> getEventDispatcher()
                            -> addEventListenerWithSceneGraphPriority(clickListener, this);
    
    //如果8秒内没有点击阳光，阳光消失
    scheduleOnce(schedule_selector(SunSprite::disappear), 8);
    
    return true;
}


//自动移除自己的方法（用于用户超时没有点击）
void SunSprite::disappear(float dt) {
    removeFromParent();
}
