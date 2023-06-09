#include "Level1Scene.h"
#include "SimpleAudioEngine.h"
#include "Level2Scene.h"

USING_NS_CC;
using namespace cocos2d;


Scene* Level1::createScene()
{
    return Level1::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in Level1Scene.cpp\n");
}

/////UPDATE
void Level1::update(float t)  {
    CCLOG("%d", count); //printing the id of the tile where the ball is located
    //Recreate the map in the update function
    auto _tileMap = TMXTiledMap::create("TileGameResources/MAPLEVEL1.tmx");
    //CHANGE TILE COLOR
        //Loop throw the trajec
      for (auto s : _traj_tiles)
       {
          //Taking the ball's and the path's coordinates and changing from Cocos Coordinates==>TiledMap Coordinates
          int a = tileCoordForPosition(Vec2(s->getPosition()), _tileMap).y -1 ;
          int b = tileCoordForPosition(Vec2(s->getPosition()), _tileMap).x ;
          int b1 = tileCoordForPosition(Vec2(_ball->getPosition()), _tileMap).y ;
          int b2 = tileCoordForPosition(Vec2(_ball->getPosition()), _tileMap).x ;
           //Condition ==> ball position == one of the path's tile position
          if (Vec2(b2,b1) == Vec2(b,a)) {
              //call the change_color function
              change_color(s);           
         }
         }
   //THE BALL IS MOVING
    if (moving == true) {
 
     //15 with small map(32x32 tiles) small ball(32x32)
     //27 with big map(64x64) big ball(64x64)
     // 8 for the speed of the ball
        //LEFT
        if (direction == 1) {
            //This function respoansable for seeting the ball position and stoping the movement if there is a collision
            setPlayerPosition(Vec2(_ball->getPositionX() -8, _ball->getPositionY()), _tileMap,-27,0);
        }
        //RIGHT
        if (direction == 2) {
            setPlayerPosition(Vec2(_ball->getPositionX() + 8, _ball->getPositionY()), _tileMap,27,0);
        }
        //UP
        else if (direction == 3) {
            setPlayerPosition(Vec2(_ball->getPositionX() , _ball->getPositionY()+8), _tileMap,0,27);
        }
        //DOWN
        else if (direction == 4) {
            setPlayerPosition(Vec2(_ball->getPositionX(), _ball->getPositionY() - 8), _tileMap,0,-27);
        }
    }
    //NEXT LEVEL
    if (count == 22) { //We count the colored tile; if all of them are colored go to the next scene
        auto lv = Level2::createScene();
        count = 0;
        Director::getInstance()->replaceScene(TransitionFade::create(0.5, lv));
    }
}

