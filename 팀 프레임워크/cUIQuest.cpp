#include "stdafx.h"
#include "cUIQuest.h"


cUIQuest::cUIQuest(string sUI, int nBtnX, int nBtnY, int nBtnWidth, int nBtnHeight)
	: cDxImgUI(sUI)
	, m_nBtnX(nBtnX)
	, m_nBtnY(nBtnY)
	, m_nBtnWidth(nBtnWidth)
	, m_nBtnHeight(nBtnHeight)
	, m_isSure(false)
	, m_isBtnOver(false)
{
}


cUIQuest::~cUIQuest()
{
}

void cUIQuest::update()
{
	if (!m_isSure)
	{
		cDxImgUI::update();

		m_rtBtn = RectMake(
			(int)GetUI()->GetPosition().x + m_nBtnX,
			(int)GetUI()->GetPosition().y + m_nBtnY,
			m_nBtnWidth,
			m_nBtnHeight);

		DXIMG_MANAGER->GetDxImg("btn_questBox_off")->SetPosition(D3DXVECTOR3(m_rtBtn.left, m_rtBtn.top, 0));
		DXIMG_MANAGER->GetDxImg("btn_questBox_on")->SetPosition(D3DXVECTOR3(m_rtBtn.left, m_rtBtn.top, 0));
	}
	
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (PtInRect(&m_rtBtn, GetMousePos()))
		{
			m_isSure = true;
			m_pUI = DXIMG_MANAGER->GetDxImg("miniQuestBox");
			m_pUI->setPos(WINSIZEX - m_pUI->GetSize().fWidth - 10, 390);
		}
	}

	//버튼(렉트)에 마우스가 충돌하면
	if (PtInRect(&m_rtBtn, GetMousePos()))
	{
		m_isBtnOver = true;
	}
	else
	{
		m_isBtnOver = false;
	}
}

void cUIQuest::render()
{
	cDxImgUI::render();
	if (!m_isSure)
	{
		//RectMake(m_rtBtn.left, m_rtBtn.top, m_nBtnWidth, m_nBtnHeight, false, RED);

		if (m_isBtnOver)
		{
			DXIMG_MANAGER->GetDxImg("btn_questBox_on")->render();
		}
		else
		{
			DXIMG_MANAGER->GetDxImg("btn_questBox_off")->render();
		}
	}
}
