#pragma once
#include "iGameNode.h"

#define fvf (D3DFVF_XYZ | D3DFVF_DIFFUSE)

//맵을 그리기 위한 위치좌표,색상 구조체
struct gridVertex
{
	D3DXVECTOR3 pos;
	D3DCOLOR color;

	//push.back할떄 대입하기 위해서  
	gridVertex(D3DXVECTOR3 _pos, D3DCOLOR _color)
		: pos(_pos)
		, color(_color)
	{}
};

class rightSmallGrid : public iGameNode
{
private:
	//맵을 그리기 위해 벡타<구조체>를 선언했다.
	vector<gridVertex> _gridVertex;
	//한쪽면당 삼각형의 갯수를 나타낼려는 변수
	int _line;
	//맵칸의 넓이
	float _lineWidth;
	//line * linewidh 가 들어가는 변수
	float _linePlus;
	//월드 행렬
	D3DXMATRIX _world;
	//색을 따로 선언하고 넣기 위한 변수
	D3DXCOLOR _colorLine;

public:
	rightSmallGrid();
	~rightSmallGrid();

	HRESULT init();
	void release();
	void update();
	void render();
};

