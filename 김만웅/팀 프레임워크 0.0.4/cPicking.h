#pragma once

#define PICKING cPicking::GetInstance()

class cPicking
{
private:
	SINGLETONE(cPicking);

private:
	map<int, bool> m_mapUse;

public:
	enum eClickType
	{
		E_LEFTCLICK = 1 << 0,	// 1 * 2^0
		E_RIGHCLICK = 1 << 1	// 1 * 2*1
	};

	void SetUse(int nClickType);
	bool GetUse(int nClickType);
};

