#pragma once
#include "resourceManager.h"
#include "xMeshSkinned.h"

class rmSkinnedMesh : public resourceManager <xMeshSkinned*, rmSkinnedMesh>
{
public:
	HRESULT init(void);
	void release(void);
	//���ҽ� �ε� ��ĸ� �������Ѵ�(�ؽ���, ���̴�����Ʈ)
	xMeshSkinned* loadResource(string filePath, void* pParam = NULL) override;
	//���ҽ� ���� ��ĸ� �������Ѵ�
	void releaseResource(xMeshSkinned* data) override;

	rmSkinnedMesh() {}
	~rmSkinnedMesh() {}
};

