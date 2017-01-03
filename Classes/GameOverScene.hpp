//游戏结束场景

#ifndef GameOverScene_hpp
#define GameOverScene_hpp

#include <stdio.h>
#include <SimpleAudioEngine.h>          //音乐引擎

USING_NS_CC;
using namespace CocosDenshion;          //音乐引擎命名空间

class GameOverScene:public Layer {

private:
    SimpleAudioEngine *audioEngine;     //音乐引擎单例
    
public:
    virtual bool init();                
    CREATE_FUNC(GameOverScene);
    static Scene *createScene();
};

#endif /* GameOverScene_hpp */
