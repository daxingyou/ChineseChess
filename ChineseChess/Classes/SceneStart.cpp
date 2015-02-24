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

    //ע�ᴥ���¼�
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

    //��ô������λ��(����)
    Point ptClick = pTouch->getLocation();

    //�����ж��Ƿ����������
    bool bClickStone = false;

    //�����к�ɫ�����ӵ�ʱ��(�������λ���ں�ɫ���������ڵķ�Χ��)
    if(_red->boundingBox().containsPoint(ptClick))
    {
        //�����˺�ɫ������
        this->_selected = true;

        //����������
        bClickStone = true;
    }
    //�����к�ɫ���ӵ�ʱ��(�������λ���ں�ɫ�������ڵķ�Χ��)
    else if(_black->boundingBox().containsPoint(ptClick))
    {
        //û���к�ɫ����
        this->_selected = false;

        //����������
        bClickStone = true;
    }

    //�����������ӵ�ʱ��
    if(bClickStone)
    {
        //�ƶ�����
        MoveTo* moveTo1 = MoveTo::create(1, ccp(winSize.width / 2, winSize.height / 2));
        MoveTo* moveTo2 = MoveTo::create(1, ccp(winSize.width / 2, winSize.height / 2));
    
        //��ת����
        RotateBy* rotate1 =  RotateBy::create(1, 360);
        RotateBy* rotate2 =  RotateBy::create(1, -360);

        //��ת���ƶ�ͬʱִ��
        Spawn* spawn1 = Spawn::create(moveTo1, rotate1, NULL);
        Spawn* spawn2 = Spawn::create(moveTo2, rotate2, NULL);

        //ִ���ж���
        _red->runAction(spawn1);
        _black->runAction(spawn2);

        //������ʱ��
         scheduleUpdate();

    }
}


void SceneStart::update(float)
{
    //��ȡ�������ӵ�x����
    float x1 = _red->getPositionX();
    float x2 = _black->getPositionX();

    //����ɫ�����Ӻͺ�ɫ��������ײ��
    //�������ӵľ���С�ڻ�������ӵ�ֱ��
    //getContentSize().width������ӵĿ��(���ӵ�ֱ��)
    if(abs(x1 - x2) <= _red->getContentSize().width)
    {      
        //������Ϸ
        Director::sharedDirector()->replaceScene(SceneGame::scene(this->_selected));
    }
}