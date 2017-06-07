#pragma once
#include "gameNode.h"
#include "xMeshStatic.h" //����ƽ�޽� Ŭ����

class useXMeshClass : public gameNode
{
private:
	xMeshStatic*	_mesh;
	transform		_trans;
	vector<light*>	_lights;


	camera* _camera;

	lightDirection* light1;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	useXMeshClass() {}
	~useXMeshClass() {}
};

