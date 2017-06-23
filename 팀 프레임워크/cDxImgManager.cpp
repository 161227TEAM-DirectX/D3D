#include "stdafx.h"
#include "cDxImgManager.h"


cDxImgManager::cDxImgManager()
{
}


cDxImgManager::~cDxImgManager()
{
	for (int i=0; i < m_vecDxImg.size(); i++)
	{
		SAFE_DELETE(m_vecDxImg[i]);
	}
	m_vecDxImg.clear();

	m_mapDxImg.clear();
}



bool cDxImgManager::AddDxImg(string sKey, cDxImg* dxImg)
{
	if (m_mapDxImg.find(sKey) != m_mapDxImg.end())
		return false;
	m_mapDxImg[sKey] = dxImg;
	m_vecDxImg.push_back(dxImg);

	sort(m_vecDxImg.begin(), m_vecDxImg.end(), [](const cDxImg* a, const cDxImg* b)
	{
		//���̾� ���� Ŭ���� ������ �켱������ �ռ���.
		return a->GetImgLayer() < b->GetImgLayer();
	});

	return true;
}



cDxImg * cDxImgManager::GetDxImg(string sKey)
{
	if (m_mapDxImg.find(sKey) == m_mapDxImg.end())
		return NULL;
	return m_mapDxImg[sKey];
}



void cDxImgManager::render(string sKey)
{
	assert(m_mapDxImg.find(sKey) != m_mapDxImg.end() && "ã���� �ϴ� Ű�� �̹����� �����ϴ�.");
	m_mapDxImg[sKey]->render();
}

void cDxImgManager::render()
{
	for (int i=0; i < m_vecDxImg.size(); i++)
	{
		m_vecDxImg[i]->render();
	}
}
