#pragma once
#include "ioBaseManager.h"

struct tagSaveMonster;

class ioSaveMonsterManger : public ioBaseManager<tagSaveMonster, ioSaveMonsterManger>
{
private:
	int count;

public:

	int getCount(void) { return count; }

	ioSaveMonsterManger() {}
	~ioSaveMonsterManger() {}

	void loadFile(string filePath) override;
	void saveFile(string filePath, vector<tagSaveMonster>& vecT) override;
};