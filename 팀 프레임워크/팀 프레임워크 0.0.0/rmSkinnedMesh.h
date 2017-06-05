#pragma once
#include "resourceManager.h"
#include "xMeshSkinned.h"

class rmSkinnedMesh : public resourceManager <xMeshSkinned*, rmSkinnedMesh>
{
public:
	HRESULT init(void);
	void release(void);
	//리소스 로딩 방식만 재정의한다(텍스쳐, 셰이더이펙트)
	xMeshSkinned* loadResource(string filePath, void* pParam = NULL) override;
	//리소스 해제 방식만 재정의한다
	void releaseResource(xMeshSkinned* data) override;

	rmSkinnedMesh() {}
	~rmSkinnedMesh() {}
};

