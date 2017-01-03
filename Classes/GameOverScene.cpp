#include "GameOverScene.hpp"
#include "BattleScene.hpp"

USING_NS_CC;

bool GameOverScene::init() {
    
    if (!Layer::init()) {
        return false;
    }
    
    audioEngine =  SimpleAudioEngine::getInstance();
    audioEngine -> playEffect("NO.mp3");
    
    Size visibleSize   = Director::getInstance() -> getVisibleSize();
    
    auto gameOverLabel =  Label::createWithTTF("Game Over", "fonts/Marker Felt.ttf", 24);
    gameOverLabel      -> setPosition(visibleSize/2);
    addChild(gameOverLabel);
    
    auto restartLabel =  Label::createWithTTF("Click to Restart", "fonts/Marker Felt.ttf", 20);
    restartLabel      -> setPosition(Vec2(visibleSize.width/2, visibleSize.height/2 - 30));
    addChild(restartLabel);
    
    auto clickListener = EventListenerTouchOneByOne::create();
    clickListener -> onTouchBegan = [  ] (Touch *t, Event *e) {
        
        Director::getInstance() -> replaceScene(BattleScene::createScene());
        return false;
    };
    Director::getInstance() -> getEventDispatcher()
                            -> addEventListenerWithSceneGraphPriority(clickListener, this);
    return true;
}


Scene * GameOverScene::createScene() {
    
    auto scene =  Scene::create();
    auto layer =  GameOverScene::create();
    scene      -> addChild(layer);
    return scene;
}
