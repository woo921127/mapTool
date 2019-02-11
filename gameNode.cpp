#include "stdafx.h"
#include "gameNode.h"


gameNode::gameNode()
{
}


gameNode::~gameNode()
{
}

HRESULT gameNode::init()
{
	_hdc = GetDC(_hWnd);
	_managerInit = false;

	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (_managerInit)
	{
		SetTimer(_hWnd, 1, 10, NULL);
		KEYMANAGER->init();
		IMAGEMANAGER->init();
		TXTDATA->init();
		TIMEMANAGER->init();
		EFFECTMANAGER->init();
		SOUNDMANAGER->init();
		SCENEMANAGER->init();
		KEYANIMANAGER->init();
		INIDATA->init();
		
	}

	return S_OK;
}

void gameNode::release()
{
	if (_managerInit)
	{
		KillTimer(_hWnd, 1);

		KEYMANAGER->release();
		KEYMANAGER->releaseSingleton();

		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
		TXTDATA->releaseSingleton();

		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();

		EFFECTMANAGER->release();
		EFFECTMANAGER->releaseSingleton();

		INIDATA->release();
		INIDATA->releaseSingleton();

		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();

		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();

		KEYANIMANAGER->release();
		KEYANIMANAGER->releaseSingleton();
	}

	ReleaseDC(_hWnd, _hdc);
}

void gameNode::update()
{
	InvalidateRect(_hWnd, NULL, false);
	SOUNDMANAGER->update();
}

void gameNode::render()
{
}

void gameNode::save()
{
}

void gameNode::load()
{
}

void gameNode::save2()
{
}

void gameNode::load2()
{
}

LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;		//조사 한 번 해바밤바1
	HDC			hdc;	//조사 한 번 해바밤바2

	switch (iMessage)
	{
		case WM_CREATE:

		break;
		case WM_PAINT:
		{
			this->render();
		}
		break;
		case WM_TIMER:
			this->update();
		break;

		case WM_MOUSEMOVE:
			_ptMouse.x = static_cast<float>(LOWORD(lParam));
			_ptMouse.y = static_cast<float>(HIWORD(lParam));

			
		break;

		case WM_LBUTTONDOWN:
			_leftButtonDown = true;
	
		break;

		case WM_LBUTTONUP:
			_leftButtonDown = false;
		break;

		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
				default:
					this->setCtrlSelect(LOWORD(wParam));
				break;
			}
		break;
		
		case WM_DESTROY:
			PostQuitMessage(0);
		return 0;
	}


	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
