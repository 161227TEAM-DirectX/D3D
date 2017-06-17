#pragma once
#include "ioBaseManager.h"

struct tagSaveMap;

class ioSaveManager : public ioBaseManager<tagSaveMap, ioSaveManager>
{
public:
	ioSaveManager(){}
	~ioSaveManager(){}

	void loadFile(string filePath) override;
	void saveFile(string filePath, vector<tagSaveMap>& vecT) override;
};

