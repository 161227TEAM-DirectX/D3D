#pragma once
#include "gameObject.h"

class cube : public gameObject
{
protected:
	vector<MYVERTEX>	_vecVertex;

public:
	HRESULT init(D3DXVECTOR3 size = D3DXVECTOR3(2, 2, 2), D3DXMATRIXA16* mat = NULL);
	void release(void);//������
	void update(void);//������
	void render(void);

	cube() {}
	~cube() {}
};

