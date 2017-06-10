#pragma once
#include "gameNode.h"

class skinnedAniTest : public gameNode
{
private:
	skinnedAnimation*		_pSkinned1;
	skinnedAnimation*		_pSkinned2;
	transform*				_pSkinnedTrans1;
	transform*				_pSkinnedTrans2;

	transform*				_pBoxTrans1;
	boundBox*				_pBox1;
	transform*				_pBoxTrans2;

	transform*				_pApplyTrans;

	vector<light*>			_lights;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	skinnedAniTest() {}
	~skinnedAniTest() {}
};

