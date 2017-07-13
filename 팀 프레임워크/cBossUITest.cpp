#include "stdafx.h"
#include "cBossUITest.h"


cBossUITest::cBossUITest()
{
}


cBossUITest::~cBossUITest()
{
}

HRESULT cBossUITest::init()
{
	m_pBar = new cDxImgBar("bossbar_cover",
						   "bossbar_back",
						   "bossbar_move",
						   D3DXVECTOR2(WINSIZEX / 2, WINSIZEY / 2),
						   true);
	m_pBar->setMoveGauge(m_pBar->GetMove()->GetSize().fWidth);
	return S_OK;
}


void cBossUITest::release()
{
	SAFE_DELETE(m_pBar);
}


void cBossUITest::update()
{
	//보스 현재 체력 / 보스 최대 체력 * 100
	//m_pBar->moveBar((float)PLAYERMANAGER->GetHp() / (float)PLAYERMANAGER->GetMaxHp() * 100);

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_pBar->moveBar(-1);
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_pBar->moveBar(1);
	}
}

void cBossUITest::render()
{
	m_pBar->render();

	FONTMANAGER->fontOut("%d", m_pBar->getCursorBar(), 100, 100, WHITE);
}
