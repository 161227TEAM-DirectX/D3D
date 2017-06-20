#include "stdafx.h"
#include "ioSaveManager.h"

void ioSaveManager::loadFile(string filePath)
{
	tagSaveMap object;
	memset(&object, 0, sizeof(object));

	memset(ioString, 0, sizeof(ioString));

	sprintf_s(ioString, "%s.txt", filePath.c_str());

	ifstream inFile(ioString);

	assert(!inFile.fail() && "경로에 리소스가 있는지 확인하십시오.");

	inFile.getline(ioString, 128);
	inFile.getline(ioString, 128);

	while(!inFile.eof())
	{
		inFile.getline(ioString, 128, '/');	//한글이름(테이블 키)
		object.infoName = ioString;

		inFile.getline(ioString, 128, '/');	//넘버값
		object.number = atoi(ioString);

		inFile.getline(ioString, 128, '/');	//넘버값
		object.mapHeight = atof(ioString);

		_resourceTable.insert(make_pair(object.infoName, object));
	}
	inFile.close();
}

void ioSaveManager::saveFile(string filePath, vector<tagSaveMap>& vecT)
{
	memset(ioString, 0, sizeof(ioString));

	sprintf_s(ioString, "%s.txt", filePath.c_str());

	ofstream outFile(ioString);
	outFile << "한글이름" << '/' << "넘버값" << '/' << "높이값" << endl << endl;

	for(int i = 0; i < vecT.size(); i++)
	{
		if(i == 0)
			outFile
			<< vecT[i].infoName.c_str() << '/'
			<< vecT[i].number << '/'
			<< vecT[i].mapHeight << endl;
		else
			outFile << '/'
			<< vecT[i].infoName.c_str() << '/'
			<< vecT[i].number << '/'
			<< vecT[i].mapHeight << endl;
	}
	outFile.close();
}
