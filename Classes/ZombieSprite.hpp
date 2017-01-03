//僵尸的类

#ifndef ZombieSprite_hpp
#define ZombieSprite_hpp

#include <stdio.h>
#include <cocos2d.h>
#include "HeroSprite.hpp"

USING_NS_CC;

class ZombieSprite:public HeroSprite {
    
private:
    int life;                           //生命值
    
public:
    virtual bool init();
    CREATE_FUNC(ZombieSprite);
    virtual void costLife();            //掉血方法
    int getLife();                      //获取僵尸的生命值
};

#endif /* ZombieSprite_hpp */
