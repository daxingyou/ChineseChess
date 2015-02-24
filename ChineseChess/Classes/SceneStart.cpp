#include "SceneStart.h"
#include "SceneGame.h"


Scene* SceneStart::createScene()
{
    Scene* scene = Scene::create();

    SceneStart* layer = SceneStart::create();

    scene->addChild(layer);

    return scene;
}


bool SceneStart::init()
{
    Layer::init();

    Size winSize = Director::sharedDirector()->getWinSize();

    Sprite* bkr = Sprite::create("bkg2.png");
    addChild(bkr);

    Sprite* bkb = Sprite::create("bkg1.png");
    addChild(bkb);

    bkr->setPosition(ccp(winSize.width / 2 - 100, winSize.height / 2));
    bkb->setPosition(ccp(winSize.width / 2 + 100, winSize.height / 2));

    _red = bkr;
    _black = bkb;

    //注册触摸事件
    setTouchEnabled(true);
    setTouchMode(kCCTouchesOneByOne);
   
    return true;
}


bool SceneStart::onTouchBegan(Touch* pTouch, Event* pEvent)
{
    return true;
}


void SceneStart::onTouchEnded(Touch* pTouch, Event* pEvent)
{
     Size winSize = Director::sharedDirector()->getWinSize();

    //获得触摸点的位置(坐标)
    Point ptClick = pTouch->getLocation();

    //用于判断是否点中了棋子
    bool bClickStone = false;

    //当点中红色的棋子的时候(触摸点的位置在红色的棋子所在的范围内)
    if(_red->boundingBox().containsPoint(ptClick))
    {
        //点中了红色的棋子
        this->_selected = true;

        //点中了棋子
        bClickStone = true;
    }
    //当点中黑色棋子的时候(触摸点的位置在黑色棋子所在的范围内)
    else if(_black->boundingBox().containsPoint(ptClick))
    {
        //没点中红色棋子
        this->_selected = false;

        //点中了棋子
        bClickStone = true;
    }

    //当点中了棋子的时候
    if(bClickStone)
    {
        //移动棋子
        MoveTo* moveTo1 = MoveTo::create(1, ccp(winSize.width / 2, winSize.height / 2));
        MoveTo* moveTo2 = MoveTo::create(1, ccp(winSize.width / 2, winSize.height / 2));
    
        //旋转棋子
        RotateBy* rotate1 =  RotateBy::create(1, 360);
        RotateBy* rotate2 =  RotateBy::create(1, -360);

        //旋转和移动同时执行
        Spawn* spawn1 = Spawn::create(moveTo1, rotate1, NULL);
        Spawn* spawn2 = Spawn::create(moveTo2, rotate2, NULL);

        //执行行动作
        _red->runAction(spawn1);
        _black->runAction(spawn2);

        //启动定时器
         scheduleUpdate();

    }
}


void SceneStart::update(float)
{
    //获取两个棋子的x坐标
    float x1 = _red->getPositionX();
    float x2 = _black->getPositionX();

    //当红色的棋子和黑色的棋子碰撞后
    //两个棋子的距离小于或等于棋子的直径
    //getContentSize().width获得棋子的宽度(棋子的直径)
    if(abs(x1 - x2) <= _red->getContentSize().width)
    {      
        //进入游戏
        Director::sharedDirector()->replaceScene(SceneGame::scene(this->_selected));
    }
}