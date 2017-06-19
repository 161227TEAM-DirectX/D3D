#include "stdafx.h"
#include "ioSaveObjectManager.h"

void ioSaveObjectManager::loadFile(string filePath)
{
	tagSaveObject object;
	memset(&object, 0, sizeof(object));

	memset(ioString, 0, sizeof(ioString));

	sprintf_s(ioString, "%s.txt", filePath.c_str());

	ifstream inFile(ioString);

	assert(!inFile.fail() && "��ο� ���ҽ��� �ִ��� Ȯ���Ͻʽÿ�.");

	inFile.getline(ioString, 128);
	inFile.getline(ioString, 128);

	count = 0;
	while(!inFile.eof())
	{
		count++;
		inFile.getline(ioString, 128, '/');	//�ѱ��̸�(���̺� Ű)
		object.infoName = ioString;

		inFile.getline(ioString, 128, '/');	//������Ʈ �ѹ�
		object.objectNumber = atof(ioString);

		inFile.getline(ioString, 128, '/');	//������Ʈ �����̼�
		object.objectRotate = atof(ioString);

		inFile.getline(ioString, 128, '/');	//������Ʈ ������
		object.objectScale = atof(ioString);

		inFile.getline(ioString, 128, '/');	//������Ʈ x
		object.objectX = atof(ioString);

		inFile.getline(ioString, 128, '/');	//������Ʈ y
		object.objectY = atof(ioString);

		inFile.getline(ioString, 128, '/');	//������Ʈ z
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
	outFile << "�ѱ��̸�" << '/' << "������Ʈ�ѹ�" << '/' << "�����̼�" << '/' << "������" << '/' << "X" << '/' << "Y" << '/' << "Z" << '/' << "����" << endl << endl;

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
