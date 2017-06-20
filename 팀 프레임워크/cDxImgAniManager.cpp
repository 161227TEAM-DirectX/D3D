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

	m_mapDxImgAni[sKey] = dxImg;
	m_mapDxImgST[sKey] = dxImgAni;
	return true;
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

	if (m_mapDxImgST[sKey].nAniCount > m_mapDxImgST[sKey].nAniTime)
	{
		if (m_mapDxImgST[sKey].nAniIndex >= GetDxImgAni(sKey).size() - 1)
		{
			m_mapDxImgST[sKey].nAniIndex = 0;
		}
		m_mapDxImgST[sKey].nAniIndex++;
		m_mapDxImgST[sKey].nAniCount = 0;
	}
	GetDxImgAni(sKey)[m_mapDxImgST[sKey].nAniIndex]->render();
}
