#pragma once
#include "cUIObject.h"

class cUIImageView;

class cUILoadingBar : public cUIObject
{
private:
	cUIImageView*	m_pUILoadingBack;
	cUIImageView*	m_pUILoadingFront;
	float			m_fLoading;

public:
	cUILoadingBar(string sBack,string sFront,D3DXVECTOR3 vPos);
	virtual ~cUILoadingBar();

	void OnUpdate();
	void OnRender();
};

