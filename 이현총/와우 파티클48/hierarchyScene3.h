#pragma once
#include "gameNode.h"

class hierarchyScene3 : public gameNode
{
private:
	LPDIRECT3DVERTEXBUFFER9 _vb;		//정점버퍼
	LPDIRECT3DINDEXBUFFER9 _ib;			//인덱스버퍼

	transform	_cubeTrans;				//큐브
	vector<transform*> _followTrans;		//따라다니는 트렌스폼들
		
	transform _camTrans;				//카메라 트렌스폼
	camera _mainCamera;					//메인카메라

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void CreateCube();
	void RenderCube();

	hierarchyScene3() {}
	~hierarchyScene3() {}
};

