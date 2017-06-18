#pragma once
#include "ioBaseManager.h"

class ioHeightManager : public ioBaseManager<D3DXVECTOR3, ioHeightManager>
{
public:
	ioHeightManager();
	~ioHeightManager();

	void loadFile(string filePath) override;
	vector<D3DXVECTOR3> loadHeight(string filePath);
	void saveFile(string filePath, vector<D3DXVECTOR3>& vecT) override;
};

