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

	char str[128] = "Resource/������/";
	strcat_s(str, ioString);

	ofstream outFile(str);

	outFile << stT.heightMap << endl;	//���̸�
	outFile << stT.splat << endl;		//���÷���
	outFile << stT.tile0 << endl;		//Ÿ��0
	outFile << stT.tile1 << endl;		//Ÿ��1
	outFile << stT.tile2 << endl;		//Ÿ��2
	outFile << stT.tile3 << endl;		//Ÿ��3

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

	char str[128] = "Resource/������/";
	strcat_s(str, ioString);

	ifstream inFile(str);

	assert(!inFile.fail() && "��ο� ���ҽ��� �ִ��� Ȯ���Ͻʽÿ�.");

	inFile.getline(str, 128);	//���̸�
	temp.heightMap = str;

	inFile.getline(str, 128);	//���÷�
	temp.splat = str;

	inFile.getline(str, 128);	//Ÿ��0
	temp.tile0 = str;

	inFile.getline(str, 128);	//Ÿ��1
	temp.tile1 = str;

	inFile.getline(str, 128);	//Ÿ��2
	temp.tile2 = str;

	inFile.getline(str, 128);	//Ÿ��3
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
