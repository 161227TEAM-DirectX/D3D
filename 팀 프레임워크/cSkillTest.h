#pragma once
#include "iGameNode.h"

class cUISkill;

class cSkillTest : public iGameNode
{
private:
	float m_fSkillMaxX;
	float m_fSkillMaxY;
	float temp;
	bool m_isCoolTime = false;

	cUISkill* m_pSkill;

public:
	cSkillTest();
	virtual ~cSkillTest();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

