#pragma once
#include "iGameNode.h"
//
class terrain;
class terrainSc;
class Environment;
class mapObject;
class WaterTerrain;
class rightView;

struct LEFTVIEWUI
{
	LPDIRECT3DTEXTURE9 tex;
	RECT rc1, rc2, rc3;
};

class leftViewHead : public iGameNode
{
private:
	
	rightView*        _rightView;		//라이트뷰클래스
	terrainSc*		  _terrainSc;		//지형클래스
	terrain*		  _terrain;			//지형클래스
	Environment*	  _environment;		//환경맵클래스
	lightDirection*	  _directionLight;	//빛클래스
	mapObject*        _mapObject;		//맵오브젝트
	WaterTerrain*	  _waterTerrain;    //물결 오브젝트
	camera			  _mainCamera;

	lightDirection*			_sceneBaseDirectionLight;	//씬에 배치된 기본라이팅

private:
	D3DXVECTOR3		_hitPos;	    //히트 포지션
	bool			_isCheck;	    //히트 여부
	POINT _ptMousePos;              //뷰적용떄문에 따로 포인트 마우스선언
	Ray ray;                        //피킹광선

private:
	vector<baseObject*>	m_vecObject;//오브젝트 push_back 해줄 변수
	float matScaleNumber;           //크기를 받을 변수
	float mapRotation;

	//맵바탕
	LEFTVIEWUI _leftView;

	//오브젝트에 관한 save
	vector<tagSaveObject> InfoObjectTemp;
	tagSaveObject ObjecTemp;

private:
	int co;
	enum eHeightType { E_NONE, E_UP, E_DOWN };
	eHeightType m_eHeightType;			//높이값을 올릴건지 내릴건지의 정보를 들고있다.

	char* tile1;
	char* tile2;
	char* tile3;
	char* tile4;
	char* splat;
	char* raw;

public:
	leftViewHead();
	~leftViewHead();

	HRESULT init();

	void release();

	void update();
	void PickUdate();
	void terrainUpdate();
	void terrainTextureUpate();
	void monsterMaptul();
	void Load();

	void render();
	void setLink(rightView* rightView) { _rightView = rightView; }
};

