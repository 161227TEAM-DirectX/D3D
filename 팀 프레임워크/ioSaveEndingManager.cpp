#include "stdafx.h"
#include "ioSaveEndingManager.h"

void ioSaveEndingManager::loadFile(string filePath)
{
	tagSaveEndingCinematic Einematic;
	memset(&Einematic, 0, sizeof(Einematic));

	memset(ioString, 0, sizeof(ioString));

	sprintf(ioString, "%s.txt", filePath.c_str());

	char str[128] = "Resource/�����ó׸�����/";
	strcat_s(str, ioString);

	ifstream inFile(str);

	assert(!inFile.fail() && "��ο� ���ҽ��� �ִ��� Ȯ���Ͻʽÿ�.");

	inFile.getline(str, 128);
	inFile.getline(str, 128);

	count = 0;
	while (!inFile.eof())
	{
		count++;
		inFile.getline(str, 128, '/');	//�ѱ��̸�(���̺� Ű)
		Einematic.infoName = str;

		inFile.getline(str, 128, '/');	//�ѹ���
		Einematic.X = atof(str);

		inFile.getline(str, 128, '/');	//�ѹ���
		Einematic.Y = atof(str);

		inFile.getline(str, 128, '/');	//�ѹ���
		Einematic.Z = atof(str);

		inFile.getline(str, 128, '/');	//�ѹ���
		Einematic.rotationX = atof(str);

		inFile.getline(str, 128, '/');	//�ѹ���
		Einematic.rotationY = atof(str);

		inFile.getline(str, 128, '/');	//�ѹ���
		Einematic.rotationZ = atof(str);

		inFile.getline(str, 128, '/');	//�ѹ���
		Einematic.EningNumber = atoi(str);

		_resourceTable.insert(make_pair(Einematic.infoName, Einematic));
	}
	inFile.close();
}

void ioSaveEndingManager::saveFile(string filePath, vector<tagSaveEndingCinematic>& vecT)
{
	memset(ioString, 0, sizeof(ioString));

	sprintf(ioString, "%s.txt", filePath.c_str());

	char str[128] = "Resource/�����ó׸�����/";
	strcat(str, ioString);

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
