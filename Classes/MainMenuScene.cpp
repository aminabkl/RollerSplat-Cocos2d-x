#include "MainMenuScene.h"
#include "Definitions.h"
#include "Level1Scene.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    return MainMenuScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainMenuSceneScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // add the Main Menu Scene  splash screen
    auto menuIMG = Sprite::create("retro.png");
        // position the sprite on the center of the screen
        menuIMG->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(menuIMG,0);
       
        // play menu "picture"
    auto PlayButton = MenuItemImage::create("PlayButton.png","PlayClick.png", CC_CALLBACK_1(MainMenuScene::GoToLevel1Scene,this));
    //position of the play menu
    PlayButton->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2.2 + origin.y));
    //size of the play menu
    PlayButton->setScale(1.5);
    ///////////////
    //the menu that's in charge of the directing the scene
    auto menu = Menu::create(PlayButton, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);
    
    
    
    return true;
}

// calling te function that's in charge of the transition
void MainMenuScene::GoToLevel1Scene(cocos2d::Ref *Sender) {
    auto scene = Level1::createScene();
    Director::getInstance()->replaceScene(TransitionFadeTR::create(TransitionTime, scene));
}