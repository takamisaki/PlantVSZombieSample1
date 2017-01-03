#include "ZombieSprite.hpp"

USING_NS_CC;

//初始化方法：通过plist载入动画
bool ZombieSprite::init() {
    
    if (!Sprite::init()) {
        return false;
    }
    
    life = 600;
    
    //把纹理加入SpriteFrameCache
    auto spriteFrameCache = SpriteFrameCache::getInstance();
    spriteFrameCache -> addSpriteFramesWithFile("ZombieMoveSheet.plist");
    
    setSpriteFrame("ZombieMove01.png");
    setAnchorPoint(Point::ZERO);
    setScale(0.65);
    
    Size contentSize = Size(69,128);
    setContentSize(contentSize);
    setPhysicsBody(PhysicsBody::createBox(contentSize));
    getPhysicsBody() -> setRotationEnable(false);
    getPhysicsBody() -> setGravityEnable(false);
    getPhysicsBody() -> setCategoryBitmask(3);
    getPhysicsBody() -> setContactTestBitmask(1);
    getPhysicsBody() -> setCollisionBitmask(1);
    
    //建立SpriteFrameVector
    Vector<SpriteFrame *> spriteFrameVector;
    spriteFrameVector.reserve(7);
    
    for (int i = 1; i<= 7; i++) {
        
        std::string name    = StringUtils::format("ZombieMove%02d.png",i);
        SpriteFrame *iFrame = spriteFrameCache -> getSpriteFrameByName(name);
        spriteFrameVector.pushBack(iFrame);
    }
    
    Animation *animation = Animation::createWithSpriteFrames(spriteFrameVector, 0.3f);
    animation -> setLoops(-1);
    animation -> setRestoreOriginalFrame(true);
    Animate *animate = Animate::create(animation);
    
    runAction(animate);
    
    return true;
}


//掉血方法：中招后先变红，掉血，然后恢复正常色
void ZombieSprite::costLife() {
    
    setColor(Color3B(255, 0, 0));
    
    scheduleOnce([this] (float dt) {
        life -= 60;
        this -> setColor(Color3B(255,255,255));
    }, 0.5, "loseLife");
}


//返回生命值的方法
int ZombieSprite::getLife() {
    return life;
}


