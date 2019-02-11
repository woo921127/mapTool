#pragma once
#include "gameNode.h"
#include "PacMap.h"
#include "camera.h"

enum packManMove
{
	PACMAN_RIGHT,
	PACMAN_TOP,
	PACMAN_LEFT,
	PACMAN_DOWN
};

class player : public gameNode

{
private:

	packManMove _pacMove;
	float _x, _y;
	float _speed;
	RECT _rc;
	image* _image;

	camera* _camera;
	
	
	PacMap* _map;



	float _cameX;
	float _cameY;
	RECT _cameRC;
	int tix;
	int tiy;
	int trx;
	int try1;




public:
	player();
	~player();

	HRESULT init();
	void release();
	void update();
	void render();

	void pacMove();
	void setpacPosition();
	void setTankMapMemoryAddressLink(PacMap* tm) { _map = tm; }


	float getPlayerX() { return _x; }
	float getPlayerY() { return _y; }
};

