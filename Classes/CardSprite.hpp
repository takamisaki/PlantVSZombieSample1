//卡片的父类

#ifndef CardSprite_hpp
#define CardSprite_hpp

#include <stdio.h>
#include <cocos2d.h>

USING_NS_CC;

class CardSprite:public Sprite {
    
public:
    virtual bool init();
    CREATE_FUNC(CardSprite);
    std::function<void(Touch *t)> touchHandler;     //点击方法
    std::function<void(Touch *t)> dragHandler;      //拖拽方法
    std::function<void(Touch *t)> dropHandler;      //松开方法
    bool canTouch;                                  //能否接收点击的开关

};

#endif /* CardSprite_hpp */
