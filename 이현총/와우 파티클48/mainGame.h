#pragma once
#include "gameNode.h"
/*앞으로 씬의 헤더만 이곳에서 추가할것!!!*/
#include "skinnedAniTest.h"
#include "particleTest.h"
#include "particleTest02.h"
#include "particleTest03.h"
#include "particleTest04.h"
#include "particleTest05.h"
#include "particleTest06.h"
#include "particleTest07.h"
#include "particleTest08.h"
#include "particleTest09.h"
#include "particleTest10.h"

#include "useXMeshClass.h"

#include "_3quadParticleEmitter.h"

class mainGame : public gameNode
{
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	mainGame() {}
	~mainGame() {}
};