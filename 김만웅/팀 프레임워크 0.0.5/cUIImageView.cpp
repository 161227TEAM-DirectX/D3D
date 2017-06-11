#include "stdafx.h"
#include "cUIImageView.h"


cUIImageView::cUIImageView() : m_pTexture(NULL)
{
	ZeroMemory(&m_stImageInfo, sizeof(D3DXIMAGE_INFO));
}

cUIImageView::cUIImageView(string sFullPath, D3DXVECTOR3 vecPos)
{
	this->SetTexture(sFullPath);
	this->SetPosition(vecPos);
}


cUIImageView::~cUIImageView()
{
}

void cUIImageView::Update()
{
	cUIObject::Update();
}

void cUIImageView::Render(LPD3DXSPRITE pSprite)
{
	if (m_pTexture)
	{
		pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

		RECT rc;
		SetRect(&rc, 0, 0, m_stImageInfo.Width, m_stImageInfo.Height);

		pSprite->SetTransform(&m_matWorld);
		pSprite->Draw(m_pTexture,
					  &rc,
					  &D3DXVECTOR3(0, 0, 0),
					  &D3DXVECTOR3(0, 0, 0),
					  D3DCOLOR_XRGB(255, 255, 255));

		pSprite->End();
	}

	cUIObject::Render(pSprite);
}

void cUIImageView::SetTexture(string sFullPath)
{
	m_sFullPath = sFullPath;
	m_pTexture = TEXTURE_MANAGER->GetTexture(sFullPath, &m_stImageInfo);
	m_stSize.fWidth = m_stImageInfo.Width;
	m_stSize.fHeight = m_stImageInfo.Height;
}

LPDIRECT3DTEXTURE9 cUIImageView::GetTexture()
{
	return m_pTexture;
}

string cUIImageView::GetFullPath()
{
	return m_sFullPath;
}
