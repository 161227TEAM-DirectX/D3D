#pragma once

#define  g_pPicking cPicking::GetInstanse() 

class cPicking
{
private:
	map<int, bool> m_mapUse;

	cPicking();
	~cPicking();
public:
	enum eClickType
	{
		E_LEFTCLICK = 1 << 0,
		E_RIGHCLICK = 1 << 1
	};

	static cPicking* GetInstanse()
	{
		static cPicking instance;
		return &instance;
	}


	void Setup();
	void Update();

	void SetUse(int nClickType);
	bool GetUse(int nClickType);
};

