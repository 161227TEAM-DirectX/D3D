#pragma once
#include "gameNode.h"

//#define FVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)
class sceneTest_0 : public gameNode
{
private:
	//정점 하나에 대한 정보를 정의하는 구조체
	typedef struct tagVertex
	{
		D3DXVECTOR3 pos;		//정점의 위치
		DWORD		color;		//정점의 컬러

		//현재 정점의 정보를 나타내는 플래그 상수값
		//D3DFVF_XYZ 정점의 위치정보
		//D3DFVF_DIFFUSE 정점의 컬러정보
		enum {FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE};
	}MYVERTEX, *LPMYVERTEX;

	MYVERTEX _vertices[3];		//정점 구조체 3개

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	sceneTest_0() {}
	~sceneTest_0() {}
};

