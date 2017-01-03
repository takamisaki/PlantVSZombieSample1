#include "BattleScene.hpp"
#include "GameOverScene.hpp"
#include "ZombieSprite.hpp"
#include "SunSprite.hpp"
#include "Edge.hpp"
#include "BulletSprite.hpp"
#include "HeroSprite.hpp"

USING_NS_CC;


//战场Scene的初始化方法，内含各种配置
bool BattleScene::init()  {
    if (!Layer::create()) {
        return false;
    }
    
#pragma mark - 背景设置
    
    //设置背景图片
    visibleSize           = Director::getInstance()->getVisibleSize();
    auto backgroundSprite = Sprite::create("BattleBackground.png");
    backgroundSprite -> setPosition(visibleSize/2);
    backgroundSprite -> setScale(0.65);
    addChild(backgroundSprite);

    //获取单个格子的长和宽
    normalWidth  = visibleSize.width /9;
    normalHeight = visibleSize.height/5;

    //设置物理Edge (可以不让场景中的Sprites掉出屏幕)
    auto edge = Edge::create();
    edge -> setPosition(visibleSize/2);
    addChild(edge);
    
    //背景音乐
    audioEngine =  SimpleAudioEngine::getInstance();
    audioEngine -> playBackgroundMusic("mainBGM.mp3");
    audioEngine -> playEffect("warning.mp3");
    
    
#pragma mark - 植物卡片设置
#pragma mark 1. 向日葵卡片设置
    
    //添加卡片
    sunflowerCard =  CardSprite::create();
    sunflowerCard -> setTexture("sunflowerCard_dark.png");
    sunflowerCard -> setAnchorPoint(Point::ZERO);
    sunflowerCard -> setPosition(300, 270);
    sunflowerCard -> setScale(0.5);
    
    /* 配置卡片的事件
        1. 点击时生成一个半透明的Sprite, 不开启物理属性
        2. 拖拽时移动该Sprite的Position
        3. 松开时移除该Sprite, 计算贴合座标，重新生成新的Sprite, 开启物理属性
        4. 最后减少对应的阳光值
     */
    //1. 点击事件
    sunflowerCard -> touchHandler = [&] (Touch *t) {
        
        audioEngine   -> playEffect("clickCard.mp3");
        tempSunflower =  SunflowerSprite::create();
        tempSunflower -> setTexture("Sunflower_halfOpacity.png");
        tempSunflower -> setPosition(t->getLocation());
        addChild(tempSunflower);
    };
    
    //2. 拖拽事件
    sunflowerCard     -> dragHandler = [&] (Touch *t) {
        tempSunflower -> setPosition(t->getLocation());
    };
    
    //3. 松开事件
    sunflowerCard     -> dropHandler = [&] (Touch *t) {
        
        audioEngine   -> playEffect("drop.mp3");
        tempSunflower -> removeFromParent();
        
        SunflowerSprite *finalSunflower = SunflowerSprite::create();
        finalSunflower -> setTexture("Sunflower_solid.png");
        
        //松开时的座标进行方格贴合
        Vec2   finalTouch     = t->getLocation();
        double finalPositionX = round(finalTouch.x / normalWidth ) * normalWidth;
        double finalPositionY = round(finalTouch.y / normalHeight) * normalHeight;
        
        //不能置放在屏幕外和顶层（因为要显示标题栏和卡片），如果置放，取消本次创建并返回对应阳光值
        if (finalPositionX < (visibleSize.width - normalWidth) && finalPositionX >= 0) {
            
            if (finalPositionY < (visibleSize.height - normalHeight) && finalPositionY >= 0) {
                
                //不能重叠置放，如果置放，取消本次创建并返回对应阳光值
                Vector<Node *> childrenNodes = this->getChildren();
                for (auto temp:childrenNodes) {
                    if(temp -> getPosition() == Vec2(finalPositionX, finalPositionY)){
                        return;
                    }
                }
                
                finalSunflower -> setPosition( Vec2(finalPositionX, finalPositionY) );
                finalSunflower -> scheduleHandler = [&] () {
                    this -> generateSunshine(8);
                };
                this -> addChild(finalSunflower);
                finalSunflower -> turnOnPhysics();
                
                //阳光值减去消耗的50并更新文本的显示
                sunValue -= 50;
                char sunValueChar[10] = {0};
                sprintf(sunValueChar, "%d",sunValue);
                
                std::string sunLabelString = "Sunshine ";
                sunLabelString += sunValueChar;
                
                sunLabel->setString(sunLabelString);
            }
        }
    };
    
    addChild(sunflowerCard);
    
    
#pragma mark 2. 豌豆射手卡片设置
    
    //添加卡片
    plantCard =  CardSprite::create();
    plantCard -> setTexture("plantCard_dark.png");
    plantCard -> setAnchorPoint(Point::ZERO);
    plantCard -> setPosition(sunflowerCard->getPositionX() + 50, sunflowerCard->getPositionY());
    plantCard -> setScale(0.5);

    //配置卡片的事件，逻辑同向日葵卡片的事件逻辑
    //1. 点击事件
    plantCard -> touchHandler = [&] (Touch *t) {
        
        audioEngine     -> playEffect("clickCard.mp3");
        tempBeanSolider =  BeanSoliderSprite::create();
        tempBeanSolider -> setTexture("BeanSolider_halfOpacity.png");
        tempBeanSolider -> setPosition(t -> getLocation());
        addChild(tempBeanSolider);
    };
    
    //2. 拖拽事件
    plantCard -> dragHandler = [&] (Touch *t) {
        tempBeanSolider -> setPosition(t -> getLocation());
    };
    
    //3. 松开事件
    plantCard -> dropHandler = [&] (Touch *t) {
        
        audioEngine      -> playEffect("drop.mp3");
        tempBeanSolider  -> removeFromParent();
        
        BeanSoliderSprite  *finalBeanSolider = BeanSoliderSprite::create();
        finalBeanSolider -> setTexture("BeanSolider_solid.png");
        
        Vec2   finalTouch     = t -> getLocation();
        double finalPositionX = round(finalTouch.x / normalWidth ) * normalWidth;
        double finalPositionY = round(finalTouch.y / normalHeight) * normalHeight;
        
        if (finalPositionX < (visibleSize.width - normalWidth) && finalPositionX >= 0) {
            
            if (finalPositionY < ( visibleSize.height - normalHeight) && finalPositionY >= 0) {
                
                Vector<Node *> childrenNodes = this -> getChildren();
                for (auto temp:childrenNodes) {
                    if(temp -> getPosition() == Vec2(finalPositionX, finalPositionY)){
                        return;
                    }
                }

                finalBeanSolider -> setPosition(Vec2(finalPositionX, finalPositionY));
                this -> addChild(finalBeanSolider);
                finalBeanSolider -> turnOnPhysics();
                
                //定时发射子弹
                finalBeanSolider -> scheduleHandler = [=] () {
                    
                    audioEngine  -> playEffect("shoot.mp3");
                    auto bullet  = BulletSprite::create();
                    bullet -> setAnchorPoint(Point::ZERO);
                    bullet -> setPosition(Vec2(finalPositionX + 30, finalPositionY + 20));
                    addChild(bullet);
                };

                //阳光值减去消耗的100
                sunValue -= 100;
                char sunValueChar[10] = {0};
                sprintf(sunValueChar, "%d",sunValue);
                
                std::string sunLabelString = "Sunshine ";
                sunLabelString += sunValueChar;
                
                sunLabel -> setString(sunLabelString);
            }
        }
    };

    addChild(plantCard);
    
    
#pragma mark - 僵尸Sprite配置
    
    //定时器，定期生成在右侧随机Y位置的僵尸
    schedule( [this] (float dt) {
        
        double zombieX    = visibleSize.width - 65;
        double zombieY    = (int)(CCRANDOM_0_1() * 4) * normalHeight;
        auto zombieSprite = ZombieSprite::create();
        zombieSprite -> setPosition(zombieX, zombieY);
        this -> addChild(zombieSprite);
        
        auto zombieMove = MoveBy::create(1, Vec2(-8, 0));
        
        auto zomebieOut = CallFunc::create( [this,zombieSprite] () {
            
            if (zombieSprite -> getPositionX() <= 0) {
                audioEngine  -> stopBackgroundMusic();
                Director::getInstance() -> replaceScene(GameOverScene::createScene());
            }
        });
        auto zombieActions = Sequence::create(zombieMove, zomebieOut, NULL);
        zombieSprite -> runAction(RepeatForever::create(zombieActions));
    }, 8, kRepeatForever, 0, "generateZombies");
    
    
#pragma mark - 物理碰撞检测设置
    /*  1. 如果碰撞双方不在同一行，不触发接触和碰撞
        2. 如果碰撞双方在同一行，触发接触和碰撞
        3. 如果是僵尸和子弹接触，删除子弹，僵尸掉血
        4. 如果是僵尸和植物接触，植物掉血
     */
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener -> onContactBegin = [=] (PhysicsContact &contact) {
        
        auto shapeA    = contact.getShapeA();
        auto shapeB    = contact.getShapeB();
        auto categoryA = shapeA -> getCategoryBitmask();
        auto categoryB = shapeB -> getCategoryBitmask();
        auto contactA  = shapeA -> getContactTestBitmask();
        auto contactB  = shapeB -> getContactTestBitmask();
        
        //如果碰撞双方不在同一行，不触发接触和碰撞
        double positionAY = shapeA -> getBody() -> getNode() -> getPositionY();
        double positionBY = shapeB -> getBody() -> getNode() -> getPositionY();
        
        if (fabs(positionAY - positionBY) > 25) {
            return false;
        }
        
        //如果碰撞双方在同一行，触发碰撞和检测
        bool result1 = categoryA & contactB;
        bool result2 = categoryB & contactA;
        
        //如果碰撞生效
        if (result1 && result2)  {
            
            //如果是僵尸和子弹接触，删除子弹，僵尸掉血
            if (contactA == 6 || contactB == 6) {
                //如果shapeA是子弹
                ZombieSprite *zombieSprite = nullptr;
                if (contactA == 6) {
                    shapeA -> getBody() -> getNode() -> removeFromParent();
                    zombieSprite = dynamic_cast<ZombieSprite *> (shapeB -> getBody() -> getNode());
                }
                //如果shapeB是子弹
                else {
                    shapeB -> getBody() -> getNode() -> removeFromParent();
                    zombieSprite = dynamic_cast<ZombieSprite *> (shapeA -> getBody() -> getNode());
                }
                audioEngine -> playEffect("hit.mp3");
                if (zombieSprite) {
                    zombieSprite -> costLife();
                    if (zombieSprite -> getLife() <= 0) {
                        audioEngine  -> playEffect("zombieDie.mp3");
                        zombieSprite -> removeFromParentAndCleanup(true);
                    }
                }
            }
        }
        
        return true;
    };

    contactListener -> onContactPreSolve = [this] (PhysicsContact &contact,
                                                   PhysicsContactPreSolve &solve) {
        auto shapeA    = contact.getShapeA();
        auto shapeB    = contact.getShapeB();
        auto categoryA = shapeA -> getCategoryBitmask();
        auto categoryB = shapeB -> getCategoryBitmask();
        auto contactA  = shapeA -> getContactTestBitmask();
        auto contactB  = shapeB -> getContactTestBitmask();
        
        bool result1   = categoryA & contactB;
        bool result2   = categoryB & contactA;
        
        //如果碰撞生效
        if (result1 && result2)  {
            
            //如果是僵尸和植物碰撞
            if (contactA == 2 || contactB == 2) {
                HeroSprite *tempSprite = nullptr;
                
                //如果shapeA 是植物
                if (contactA  == 2) {
                    tempSprite = dynamic_cast<HeroSprite *> (shapeA -> getBody() -> getNode());
                }
                //如果shapeB是植物
                else {
                    tempSprite = dynamic_cast<HeroSprite *> (shapeB -> getBody() -> getNode());
                }
                
                if (tempSprite) {
                    
                    tempSprite -> scheduleOnce([this,tempSprite,shapeA,shapeB] (float dt) {
                        audioEngine -> playEffect("zombieChew.mp3");
                        tempSprite  -> costLife();
                    }, 1, "plantCostLife");
                }
            }
        }
        return true;
    };
    
    //注册碰撞监听
    Director::getInstance() -> getEventDispatcher()
                            -> addEventListenerWithSceneGraphPriority(contactListener, this);
    
    
#pragma mark - 文字栏设置
#pragma mark 1. 阳光文字栏设置
    
    sunValue = 0;
    char sunValueChar[10] = {0};
    sprintf(sunValueChar, "%d",sunValue);
    
    std::string sunLabelString = "Sunshine ";
    sunLabelString += sunValueChar;
    
    sunLabel =  Label::createWithTTF(sunLabelString, "fonts/Marker Felt.ttf", 20);
    sunLabel -> setAnchorPoint( Point::ZERO );
    sunLabel -> setPosition( Vec2(10, 290) );
    addChild(sunLabel);
    
#pragma mark 2. 倒计时文字栏设置
    
    timeValue = 120;
    std::string countDownLabelString = StringUtils::format("Time %d",timeValue);
    countDownLabel =  Label::createWithTTF(countDownLabelString, "fonts/Marker Felt.ttf", 20);
    countDownLabel -> setAnchorPoint( Point::ZERO );
    countDownLabel -> setPosition( Vec2(150, 290) );
    addChild(countDownLabel);
    schedule(schedule_selector(BattleScene::countDown), 1, kRepeatForever, 0);
    
    
#pragma mark - 其他设置
#pragma mark 1. 定时生成阳光
    
    this -> schedule(schedule_selector(BattleScene::generateSunshine), 3, kRepeatForever, 0);

#pragma mark 2. 激活update
    scheduleUpdate();
    
    return true;
}


