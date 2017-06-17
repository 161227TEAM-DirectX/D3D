#include "stdafx.h"
#include "ioHeightManager.h"


ioHeightManager::ioHeightManager()
{
}


ioHeightManager::~ioHeightManager()
{
}

void ioHeightManager::loadFile(string filePath)
{
}

vector<D3DXVECTOR3> ioHeightManager::loadHeight(string filePath)
{
	vector<D3DXVECTOR3> vecTemp;
	D3DXVECTOR3 temp;

	memset(ioString, 0, sizeof(ioString));

	sprintf_s(ioString, "%s.txt", filePath.c_str());

	ifstream inFile(ioString);

	if (inFile.fail())
	{
		exit(0);
	}

	while (!inFile.eof())
	{
		inFile.getline(ioString, 128, '/');		//x
		temp.x = atoi(ioString);

		inFile.getline(ioString, 128, '/');		//y
		temp.y = atoi(ioString);

		inFile.getline(ioString, 128, '/');		//z
		temp.z = atoi(ioString);

		vecTemp.push_back(temp);
	}

	return vecTemp;
}

void ioHeightManager::saveFile(string filePath, vector<D3DXVECTOR3>& vecT)
{
	memset(ioString, 0, sizeof(ioString));

	sprintf_s(ioString, "%s.txt", filePath.c_str());

	ofstream outFile(ioString);

	for (int i = 0; i < vecT.size(); i++)
	{
		outFile
			<< vecT[i].x << '/'
			<< vecT[i].y << '/'
			<< vecT[i].z << '/' << endl;
	}

	outFile.close();
}
