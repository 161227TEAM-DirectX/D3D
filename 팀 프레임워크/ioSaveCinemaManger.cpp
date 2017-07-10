#include "stdafx.h"
#include "ioSaveCinemaManger.h"

void ioSaveCinemaManger::loadFile(string filePath)
{
	tagSaveCinematic cinematic;
	memset(&cinematic, 0, sizeof(cinematic));

	memset(ioString, 0, sizeof(ioString));

	sprintf(ioString, "%s.txt", filePath.c_str());

	char str[128] = "Resource/ĳ���ͽó׸�����/";
	strcat_s(str, ioString);

	ifstream inFile(str);

	assert(!inFile.fail() && "��ο� ���ҽ��� �ִ��� Ȯ���Ͻʽÿ�.");

	inFile.getline(str, 128);
	inFile.getline(str, 128);

	count = 0;
	_resourceTable.clear();
	while (!inFile.eof())
	{
		count++;
		inFile.getline(str, 128, '/');	//�ѱ��̸�(���̺� Ű)
		cinematic.infoName = str;

		inFile.getline(str, 128, '/');	//�ѹ���
		cinematic.X = atof(str);

		inFile.getline(str, 128, '/');	//�ѹ���
		cinematic.Y = atof(str);

		inFile.getline(str, 128, '/');	//�ѹ���
		cinematic.Z = atof(str);

		inFile.getline(str, 128, '/');	//�ѹ���
		cinematic.Height = atof(str);

		_resourceTable.insert(make_pair(cinematic.infoName, cinematic));
	}
	inFile.close();
}

void ioSaveCinemaManger::saveFile(string filePath, vector<tagSaveCinematic>& vecT)
{
	memset(ioString, 0, sizeof(ioString));

	sprintf(ioString, "%s.txt", filePath.c_str());

	char str[128] = "Resource/ĳ���ͽó׸�����/";
	strcat_s(str, ioString);

	ofstream outFile(str);
	outFile << "�ѱ��̸�" << '/' << "X" << '/' << "Y" << '/' << "Z" << endl << endl;

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
