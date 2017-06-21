#include "stdafx.h"
#include "cDxImgButton.h"


cDxImgButton::cDxImgButton(cDxImg* dxImg, D3DXVECTOR2 vecPos, bool isCenter, bool isBoundingBox)
{
	m_pDxImg = dxImg;
	m_pDxImg->SetCenterDraw(isCenter);
	m_pDxImg->SetDrawBoundingBox(isBoundingBox);
	m_pDxImg->SetPosition(D3DXVECTOR3(vecPos.x, vecPos.y, 0));
}


cDxImgButton::~cDxImgButton()
{
}

void cDxImgButton::render()
{
	m_pDxImg->render();
}

bool cDxImgButton::click()
{
	if(KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if(PtInRect(&m_pDxImg->getRect(), GetMousePos()))
		{
			return true;
		}
		else false;
	}
}
