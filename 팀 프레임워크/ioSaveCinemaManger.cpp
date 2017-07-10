#include "stdafx.h"
#include "ioSaveCinemaManger.h"

void ioSaveCinemaManger::loadFile(string filePath)
{
	tagSaveCinematic cinematic;
	memset(&cinematic, 0, sizeof(cinematic));

	memset(ioString, 0, sizeof(ioString));

	sprintf(ioString, "%s.txt", filePath.c_str());

	char str[128] = "Resource/캐릭터시네마정보/";
	strcat_s(str, ioString);

	ifstream inFile(str);

	assert(!inFile.fail() && "경로에 리소스가 있는지 확인하십시오.");

	inFile.getline(str, 128);
	inFile.getline(str, 128);

	count = 0;
	_resourceTable.clear();
	while (!inFile.eof())
	{
		count++;
		inFile.getline(str, 128, '/');	//한글이름(테이블 키)
		cinematic.infoName = str;

		inFile.getline(str, 128, '/');	//넘버값
		cinematic.X = atof(str);

		inFile.getline(str, 128, '/');	//넘버값
		cinematic.Y = atof(str);

		inFile.getline(str, 128, '/');	//넘버값
		cinematic.Z = atof(str);

		inFile.getline(str, 128, '/');	//넘버값
		cinematic.Height = atof(str);

		_resourceTable.insert(make_pair(cinematic.infoName, cinematic));
	}
	inFile.close();
}

void ioSaveCinemaManger::saveFile(string filePath, vector<tagSaveCinematic>& vecT)
{
	memset(ioString, 0, sizeof(ioString));

	sprintf(ioString, "%s.txt", filePath.c_str());

	char str[128] = "Resource/캐릭터시네마정보/";
	strcat_s(str, ioString);

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
			<< vecT[i].Height << endl;
		else
			outFile << '/'
			<< vecT[i].infoName.c_str() << '/'
			<< vecT[i].X << '/'
			<< vecT[i].Y << '/'
			<< vecT[i].Z << '/'
			<< vecT[i].Height << endl;
	}
	outFile.close();
}
