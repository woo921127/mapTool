#include "stdafx.h"
#include "gameScene.h"


gameScene::gameScene()
{
}


gameScene::~gameScene()
{
}

HRESULT gameScene::init()
{
	_map = new PacMap;
	_map->init();

	_player = new player;
	_player->init();
	_player->setTankMapMemoryAddressLink(_map);

	return S_OK;
}

void gameScene::release()
{
}

void gameScene::update()
{	
	//_map->update();
	_player->update();
	
}

void gameScene::render()
{
	
	_map->render();
	_player->render();
}
