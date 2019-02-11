#include "stdafx.h"
#include "mapTool.h"


mapTool::mapTool()
{
}


mapTool::~mapTool()
{
}

HRESULT mapTool::init()
{
	
	_image = IMAGEMANAGER->findImage("mapTiles");

	_camera = new camera;
	_camera->init();

	for (int i = 0; i < basicTileY; ++i)
	{
		for (int j = 0; j < basicTileX; ++j)
		{
			_tilesteeing[i * basicTileX + j].tilex = j;
			_tilesteeing[i * basicTileX + j].tiley = i;


			SetRect(&_tilesteeing[i * basicTileX + j].tilerc,
				(WINSIZEX - IMAGEMANAGER->findImage("mapTiles")->GetWidth()) + j * TileSIZE,
				i * TileSIZE,
				(WINSIZEX - IMAGEMANAGER->findImage("mapTiles")->GetWidth()) + j * TileSIZE + TileSIZE,
				i * TileSIZE + TileSIZE);
		}
	}

	for (int i = 0; i < tileY; ++i)
	{
		for (int j = 0; j < tileX; ++j)
		{
			SetRect(&_tiles[i * tileX + j].rc, j * TileMainSIZE, i * TileMainSIZE, j * TileMainSIZE + TileMainSIZE, i * TileMainSIZE + TileMainSIZE);
		}
	}

	_player.x = 0;
	_player.y = 0;
	_player.rc = RectMake(_player.x, _player.y, 10, 10);

	setup();

	ptmouse2.x = 0;
	ptmouse2.y = 0;

	

	return S_OK;
}

void mapTool::release()
{
}

void mapTool::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_player.x += 5;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (_player.x > 0)
		{
			_player.x -= 5;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{

		if (_player.y > 0)
		{
			_player.y -= 5;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_player.y += 5;
	}


	ptmouse2.x = _ptMouse.x + _camera->getCameraX();
	ptmouse2.y = _ptMouse.y + _camera->getCameraY();


	_camera->update(false,_player.x, _player.y);


	_player.rc = RectMake(_player.x - _camera->getCameraX(), _player.y - _camera->getCameraY(), 10, 10);

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		load();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		save();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		_ctrSelect = CTRL_OBJDRAW;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F4))
	{
		_ctrSelect = CTRL_ERASER;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F5))
	{
		_ctrSelect = CTRL_TERRAINDRAW;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		setMap();
	}
}

void mapTool::render()
{
	
	//IMAGEMANAGER->render("mapTiles", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("mapTiles")->GetWidth(), 0);
	IMAGEMANAGER->render("background", getMemDC(), 0, 0, 0, 0, 800, WINSIZEY);
	

	for (int i = 0; i < tileX * tileY; ++i)
	{
		if (_tiles[i].rc.left - _camera->getCameraX() + 32 < 0) continue;
		if (_tiles[i].rc.left - _camera->getCameraX() > 800) continue;
		if (_tiles[i].rc.top - _camera->getCameraY() + 32 < 0) continue;
		if (_tiles[i].rc.top - _camera->getCameraY() > 600) continue;
		
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
		if (_tiles[i].rc.left - _camera->getCameraX() + 32 < 0) continue;
		if (_tiles[i].rc.left - _camera->getCameraX() > 800) continue;
		if (_tiles[i].rc.top - _camera->getCameraY() + 32 < 0) continue;
		if (_tiles[i].rc.top - _camera->getCameraY() > 600) continue;

		IMAGEMANAGER->frameRender("mapTiles", IMAGEMANAGER->findImage("background")->getMemDC(),
			_tiles[i].rc.left - _camera->getCameraX(), _tiles[i].rc.top - _camera->getCameraY(),
			_tiles[i].objFrameX, _tiles[i].objFrameY);
	}
	char str[128];

	sprintf_s(str, "툴박스x : %f  툴박스y : %f", _camera->getCameraX(), _camera->getCameraY());
	TextOut(getMemDC(), WINSIZEX / 2 - 150, 50, str, strlen(str));

	sprintf_s(str, "툴박스x : %f  툴박스y : %f", _player.x, _player.y);
	TextOut(getMemDC(), WINSIZEX / 2 - 150, 70, str, strlen(str));


	sprintf_s(str, "로드 : F1 , 저장 : F2 , 오브젝트 : F3 , 지우개 : F4 ,  지형 : F5");
	TextOut(getMemDC(), 600,270, str, strlen(str));

	Rectangle(IMAGEMANAGER->findImage("background")->getMemDC(), _player.rc);

}

void mapTool::setup()
{
	_ctrSelect = CTRL_TERRAINDRAW;

	for (int i = 0; i < tileX * tileY; ++i)
	{
		_tiles[i].FrameX = 2;
		_tiles[i].FrameY = 4;
		_tiles[i].objFrameX = 0;
		_tiles[i].objFrameY = 0;
		_tiles[i].terrain = terrainSelect(_tiles[i].objFrameX, _tiles[i].objFrameY);
		_tiles[i].obj = OBJ_NONE;
	}

}

void mapTool::setMap()
{
	for (int i = 0; i < basicTileX * basicTileY; ++i)
	{
		if (PtInRect(&_tilesteeing[i].tilerc, _ptMouse))
		{
			_tileBox.x = _tilesteeing[i].tilex;
			_tileBox.y = _tilesteeing[i].tiley;
		}
	}


	for (int i = 0; i < tileX * tileY; ++i)
	{
		{   if (_ptMouse.x <= 800)
		{
			if (PtInRect(&_tiles[i].rc, ptmouse2))
			{
				if (_ctrSelect == CTRL_TERRAINDRAW)
				{
					_tiles[i].FrameX = _tileBox.x;
					_tiles[i].FrameY = _tileBox.y;

					_tiles[i].terrain = terrainSelect(_tileBox.x, _tileBox.y);
				}
				else if (_ctrSelect == CTRL_OBJDRAW)
				{
					_tiles[i].objFrameX = _tileBox.x;
					_tiles[i].objFrameY = _tileBox.y;

					_tiles[i].obj = objSelect(_tileBox.x, _tileBox.y);
				}
				else  if (_ctrSelect == CTRL_ERASER)
				{
					_tiles[i].objFrameX = NULL;
					_tiles[i].objFrameX = NULL;
					_tiles[i].obj = OBJ_NONE;
				}
				InvalidateRect(_hWnd, NULL, false);
				break;
			}
		}
		}
	}
}

void mapTool::save()
{
	HANDLE file;
	DWORD save;

	file = CreateFile("mapSave.map", GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _tiles, sizeof(tagTile) * tileX * tileY, &save, NULL);

	CloseHandle(file);
}

void mapTool::load()
{
	HANDLE file;
	DWORD read;

	file = CreateFile("mapSave.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * tileX * tileY, &read, NULL);


	CloseHandle(file);
}

TERRAIN mapTool::terrainSelect(int frameX, int frameY)
{
	
	if (frameX == 0 && frameY == 4)
			
	return TR_TILE_ONE;
	
}

OBJECT mapTool::objSelect(int frameX, int frameY)
{
	
		if (frameX == 1 && frameY ==4) 
		
	return OBJ_WALL;
	
}