//////INIT
// on "init" you need to initialize your instance
bool Level1::init()
{
    if (!Scene::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    ////////////////////////// LABEL
    auto Level = Label::createWithTTF("LEV 1", "fonts/BebasNeue-Regular.ttf", 65);
    Level->enableShadow();
    Level->setTextColor(Color4B::WHITE);
    /// position the label on the center of the screen
    Level->setPosition(Vec2(37,origin.y + visibleSize.height-25));
    Level->setScale(0.7);

    //// add the label as a child to this layer 
    this->addChild(Level, 1);

//Create the map
    auto _tileMap = TMXTiledMap::create("TileGameResources/MAPLEVEL1.tmx");
//Inseret the layers
    auto bg = _tileMap->getLayer("Background");
    auto traj = _tileMap->getLayer("traj");
    auto _block = _tileMap->getLayer("blockage01");
//Hiding this layer because it responsable of the collision
    _block->setVisible(false);
//Adding the map
    this->addChild(_tileMap);

//ADDING OBJECT
    TMXObjectGroup* objects = _tileMap->getObjectGroup("Objects");
    auto obj = objects->getObject("Ball");
//Getting the object position from the source file
    int x = obj["x"].asInt();
    int y = obj["y"].asInt();
//The player Sprite
    _ball = Sprite::create("ballretro.png");
//The anchorPoint is in the middle of the picture So it detects collision early
    _ball->setAnchorPoint(Vec2(0.5, 0.5));
//Object's position from the map
    _ball->setPosition(x,y);
//Addint the object to our project 
    this->addChild(_ball);
//PATH'S TILES    
    //loop throw the map
    for (int y = 0; y < _tileMap->getMapSize().height; y++)
    {
        for (int x = 0; x < _tileMap->getMapSize().width; x++)
        {
            auto id1 = traj->getTileGIDAt(Vec2(x, y));
            auto id2 = traj->getTileGIDAt(Vec2(1, 2));
        //Geeting the GID of one of the path's tiles that we know and comparet with the rest
            if (id1 == id2) {
                //Create a tile Sprite if it's in the path
                Sprite* c1 = traj->getTileAt(Vec2(x, y));
                //Adding to our Vector so we can use it the update function
                _traj_tiles.pushBack(c1);
            }
        }
    } 
 
//MOUVEMENT   
     auto eventListener = EventListenerKeyboard::create();
        //Keyboard Event
     eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
         //When the ball not moving we can change direction
         if (moving == false) {
             switch (keyCode) {
             case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
                 direction = 1;
                 //changing the mouvement to true so we triggered the condition in the update function
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
     
     //calling the update function
    this->scheduleUpdate();
    //calling the mouvement event with the sprite we created
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, _ball);
    return true;
}
//Change Color Function
void Level1::change_color(Sprite* s) {
    //if we already colored the tile we return and get out from the function
    if (s->getColor() == Color3B(137, 207, 239)) return;
    //if not we color the tile and we add +1 to our counter
    s->setColor(Color3B(137, 207, 239));
    Level1::count++;
}
//COCOS Coord. ==> TiledMap Coord Function (taking from the cocos forum in 2013 still got some bugs)
Vec2 Level1::tileCoordForPosition(Point& position, TMXTiledMap* map)
{
    int x = position.x / map->getTileSize().width; // tile x coord
    int y = ((map->getMapSize().height * map->getTileSize().height) - position.y) / map->getTileSize().height; // tile y coord
    return cocos2d::Vec2(x, y);
}

//Moving Function
void Level1::setPlayerPosition(Point position, TMXTiledMap* map, int directionx, int directiony)
{
    //Taking the position where the player is moving and changing it to tiledmap coord.
    // we add the directionx-directiony argument so we check a little bit forward from the ball's position (to detect a little bit the collision before the ball reaches it) 
    int tileCoordx = this->tileCoordForPosition(Vec2(position.x+directionx,position.y), map).x ;
    int tileCoordy = this->tileCoordForPosition(Vec2(position.x + directionx, position.y+directiony), map).y;
    cocos2d::Vec2 tileCoord = Vec2(tileCoordx, tileCoordy);
    //Getting the GID  of the tile in the Collision Layer
    int tileGid = map->getLayer("blockage01")->getTileGIDAt(tileCoord);
    //Ball Positon
    cocos2d::Vec2 playerPos = _ball->getPosition();
    //If there is a GID
    if (tileGid) {
        //Take the tile's properties
        cocos2d::ValueMap properties = map->getPropertiesForGID(tileGid).asValueMap();
        //If we found a propertie
        if (properties.size() > 0) {
            //Take the "Blockage" Propertie
            cocos2d::String collisionType = properties.at("Blockage").asString();
            if (collisionType.boolValue()) {
                //If it is True
                if (collisionType.compare("True") == 0) {
                    //Stop the movement
                    moving = false;
                    return; // Don't do anything else
                }

            }
        }
    }
    //Safe check so the ball doesn't get out from the map
    if (position.x <= (map->getMapSize().width * map->getTileSize().width) &&
        position.y <= (map->getMapSize().height * map->getTileSize().height) &&
        position.y >= 0 &&
        position.x >= 0)
    {
        //Move the ball
        _ball->setPosition(position);
    }
}