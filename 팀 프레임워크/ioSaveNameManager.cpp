#include "stdafx.h"
#include "ioSaveNameManager.h"

void ioSaveNameManager::loadFile(string filePath)
{
	tagSaveName saveName;
	memset(&saveName, 0, sizeof(saveName));

	memset(ioString, 0, sizeof(ioString));

	sprintf(ioString, "%s.txt", filePath.c_str());

	ifstream inFile(ioString);

	if (inFile.fail())
	{
		exit(0);
	}

	inFile.getline(ioString, 128);
	inFile.getline(ioString, 128);

	while (!inFile.eof())
	{
		inFile.getline(ioString, 128, '/');	//�ѱ��̸�(���̺� Ű)
		saveName.infoName = ioString;

		inFile.getline(ioString, 128, '/');	//�ѹ���
		saveName.chatName = ioString;

		inFile.getline(ioString, 128, '/');	//�ѹ���
		saveName.password = ioString;

		_resourceTable.insert(make_pair(saveName.infoName, saveName));
	}
	inFile.close();
}

void ioSaveNameManager::saveFile(string filePath, vector<tagSaveName>& vecT)
{
	memset(ioString, 0, sizeof(ioString));

	sprintf(ioString, "%s.txt", filePath.c_str());

	ofstream outFile(ioString);
	outFile << "�ѱ��̸�" << '/' << "���̵�" << '/' << "��й�ȣ" << endl << endl;

	for (int i = 0; i < vecT.size(); i++)
	{
		if (i == 0)
			outFile
			<< vecT[i].infoName.c_str() << '/'
			<< vecT[i].chatName.c_str() << '/'
			<< vecT[i].password.c_str() << endl;
		else
			outFile << '/'
			<< vecT[i].infoName.c_str() << '/'
			<< vecT[i].chatName.c_str() << '/'
			<< vecT[i].password.c_str() << endl;
	}
	outFile.close();
}
