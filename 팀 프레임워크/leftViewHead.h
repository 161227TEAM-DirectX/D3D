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
	bool FT;
};

class leftViewHead : public iGameNode
{
private:
	rightView*			_rightView;			//라이트뷰클래스
	terrainSc*			_terrainSc;			//지형클래스
	terrain*			_terrain;			//지형클래스
	Environment*		_environment;		//환경맵클래스
	lightDirection*		_directionLight;	//빛클래스
	mapObject*			_mapObject;			//맵오브젝트
	WaterTerrain*		_waterTerrain;		//물결 오브젝트
	camera*				_mainCamera;		//그래

	vector<baseObject*>	_monster;

	lightDirection*		_sceneBaseDirectionLight;	//씬에 배치된 기본라이팅

private:
	D3DXVECTOR3		_hitPos;	    //히트 포지션
	bool			_isCheck;	    //히트 여부
	POINT _ptMousePos;              //뷰적용떄문에 따로 포인트 마우스선언
	Ray ray;                        //피킹광선

private:
	vector<baseObject*>	m_vecObject;//오브젝트 push_back 해줄 변수
	float matScaleNumber;           //크기를 받을 변수
	float mapRotation;
	int   NumberCount;
	//맵바탕
	LEFTVIEWUI _leftView;
	LEFTVIEWUI _SaveButton;
	LEFTVIEWUI _LoadButton;

	//오브젝트에 관한 save
	vector<tagSaveObject> InfoObjectTemp;
	tagSaveObject ObjecTemp;

	//높낮이 변수
	D3DXVECTOR2		m_vSelectIdx;

private:
	enum eHeightType { E_NONE, E_UP, E_DOWN };
	eHeightType m_eHeightType;			//높이값을 올릴건지 내릴건지의 정보를 들고있다.

	char* tile1;
	char* tile2;
	char* tile3;
	char* tile4;
	char* splat;
	char* raw;

	int sour;
	int dest;
	bool first;
	//LOAD부분

private:
	tagSaveObject object;
	//텍스쳐칠하는부분
private:
	D3DXVECTOR3		m_vCSelectRangePos;
	string			m_sCCurTex;
	D3DXVECTOR3		m_vCSelectPos;
	D3DXVECTOR3		m_vCSelectColor;
	D3DXVECTOR2		m_vCSelectIdx;
	LPDIRECT3DTEXTURE9 m_pCSplatBase;

	int m_nSplatRange;		//색칠 범위

	LEFTVIEWUI _textureColorBack;   //뒷배경
	LEFTVIEWUI _textureColorMix[4];    //섞는 버튼
	LEFTVIEWUI _textureColorMixSize[4];//섞는 사이즈

	pair <bool, POINT> _pick1;
	pair <bool, POINT> _pick2;

	enum MOVETYPE { BackRight = 1, BackLeft = 2, RightSTOP = 3, LeftSTOP = 4 };
	int MoveX, MAXX;
	int MoveY, MAXY;


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
	void save();

	//칠하는 부분 함수
	void textureColorInit();
	void textureColorUpdate();
	void textureColorRender();

	void render();
	void setLink(rightView* rightView) { _rightView = rightView; }

	void monsterSelect(string str, int monsterNumber);
	void loadMonster(void);

	xMesh* findMonster(int&);
	string findMonsterName(int&);

	void loadNode(void);
};