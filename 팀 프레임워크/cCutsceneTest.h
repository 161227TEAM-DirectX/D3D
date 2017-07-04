#pragma once
#include "iGameNode.h"

class cCutsceneTest : public iGameNode
{
private:
	float m_fCutscnGauge = 0;
	float m_fCutscnMaxGauge = 160;
	float m_fCutscnSpeed = 1.5f;
	int   m_nCutscnDir = -1;


	float m_fCutscnUp = -300.f;
	float m_fCutscnDown = WINSIZEY;

	float m_fCutscnUpEnd = -140.f;
	float m_fCutscnDownEnd = WINSIZEY - 160;

	bool  m_isCutscn = false;

	vector<string> m_vecString;
	int m_nStrCount = 0;
	int m_nTimeCount = 0;
	int m_nTimeMax = 200;

	bool m_isCutStart = false;

public:
	cCutsceneTest();
	virtual ~cCutsceneTest();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

