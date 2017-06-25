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
	//���̾� �ܰ谡 �������� ȭ�� ���ʿ� �׷�����.

	//�̵������̰� ���̾ 2�ܰ��̸�
	if (m_isMove && m_eUILayer == E_NONE2)
	{
		//UI�̹��� ��ġ ��ǥ�� �����Ѵ�.
		m_pUI->SetPosition(D3DXVECTOR3(GetMousePos().x + m_fSaveX,
									   GetMousePos().y + m_fSaveY,
									   0));
	}

	//UI�̹��� ��Ʈ�� ���콺�� �浹�ϸ�
	if (PtInRect(&m_pUI->getRect(), GetMousePos()))
	{
		//���콺 ���� ��ư�� ������ ������
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			//�̵����°� �ƴϸ�
			if (!m_isMove)
			{
				//�̵����·� �ٲٰ�
				m_isMove = true;
				m_fSaveX = m_pUI->GetPosition().x - GetMousePos().x;	//x��ǥ ���� ���
				m_fSaveY = m_pUI->GetPosition().y - GetMousePos().y;	//y��ǥ ���� ���
			}
		}
		else	//�ȴ����� ������
		{
			m_eUILayer = E_NONE2;	//���̾�� 2�ܰ�(���콺�� �ø��� �־ ���̾�ܰ� ���)
			m_isMove = false;		//�̵����´� ����.
		}
	}
	else //���浹�ϸ� ���̾ 1�ܰ�� �ٲ۴�.
	{
		m_eUILayer = E_NONE;
		m_isMove = false;		//�̵����´� ����.
	}
}

void cDxImgUI::render()
{
	m_pUI->render();
}
