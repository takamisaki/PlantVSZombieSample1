//豌豆射手的类

#ifndef BeanSoliderSprite_hpp
#define BeanSoliderSprite_hpp

#include <stdio.h>
#include <cocos2d.h>
#include "HeroSprite.hpp"

USING_NS_CC;

class BeanSoliderSprite:public HeroSprite {

private:
    int life;                                   //生命值
    virtual void update(float dt);

public:
    virtual bool init();
    CREATE_FUNC(BeanSoliderSprite);
    std::function<void()> scheduleHandler;      //定时器要执行的方法
    virtual void costLife();                    //掉血方法
    void turnOnPhysics();                       //开关物理引擎方法
};



#endif /* BeanSoliderSprite_hpp */
