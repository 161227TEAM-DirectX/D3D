#include "stdafx.h"
#include "ioSaveMonsterBoxManager.h"


ioSaveMonsterBoxManager::ioSaveMonsterBoxManager()
{
}


ioSaveMonsterBoxManager::~ioSaveMonsterBoxManager()
{
}

void ioSaveMonsterBoxManager::loadFile(string filePath)
{
	tagSaveMonsterBoundBox monster;

	memset(&monster, 0, sizeof(monster));

	memset(ioString, 0, sizeof(ioString));

	sprintf_s(ioString, "%s.map", filePath.c_str());

	char str[256] = "Resource/��������/";
	strcat_s(str, ioString);

	ifstream inFile(str);

	assert(!inFile.fail() && "��ο� ���ҽ��� �ִ��� Ȯ���Ͻʽÿ�.");

	while (!inFile.eof())
	{
		inFile.getline(str, 256, '/');	//�ѱ��̸�(���̺� Ű)
		monster.Name = str;

		inFile.getline(str, 256, '/');	//���� x��ǥ
		monster.localCenter.x = atof(str);
		inFile.getline(str, 256, '/');	//���� y��ǥ
		monster.localCenter.y = atof(str);
		inFile.getline(str, 256, '/');	//���� z��ǥ
		monster.localCenter.z = atof(str);

		inFile.getline(str, 256, '/');	//�ּ� x��ǥ
		monster.localMinPos.x = atof(str);
		inFile.getline(str, 256, '/');	//�ּ� y��ǥ
		monster.localMinPos.y = atof(str);
		inFile.getline(str, 256, '/');	//�ּ� z��ǥ
		monster.localMinPos.z = atof(str);

		inFile.getline(str, 128, '/');	//�ִ� x��ǥ
		monster.localMaxPos.x = atof(str);
		inFile.getline(str, 128, '/');	//�ִ� y��ǥ
		monster.localMaxPos.y = atof(str);
		inFile.getline(str, 128, '/');	//�ִ� z��ǥ
		monster.localMaxPos.z = atof(str);

		inFile.getline(str, 256, '/');	//������ǥ x��ǥ
		monster.halfSize.x = atof(str);
		inFile.getline(str, 256, '/');	//������ǥ y��ǥ
		monster.halfSize.y = atof(str);
		inFile.getline(str, 256, '/');	//������ǥ z��ǥ
		monster.halfSize.z = atof(str);

		inFile.getline(str, 256, '\n');	//���� ������
		monster.radius = atof(str);

		_resourceTable.insert(make_pair(monster.Name, monster));
	}
	inFile.close();
}

void ioSaveMonsterBoxManager::saveFile(string filePath, vector<tagSaveMonsterBoundBox>& vecT)
{
}
