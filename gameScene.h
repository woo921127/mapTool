#pragma once
#include "gameNode.h"
#include "PacMap.h"
#include "player.h"
class gameScene : public gameNode
{

private:
	PacMap* _map;
	player* _player;

public:
	gameScene();
	~gameScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

