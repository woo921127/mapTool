#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}


HRESULT playGround::init()
{
	gameNode::init(true);

	//IMAGEMANAGER->addFrameImage("mapTiles", "map.bmp", 0, 0, 128, 160, basicTileX, basicTileY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mapTiles", "terranigma4.bmp", 0, 0, 960, 512, basicTileX, basicTileY, true, RGB(255, 0, 255));
	

	SCENEMANAGER->addScene("¸ÊÅø¾À", new mapTool);
	
	SCENEMANAGER->addScene("player", new gameScene);

	SCENEMANAGER->changeScene("¸ÊÅø¾À");

	


	return S_OK;
}


void playGround::release()
{
	gameNode::release();

}


void playGround::update()
{
	gameNode::update();

	SCENEMANAGER->update();

	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		SCENEMANAGER->changeScene("player");
	}
}



void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	
	SCENEMANAGER->render();
	//===========================================================
	
	this->getBackBuffer()->render(getHDC(), 0, 0);
}
