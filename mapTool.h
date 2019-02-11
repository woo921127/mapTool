#pragma once
#include "gameNode.h"
#include "camera.h"


#define tileX 40
#define tileY 40
#define TileMainSIZE 32

#define TileSIZE 32

#define basicTileX 30
#define basicTileY 16


#define ATTR_UNMOVE 0x00000001		//�������� Ÿ�ϼӼ�
#define ATTR_SWAMP  0x00000002		//�̵��ӵ��� �������� Ÿ�ϼӼ�
#define ATTR_POISON 0x00000004		//HP�� ���� ���̴� Ÿ�ϼӼ�
#define ATTR_FROZEN 0x00000008		//�̲������� Ÿ�ϼӼ�

//����
enum TERRAIN
{
	TR_TILE_ONE, TR_TILE_TWO, TR_TILE_THREE, TR_TILE_FOUR, TR_TILE_FIVE, TR_END,
};

enum OBJECT
{
	
	OBJ_WALL, OBJ_ENEMY1, OBJ_ENEMY2, OBJ_ENEMY3,
	OBJ_PLAYER1, OBJ_PLAYER2,
	OBJ_NONE,
};

enum CTRL
{
	CTRL_SAVE,				//���̺� ��ư
	CTRL_LOAD,				//�ε�  ��ư
	CTRL_SAVE2,
	CTRL_LOAD2,
	CTRL_TERRAINDRAW,		//���� ��ư
	CTRL_OBJDRAW,			//������Ʈ ��ư
	CTRL_ERASER,			//���찳 ��ư
	CTRL_END
};

struct tagTile
{
	RECT rc;
	int FrameX;
	int FrameY;
	TERRAIN terrain; //����
	OBJECT obj; //������Ʈ
	int objFrameX; //������Ʈ ��ȣ
	int objFrameY;
};


//Ÿ�� ����
struct TileSetting
{
	RECT tilerc;
	int tilex;
	int tiley;
};

// Ŭ���� Ÿ�� ���
struct tilebox
{
	int x;
	int y;
};

struct tagPlayer
{
	float x;
	float y;
	RECT rc;

};


class mapTool : public gameNode
{
private:
	TileSetting _tilesteeing[basicTileX * basicTileY];
	tilebox _tileBox;
	tagTile _tiles[tileX * tileY];
	DWORD _attribute[tileX * tileY];


	image* _image;

	camera* _camera;

	float ui2x;
	float ui2y;
	
	tagPlayer _player;
	int _pos[2];
	POINT ptmouse2;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setup();

	virtual void setMap();
	virtual void save();
	virtual void load();

	tagTile* getTile() { return _tiles; }
	DWORD* getattribute() { return _attribute; }


	void getMapLoad() { return load(); }

	//� ������ �����ߴ°�?
	TERRAIN terrainSelect(int frameX, int frameY);
	//� ������Ʈ�� �����ߴ°�?

	OBJECT objSelect(int frameX, int frameY);


	mapTool();
	~mapTool();


};

