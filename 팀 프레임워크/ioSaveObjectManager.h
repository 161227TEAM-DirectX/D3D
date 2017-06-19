#pragma once
#include "ioBaseManager.h"

struct tagSaveObject;

class ioSaveObjectManager : public ioBaseManager<tagSaveObject, ioSaveObjectManager>
{
private:
	int count;

public:

	int getCount(void) { return count; }

	ioSaveObjectManager() {}
	~ioSaveObjectManager() {}

	void loadFile(string filePath) override;
	void saveFile(string filePath, vector<tagSaveObject>& vecT) override;

};

