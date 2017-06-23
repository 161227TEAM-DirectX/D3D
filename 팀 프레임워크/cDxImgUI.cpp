#include "stdafx.h"
#include "cDxImgUI.h"

cDxImgUI::cDxImgUI(string sUI)
	: m_pUI(nullptr)
	, m_isMove(false)
	, m_fSaveX(0)
	, m_fSaveY(0)
	, m_eUILayer(E_NONE)
	, m_isColl(false)
{
	m_pUI = DXIMG_MANAGER->GetDxImg(sUI);
}

cDxImgUI::~cDxImgUI()
{
}

void cDxImgUI::update()
{
	if (PtInRect(&m_pUI->getRect(), GetMousePos()))
	{
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			if (!m_isMove)
			{
				m_isMove = true;
				m_fSaveX = m_pUI->GetPosition().x - GetMousePos().x;
				m_fSaveY = m_pUI->GetPosition().y - GetMousePos().y;
			}
			else
			{
				if (m_eUILayer == E_NONE2)
				{
					m_pUI->SetPosition(D3DXVECTOR3(GetMousePos().x + m_fSaveX,
												   GetMousePos().y + m_fSaveY,
												   0));
				}
			}
		}
		else
		{
			m_eUILayer = E_NONE2;
			m_isMove = false;
		}
	}
	else
	{
		m_eUILayer = E_NONE;
	}
}

void cDxImgUI::render()
{
	m_pUI->render();
}
