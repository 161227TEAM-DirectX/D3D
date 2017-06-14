#pragma once
//#include "gameNode.h"
//#include "dxParticleSystem.h"
#include "gameNode.h"

#include "dxSkillManager.h"
#include "dxSkill.h"
#include "SK00.h"

//class dxMeshEmitter;
//class camera;

class particleTest12 : public gameNode
{
private:
	dx::transform* _player;
	dx::transform* _target;
	dxParticleSystem* _testPS;

	dxSkillManager* _skm;

	SK00* _testEmitter;

	dxSkill* testSkill00;

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



	particleTest12() {};
	~particleTest12() {};
};

