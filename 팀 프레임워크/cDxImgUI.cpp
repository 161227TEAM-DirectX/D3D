#include "stdafx.h"
#include "cDxImgUI.h"

cDxImgUI::cDxImgUI(string sUI)
	: m_pUI(NULL)
	, m_isMove(false)
	, m_fSaveX(0)
	, m_fSaveY(0)
	, m_eUILayer(E_NONE)
{
	m_pUI = DXIMG_MANAGER->GetDxImg(sUI);
}

cDxImgUI::~cDxImgUI()
{
}

void cDxImgUI::update()
{
	//레이어 단계가 높을수록 화면 앞쪽에 그려진다.

	//이동상태이고 레이어가 2단계이면
	if (m_isMove && m_eUILayer == E_NONE2)
	{
		//UI이미지 위치 좌표를 갱신한다.
		m_pUI->SetPosition(D3DXVECTOR3(GetMousePos().x + m_fSaveX,
									   GetMousePos().y + m_fSaveY,
									   0));
	}

	//UI이미지 렉트랑 마우스랑 충돌하면
	if (PtInRect(&m_pUI->getRect(), GetMousePos()))
	{
		//마우스 왼쪽 버튼을 누르고 있으면
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			//이동상태가 아니면
			if (!m_isMove)
			{
				//이동상태로 바꾸고
				m_isMove = true;
				m_fSaveX = m_pUI->GetPosition().x - GetMousePos().x;	//x좌표 차를 기억
				m_fSaveY = m_pUI->GetPosition().y - GetMousePos().y;	//y좌표 차를 기억
			}
		}
		else	//안누르고 있으면
		{
			m_eUILayer = E_NONE2;	//레이어는 2단계(마우스를 올리고만 있어도 레이어단계 상승)
			m_isMove = false;		//이동상태는 끈다.
		}
	}
	else //안충돌하면 레이어를 1단계로 바꾼다.
	{
		m_eUILayer = E_NONE;
		m_isMove = false;		//이동상태는 끈다.
	}
}

void cDxImgUI::render()
{
	m_pUI->render();
}
