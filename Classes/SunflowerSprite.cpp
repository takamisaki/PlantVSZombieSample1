#include "SunflowerSprite.hpp"

USING_NS_CC;


//初始化方法
bool SunflowerSprite::init(){
    
    if (!Sprite::init()) {
        return false;
    }
    
    setScale(0.2);
    setTexture("Sunflower_solid.png");
    setAnchorPoint(Point::ZERO);

    //定时执行Scene配置的方法（本项目用来执行生成阳光）
    schedule([&](float dt) {
        
        if (scheduleHandler) {
            scheduleHandler();
        }
    }, 8, "generateSun");
    
    life = 180;
    
    return true;
}


//如果生命值降为0，移除自身
void SunflowerSprite::update(float dt) {
    
    if (life <= 0) {
        removeFromParentAndCleanup(true);
    }
}


//掉血方法：中招后先变红，掉血，然后恢复正常色
void SunflowerSprite::costLife() {
    
    setColor(Color3B(255, 0, 0));
    
    scheduleOnce([this](float dt){
        life -= 60;
        this -> setColor(Color3B(255,255,255));
    },0.5, "loseLife");
}


//开关物理引擎方法（用于卡片拖放）
void SunflowerSprite::turnOnPhysics() {
    
    Size contentSize = Size(205,242);
    setContentSize(contentSize);
    setPhysicsBody(PhysicsBody::createBox(contentSize));
    getPhysicsBody() -> setDynamic(false);
    getPhysicsBody() -> setGravityEnable(false);
    getPhysicsBody() -> setCategoryBitmask(1);
    getPhysicsBody() -> setContactTestBitmask(2);
    getPhysicsBody() -> setCollisionBitmask(2);
}
