#include "stdafx.h"
#include "cPicking.h"


cPicking::cPicking()
{
}


cPicking::~cPicking()
{
}

void cPicking::SetUse(int nClickType)
{
	m_mapUse[nClickType] = true;
}

bool cPicking::GetUse(int nClickType)
{
	if (m_mapUse.find(nClickType) != m_mapUse.end() && m_mapUse[nClickType])
		return false;
	else
		return true;
}
