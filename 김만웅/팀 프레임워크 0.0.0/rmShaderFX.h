#pragma once
#include "resourceManager.h"

class rmShaderFX : public resourceManager <LPD3DXEFFECT, rmShaderFX>
{
public:
	HRESULT init(void);
	void release(void);
	//리소스 로딩 방식만 재정의한다(텍스쳐, 셰이더이펙트)
	LPD3DXEFFECT loadResource(string filePath, void* pParam = NULL) override;
	//리소스 해제 방식만 재정의한다
	void releaseResource(LPD3DXEFFECT data) override;

	rmShaderFX() {}
	~rmShaderFX() {}
};

