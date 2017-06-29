#include "stdafx.h"
#include "cDxImgButton.h"


cDxImgButton::cDxImgButton(cDxImg* off, cDxImg* over, D3DXVECTOR2 vecPos, string sBtnName, bool isCenter, bool isBoundingBox)
	: m_isOver(false)
	, m_sBtnName(sBtnName)
{
	m_pOff = off;
	m_pOff->SetCenterDraw(isCenter);
	m_pOff->SetDrawBoundingBox(isBoundingBox);
	m_pOff->SetPosition(D3DXVECTOR3(vecPos.x, vecPos.y, 0));

	m_pOver = over;
	m_pOver->SetCenterDraw(isCenter);
	m_pOver->SetDrawBoundingBox(isBoundingBox);
	m_pOver->SetPosition(D3DXVECTOR3(vecPos.x, vecPos.y, 0));

	m_rtBtn = m_pOff->getRect();
}


cDxImgButton::~cDxImgButton()
{
}

void cDxImgButton::render()
{
	if (PtInRect(&m_pOff->getRect(), GetMousePos()))
	{
		m_isOver = true;
	}
	else
	{
		m_isOver = false;
	}

	if (m_isOver)
	{
		m_pOver->render();
	}
	else
	{
		m_pOff->render();
	}
}

bool cDxImgButton::click()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON, false))
	{
		if (PtInRect(&m_pOff->getRect(), GetMousePos()))
		{
			return true;
		}
	}
	return false;
}

void cDxImgButton::setPos(D3DXVECTOR2 vecPos)
{
	m_pOff->SetPosition(D3DXVECTOR3(vecPos.x, vecPos.y, 0));
	m_pOver->SetPosition(D3DXVECTOR3(vecPos.x, vecPos.y, 0));
}
