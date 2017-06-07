#pragma once

#define OBJECT_MANAGER cObjectManager::GetInstance()

class cObjectManager
{
public:
	SINGLETONE(cObjectManager);

private:
	set<cObject*>		m_setObject;
	vector<cObject*>	m_vecAutoRelease;

public:
	void AddObject(cObject* pObject);
	void RemoveObject(cObject* pObject);
	void Destroy();

	void AddAutoReleasePool(cObject* pObject);
	void Drain();
};

