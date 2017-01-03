#ifndef BattleScene_hpp
#define BattleScene_hpp

#include <stdio.h>
#include <cocos2d.h>
#include <SimpleAudioEngine.h>              //音乐引擎
#include "CardSprite.hpp"
#include "BeanSoliderSprite.hpp"
#include "SunflowerSprite.hpp"


USING_NS_CC;
using namespace CocosDenshion;              //音乐引擎的命名空间

class BattleScene:public Layer {
    
private:
    Size visibleSize;                       //屏幕大小
    double normalWidth;                     //单位方格的宽
    double normalHeight;                    //单位方格的高
    int sunValue;                           //阳光值
    Label *sunLabel;                        //阳光文本栏
    int timeValue;                          //时间值
    Label *countDownLabel;                  //倒计时文本栏
    void countDown(float dt);               //倒计时方法
    CardSprite *sunflowerCard;              //向日葵卡片
    CardSprite *plantCard;                  //豌豆射手卡片
    SunflowerSprite *tempSunflower;         //临时使用的向日葵
    BeanSoliderSprite *tempBeanSolider;     //临时使用的豌豆射手
    virtual void update(float dt);          //更新方法
    SimpleAudioEngine *audioEngine;         //音乐引擎单例

public:
    virtual bool init();                    //初始化方法
    CREATE_FUNC(BattleScene);               //创建实例的方法
    static Scene *createScene();            //创建场景方法
    void generateSunshine(float dt);        //生成阳光的方法
};

#endif /* BattleScene_hpp */
