#pragma once
#include "resourceManager.h"
class rmTexture : public resourceManager <LPDIRECT3DTEXTURE9, rmTexture>
{
public:
	HRESULT init(void);
	void release(void);
	//리소스 로딩 방식만 재정의한다(텍스쳐, 셰이더이펙트)
	LPDIRECT3DTEXTURE9 loadResource(string filePath, void* pParam = NULL) override;
	//리소스 해제 방식만 재정의한다
	void releaseResource(LPDIRECT3DTEXTURE9 data) override;

	rmTexture() {}
	~rmTexture() {}
};

