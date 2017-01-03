//阳光的类

#ifndef SunSprite_hpp
#define SunSprite_hpp

#include <stdio.h>
#include <cocos2d.h>

USING_NS_CC;

class SunSprite:public Sprite {
    
private:
    void disappear(float dt);                   //消失的方法
    
public:
    virtual bool init();
    CREATE_FUNC(SunSprite);
    std::function<void()> addSunshineHandler;   //点击后它会调用的方法（本项目用来增加阳光值）
    
};

#endif /* SunSprite_hpp */
