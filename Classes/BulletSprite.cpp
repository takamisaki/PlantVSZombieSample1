#include "BulletSprite.hpp"

USING_NS_CC;

//初始化
bool BulletSprite::init() {
    
    if (!Sprite::init()) {
        return false;
    }
    
    setScale(0.25);
    setTexture("Bullet.png");
    setAnchorPoint(Point::ZERO);
    
    //配置物理属性
    Size contentSize = Size(76,76);
    setContentSize(contentSize);
    setPhysicsBody(PhysicsBody::createBox(contentSize));
    getPhysicsBody() -> setGravityEnable(false);
    getPhysicsBody() -> setCategoryBitmask(1);
    getPhysicsBody() -> setContactTestBitmask(6);
    getPhysicsBody() -> setCollisionBitmask(0);
    
    auto move = MoveBy::create(1.0f, Vec2(400, 0));
    runAction(RepeatForever::create(move));
    
    return true;
}


//检测，如果自己在屏幕外，删除自己
void BulletSprite::update(float dt) {
    
    Vec2 worldPosition = getParent() -> convertToWorldSpace(getPosition());
    
    if (worldPosition.x > Director::getInstance() -> getVisibleSize().width) {
        removeFromParent();
    }
}
