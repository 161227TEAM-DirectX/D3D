#include "stdafx.h"
#include "cDxImgBar.h"

cDxImgBar::cDxImgBar(string sBack, string sMove, D3DXVECTOR2 vecPos, bool isCenter)
	: m_eBarType(E_BTN0)
	, m_pCover(NULL)
	, m_pBack(NULL)
	, m_pMove(NULL)
	, m_nTimeCount(0)
	, m_fGaugeSpeed(1)
	, m_fGaugeInterval(0)
{
	m_eBarType = E_BTN2;

	m_pBack = DXIMG_MANAGER->GetDxImg(sBack);
	m_pBack->SetPosition(D3DXVECTOR3(vecPos.x, vecPos.y, 0));
	m_pBack->SetCenterDraw(isCenter);

	m_pMove = DXIMG_MANAGER->GetDxImg(sMove);
	m_pMove->SetPosition(D3DXVECTOR3(vecPos.x, vecPos.y, 0));
	m_pMove->SetCenterDraw(isCenter);
}

cDxImgBar::cDxImgBar(string sCover, string sBack, string sMove, D3DXVECTOR2 vecPos, bool isCenter)
	: m_eBarType(E_BTN0)
	, m_pCover(NULL)
	, m_pBack(NULL)
	, m_pMove(NULL)
	, m_nTimeCount(0)
	, m_fGaugeSpeed(1)
	, m_fGaugeInterval(0)
{
	m_eBarType = E_BTN3;

	m_pCover = DXIMG_MANAGER->GetDxImg(sCover);
	m_pCover->SetPosition(D3DXVECTOR3(vecPos.x, vecPos.y, 0));
	m_pCover->SetCenterDraw(isCenter);

	m_pBack = DXIMG_MANAGER->GetDxImg(sBack);
	m_pBack->SetPosition(D3DXVECTOR3(vecPos.x, vecPos.y, 0));
	m_pBack->SetCenterDraw(isCenter);

	m_pMove = DXIMG_MANAGER->GetDxImg(sMove);
	m_pMove->SetPosition(D3DXVECTOR3(vecPos.x, vecPos.y, 0));
	m_pMove->SetCenterDraw(isCenter);
}


cDxImgBar::~cDxImgBar()
{
}


void cDxImgBar::setMoveGauge(int nGauge)
{
	m_pMove->SetCurX(nGauge);
}


void cDxImgBar::updateLoading()
{
	if (m_nTimeCount++ >= m_fGaugeInterval)
	{
		m_nTimeCount = 0;
		m_pMove->SetCurX(m_pMove->GetCurX() + m_fGaugeSpeed);
	}
}


void cDxImgBar::moveBar(int nCurX)
{
	m_pMove->SetCurX(m_pMove->GetCurX() + nCurX);
}


void cDxImgBar::movePos(int cx, int cy)
{
	if (m_pCover != NULL) m_pCover->SetPosition(D3DXVECTOR3(cx, cy, 0));
	if (m_pBack != NULL) m_pBack->SetPosition(D3DXVECTOR3(cx, cy, 0));
	if (m_pMove != NULL) m_pMove->SetPosition(D3DXVECTOR3(cx, cy, 0));
}


void cDxImgBar::render()
{
	switch (m_eBarType)
	{
	case E_BTN2:
		m_pMove->renderBarX();
		m_pBack->render();
		break;
	case E_BTN3:
		m_pBack->render();
		m_pMove->renderBarX();
		m_pCover->render();
		break;
	}
}


bool cDxImgBar::IsFullBar()
{
	if (m_pMove->GetCurX() >= m_pMove->GetSize().fWidth)
	{
		return true;
	}
	return false;
}