#pragma mark - 用到的方法

#pragma mark ⭕️ update

//检测如果阳光值满足卡片条件，就让卡片高亮（通过替换纹理实现）
void BattleScene::update(float dt) {
    
    if (sunValue >= 50) {
        
        sunflowerCard -> canTouch = true;
        sunflowerCard -> setTexture("sunflowerCard_light.png");
        
        if (sunValue  >= 100) {
            plantCard -> canTouch = true;
            plantCard -> setTexture("plantCard_light.png");
        }else{
            plantCard -> canTouch = false;
            plantCard -> setTexture("plantCard_dark.png");
        }
    
    }else {
        sunflowerCard -> canTouch = false;
        sunflowerCard -> setTexture("sunflowerCard_dark.png");
        plantCard     -> canTouch = false;
        plantCard     -> setTexture("plantCard_dark.png");
    }
}


#pragma mark ⭕️ 倒计时

//倒计时结束后切换到gameover scene.
void BattleScene::countDown(float dt) {
    
    if (timeValue >  0) {
        timeValue -- ;
        std::string countDownLabelString = StringUtils::format("Time %d",timeValue);
        countDownLabel -> setString(countDownLabelString);
    
    }else {
        audioEngine -> stopBackgroundMusic();
        Director::getInstance() -> replaceScene(GameOverScene::createScene());
    }
}


