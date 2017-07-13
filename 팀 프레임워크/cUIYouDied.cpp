#include "stdafx.h"
#include "cUIYouDied.h"


cUIYouDied::cUIYouDied()
	: m_nAlpha(0)
	, m_nAlphaMax(200)
	, m_nAlphaSpeed(1)
	, m_isDied(false)
{
	DXIMG_MANAGER->GetDxImg("YOU DIED")->SetPosition(D3DXVECTOR3(WINSIZEX / 2, WINSIZEY / 2, 0));
	DXIMG_MANAGER->GetDxImg("YOU DIED")->SetCenterDraw(true);
	DXIMG_MANAGER->GetDxImg("YOU DIED")->SetImgAlpha(170);
}


cUIYouDied::~cUIYouDied()
{
}


void cUIYouDied::render()
{
	if (m_isDied)
	{
		m_nAlpha = m_nAlpha < m_nAlphaMax ? m_nAlpha + m_nAlphaSpeed : m_nAlphaMax;

		DXIMG_MANAGER->GetDxImg("죽었을때화면")->SetImgAlpha(m_nAlpha);

		DXIMG_MANAGER->GetDxImg("죽었을때화면")->render();
		DXIMG_MANAGER->GetDxImg("YOU DIED")->render();
	}
	else
	{
		m_nAlpha = 0;
	}
}
