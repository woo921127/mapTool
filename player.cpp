#include "stdafx.h"
#include "player.h"


player::player()
{
}


player::~player()
{
}

HRESULT player::init()
{
	_image  = IMAGEMANAGER->addFrameImage("pac", "pacMan.bmp", 0, 0, 256, 32, 8, 1, true, RGB(255, 0, 255));


	_camera = new camera;
	_camera->init();

	_x = 48;
	_y = 48;

	_pacMove = PACMAN_RIGHT;

	_speed = 100;

	_rc = RectMakeCenter(_x, _y, 32, 32);

	return S_OK;
}

void player::release()
{
}

void player::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_pacMove = PACMAN_RIGHT;
	//	pacMove();
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_pacMove = PACMAN_LEFT;
	//	pacMove();
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_pacMove = PACMAN_TOP;
	//	pacMove();
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_pacMove = PACMAN_DOWN;
		//pacMove();
	}
	
	for (int i = 0; i < tileX * tileY; ++i)
	{
		if (PtInRect(&_map->getTile()[i].rc, _ptMouse))
		{
			tix = _map->getTile()[i].objFrameX;
			tiy = _map->getTile()[i].objFrameY;
			trx = _map->getTile()[i].FrameX;
			try1 = _map->getTile()[i].FrameY;
		}
	}

	pacMove();

	_camera->update(false, _x, _y);
}

void player::render()
{
	_image->frameRender(getMemDC(), _rc.left - _camera->getCameraX() , _rc.top - _camera->getCameraY());
	
	//Rectangle(getMemDC(), _rc.left - _camera->getCameraX(), _rc.top - _camera->getCameraY() , _rc.right - _camera->getCameraX(), _rc.bottom - _camera->getCameraY());

	char str[128];
	sprintf_s(str, "렉트위치 : %f   :%f", _x , _y);
	TextOut(getMemDC(), 300, 70, str, strlen(str));

	//sprintf_s(str, "카메라위치 : %f   :%f", _camera->getCameraX(), _camera->getCameraY());
	//TextOut(getMemDC(), 300, 90, str, strlen(str));

	sprintf_s(str, "오브젝트x :%d   오브젝트y : %d   지형x :%d   지형y : %d ", tix, tiy, trx, try1);
	TextOut(getMemDC(), WINSIZEX / 2, WINSIZEY / 2 + 200, str, strlen(str));

}

void player::pacMove()
{

	RECT rcCollision;
	rcCollision = _rc;

	float elapsedTIme = TIMEMANAGER->getElpasedTime();
	float MoveSpeed = 0.016f * _speed;



	switch (_pacMove)
	{	
	case PACMAN_RIGHT:

		_image->SetFrameX(2);
		
		_x += MoveSpeed;

		rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth() - 4 , _image->getFrameHeight() - 4);

		break;
	case PACMAN_TOP:
		_image->SetFrameX(4);
		
		_y -= MoveSpeed;

		rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth() - 4, _image->getFrameHeight() - 4);

		break;
	case PACMAN_LEFT:

		_image->SetFrameX(0);
		
		_x -= MoveSpeed;

		rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth() - 4, _image->getFrameHeight() - 4);
		break;
	case PACMAN_DOWN:
		_image->SetFrameX(6);

		_y += MoveSpeed;

		rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth() - 4, _image->getFrameHeight() - 4);
		break;
	default:
		break;
	}


	switch (_pacMove)
	{
		RECT temp;
	case PACMAN_RIGHT:
		for (int i = 0; i < tileX * tileY; ++i)
		{
			if (IntersectRect(&temp, &rcCollision, &_map->getTile()[i].rc))
			{
				if (_map->getTile()[i].objFrameX == 1 && _map->getTile()[i].objFrameY == 4)
				{
					_x -= MoveSpeed;
					break;
				}
			}
		}
		break;
	case PACMAN_TOP:
		for (int i = 0; i < tileX * tileY; ++i)
		{
			if (IntersectRect(&temp, &rcCollision, &_map->getTile()[i].rc))
			{
				if (_map->getTile()[i].objFrameX == 1 && _map->getTile()[i].objFrameY == 4)
				{
					_y += MoveSpeed;
					break;
				}
			}
		}
		break;
	case PACMAN_LEFT:
		for (int i = 0; i < tileX * tileY; ++i)
		{
			if (IntersectRect(&temp, &rcCollision, &_map->getTile()[i].rc))
			{
				if (_map->getTile()[i].objFrameX == 1 && _map->getTile()[i].objFrameY == 4)
				{
					_x += MoveSpeed;
					break;
				}
			}
		}
		break;
	case PACMAN_DOWN:
		for (int i = 0; i < tileX * tileY; ++i)
		{
			if (IntersectRect(&temp, &rcCollision, &_map->getTile()[i].rc))
			{
				if (_map->getTile()[i].objFrameX == 1 && _map->getTile()[i].objFrameY == 4)
				{
					_y -= MoveSpeed;
					break;
				}
			}
		}
		break;
	}

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());

	_rc = rcCollision;
}

void player::setpacPosition()
{
}

