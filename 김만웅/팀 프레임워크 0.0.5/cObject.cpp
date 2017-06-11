#include "stdafx.h"
#include "cObject.h"


cObject::cObject() : m_nRefCount(1)
{
	OBJECT_MANAGER->AddObject(this);
}


cObject::~cObject()
{
	assert(m_nRefCount == 0 && "참조카운트가 0이 아닙니다!");
	OBJECT_MANAGER->RemoveObject(this);
}

void cObject::AddRef()
{
	++m_nRefCount;
}

void cObject::Release()
{
	--m_nRefCount;
	if (m_nRefCount == 0)
		delete this;
}

void cObject::AutoRelease()
{
	OBJECT_MANAGER->AddAutoReleasePool(this);
}
