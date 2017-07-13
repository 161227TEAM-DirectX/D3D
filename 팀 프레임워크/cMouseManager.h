#pragma once

#define MOUSE_MANAGER cMouseManager::GetInstance()

class cMouseManager
{
	SINGLETONE(cMouseManager);
	SYNTHESIZE(cDxImg*, m_pMouse, Mouse);

public:
	void render();
};

