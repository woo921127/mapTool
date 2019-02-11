#pragma once
#include "gameNode.h"
#include "mapTool.h"
#include "camera.h"

class PacMap : public gameNode
{

private:
	tagTile _tiles[tileX * tileY];
	DWORD _attribute[tileX * tileY];		

	
	int _pos[2];

	int test[tileX * tileY];



	camera* _camera;
	

public:
	PacMap();
	~PacMap();



	HRESULT init();
	void release();
	void update();
	void render();

	void load();

	tagTile* getTile() { return _tiles; }
	DWORD* getAttribute() { return _attribute; }

	int getPosFirst() { return _pos[0]; }
	int getPosSecond() { return _pos[1]; }

};

