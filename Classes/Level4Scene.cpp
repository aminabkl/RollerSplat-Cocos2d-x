
// SAME CONCEPT AS THE CODE OF THE FIRST LEVEL

#include "Level4Scene.h"
#include "SimpleAudioEngine.h"
#include "Level5Scene.h"

USING_NS_CC;
using namespace cocos2d;


Scene* Level4::createScene()
{
    return Level4::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in Level4Scene.cpp\n");
}

void Level4::update(float t)  {
    CCLOG("%d", count);
    auto _tileMap = TMXTiledMap::create("TileGameResources/MAPLEVEL4.tmx");
      for (auto s : _traj_tiles)
       {
          int a = tileCoordForPosition(Vec2(s->getPosition()), _tileMap).y -1 ;
          int b = tileCoordForPosition(Vec2(s->getPosition()), _tileMap).x ;
          int b1 = tileCoordForPosition(Vec2(_ball->getPosition()), _tileMap).y ;
          int b2 = tileCoordForPosition(Vec2(_ball->getPosition()), _tileMap).x ;
          if (Vec2(b2,b1) == Vec2(b,a)) {
              change_color(s);           
         }
         }
    if (moving == true) {
 
        if (direction == 1) {
            setPlayerPosition(Vec2(_ball->getPositionX() -8, _ball->getPositionY()), _tileMap,-27,0);
        }
        if (direction == 2) {
            setPlayerPosition(Vec2(_ball->getPositionX() + 8, _ball->getPositionY()), _tileMap,27,0);
        }
        else if (direction == 3) {
            setPlayerPosition(Vec2(_ball->getPositionX() , _ball->getPositionY()+8), _tileMap,0,27);
        }
        else if (direction == 4) {
            setPlayerPosition(Vec2(_ball->getPositionX(), _ball->getPositionY() - 8), _tileMap,0,-27);
        }
    }
    if (count == 33) { 
        auto lv = Level5::createScene();
        count = 0;
        Director::getInstance()->replaceScene(TransitionFade::create(0.5, lv));
    }
}

bool Level4::init()
{
    if (!Scene::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto Level = Label::createWithTTF("LEV 4", "fonts/BebasNeue-Regular.ttf", 65);
    Level->enableShadow();
    Level->setTextColor(Color4B::WHITE);
    Level->setPosition(Vec2(37, origin.y + visibleSize.height - 25));
    Level->setScale(0.7);
    this->addChild(Level, 1);

    auto _tileMap = TMXTiledMap::create("TileGameResources/MAPLEVEL4.tmx");
    auto bg = _tileMap->getLayer("Background");
    auto traj = _tileMap->getLayer("traj");
    auto _block = _tileMap->getLayer("blockage01");
    _block->setVisible(false);
    this->addChild(_tileMap);

    TMXObjectGroup* objects = _tileMap->getObjectGroup("Objects");
    auto obj = objects->getObject("Ball");
    int x = obj["x"].asInt();
    int y = obj["y"].asInt();
    _ball = Sprite::create("ballretro.png");
    _ball->setAnchorPoint(Vec2(0.5, 0.5));
    _ball->setPosition(x,y);
    this->addChild(_ball);

    for (int y = 0; y < _tileMap->getMapSize().height; y++)
    {
        for (int x = 0; x < _tileMap->getMapSize().width; x++)
        {
            auto id1 = traj->getTileGIDAt(Vec2(x, y));
            auto id2 = traj->getTileGIDAt(Vec2(1, 10));
            if (id1 == id2) {
                Sprite* c1 = traj->getTileAt(Vec2(x, y));
                _traj_tiles.pushBack(c1);
            }
        }
    } 
     auto eventListener = EventListenerKeyboard::create();
     eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
         if (moving == false) {
             switch (keyCode) {
             case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
                 direction = 1;
                 moving = true;
                 break;
             case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
                 direction = 2;
                 moving = true;
                 break;
             case  EventKeyboard::KeyCode::KEY_UP_ARROW:
                 direction = 3;
                 moving = true;
                 break;
             case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
                 direction = 4;
                 moving = true;
                 break;
             }
         }
     };
     
    this->scheduleUpdate();
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, _ball);
    return true;
}
void Level4::change_color(Sprite* s) {
    if (s->getColor() == Color3B(137, 207, 239)) return;
    s->setColor(Color3B(137, 207, 239));
    Level4::count++;
}
Vec2 Level4::tileCoordForPosition(Point& position, TMXTiledMap* map)
{
    int x = position.x / map->getTileSize().width; // tile x coord
    int y = ((map->getMapSize().height * map->getTileSize().height) - position.y) / map->getTileSize().height; // tile y coord
    return cocos2d::Vec2(x, y);
}

void Level4::setPlayerPosition(Point position, TMXTiledMap* map, int directionx, int directiony)
{
    int tileCoordx = this->tileCoordForPosition(Vec2(position.x+directionx,position.y), map).x ;
    int tileCoordy = this->tileCoordForPosition(Vec2(position.x + directionx, position.y+directiony), map).y;
    cocos2d::Vec2 tileCoord = Vec2(tileCoordx, tileCoordy);
    int tileGid = map->getLayer("blockage01")->getTileGIDAt(tileCoord);
    cocos2d::Vec2 playerPos = _ball->getPosition();
    if (tileGid) {
        cocos2d::ValueMap properties = map->getPropertiesForGID(tileGid).asValueMap();
        if (properties.size() > 0) {
            cocos2d::String collisionType = properties.at("Blockage").asString();
            if (collisionType.boolValue()) {
                if (collisionType.compare("True") == 0) {
                    moving = false;
                }

            }
        }
    }
    if (position.x <= (map->getMapSize().width * map->getTileSize().width) &&
        position.y <= (map->getMapSize().height * map->getTileSize().height) &&
        position.y >= 0 &&
        position.x >= 0)
    {
        _ball->setPosition(position);
    }
}