#pragma mark ⭕️ 生成阳光

//随机位置出现阳光，点击后增加阳光值，如果8秒内没有点击它，它会自动消失
void BattleScene::generateSunshine(float dt) {
    
    float x = CCRANDOM_0_1() * (visibleSize.width - 100);
    float y = CCRANDOM_0_1() * (visibleSize.height - 100);
    
    SunSprite *sunshine = SunSprite::create();
    sunshine -> setPosition(Vec2(x, y));
    
    //配置阳光Sprite的点击事件：点击时，加值到阳光文本栏
    sunshine -> addSunshineHandler = [&] () {
        
        audioEngine -> playEffect("pickUp.mp3");
        sunValue += 25;
        char sunValueChar[10] = {0};
        sprintf(sunValueChar, "%d",sunValue);
        
        std::string sunLabelString = "Sunshine ";
        sunLabelString += sunValueChar;
        
        sunLabel -> setString(sunLabelString);
    };
    
    addChild(sunshine);
}


#pragma mark ⭕️ 创建BattleScene场景

//用于AppDelegate的调用
Scene * BattleScene::createScene() {
    
    auto scene = Scene::createWithPhysics();
    
    //是否显示物理框
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    auto layer = BattleScene::create();
    scene -> addChild(layer);
    
    return scene;
}

    
