#pragma once
class cObject
{
protected:
	int m_nRefCount;

public:
	cObject();
	virtual ~cObject();

	virtual void AddRef();
	virtual void Release();
	virtual void AutoRelease();
};

