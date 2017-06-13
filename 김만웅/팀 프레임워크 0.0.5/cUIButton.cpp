#include "stdafx.h"
#include "cUIButton.h"


cUIButton::cUIButton()
	: m_eButtonState(E_NORMAL)
	, m_pDelegate(NULL)
{
}

cUIButton::cUIButton(string sNor, string sOvr, string sSel, D3DXVECTOR3 vecPos, iUIButtonDelegate * del)
{
	this->SetButtonImage(sNor,sOvr,sSel);
	this->SetPosition(vecPos);
	this->SetTag(m_nTag++);
	this->SetDelegate(del);
}


cUIButton::~cUIButton()
{
}

void cUIButton::Update()
{
	cUIObject::Update();

	RECT rc;
	SetRect(&rc,
			int(m_matWorld._41),
			int(m_matWorld._42),
			int(m_matWorld._41 + m_stSize.fWidth),
			int(m_matWorld._42 + m_stSize.fHeight));

	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(_hWnd, &pt);

	if (PtInRect(&rc, pt))
	{
		if(KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (PICKING->GetUse(cPicking::E_LEFTCLICK))
			{
				PICKING->SetUse(cPicking::E_LEFTCLICK);
				if (m_eButtonState == E_MOVER)
				{
					m_eButtonState = E_SELECTED;
				}
			}
		}
		else
		{
			if (m_eButtonState == E_SELECTED)
			{
				//델리게이트가 존재하면
				if (m_pDelegate)
				{
					//델리게이트 함수를 호출한다.
					m_pDelegate->OnClick(this);
					return;
				}
			}
			m_eButtonState = E_MOVER;
		}
	}
	else
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (m_eButtonState != E_SELECTED)
			{
				m_eButtonState = E_NORMAL;
			}
		}
		else
		{
			m_eButtonState = E_NORMAL;
		}
	}
}

void cUIButton::Render(LPD3DXSPRITE pSprite)
{
	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	RECT rc;
	SetRect(&rc, 0, 0, (int)m_stSize.fWidth, (int)m_stSize.fHeight);

	pSprite->SetTransform(&m_matWorld);

	pSprite->Draw(m_aTexture[m_eButtonState],
				  &rc,
				  &D3DXVECTOR3(0, 0, 0),
				  &D3DXVECTOR3(0, 0, 0),
				  D3DCOLOR_XRGB(255, 255, 255));

	pSprite->End();

	cUIObject::Render(pSprite);
}

void cUIButton::SetButtonImage(string sNor, string sOvr, string sSel)
{
	D3DXIMAGE_INFO stImageInfo;
	m_aTexture[E_NORMAL] = TEXTURE_MANAGER->GetTexture(sNor, &stImageInfo);
	m_aTexture[E_MOVER] = TEXTURE_MANAGER->GetTexture(sOvr, &stImageInfo);
	m_aTexture[E_SELECTED] = TEXTURE_MANAGER->GetTexture(sSel, &stImageInfo);

	m_stSize.fWidth = float(stImageInfo.Width);
	m_stSize.fHeight = float(stImageInfo.Height);
}
