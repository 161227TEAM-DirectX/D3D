#include "stdafx.h"
#include "cDxImgBar.h"


cDxImgBar::cDxImgBar()
{
}

cDxImgBar::cDxImgBar(string sCover, string sBack, string sMove, D3DXVECTOR2 vecPos, bool isCenter)
	: m_fGaugeSpeed(1)
	, m_fGaugeInterval(0)
	, m_timeCount(0)
{
	DXIMG_MANAGER->AddDxImg("UI_MoveBar",
							new cDxImg(FILEPATH_MANAGER->GetFilepath(sMove),
									   D3DXVECTOR2(vecPos.x, vecPos.y),
									   isCenter));

	DXIMG_MANAGER->AddDxImg("UI_BackBar",
							new cDxImg(FILEPATH_MANAGER->GetFilepath(sBack),
									   D3DXVECTOR2(vecPos.x, vecPos.y),
									   isCenter));

	DXIMG_MANAGER->AddDxImg("UI_CoverBar",
							new cDxImg(FILEPATH_MANAGER->GetFilepath(sCover),
									   D3DXVECTOR2(vecPos.x, vecPos.y),
									   isCenter));
}


cDxImgBar::~cDxImgBar()
{
}

void cDxImgBar::update()
{
	if (m_timeCount++ >= m_fGaugeInterval)
	{
		m_timeCount = 0;
		DXIMG_MANAGER->GetDxImg("UI_MoveBar")->SetCurX(DXIMG_MANAGER->GetDxImg("UI_MoveBar")->GetCurX() + m_fGaugeSpeed);
	}
}

void cDxImgBar::render()
{
	DXIMG_MANAGER->GetDxImg("UI_BackBar")->render();
	DXIMG_MANAGER->GetDxImg("UI_MoveBar")->renderBarX();
	DXIMG_MANAGER->GetDxImg("UI_CoverBar")->render();
}

bool cDxImgBar::IsFullBar()
{
	if (DXIMG_MANAGER->GetDxImg("UI_MoveBar")->GetCurX() >= DXIMG_MANAGER->GetDxImg("UI_MoveBar")->GetSize().fWidth)
	{
		return true;
	}
	return false;
}
