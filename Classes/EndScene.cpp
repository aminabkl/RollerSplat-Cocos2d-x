#include "EndScene.h"
#include "Definitions.h"

USING_NS_CC;

Scene* EndScene::createScene()
{
    return EndScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in EndSceneScene.cpp\n");
}

// on "init" you need to initialize your instance
bool EndScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto EndIMG = Sprite::create("upco.png");
    
    EndIMG->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    
    this->addChild(EndIMG, 0);

    return true;
}