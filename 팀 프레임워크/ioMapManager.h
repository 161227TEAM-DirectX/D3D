#pragma once
#include "ioBaseManager.h"

struct ST_MAP;

class ioMapManager : public ioBaseManager<ST_MAP, ioMapManager>
{
public:
	ioMapManager();
	~ioMapManager();

	void loadFile(string filePath) override;
	void saveFile(string filePath, vector<ST_MAP>& vecT) override;

	void saveFile(string filePath, ST_MAP& stT);
	ST_MAP loadMapInfo(string filePath);
};

