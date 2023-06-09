#ifndef __INTRO_SCENE_H__
#define __INTRO_SCENE_H__

#include "cocos2d.h"

class IntroScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(IntroScene);

    //initialise the function that's in charge of the transition
private: 
    void GoToMainMenuScene(float dt);
};

#endif // __INTRO_SCENE_H__
