#ifndef  _SceneStart_H_
#define _SceneStart_H_

#include "cocos2d.h"
USING_NS_CC;

class SceneStart : public Layer
{
public:
    static Scene* createScene();

    bool init();

    CREATE_FUNC(SceneStart);

    bool onTouchBegan(Touch* pTouch, Event* pEvent);
    void onTouchEnded(Touch* pTouch, Event* pEvent);

    Sprite* _red;
    Sprite* _black;

    void update(float);

    //����Ƿ�ѡ���˺�ɫ����
     bool _selected;
};

#endif

