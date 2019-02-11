#include "stdafx.h"
#include "PacMap.h"


PacMap::PacMap()
{
}


PacMap::~PacMap()
{
}

HRESULT PacMap::init()
{
	IMAGEMANAGER->addFrameImage("mapTiles", "map.bmp", 0, 0, 128, 160, basicTileX, basicTileY, true, RGB(255, 0, 255));

	load();

	for (int i = 0; i < tileX * tileY; ++i)
	{
		test[i] = _tiles[i].FrameX;
	}

	_camera = new camera;
	_camera->init();
	
	return S_OK;
}

void PacMap::release()
{
}

void PacMap::update()
{
}

void PacMap::render()
{
	IMAGEMANAGER->render("background", getMemDC(), 0, 0, 0, 0, 800, WINSIZEY);
	//IMAGEMANAGER->render("mapTiles", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("mapTiles")->GetWidth(), 0);
	//지형
	
	for (int i = 0; i < tileX * tileY; ++i)
	{

		IMAGEMANAGER->frameRender("mapTiles", IMAGEMANAGER->findImage("background")->getMemDC(),
			_tiles[i].rc.left - _camera->getCameraX(), _tiles[i].rc.top - _camera->getCameraY(),
			_tiles[i].FrameX, _tiles[i].FrameY);
	}



	//
	////오브젝트
	for (int i = 0; i < tileX * tileY; ++i)
	{
		//오브젝트가 아니면 오브젝트를 그리지마라
		if (_tiles[i].obj == OBJ_NONE) continue;

		IMAGEMANAGER->frameRender("mapTiles", IMAGEMANAGER->findImage("background")->getMemDC(),
			_tiles[i].rc.left - _camera->getCameraX(), _tiles[i].rc.top - _camera->getCameraY(),
			_tiles[i].objFrameX, _tiles[i].objFrameY);
	}

	char str[128];
//	for (int i = 0; i < tileX * tileY; ++i)
//	{
	//	sprintf_s(str, "%f   %f ", _camera->getCameraX(), _camera->getCameraY());
	//	TextOut(getMemDC(), 60 , 50, str, strlen(str));
//	}
	
}

void PacMap::load()
{
	HANDLE file;
	DWORD read;

	file = CreateFile("mapSave.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * tileX * tileY, &read, NULL);


	CloseHandle(file);
	//ReadFile(file, _pos, sizeof(int) * 2, &read, NULL);
	//
	//
	//memset(_attribute, 0, sizeof(DWORD)* tileX * tileY);


	//for (int i = 0; i < tileX * tileY; ++i)
	//{
	//	if (_tiles[i].obj == OBJ_ENEMY1) _attribute[i] |= ATTR_UNMOVE;
	//
	//}

}
