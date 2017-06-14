#pragma once
//#include "gameNode.h"
//#include "dxParticleSystem.h"
#include "gameNode.h"

#include "dxSkillManager.h"
#include "dxSkill.h"
#include "SK_Boss00.h"
#include "SK_Effect00.h"

//class dxMeshEmitter;
//class camera;

class particleTest13 : public gameNode
{
private:
	dx::transform* _player;
	dx::transform* _target;
	dxParticleSystem* _testPS;
	
	dxSkillManager* _skm;

	dxEmitter* _testEmitter;

	SK_Effect00* testSkill00;

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



	particleTest13() {};
	~particleTest13() {};
};

