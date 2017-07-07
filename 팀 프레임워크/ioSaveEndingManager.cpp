#include "stdafx.h"
#include "ioSaveEndingManager.h"

void ioSaveEndingManager::loadFile(string filePath)
{
	tagSaveEndingCinematic Einematic;
	memset(&Einematic, 0, sizeof(Einematic));

	memset(ioString, 0, sizeof(ioString));

	sprintf(ioString, "%s.txt", filePath.c_str());

	char str[128] = "Resource/엔딩시네마정보/";
	strcat_s(str, ioString);

	ifstream inFile(str);

	assert(!inFile.fail() && "경로에 리소스가 있는지 확인하십시오.");

	inFile.getline(str, 128);
	inFile.getline(str, 128);

	count = 0;
	while (!inFile.eof())
	{
		count++;
		inFile.getline(str, 128, '/');	//한글이름(테이블 키)
		Einematic.infoName = str;

		inFile.getline(str, 128, '/');	//넘버값
		Einematic.X = atof(str);

		inFile.getline(str, 128, '/');	//넘버값
		Einematic.Y = atof(str);

		inFile.getline(str, 128, '/');	//넘버값
		Einematic.Z = atof(str);

		inFile.getline(str, 128, '/');	//넘버값
		Einematic.rotationX = atof(str);

		inFile.getline(str, 128, '/');	//넘버값
		Einematic.rotationY = atof(str);

		inFile.getline(str, 128, '/');	//넘버값
		Einematic.rotationZ = atof(str);

		inFile.getline(str, 128, '/');	//넘버값
		Einematic.EningNumber = atoi(str);

		_resourceTable.insert(make_pair(Einematic.infoName, Einematic));
	}
	inFile.close();
}

void ioSaveEndingManager::saveFile(string filePath, vector<tagSaveEndingCinematic>& vecT)
{
	memset(ioString, 0, sizeof(ioString));

	sprintf(ioString, "%s.txt", filePath.c_str());

	char str[128] = "Resource/엔딩시네마정보/";
	strcat(str, ioString);

	ofstream outFile(str);
	outFile << "한글이름" << '/' << "X" << '/' << "Y" << '/' << "Z" << endl << endl;

	for (int i = 0; i < vecT.size(); i++)
	{
		if (i == 0)
			outFile
			<< vecT[i].infoName.c_str() << '/'
			<< vecT[i].X << '/'
			<< vecT[i].Y << '/'
			<< vecT[i].Z << '/'
			<< vecT[i].rotationX << '/'
			<< vecT[i].rotationY << '/'
			<< vecT[i].rotationZ << '/'
			<< vecT[i].EningNumber << endl;
		else
			outFile << '/'
			<< vecT[i].infoName.c_str() << '/'
			<< vecT[i].X << '/'
			<< vecT[i].Y << '/'
			<< vecT[i].Z << '/'
			<< vecT[i].rotationX << '/'
			<< vecT[i].rotationY << '/'
			<< vecT[i].rotationZ << '/'
			<< vecT[i].EningNumber << endl;
	}
	outFile.close();
}
