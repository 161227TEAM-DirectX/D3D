#pragma once

class boundBox;
class baseObject;

class xMesh
{
public:
	virtual HRESULT init(string filePath, D3DXMATRIXA16* matCorrection = NULL) = 0;
	virtual void release(void) = 0;
	virtual void render(dx::transform* trans) = 0;
	xMesh() {}
	~xMesh() {}
};

