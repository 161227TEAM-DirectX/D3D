#include "stdafx.h"
#include "cUIManager.h"
//
#include "cDxImgUI.h"

cUIManager::cUIManager()
{
}


cUIManager::~cUIManager()
{
	m_mapUI.clear();
	m_vecUI.clear();
}

bool cUIManager::AddUI(string sKey, cDxImgUI * ui)
{
	if (m_mapUI.find(sKey) != m_mapUI.end())
		return false;
	m_mapUI[sKey] = ui;
	m_vecUI.push_back(ui);

	sort(m_vecUI.begin(), m_vecUI.end(), [](const cDxImgUI* a, const cDxImgUI* b)
	{
		//���̾� ���� Ŭ���� ������ �켱������ �ռ���.
		return a->GetUILayer() < b->GetUILayer();
	});
	return true;
}

cDxImgUI * cUIManager::GetUI(string sKey)
{
	if (m_mapUI.find(sKey) == m_mapUI.end())
		return NULL;
	return m_mapUI[sKey];
}

void cUIManager::update()
{
	for (int i=0; i < m_vecUI.size(); i++)
	{
		m_vecUI[i]->update();
	}

	sort(m_vecUI.begin(), m_vecUI.end(), [](const cDxImgUI* a, const cDxImgUI* b)
	{
		//���̾� ���� Ŭ���� ������ �켱������ �ռ���.
		return a->GetUILayer() < b->GetUILayer();
	});
}

void cUIManager::render(string sKey)
{
	assert(m_mapUI.find(sKey) != m_mapUI.end() && "ã���� �ϴ� Ű�� �̹����� �����ϴ�.");
	m_mapUI[sKey]->render();
}

void cUIManager::render()
{
	for (int i=0; i < m_vecUI.size(); i++)
	{
		m_vecUI[i]->render();
	}
}
