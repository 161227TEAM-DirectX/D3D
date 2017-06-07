#pragma once
#include "resourceManager.h"

class rmShaderFX : public resourceManager <LPD3DXEFFECT, rmShaderFX>
{
public:
	HRESULT init(void);
	void release(void);
	//���ҽ� �ε� ��ĸ� �������Ѵ�(�ؽ���, ���̴�����Ʈ)
	LPD3DXEFFECT loadResource(string filePath, void* pParam = NULL) override;
	//���ҽ� ���� ��ĸ� �������Ѵ�
	void releaseResource(LPD3DXEFFECT data) override;

	rmShaderFX() {}
	~rmShaderFX() {}
};

