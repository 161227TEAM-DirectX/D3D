#include "stdafx.h"
#include "cUISkill.h"


cUISkill::cUISkill(string sUIon, string sUIoff, float posX, float posY, bool isCenter)
	:cDxImgUI(sUIon)
	, m_fSkillMaxX(0.0f)
	, m_fSkillMaxY(0.0f)
	, m_fSkillGauge(0.0f)
	, m_fSkillCool(0.1f)
	, m_isCoolTime(false)
	, m_isOnSkill(false)
	, m_nSkillKey(0)
	, m_isSkillCool(false)
	, m_pCoolTimeImg(nullptr)
	, m_nCoolAlpha(1)
{
	m_pOffImg = DXIMG_MANAGER->GetDxImg(sUIoff);

	m_fSkillMaxX = m_pOffImg->GetSize().fWidth;
	m_fSkillMaxY = m_pOffImg->GetSize().fHeight;

	changePos(posX, posY, isCenter);
}

cUISkill::cUISkill(string sUIon, string sUIoff, string sCool, int nSkillKey, float posX, float posY, bool isCenter)
	:cDxImgUI(sUIon)
	, m_fSkillMaxX(0.0f)
	, m_fSkillMaxY(0.0f)
	, m_fSkillGauge(0.0f)
	, m_fSkillCool(0.5f)
	, m_isCoolTime(false)
	, m_isOnSkill(false)
	, m_nSkillKey(0)
	, m_isSkillCool(false)
	, m_pCoolTimeImg(nullptr)
	, m_nCoolAlpha(1)
{
	m_pOffImg = DXIMG_MANAGER->GetDxImg(sUIoff);

	m_fSkillMaxX = m_pOffImg->GetSize().fWidth;
	m_fSkillMaxY = m_pOffImg->GetSize().fHeight;

	m_nSkillKey = nSkillKey;

	changePos(posX, posY, isCenter);

	m_pCoolTimeImg = DXIMG_MANAGER->GetDxImg(sCool);
	m_pCoolTimeImg->SetPosition(D3DXVECTOR3((WINSIZEX - m_pCoolTimeImg->GetSize().fWidth) / 2, 300, 0));

	n = 0;
}


cUISkill::~cUISkill()
{
}

void cUISkill::update()
{
	cDxImgUI::update();

	//스킬온의 위치로 동기화시킨다.
	m_pOffImg->SetPosition(D3DXVECTOR3(m_pUI->GetPosition().x,
									   m_pUI->GetPosition().y,
									   m_pUI->GetPosition().z));

	//if(KEYMANAGER->isOnceKeyDown(m_nSkillKey))
	if (GetAsyncKeyState(m_nSkillKey) & 0x8000)
	{
		if(m_fSkillGauge == 0)
		{
			m_isOnSkill = true;
			m_isSkillCool = false;
			m_pCoolTimeImg->SetImgAlpha(255);
			n = 0;
		}
		if (n>0)
		{
			m_isSkillCool = true;
			//m_pCoolTimeImg->SetPosition(D3DXVECTOR3(WINSIZEX / 2, 300, 0));
			m_pCoolTimeImg->SetPosition(D3DXVECTOR3((WINSIZEX - m_pCoolTimeImg->GetSize().fWidth) / 2, 300, 0));
			m_pCoolTimeImg->SetImgAlpha(255);
		}
	}
	if (KEYMANAGER->isOnceKeyUp(m_nSkillKey))
	{
		n++;
	}

	
	if(m_isSkillCool)
	{
		m_pCoolTimeImg->SetPosition(D3DXVECTOR3(m_pCoolTimeImg->GetPosition().x,
												m_pCoolTimeImg->GetPosition().y-1,
												0));
		if (m_pCoolTimeImg->GetImgAlpha() > 0)
		{
			m_pCoolTimeImg->SetImgAlpha(m_pCoolTimeImg->GetImgAlpha() - m_nCoolAlpha);
		}
	}



	//스킬 발동상태가 트루이면
	if (m_isOnSkill)
	{
		//스킬오프이미지를 보여주고
		m_fSkillGauge = m_fSkillMaxY;
		
		//스킬 발동상태를 펄스로 한다.
		m_isOnSkill = false;
	}
	
	//스킬 상태가 온이 되도록 돌아가려고 하는 식
	m_fSkillGauge = m_fSkillGauge <= 0 ? 0 : m_fSkillGauge - m_fSkillCool;
}

void cUISkill::render()
{
	cDxImgUI::render();
	
	m_pOffImg->render(0,0, m_fSkillMaxX, m_fSkillGauge);

	if(m_isSkillCool)
	{
		m_pCoolTimeImg->render();
	}

}

void cUISkill::changePos(float x, float y, bool isCenter)
{
	m_pUI->SetCenterDraw(isCenter);
	m_pOffImg->SetCenterDraw(isCenter);

	m_pUI->SetPosition(D3DXVECTOR3(x, y, 0));
	m_pOffImg->SetPosition(D3DXVECTOR3(x, y, 0));

	
}
