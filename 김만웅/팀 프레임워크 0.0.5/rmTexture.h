#pragma once
#include "resourceManager.h"
class rmTexture : public resourceManager <LPDIRECT3DTEXTURE9, rmTexture>
{
public:
	HRESULT init(void);
	void release(void);
	//���ҽ� �ε� ��ĸ� �������Ѵ�(�ؽ���, ���̴�����Ʈ)
	LPDIRECT3DTEXTURE9 loadResource(string filePath, void* pParam = NULL) override;
	//���ҽ� ���� ��ĸ� �������Ѵ�
	void releaseResource(LPDIRECT3DTEXTURE9 data) override;

	rmTexture() {}
	~rmTexture() {}
};

