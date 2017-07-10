#include "stdafx.h"
#include "ioSaveObjectManager.h"

void ioSaveObjectManager::loadFile(string filePath)
{


	tagSaveObject object;
	memset(&object, 0, sizeof(object));

	memset(ioString, 0, sizeof(ioString));

	sprintf_s(ioString, "%s.txt", filePath.c_str());

	char str[128] = "Resource/������/";
	strcat_s(str, ioString);

	ifstream inFile(str);

	assert(!inFile.fail() && "��ο� ������Ʈ.txt ���ҽ��� �ִ��� Ȯ���Ͻʽÿ�.");

	inFile.getline(str, 128);
	inFile.getline(str, 128);
	
	_resourceTable.clear();
	count = 0;

	while(!inFile.eof())
	{
		count++;
		inFile.getline(str, 128, '/');	//�ѱ��̸�(���̺� Ű)
		object.infoName = str;

		inFile.getline(str, 128, '/');	//������Ʈ �ѹ�
		object.objectNumber = atof(str);

		inFile.getline(str, 128, '/');	//������Ʈ �����̼�
		object.objectRotate = atof(str);

		inFile.getline(str, 128, '/');	//������Ʈ ������
		object.objectScale = atof(str);

		inFile.getline(str, 128, '/');	//������Ʈ x
		object.objectX = atof(str);

		inFile.getline(str, 128, '/');	//������Ʈ y
		object.objectY = atof(str);

		inFile.getline(str, 128, '/');	//������Ʈ z
		object.objectZ = atof(str);

		_resourceTable.insert(make_pair(object.infoName, object));
	}
	inFile.close();
}

void ioSaveObjectManager::saveFile(string filePath, vector<tagSaveObject>& vecT)
{
	memset(ioString, 0, sizeof(ioString));

	sprintf_s(ioString, "%s.txt", filePath.c_str());


	char str[128] = "Resource/������/";
	strcat_s(str, ioString);

	ofstream outFile(str);
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
