#pragma once
//#include "gameNode.h"
//#include "dxParticleSystem.h"
#include "iGameNode.h"

#include "dxSkillManager.h"
#include "dxSkill.h"
#include "skBoss_Breath.h"

#include "skPlayer_MagicShoot.h"

#include "skPlayer_Heal.h"

#include "skBoss_Shouting.h"

#include "skBoss_GrandMagic.h"
//class dxMeshEmitter;
//class camera;

class particleTest13 : public iGameNode
{
private:
	dx::transform* _player;
	dx::transform* _target;
	dx::transform* _manyTarget;
	dxParticleSystem* _testPS;
	
	dxSkillManager* _skm;

	dxEmitter* _testEmitter;

	skBoss_GrandMagic* testSkill00;

	camera* _mainCamera;

	float rotateY;
	float wave;

	float radius;

public:
	/*HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);*/

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();



	particleTest13() {};
	~particleTest13() {};
};

