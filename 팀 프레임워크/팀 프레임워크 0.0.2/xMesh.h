#pragma once

class boundBox;
class baseObject;

class xMesh
{
protected:
	float scale;
	string filePath;
public:
	virtual HRESULT init(string filePath, D3DXMATRIXA16* matCorrection = NULL) = 0;
	virtual void release(void) = 0;
	virtual void render(dx::transform* trans) = 0;

	float& getScale(void) { return scale; }
	void setScale(const float& scale) { this->scale = scale; }

	string& getFilePath(void) { return filePath; }
	xMesh() {}
	~xMesh() {}
};

