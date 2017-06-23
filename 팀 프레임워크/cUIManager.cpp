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
		//레이어 값이 클수록 렌더링 우선순위가 앞선다.
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
		//레이어 값이 클수록 렌더링 우선순위가 앞선다.
		return a->GetUILayer() < b->GetUILayer();
	});
}

void cUIManager::render(string sKey)
{
	assert(m_mapUI.find(sKey) != m_mapUI.end() && "찾고자 하는 키의 이미지가 없습니다.");
	m_mapUI[sKey]->render();
}

void cUIManager::render()
{
	for (int i=0; i < m_vecUI.size(); i++)
	{
		m_vecUI[i]->render();
	}
}
