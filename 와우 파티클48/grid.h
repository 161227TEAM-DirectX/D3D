#pragma once

struct ST_PC_VERTEX
{
	D3DXVECTOR3	p;
	D3DCOLOR c;
	ST_PC_VERTEX(D3DXVECTOR3 pos, D3DCOLOR color) : p(pos), c(color) {}
	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };
};

class grid
{
private:
	vector<ST_PC_VERTEX> _vVertex;

public:
	//init(라인갯수, 라인간격)
	HRESULT init(int line = 15, float interval = 1.0f);
	void render(void);

	grid() {}
	~grid() {}
};

