//向日葵的类

#ifndef SunflowerSprite_hpp
#define SunflowerSprite_hpp

#include <stdio.h>
#include <cocos2d.h>
#include "HeroSprite.hpp"

USING_NS_CC;

class SunflowerSprite:public HeroSprite {
    
private:
    int life;                               //生命值
    virtual void update(float dt);
    
public:
    virtual bool init();
    CREATE_FUNC(SunflowerSprite);
    std::function<void()> scheduleHandler;  //定时器要执行的方法
    virtual void costLife();                //掉血方法
    void turnOnPhysics();                   //开关物理引擎的方法
};

#endif /* SunflowerSprite_hpp */
