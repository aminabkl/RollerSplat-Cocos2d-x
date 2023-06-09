#ifndef __LEVEL_2_SCENE_H__
#define __LEVEL_2_SCENE_H__
#define TIME 1
#include "cocos2d.h"
using namespace cocos2d;

class Level2 : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
	CREATE_FUNC(Level2);


public:
	

	Vec2 tileCoordForPosition(Vec2& position, TMXTiledMap* map);
	Vec2 positionForTileCoord(Vec2& tileCoord, TMXTiledMap* map);
	void setPlayerPosition(Point position, TMXTiledMap* map, int directionx, int directiony);
	void update(float dt);
	void UpdateWithPriority(float dt);
	void change_color(Sprite* s);
	bool moving = false;

	EventListenerKeyboard* onKeyBoardEvent();
	int direction = 0;

	TMXTiledMap* _tileMap;

	Sprite* _ball;

	TMXLayer* _block;
	TMXLayer* bg;
	TMXLayer* traj;
	int count = 0;
	Vector<Sprite*> _spritevector;
	
};
#endif // __LEVEL_2_SCENE_H__