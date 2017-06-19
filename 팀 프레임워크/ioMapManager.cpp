#include "stdafx.h"
#include "ioMapManager.h"


ioMapManager::ioMapManager()
{
}


ioMapManager::~ioMapManager()
{
}

void ioMapManager::loadFile(string filePath)
{
}

void ioMapManager::saveFile(string filePath, vector<ST_MAP>& vecT)
{
}

void ioMapManager::saveFile(string filePath, ST_MAP & stT)
{
	memset(ioString, 0, sizeof(ioString));

	sprintf_s(ioString, "%s.txt", filePath.c_str());

	char str[128] = "Resource/맵정보/";
	strcat_s(str, ioString);

	ofstream outFile(str);

	outFile << stT.heightMap << endl;	//높이맵
	outFile << stT.splat << endl;		//스플랫팅
	outFile << stT.tile0 << endl;		//타일0
	outFile << stT.tile1 << endl;		//타일1
	outFile << stT.tile2 << endl;		//타일2
	outFile << stT.tile3 << endl;		//타일3

	for (int i=0; i < stT.vecPos.size(); i++)
	{
		outFile <<
			stT.vecPos[i].x << '/' <<
			stT.vecPos[i].y << '/' <<
			stT.vecPos[i].z << '/' <<
			endl;
	}

	outFile.close();
}

ST_MAP ioMapManager::loadMapInfo(string filePath)
{
	ST_MAP temp;
	vector<D3DXVECTOR3> vecTemp;
	D3DXVECTOR3 vec;

	memset(ioString, 0, sizeof(ioString));

	sprintf_s(ioString, "%s.txt", filePath.c_str());

	char str[128] = "Resource/맵정보/";
	strcat_s(str, ioString);

	ifstream inFile(str);

	assert(!inFile.fail() && "경로에 리소스가 있는지 확인하십시오.");

	inFile.getline(str, 128);	//높이맵
	temp.heightMap = str;

	inFile.getline(str, 128);	//스플랫
	temp.splat = str;

	inFile.getline(str, 128);	//타일0
	temp.tile0 = str;

	inFile.getline(str, 128);	//타일1
	temp.tile1 = str;

	inFile.getline(str, 128);	//타일2
	temp.tile2 = str;

	inFile.getline(str, 128);	//타일3
	temp.tile3 = str;

	while (!inFile.eof())
	{
		inFile.getline(str, 128, '/');		//x
		vec.x = atoi(str);

		inFile.getline(str, 128, '/');		//y
		vec.y = atoi(str);

		inFile.getline(str, 128, '/');		//z
		vec.z = atoi(str);

		vecTemp.push_back(vec);
	}
	temp.vecPos = vecTemp;

	inFile.close();

	return temp;
}
