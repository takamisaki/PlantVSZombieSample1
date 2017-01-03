//本项目主角的父类

#ifndef HeroSprite_hpp
#define HeroSprite_hpp

#include <stdio.h>
#include <cocos2d.h>

USING_NS_CC;

class HeroSprite:public Sprite {
    
private:
    int life;                       //生命值
    
public:
    virtual bool init();
    CREATE_FUNC(HeroSprite);
    virtual void costLife();        //掉血方法
};

#endif /* HeroSprite_hpp */
