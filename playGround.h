#pragma once
#include "gameNode.h"
#include "gameScene.h"


class playGround : public gameNode
{
private:
	
	

public:
	 HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


	playGround();
	~playGround();
};

