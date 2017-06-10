#pragma once
#include "gameNode.h"
#include "xMeshStatic.h" //����ƽ�޽� Ŭ����

class useXMeshClass : public gameNode
{
private:
	xMeshStatic*	_mesh;
	transform		_trans;
	vector<light*>	_lights;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	useXMeshClass() {}
	~useXMeshClass() {}
};

