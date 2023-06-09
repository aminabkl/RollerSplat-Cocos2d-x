#ifndef __LEVEL_5_SCENE_H__
#define __LEVEL_5_SCENE_H__
#define TIME 1
#include "cocos2d.h"
using namespace cocos2d;

class Level5 : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
	CREATE_FUNC(Level5);



	Vec2 tileCoordForPosition(Vec2& position, TMXTiledMap* map);
	void setPlayerPosition(Point position, TMXTiledMap* map, int directionx, int directiony);
	void change_color(Sprite* s);
	void update(float dt);

	EventListenerKeyboard* onKeyBoardEvent();

	TMXTiledMap* _tileMap;
	TMXLayer* _block;
	TMXLayer* bg;
	TMXLayer* traj;
	Sprite* _ball;
	Vector<Sprite*> _traj_tiles;

	int count = 0;
	bool moving = false;
	int direction = 0;
	
};
#endif // __LEVEL_5_SCENE_H__