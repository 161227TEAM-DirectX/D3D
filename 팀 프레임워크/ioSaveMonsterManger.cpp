#include "stdafx.h"
#include "ioSaveMonsterManger.h"

void ioSaveMonsterManger::loadFile(string filePath)
{
	tagSaveMonster monster;
	memset(&monster, 0, sizeof(monster));

	memset(ioString, 0, sizeof(ioString));

	sprintf_s(ioString, "%s.map", filePath.c_str());

	char str[128] = "Resource/��������/";
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
		monster.infoName = str;

		inFile.getline(str, 128, '/');	//���� �ѹ�
		monster.monsterNumber = atof(str);

		inFile.getline(str, 128, '/');	//���� x
		monster.monsterX = atof(str);

		inFile.getline(str, 128, '/');	//���� y
		monster.monsterY = atof(str);

		inFile.getline(str, 128, '/');	//����  z
		monster.monsterZ = atof(str);

		inFile.getline(str, 128, '/');	//���� ������
		monster.scale = atof(str);

		_resourceTable.insert(make_pair(monster.infoName, monster));
	}
	inFile.close();
}

void ioSaveMonsterManger::saveFile(string filePath, vector<tagSaveMonster>& vecT)
{
	memset(ioString, 0, sizeof(ioString));

	sprintf_s(ioString, "%s.map", filePath.c_str());

	char str[128] = "Resource/��������/";
	strcat_s(str, ioString);

	ofstream outFile(str);
	outFile << "�ѱ��̸�" << '/' << "���ͳҹ�" << '/' << "����x" << '/' << "����y" << '/' << "����z" << '/' << "���ͽ�����" << endl << endl;

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
