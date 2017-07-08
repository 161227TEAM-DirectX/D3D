#pragma once
#include "ioBaseManager.h"

struct tagSaveEndingCinematic;

class ioSaveEndingManager : public ioBaseManager<tagSaveEndingCinematic, ioSaveEndingManager>
{
private:
	int count;
public:

	ioSaveEndingManager() {}
	~ioSaveEndingManager() {}

	int getCount(void) { return count; }

	void loadFile(string filePath) override;
	void saveFile(string filePath, vector<tagSaveEndingCinematic>& vecT) override;
};

