#include "stdafx.h"
#include "cSkillTest.h"
//
#include "cUISkill.h"

cSkillTest::cSkillTest()
{
}


cSkillTest::~cSkillTest()
{
}

HRESULT cSkillTest::init()
{
	//DXIMG_MANAGER->GetDxImg("skill0_On")->SetPosition(D3DXVECTOR3(WINSIZEX / 2, WINSIZEY / 2, 0));
	//DXIMG_MANAGER->GetDxImg("skill0_On")->SetCenterDraw(true);

	//DXIMG_MANAGER->GetDxImg("skill0_Off")->SetPosition(D3DXVECTOR3(WINSIZEX / 2, WINSIZEY / 2, 0));
	//DXIMG_MANAGER->GetDxImg("skill0_Off")->SetCenterDraw(true);

	//m_fSkillMaxX = DXIMG_MANAGER->GetDxImg("skill0_Off")->GetSize().fWidth;
	//m_fSkillMaxY = DXIMG_MANAGER->GetDxImg("skill0_Off")->GetSize().fHeight;

	//temp = 0;

	//m_pSkill = new cUISkill("skill0_On", "skill0_Off", '1', WINSIZEX / 2, WINSIZEY / 2, false);
	//m_pSkill->SetSkillKey('1');
	return S_OK;
}

void cSkillTest::release()
{
}

void cSkillTest::update()
{
	//if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	//{
	//	temp = m_fSkillMaxY;
	//	m_isCoolTime = true;
	//}

	//if (m_isCoolTime)
	//{
	//	if (temp == 0) m_isCoolTime = false;
	//	temp = temp <= 0 ? 0 : temp - 1.0f;
	//}


	//if (GetAsyncKeyState(VK_UP) & 0x8000)
	//{
	//	temp = temp <= 0 ? 0 : temp - 1;
	//}
	//if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	//{
	//	temp = temp >= m_fSkillMaxY ? m_fSkillMaxY : temp + 1;
	//}



	//if (GetAsyncKeyState('1') & 0x8000)
	//{
	//	m_pSkill->SetIsOnSkill(true);
	//}
	//m_pSkill->update();
}

void cSkillTest::render()
{
	//m_pSkill->render();
}
