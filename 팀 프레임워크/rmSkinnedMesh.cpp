#include "stdafx.h"
#include "rmSkinnedMesh.h"

HRESULT rmSkinnedMesh::init(void)
{
	return S_OK;
}

void rmSkinnedMesh::release(void)
{
}

xMeshSkinned * rmSkinnedMesh::loadResource(string filePath, void * pParam)
{
	xMeshSkinned* pNewMesh = new xMeshSkinned;
	if (FAILED(pNewMesh->init(filePath, (D3DXMATRIXA16*)pParam)))
	{
		SAFE_DELETE(pNewMesh);
		return NULL;
	}

	return pNewMesh;
}

void rmSkinnedMesh::releaseResource(xMeshSkinned * data)
{
	data->release();
	SAFE_DELETE(data);
}
