#include "stdafx.h"
#include "cMouseManager.h"


cMouseManager::cMouseManager()
	: m_pMouse(NULL)
{
	SetCursor(NULL);
	ShowCursor(FALSE);
}


cMouseManager::~cMouseManager()
{
}


void cMouseManager::render()
{
	if (m_pMouse != NULL)
	{
		DXIMG_MANAGER->GetDxImg("mouseCursor")->setPos(GetMousePos().x, GetMousePos().y);
		DXIMG_MANAGER->GetDxImg("mouseCursor")->render();
	}
	else
	{
		m_pMouse = DXIMG_MANAGER->GetDxImg("mouseCursor");
	}
}
