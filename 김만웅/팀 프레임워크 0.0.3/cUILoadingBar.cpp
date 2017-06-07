#include "stdafx.h"
#include "cUILoadingBar.h"

#include "cUIImageView.h"

cUILoadingBar::cUILoadingBar(string sBack, string sFront, D3DXVECTOR3 vPos)
	: m_pUILoadingBack(NULL)
	, m_pUILoadingFront(NULL)
	, m_fLoading(0)
{
	D3DXCreateSprite(_device, &m_pSprite);

	m_pUILoadingBack = new cUIImageView(sBack, vPos);
	AddChild(m_pUILoadingBack);

	m_pUILoadingFront = new cUIImageView(sFront, vPos);
	m_pUILoadingFront->SetScale(D3DXVECTOR3(m_fLoading, 1.f, 1.f));
	AddChild(m_pUILoadingFront);
}


cUILoadingBar::~cUILoadingBar()
{
	SAFE_RELEASE(m_pUILoadingBack);
	SAFE_RELEASE(m_pUILoadingFront);
}

void cUILoadingBar::OnUpdate()
{
	cUIObject::Update();
	if(m_fLoading <= 1.f)
		m_fLoading += TIMEMANAGER->getElapedTime() / 20.f;
	m_pUILoadingFront->SetScale(D3DXVECTOR3(m_fLoading, 1.f, 1.f));
}

void cUILoadingBar::OnRender()
{
	cUIObject::Render(m_pSprite);
}
