#include "stdafx.h"
#include "ioSaveMonsterBoxManager.h"


ioSaveMonsterBoxManager::ioSaveMonsterBoxManager()
{
}


ioSaveMonsterBoxManager::~ioSaveMonsterBoxManager()
{
}

void ioSaveMonsterBoxManager::loadFile(string filePath)
{
	tagSaveMonsterBoundBox monster;

	memset(&monster, 0, sizeof(monster));

	memset(ioString, 0, sizeof(ioString));

	sprintf_s(ioString, "%s.map", filePath.c_str());

	char str[256] = "Resource/몬스터정보/";
	strcat_s(str, ioString);

	ifstream inFile(str);

	assert(!inFile.fail() && "경로에 리소스가 있는지 확인하십시오.");

	while (!inFile.eof())
	{
		inFile.getline(str, 256, '/');	//한글이름(테이블 키)
		monster.Name = str;

		inFile.getline(str, 256, '/');	//센터 x좌표
		monster.localCenter.x = atof(str);
		inFile.getline(str, 256, '/');	//센터 y좌표
		monster.localCenter.y = atof(str);
		inFile.getline(str, 256, '/');	//센터 z좌표
		monster.localCenter.z = atof(str);

		inFile.getline(str, 256, '/');	//최소 x좌표
		monster.localMinPos.x = atof(str);
		inFile.getline(str, 256, '/');	//최소 y좌표
		monster.localMinPos.y = atof(str);
		inFile.getline(str, 256, '/');	//최소 z좌표
		monster.localMinPos.z = atof(str);

		inFile.getline(str, 128, '/');	//최대 x좌표
		monster.localMaxPos.x = atof(str);
		inFile.getline(str, 128, '/');	//최대 y좌표
		monster.localMaxPos.y = atof(str);
		inFile.getline(str, 128, '/');	//최대 z좌표
		monster.localMaxPos.z = atof(str);

		inFile.getline(str, 256, '/');	//절반좌표 x좌표
		monster.halfSize.x = atof(str);
		inFile.getline(str, 256, '/');	//절반좌표 y좌표
		monster.halfSize.y = atof(str);
		inFile.getline(str, 256, '/');	//절반좌표 z좌표
		monster.halfSize.z = atof(str);

		inFile.getline(str, 256, '\n');	//몬스터 스케일
		monster.radius = atof(str);

		_resourceTable.insert(make_pair(monster.Name, monster));
	}
	inFile.close();
}

void ioSaveMonsterBoxManager::saveFile(string filePath, vector<tagSaveMonsterBoundBox>& vecT)
{
}
