#pragma once
#include "cUIObject.h"

class cUIImageView;
class cUILoadingBar;

class cUILoading : public cUIObject
{
private:
	cUIImageView*	m_pUILoadingScreen;
	cUILoadingBar*	m_pUILoadingBar;
	volatile float	m_fLoading;
	
public:
	cUILoading(string sScreen, string sBack, string sFront, D3DXVECTOR3 vPos);
	virtual ~cUILoading();

	void OnUpdate();
	void OnRender();

public:
	static HRESULT ThreadInit(LPVOID lpVod);
};

