#include "stdafx.h"
#include "camera.h"


HRESULT camera::init()
{

	_cameraPos.x =0;
	_cameraPos.y = 0;



	return S_OK;
}

void camera::release()
{
}

void camera::update(bool change , float playerX, float playerY)
{
	
	if (change == true)
	{
		_cameraPos.x = playerX;
		_cameraPos.y = playerY;
	}


	else if (change == false)
	{
		//왼쪽 위
		if (playerX < 800/ 2 && playerY < WINSIZEY / 2)
		{
			_cameraPos.x = 0;
			_cameraPos.y = 0;
		}
		//오른 위
		else if (playerX > 1280 - 800 / 2 && playerY < WINSIZEY / 2)
		{
			_cameraPos.x = 1280 - 800;
			_cameraPos.y = 0;
		}
		//왼쪽 아래
		else if (playerX < 800 / 2 && playerY > 1280 - WINSIZEY / 2)
		{
			_cameraPos.x = 0;
			_cameraPos.y = 1280 - WINSIZEY;
		}
		//오른 아래
		else if (playerX > 1280 - 800 / 2 && playerY > 1280 - WINSIZEY / 2)
		{
			_cameraPos.x = 1280 - 800;
			_cameraPos.y = 1280 - WINSIZEY;
		}

		else if (playerX < 800 / 2)
		{
			_cameraPos.x = 0;
			_cameraPos.y = playerY - WINSIZEY / 2;
		}
		//왼쪽
		else if (playerX  > 1280 - 800 / 2)
		{
			_cameraPos.x = 1280 - 800;
			_cameraPos.y = playerY - WINSIZEY / 2;
		}
		//위
		else if (playerY < WINSIZEY / 2)
		{
			_cameraPos.x = playerX - 800 / 2;
			_cameraPos.y = 0;
		}
		//아래
		else if (playerY > 1280 - WINSIZEY / 2)
		{
			_cameraPos.x = playerX - 800 / 2;
			_cameraPos.y = 1280 - WINSIZEY;
		}
		//기본
		else
		{
			_cameraPos.x = playerX - 800 / 2;
			_cameraPos.y = playerY - WINSIZEY / 2;
		}
	}
}


void camera::render()
{

}

camera::camera()
{
}


camera::~camera()
{
}
