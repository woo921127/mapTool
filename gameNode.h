#pragma once
#include "image.h"

//����� ���� ����
static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);

static	image* _backBuffer1 = IMAGEMANAGER->addImage("background", 800, WINSIZEY);


class gameNode
{
private:
	HDC _hdc;
	//�Ŵ����� �̴��Ҳ��� ����
	bool _managerInit;

public:
	gameNode();
	virtual ~gameNode();

	int _ctrSelect;			//��Ʈ�� ��ư �̳ѹ��� �����ϱ� ����

	//���� ���� -> ����� ��忡�� �ʱ�ȭ�� �ߵǾ����� ������ ������ ���� ����
	//S_OK, E_FAIL, SUCCEDED ������ �˷���.
	virtual HRESULT init();
	virtual HRESULT init(bool managerInit);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void save();
	virtual void load();
	virtual void save2();
	virtual void load2();

	void setCtrlSelect(int num) { _ctrSelect = num; }


	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	image* getBackBuffer() { return _backBuffer; }
//	image* getCameraBuffer() { return _backBuffer1; }


	//DC ������
	HDC getMemDC() { return _backBuffer->getMemDC(); }

	

	//HDC getCameraDC() { return _backBuffer1->getMemDC();}

	HDC getHDC() { return _hdc; }

};

