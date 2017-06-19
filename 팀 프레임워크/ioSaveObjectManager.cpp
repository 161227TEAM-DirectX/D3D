#include "stdafx.h"
#include "ioSaveObjectManager.h"

void ioSaveObjectManager::loadFile(string filePath)
{
	tagSaveObject object;
	memset(&object, 0, sizeof(object));

	memset(ioString, 0, sizeof(ioString));

	sprintf_s(ioString, "%s.txt", filePath.c_str());

	ifstream inFile(ioString);

	assert(!inFile.fail() && "경로에 리소스가 있는지 확인하십시오.");

	inFile.getline(ioString, 128);
	inFile.getline(ioString, 128);

	count = 0;
	while(!inFile.eof())
	{
		count++;
		inFile.getline(ioString, 128, '/');	//한글이름(테이블 키)
		object.infoName = ioString;

		inFile.getline(ioString, 128, '/');	//오브젝트 넘버
		object.objectNumber = atof(ioString);

		inFile.getline(ioString, 128, '/');	//오브젝트 로테이션
		object.objectRotate = atof(ioString);

		inFile.getline(ioString, 128, '/');	//오브젝트 스케일
		object.objectScale = atof(ioString);

		inFile.getline(ioString, 128, '/');	//오브젝트 x
		object.objectX = atof(ioString);

		inFile.getline(ioString, 128, '/');	//오브젝트 y
		object.objectY = atof(ioString);

		inFile.getline(ioString, 128, '/');	//오브젝트 z
		object.objectZ = atof(ioString);

		_resourceTable.insert(make_pair(object.infoName, object));
	}
	inFile.close();
}

void ioSaveObjectManager::saveFile(string filePath, vector<tagSaveObject>& vecT)
{
	memset(ioString, 0, sizeof(ioString));

	sprintf_s(ioString, "%s.txt", filePath.c_str());

	ofstream outFile(ioString);
	outFile << "한글이름" << '/' << "오브젝트넘버" << '/' << "로테이션" << '/' << "스케일" << '/' << "X" << '/' << "Y" << '/' << "Z" << '/' << "개수" << endl << endl;

	for(int i = 0; i < vecT.size(); i++)
	{
		if(i == 0)
			outFile
			<< vecT[i].infoName.c_str() << '/'
			<< vecT[i].objectNumber << '/'
			<< vecT[i].objectRotate << '/'
			<< vecT[i].objectScale << '/'
			<< vecT[i].objectX << '/'
			<< vecT[i].objectY << '/'
			<< vecT[i].objectZ << endl;
		else
			outFile << '/'
			<< vecT[i].infoName.c_str() << '/'
			<< vecT[i].objectNumber << '/'
			<< vecT[i].objectRotate << '/'
			<< vecT[i].objectScale << '/'
			<< vecT[i].objectX << '/'
			<< vecT[i].objectY << '/'
			<< vecT[i].objectZ << endl;
	}
	outFile.close();
}
