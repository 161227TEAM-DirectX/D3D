#pragma once
#include "ioBaseManager.h"

struct tagSaveName;

class ioSaveNameManager : public ioBaseManager<tagSaveName, ioSaveNameManager>
{
public:
	ioSaveNameManager() {}
	~ioSaveNameManager() {}

	void loadFile(string filePath) override;
	void saveFile(string filePath, vector<tagSaveName>& vecT) override;
};
