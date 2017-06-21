#include "stdafx.h"
#include "ioSaveMonsterManger.h"

void ioSaveMonsterManger::loadFile(string filePath)
{
	tagSaveMonster monster;
	memset(&monster, 0, sizeof(monster));

	memset(ioString, 0, sizeof(ioString));

	sprintf_s(ioString, "%s.map", filePath.c_str());

	ifstream inFile(ioString);

	assert(!inFile.fail() && "경로에 리소스가 있는지 확인하십시오.");

	inFile.getline(ioString, 128);
	inFile.getline(ioString, 128);

	count = 0;
	while (!inFile.eof())
	{
		count++;
		inFile.getline(ioString, 128, '/');	//한글이름(테이블 키)
		monster.infoName = ioString;

		inFile.getline(ioString, 128, '/');	//몬스터 넘버
		monster.monsterNumber = atof(ioString);

		inFile.getline(ioString, 128, '/');	//몬스터 x
		monster.monsterX = atof(ioString);

		inFile.getline(ioString, 128, '/');	//몬스터 y
		monster.monsterY = atof(ioString);

		inFile.getline(ioString, 128, '/');	//몬스터  z
		monster.monsterZ = atof(ioString);

		inFile.getline(ioString, 128, '/');	//몬스터 스케일
		monster.scale = atof(ioString);

		_resourceTable.insert(make_pair(monster.infoName, monster));
	}
	inFile.close();
}

void ioSaveMonsterManger::saveFile(string filePath, vector<tagSaveMonster>& vecT)
{
	memset(ioString, 0, sizeof(ioString));

	sprintf_s(ioString, "%s.map", filePath.c_str());

	ofstream outFile(ioString);
	outFile << "한글이름" << '/' << "몬스터넙버" << '/' << "몬스터x" << '/' << "몬스터y" << '/' << "몬스터z" << '/' << "몬스터스케일" << endl << endl;

	for (int i = 0; i < vecT.size(); i++)
	{
		if (i == 0)
			outFile
			<< vecT[i].infoName.c_str() << '/'
			<< vecT[i].monsterNumber << '/'
			<< vecT[i].monsterX << '/'
			<< vecT[i].monsterY << '/'
			<< vecT[i].monsterZ << '/'
			<< vecT[i].scale << endl;
		else
			outFile << '/'
			<< vecT[i].infoName.c_str() << '/'
			<< vecT[i].monsterNumber << '/'
			<< vecT[i].monsterX << '/'
			<< vecT[i].monsterY << '/'
			<< vecT[i].monsterZ << '/'
			<< vecT[i].scale << endl;
	}
	outFile.close();
}
