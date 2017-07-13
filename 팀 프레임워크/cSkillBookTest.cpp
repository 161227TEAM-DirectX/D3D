#include "stdafx.h"
#include "cSkillBookTest.h"
//
#include "cUIPlayer.h"

cSkillBookTest::cSkillBookTest()
{
}


cSkillBookTest::~cSkillBookTest()
{
}

HRESULT cSkillBookTest::init()
{
	//�÷��̾�UI ����
	m_pUIPlayer = new cUIPlayer;
	m_pUIPlayer->SetMinimap("worldmapTest");
	m_pUIPlayer->init();

	DXIMGANI_MANAGER->setDxAniIsOnce("skillbook01", true);
	return S_OK;
}

void cSkillBookTest::release()
{
	SAFE_DELETE(m_pUIPlayer);
}

void cSkillBookTest::update()
{
	m_pUIPlayer->update();
}

void cSkillBookTest::render()
{
	//UI����
	m_pUIPlayer->render();
}
