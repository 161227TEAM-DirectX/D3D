#include "stdafx.h"
#include "cUISkillBook.h"


cUISkillBook::cUISkillBook(string sSkillBook)
	: m_sSkillBook(sSkillBook)
	, m_isAct(false)
	, m_nCount(0)
	, m_nMaxCount(30)
	, m_nActStart(8)
	, m_nActEnd(37)
	, m_nPosX(0)
	, m_nPosY(0)
{
	DXIMGANI_MANAGER->setDxAniIsOnce(m_sSkillBook, true);
	m_nPosX = DXIMGANI_MANAGER->GetDxImgAni(sSkillBook)[0]->GetPosition().x;
	m_nPosY = DXIMGANI_MANAGER->GetDxImgAni(sSkillBook)[0]->GetPosition().y;

	cDxImg* tempImg;

	tempImg = DXIMG_MANAGER->GetDxImg("skillbookText00"); tempImg->SetPosition(D3DXVECTOR3(m_nPosX - 310, m_nPosY - 230, 0));  m_vecSkill.push_back(tempImg);
	tempImg = DXIMG_MANAGER->GetDxImg("skillbookText01"); tempImg->SetPosition(D3DXVECTOR3(m_nPosX - 310, m_nPosY - 120, 0)); m_vecSkill.push_back(tempImg);
	tempImg = DXIMG_MANAGER->GetDxImg("skillbookText02"); tempImg->SetPosition(D3DXVECTOR3(m_nPosX - 310, m_nPosY - 10, 0)); m_vecSkill.push_back(tempImg);
	tempImg = DXIMG_MANAGER->GetDxImg("skillbookText03"); tempImg->SetPosition(D3DXVECTOR3(m_nPosX - 310, m_nPosY + 100, 0)); m_vecSkill.push_back(tempImg);
	tempImg = DXIMG_MANAGER->GetDxImg("skillbookText04"); tempImg->SetPosition(D3DXVECTOR3(m_nPosX + 25, m_nPosY - 230, 0)); m_vecSkill.push_back(tempImg);
	tempImg = DXIMG_MANAGER->GetDxImg("skillbookText05"); tempImg->SetPosition(D3DXVECTOR3(m_nPosX + 25, m_nPosY - 120, 0)); m_vecSkill.push_back(tempImg);
	tempImg = DXIMG_MANAGER->GetDxImg("skillbookText06"); tempImg->SetPosition(D3DXVECTOR3(m_nPosX + 25, m_nPosY - 10, 0)); m_vecSkill.push_back(tempImg);
	tempImg = DXIMG_MANAGER->GetDxImg("skillbookText07"); tempImg->SetPosition(D3DXVECTOR3(m_nPosX + 25, m_nPosY + 100, 0)); m_vecSkill.push_back(tempImg);
}


cUISkillBook::~cUISkillBook()
{
}

void cUISkillBook::update()
{
	if (m_isAct)
	{
		DXIMGANI_MANAGER->setDxAniIsReverse(m_sSkillBook, false);
		DXIMGANI_MANAGER->setDxAniIsSection(m_sSkillBook, true, m_nActStart, m_nActEnd);
		DXIMGANI_MANAGER->setDxAniType(m_sSkillBook, eAniState::E_ANI_PLAY);
	}
	else
	{
		DXIMGANI_MANAGER->setDxAniIsReverse(m_sSkillBook, true);
		DXIMGANI_MANAGER->setDxAniIsSection(m_sSkillBook, true, m_nActEnd, m_nActStart);
	}
}

void cUISkillBook::render()
{
	if (DXIMGANI_MANAGER->getDxAniST(m_sSkillBook).nAniType == eAniState::E_ANI_PLAY)
	{
		if (DXIMGANI_MANAGER->getDxAniST(m_sSkillBook).isReverse &&
			DXIMGANI_MANAGER->getDxAniST(m_sSkillBook).nAniIndex == m_nActStart)
		{
			if (m_nCount++ > m_nMaxCount)
			{
				m_nCount = 0;
				DXIMGANI_MANAGER->setDxAniType(m_sSkillBook, eAniState::E_ANI_STOP);
			}
		}
		DXIMGANI_MANAGER->render(m_sSkillBook);
	}

	if(DXIMGANI_MANAGER->getDxAniST(m_sSkillBook).nAniIndex == m_nActEnd)
	{
		for (int i=0; i < m_vecSkill.size(); i++)
		{
			m_vecSkill[i]->render();
		}
	}
}
