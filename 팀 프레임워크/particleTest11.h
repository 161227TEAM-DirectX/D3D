#pragma once
//#include "gameNode.h"
//#include "dxParticleSystem.h"
#include "gameNode.h"

//#include "skill00.h"
//#include "skill00_03.h"

//class dxMeshEmitter;
//class camera;

class particleTest11 : public gameNode
{
private:
	dx::transform* _player;
	dx::transform* _target;
	dxParticleSystem* _testPS;
	dxMeshEmitter* _testEmitter;

	camera* _mainCamera;

	float rotateY;
	float wave;

	float radius;

public:
	/*HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);*/

	virtual void Setup();
	virtual void Update();
	virtual void Render();

	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {};



	particleTest11() {};
	~particleTest11() {};
};

