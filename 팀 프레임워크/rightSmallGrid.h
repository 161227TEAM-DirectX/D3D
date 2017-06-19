#pragma once
#include "iGameNode.h"

#define fvf (D3DFVF_XYZ | D3DFVF_DIFFUSE)

//���� �׸��� ���� ��ġ��ǥ,���� ����ü
struct gridVertex
{
	D3DXVECTOR3 pos;
	D3DCOLOR color;

	//push.back�ҋ� �����ϱ� ���ؼ�  
	gridVertex(D3DXVECTOR3 _pos, D3DCOLOR _color)
		: pos(_pos)
		, color(_color)
	{}
};

class rightSmallGrid : public iGameNode
{
private:
	//���� �׸��� ���� ��Ÿ<����ü>�� �����ߴ�.
	vector<gridVertex> _gridVertex;
	//���ʸ�� �ﰢ���� ������ ��Ÿ������ ����
	int _line;
	//��ĭ�� ����
	float _lineWidth;
	//line * linewidh �� ���� ����
	float _linePlus;
	//���� ���
	D3DXMATRIX _world;
	//���� ���� �����ϰ� �ֱ� ���� ����
	D3DXCOLOR _colorLine;

public:
	rightSmallGrid();
	~rightSmallGrid();

	HRESULT init();
	void release();
	void update();
	void render();
};

