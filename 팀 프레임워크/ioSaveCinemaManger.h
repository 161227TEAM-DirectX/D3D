#pragma once
#include "ioBaseManager.h"

struct tagSaveCinematic;

class ioSaveCinemaManger : public ioBaseManager<tagSaveCinematic, ioSaveCinemaManger>
{
private:
	int count;
public:

	ioSaveCinemaManger() {}
	~ioSaveCinemaManger() {}

	int getCount(void) { return count; }

	void loadFile(string filePath) override;
	void saveFile(string filePath, vector<tagSaveCinematic>& vecT) override;
};

