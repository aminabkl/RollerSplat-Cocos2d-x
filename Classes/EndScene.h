#ifndef __END_SCENE_H__
#define __END_SCENE_H__

#include "cocos2d.h"

class EndScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
        
    // implement the "static create()" method manually
    CREATE_FUNC(EndScene);
};

#endif // __END_SCENE_H__
