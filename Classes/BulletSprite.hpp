//子弹类

#ifndef BulletSprite_hpp
#define BulletSprite_hpp

#include <stdio.h>
#include <cocos2d.h>

USING_NS_CC;


class BulletSprite:public Sprite {
    
private:
    virtual void update(float dt);
    
public:
    virtual bool init();
    CREATE_FUNC(BulletSprite);
};


#endif /* BulletSprite_hpp */
