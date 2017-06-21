#pragma once
#include "ioBaseManager.h"

struct tagSaveNode;

class ioSaveNodeManager : public ioBaseManager<tagSaveNode, ioSaveNodeManager>
{
private:
	int count;

public:

	int getCount(void) { return count; }

	ioSaveNodeManager() {}
	~ioSaveNodeManager() {}

	void loadFile(string filePath) override;
	void saveFile(string filePath, vector<tagSaveNode>& vecT) override;

};
