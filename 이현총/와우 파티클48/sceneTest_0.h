#pragma once
#include "gameNode.h"

//#define FVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)
class sceneTest_0 : public gameNode
{
private:
	//���� �ϳ��� ���� ������ �����ϴ� ����ü
	typedef struct tagVertex
	{
		D3DXVECTOR3 pos;		//������ ��ġ
		DWORD		color;		//������ �÷�

		//���� ������ ������ ��Ÿ���� �÷��� �����
		//D3DFVF_XYZ ������ ��ġ����
		//D3DFVF_DIFFUSE ������ �÷�����
		enum {FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE};
	}MYVERTEX, *LPMYVERTEX;

	MYVERTEX _vertices[3];		//���� ����ü 3��

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	sceneTest_0() {}
	~sceneTest_0() {}
};

