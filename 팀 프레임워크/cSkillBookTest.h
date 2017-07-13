#pragma once
#include "iGameNode.h"
//
class cUIPlayer;

class cSkillBookTest : public iGameNode
{
private:
	cUIPlayer* m_pUIPlayer;

public:
	cSkillBookTest();
	virtual ~cSkillBookTest();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

