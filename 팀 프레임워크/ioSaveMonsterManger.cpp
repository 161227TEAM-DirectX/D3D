#include "stdafx.h"
#include "ioSaveMonsterManger.h"

void ioSaveMonsterManger::loadFile(string filePath)
{
	tagSaveMonster monster;
	memset(&monster, 0, sizeof(monster));

	memset(ioString, 0, sizeof(ioString));

	sprintf_s(ioString, "%s.map", filePath.c_str());

	ifstream inFile(ioString);

	assert(!inFile.fail() && "��ο� ���ҽ��� �ִ��� Ȯ���Ͻʽÿ�.");

	inFile.getline(ioString, 128);
	inFile.getline(ioString, 128);

	count = 0;
	while (!inFile.eof())
	{
		count++;
		inFile.getline(ioString, 128, '/');	//�ѱ��̸�(���̺� Ű)
		monster.infoName = ioString;

		inFile.getline(ioString, 128, '/');	//���� �ѹ�
		monster.monsterNumber = atof(ioString);

		inFile.getline(ioString, 128, '/');	//���� x
		monster.monsterX = atof(ioString);

		inFile.getline(ioString, 128, '/');	//���� y
		monster.monsterY = atof(ioString);

		inFile.getline(ioString, 128, '/');	//����  z
		monster.monsterZ = atof(ioString);

		inFile.getline(ioString, 128, '/');	//���� ������
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
