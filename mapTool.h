#pragma once
#include "gameNode.h"
#include "camera.h"


#define tileX 40
#define tileY 40
#define TileMainSIZE 32

#define TileSIZE 32

#define basicTileX 30
#define basicTileY 16


#define ATTR_UNMOVE 0x00000001		//갈수없는 타일속성
#define ATTR_SWAMP  0x00000002		//이동속도가 느려지는 타일속성
#define ATTR_POISON 0x00000004		//HP가 점점 깍이는 타일속성
#define ATTR_FROZEN 0x00000008		//미끄러지는 타일속성

//지형
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
	CTRL_SAVE,				//세이브 버튼
	CTRL_LOAD,				//로드  버튼
	CTRL_SAVE2,
	CTRL_LOAD2,
	CTRL_TERRAINDRAW,		//지형 버튼
	CTRL_OBJDRAW,			//오브젝트 버튼
	CTRL_ERASER,			//지우개 버튼
	CTRL_END
};

struct tagTile
{
	RECT rc;
	int FrameX;
	int FrameY;
	TERRAIN terrain; //지형
	OBJECT obj; //오브젝트
	int objFrameX; //오브젝트 번호
	int objFrameY;
};


//타일 세팅
struct TileSetting
{
	RECT tilerc;
	int tilex;
	int tiley;
};

// 클릭한 타일 담기
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

	//어떤 지형을 선택했는가?
	TERRAIN terrainSelect(int frameX, int frameY);
	//어떤 오브젝트를 선택했는가?

	OBJECT objSelect(int frameX, int frameY);


	mapTool();
	~mapTool();


};

