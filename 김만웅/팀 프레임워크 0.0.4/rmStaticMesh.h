#pragma once
#include "resourceManager.h"
#include "xMeshStatic.h"

class rmStaticMesh : public resourceManager <xMeshStatic*, rmStaticMesh>
{
public:
	HRESULT init(void);
	void release(void);
	//���ҽ� �ε� ��ĸ� �������Ѵ�(�ؽ���, ���̴�����Ʈ)
	xMeshStatic* loadResource(string filePath, void* pParam = NULL) override;
	//���ҽ� ���� ��ĸ� �������Ѵ�
	void releaseResource(xMeshStatic* data) override;

	rmStaticMesh() {}
	~rmStaticMesh() {}
};

