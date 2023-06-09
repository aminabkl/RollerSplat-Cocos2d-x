#include "IntroScene.h"
#include "Definitions.h"
#include "MainMenuScene.h"
USING_NS_CC;

Scene* IntroScene::createScene()
{
    return IntroScene::create();
}
// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in IntroSceneScene.cpp\n");
}
// on "init" you need to initialize your instance
bool IntroScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

     
    // add Ending Scene picture
    auto IntroIMG = Sprite::create("BGPIC.png");

    IntroIMG->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        this->addChild(IntroIMG, 0);
        // set display time
        this->scheduleOnce(schedule_selector(IntroScene::GoToMainMenuScene), DisplayTime);

        return true;
}
// calling te function that's in charge of the transition
void IntroScene::GoToMainMenuScene(float dt) {
    auto scene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TransitionTime, scene));
}