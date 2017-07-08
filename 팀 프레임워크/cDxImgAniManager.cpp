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

	m_mapDxImgAni[sKey] = dxImg;		//�ִϸ��̼� �̹���
	m_mapDxImgST[sKey] = dxImgAni;		//�ִϸ��̼� ���� ����ü
	m_mapDxAniIsOnce[sKey] = false;		//�ִϸ��̼��� �ѹ��� ���� ����
	return true;
}

void cDxImgAniManager::setDxImgAniPosition(string sKey, D3DXVECTOR2 vecPos)
{
	assert(m_mapDxImgAni.find(sKey) != m_mapDxImgAni.end() &&
		   "Ű�� �ش��ϴ� ���� ã�� �� �����ϴ�.");

	for (int i = 0; i < m_mapDxImgAni[sKey].size(); i++)
	{
		m_mapDxImgAni[sKey][i]->SetPosition(D3DXVECTOR3(vecPos.x, vecPos.y, 0));
	}
}

void cDxImgAniManager::setDxAniIsOnce(string sKey, bool isOnce)
{
	assert(m_mapDxAniIsOnce.find(sKey) != m_mapDxAniIsOnce.end() &&
		"Ű�� �ش��ϴ� ���� ã�� �� �����ϴ�.");
	m_mapDxAniIsOnce[sKey] = isOnce;
}

vector<cDxImg*> cDxImgAniManager::GetDxImgAni(string sKey)
{
	assert(m_mapDxImgAni.find(sKey) != m_mapDxImgAni.end() &&
		   "Ű�� �ش��ϴ� ���� ã�� �� �����ϴ�.");
	return m_mapDxImgAni[sKey];
}

void cDxImgAniManager::render(string sKey)
{
	m_mapDxImgST[sKey].nAniCount++;

	if (m_mapDxImgST[sKey].nAniCount > m_mapDxImgST[sKey].nAniTime)
	{
		m_mapDxImgST[sKey].nAniIndex++;
		m_mapDxImgST[sKey].nAniCount = 0;

		if (m_mapDxImgST[sKey].nAniIndex >= GetDxImgAni(sKey).size())
		{
			if (!m_mapDxAniIsOnce[sKey])
			{
				m_mapDxImgST[sKey].nAniIndex = 0;
			}
			else
			{
				m_mapDxImgST[sKey].nAniIndex = GetDxImgAni(sKey).size() - 1;
			}
		}
	}
	GetDxImgAni(sKey)[m_mapDxImgST[sKey].nAniIndex]->render();
}
