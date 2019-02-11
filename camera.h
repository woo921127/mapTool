#pragma once
#include "gameNode.h"

class camera : public gameNode
{

private:

	image* _image;

	POINTFLOAT _cameraPos;

	


public:

	 HRESULT init();
	 void release();
	 void update(bool change, float playerX, float playerY);
	 void render();

	float getCameraX() { return _cameraPos.x; }
	float getCameraY() { return _cameraPos.y; }


	camera();
	~camera();
};

