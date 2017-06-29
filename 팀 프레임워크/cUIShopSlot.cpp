#include "stdafx.h"
#include "cUIShopSlot.h"


cUIShopSlot::cUIShopSlot(string sUI, int nBtnX, int nBtnY, int nBtnWidth, int nBtnHeight)
	: cDxImgUI(sUI)
	, m_isBtnSetting(false)
	, m_nBtnX(nBtnX)
	, m_nBtnY(nBtnY)
	, m_nBtnWidth(nBtnWidth)
	, m_nBtnHeight(nBtnHeight)
	, m_isBtnCheck(false)
	, m_isBtnCheckBack(false)
	, m_eUIBtnState(E_UIBTN_NONE)
	, m_nBtnSpeed(3)
	, m_nCountMax(100)
	, m_nCount(0)
{
		
}


cUIShopSlot::~cUIShopSlot()
{
}

void cUIShopSlot::update()
{
	//cDxImgUI::update();

	if(!m_isBtnSetting)
	{
		m_isBtnSetting = true;

		m_rtBtn = RectMake(
			(int)GetUI()->GetPosition().x + m_nBtnX,
			(int)GetUI()->GetPosition().y + m_nBtnY,
			m_nBtnWidth,
			m_nBtnHeight);
	}


	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&GetRtBtn(), GetMousePos()))
		{
			switch(m_eUIBtnState)
			{
			case E_UIBTN_NONE:
				m_eUIBtnState = E_UIBTN_GO;
				break;
			case E_UIBTN_SHOP:
				m_eUIBtnState = E_UIBTN_BACK;
				break;
			}
		}
	}



	if (m_eUIBtnState == E_UIBTN_GO)
	{
		m_nBtnSpeed = m_nBtnSpeed < 0 ? m_nBtnSpeed*=-1 : m_nBtnSpeed;
		if (m_nCount++ > m_nCountMax)
		{
			m_eUIBtnState = E_UIBTN_SHOP;
			m_nCount = 0;
		}

		GetUI()->SetPosition(D3DXVECTOR3(GetUI()->GetPosition().x + m_nBtnSpeed,
										 GetUI()->GetPosition().y,
										 GetUI()->GetPosition().z));
		m_rtBtn = RectMake(m_rtBtn.left + m_nBtnSpeed, m_rtBtn.top, m_nBtnWidth, m_nBtnHeight);
	}


	if (m_eUIBtnState == E_UIBTN_BACK)
	{
		m_nBtnSpeed = m_nBtnSpeed > 0 ? m_nBtnSpeed*=-1 : m_nBtnSpeed;
		if (m_nCount++ > m_nCountMax)
		{
			m_eUIBtnState = E_UIBTN_NONE;
			m_nCount = 0;
		}

		GetUI()->SetPosition(D3DXVECTOR3(GetUI()->GetPosition().x + m_nBtnSpeed,
										 GetUI()->GetPosition().y,
										 GetUI()->GetPosition().z));
		m_rtBtn = RectMake(m_rtBtn.left + m_nBtnSpeed, m_rtBtn.top, m_nBtnWidth, m_nBtnHeight);
	}
}

void cUIShopSlot::render()
{
	cDxImgUI::render();
	
	//상점슬롯 버튼 렉트를 그려준다.
	//RectMake(m_rtBtn.left,m_rtBtn.top,m_nBtnWidth,m_nBtnHeight,false,RED);
}
