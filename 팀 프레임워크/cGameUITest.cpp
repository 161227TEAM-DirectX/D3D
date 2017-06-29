#include "stdafx.h"
#include "cGameUITest.h"


cGameUITest::cGameUITest()
{
}


cGameUITest::~cGameUITest()
{
}

HRESULT cGameUITest::init()
{
	m_pPlBar = new cDxImgUI("playerbar_back");
	m_pPlBar->GetUI()->SetPosition(D3DXVECTOR3(WINSIZEX / 2, 0, 0));

	m_pBar = new cDxImgBar("playerbarHP_cover", "playerbarHP_move",
						   D3DXVECTOR2(m_pPlBar->GetUI()->GetPosition().x,
									   m_pPlBar->GetUI()->GetPosition().y));
	m_pBar->setMoveGauge(m_pBar->GetMove()->GetSize().fWidth);

	m_pBar2 = new cDxImgBar("playerbarMP_cover", "playerbarMP_move",
							D3DXVECTOR2(0, 0));
	m_pBar2->setMoveGauge(m_pBar2->GetMove()->GetSize().fWidth);


	cDxImgUI* temp;

	//temp = new cDxImgUI("playerbar_back");
	//temp->GetUI()->SetPosition(D3DXVECTOR3(WINSIZEX / 2, 0, 0));
	//temp->GetUI()->SetDrawBoundingBox(true);
	//UI_MANAGER->AddUI("플레이어바", temp);


	//temp = new cDxImgUI("quickSlotUI_back");
	//temp->GetUI()->SetPosition(D3DXVECTOR3(WINSIZEX / 2, WINSIZEY / 2, 0));
	//temp->GetUI()->SetDrawBoundingBox(true);
	//temp->GetUI()->SetCenterDraw(true);
	//UI_MANAGER->AddUI("quickSlotUI_back", temp);

	return S_OK;
}

void cGameUITest::release()
{
}

void cGameUITest::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		m_pBar->moveBar(-1);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		m_pBar->moveBar(1);
	}

	m_pPlBar->update();
	m_pBar->movePos(m_pPlBar->GetUI()->GetPosition().x, m_pPlBar->GetUI()->GetPosition().y);
	m_pBar2->movePos(m_pPlBar->GetUI()->GetPosition().x, m_pPlBar->GetUI()->GetPosition().y);

	//UI_MANAGER->update();
}

void cGameUITest::render()
{
	LineMake(0, WINSIZEY / 2, WINSIZEX, WINSIZEY / 2);
	LineMake(WINSIZEX / 2, 0, WINSIZEX / 2, WINSIZEY);

	//UI_MANAGER->render();

	m_pPlBar->render();
	m_pBar->render();
	m_pBar2->render();
}
