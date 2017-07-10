#pragma once
#include "ioBaseManager.h"
class ioSaveMonsterBoxManager : public ioBaseManager<tagSaveMonsterBoundBox, ioSaveMonsterBoxManager>
{
private:
public:
	ioSaveMonsterBoxManager();
	~ioSaveMonsterBoxManager();

	void loadFile(string filePath) override;
	void saveFile(string filePath, vector<tagSaveMonsterBoundBox>& vecT) override;
};

