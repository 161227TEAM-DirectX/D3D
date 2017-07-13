#include "stdafx.h"
#include "cDxImgAniManager.h"


cDxImgAniManager::cDxImgAniManager()
{
}


cDxImgAniManager::~cDxImgAniManager()
{
	m_mapDxImgAni.clear();
	m_mapDxImgST.clear();
}

bool cDxImgAniManager::AddDxImgAni(string sKey, vector<cDxImg*> dxImg, ST_DXIMGANI dxImgAni, D3DXVECTOR2 vPos, bool isCenter)
{
	if (m_mapDxImgAni.find(sKey) != m_mapDxImgAni.end())
		return false;

	for (int i = 0; i < dxImg.size(); i++)
	{
		dxImg[i]->SetPosition(D3DXVECTOR3(vPos.x, vPos.y, 0));
		dxImg[i]->SetCenterDraw(isCenter);
	}

	m_mapDxImgAni[sKey] = dxImg;			//애니메이션 이미지
	m_mapDxImgST[sKey] = dxImgAni;			//애니메이션 구조체
	m_mapDxImgST[sKey].nStartIdx = 0;
	m_mapDxImgST[sKey].nEndIdx = m_mapDxImgAni[sKey].size() - 1;

	return true;
}

void cDxImgAniManager::setDxImgAniPosition(string sKey, D3DXVECTOR2 vecPos)
{
	assert(m_mapDxImgAni.find(sKey) != m_mapDxImgAni.end() &&
		   "키에 해당하는 값을 찾을 수 없습니다.");

	for (int i = 0; i < m_mapDxImgAni[sKey].size(); i++)
	{
		m_mapDxImgAni[sKey][i]->SetPosition(D3DXVECTOR3(vecPos.x, vecPos.y, 0));
	}
}



void cDxImgAniManager::setDxAniTime(string sKey, int aniTime)
{
	assert(m_mapDxImgST.find(sKey) != m_mapDxImgST.end() &&
		   "키에 해당하는 값을 찾을 수 없습니다.");
	m_mapDxImgST[sKey].nAniTime = aniTime;
}



void cDxImgAniManager::setDxAniIsOnce(string sKey, bool isOnce)
{
	assert(m_mapDxImgST.find(sKey) != m_mapDxImgST.end() &&
		   "키에 해당하는 값을 찾을 수 없습니다.");
	m_mapDxImgST[sKey].isOnce = isOnce;
}



void cDxImgAniManager::setDxAniIsReverse(string sKey, bool isReverse)
{
	assert(m_mapDxImgST.find(sKey) != m_mapDxImgST.end() &&
		   "키에 해당하는 값을 찾을 수 없습니다.");
	m_mapDxImgST[sKey].isReverse = isReverse;
	m_mapDxImgST[sKey].nStartIdx = m_mapDxImgAni[sKey].size() - 1;
	m_mapDxImgST[sKey].nEndIdx = 0;

	m_mapDxImgST[sKey].nAniIndex = m_mapDxImgST[sKey].nStartIdx;
}



void cDxImgAniManager::setDxAniIsSection(string sKey, bool isSection, int start, int end)
{
	assert(m_mapDxImgST.find(sKey) != m_mapDxImgST.end() &&
		   "키에 해당하는 값을 찾을 수 없습니다.");
	m_mapDxImgST[sKey].isSection = isSection;
	m_mapDxImgST[sKey].nStartIdx = start;
	m_mapDxImgST[sKey].nEndIdx = end;
	m_mapDxImgST[sKey].nAniIndex = m_mapDxImgST[sKey].nStartIdx;
}

void cDxImgAniManager::setDxAniType(string sKey, eAniState aniType)
{
	assert(m_mapDxImgAni.find(sKey) != m_mapDxImgAni.end() &&
		   "키에 해당하는 값을 찾을 수 없습니다.");
	m_mapDxImgST[sKey].nAniType = aniType;
}



ST_DXIMGANI cDxImgAniManager::getDxAniST(string sKey)
{
	assert(m_mapDxImgAni.find(sKey) != m_mapDxImgAni.end() &&
		   "키에 해당하는 값을 찾을 수 없습니다.");
	return m_mapDxImgST[sKey];
}

vector<cDxImg*> cDxImgAniManager::GetDxImgAni(string sKey)
{
	assert(m_mapDxImgAni.find(sKey) != m_mapDxImgAni.end() &&
		   "키에 해당하는 값을 찾을 수 없습니다.");
	return m_mapDxImgAni[sKey];
}



void cDxImgAniManager::render(string sKey)
{
	m_mapDxImgST[sKey].nAniCount++;

	if (m_mapDxImgST[sKey].isReverse)
	{
		if (m_mapDxImgST[sKey].nAniCount > m_mapDxImgST[sKey].nAniTime)
		{
			m_mapDxImgST[sKey].nAniIndex--;
			m_mapDxImgST[sKey].nAniCount = 0;

			if (m_mapDxImgST[sKey].nAniIndex < m_mapDxImgST[sKey].nEndIdx)
			{
				if (m_mapDxImgST[sKey].isOnce)
				{
					m_mapDxImgST[sKey].nAniIndex = m_mapDxImgST[sKey].nEndIdx;
				}
				else
				{
					m_mapDxImgST[sKey].nAniIndex =  m_mapDxImgST[sKey].nStartIdx;
				}
			}
		}
	}
	else
	{
		if (m_mapDxImgST[sKey].nAniCount > m_mapDxImgST[sKey].nAniTime)
		{
			m_mapDxImgST[sKey].nAniIndex++;
			m_mapDxImgST[sKey].nAniCount = 0;

			if (m_mapDxImgST[sKey].nAniIndex >= m_mapDxImgST[sKey].nEndIdx)
			{
				if (m_mapDxImgST[sKey].isOnce)
				{
					m_mapDxImgST[sKey].nAniIndex = m_mapDxImgST[sKey].nEndIdx;
				}
				else
				{
					m_mapDxImgST[sKey].nAniIndex = m_mapDxImgST[sKey].nStartIdx;
				}
			}
		}
	}

	GetDxImgAni(sKey)[m_mapDxImgST[sKey].nAniIndex]->render();
}