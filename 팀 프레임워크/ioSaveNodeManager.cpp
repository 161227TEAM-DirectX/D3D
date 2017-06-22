#include "stdafx.h"
#include "ioSaveNodeManager.h"


void ioSaveNodeManager::loadFile(string filePath)
{
	tagSaveNode node;
	memset(&node, 0, sizeof(node));

	memset(ioString, 0, sizeof(ioString));

	sprintf_s(ioString, "%s.map", filePath.c_str());

	ifstream inFile(ioString);

	assert(!inFile.fail() && "경로에 리소스가 있는지 확인하십시오.");

	inFile.getline(ioString, 128);
	inFile.getline(ioString, 128);

	count = 0;
	while (!inFile.eof())
	{
		count++;
		memset(&node, 0, sizeof(node));
		inFile.getline(ioString, 128, '/');	//한글이름(테이블 키)
		node.infoName = ioString;

		inFile.getline(ioString, 128, '/');	
		node.Inumber = atof(ioString);

		inFile.getline(ioString, 128, '/');	
		node.nodeX = atof(ioString);

		inFile.getline(ioString, 128, '/');	
		node.nodeY = atof(ioString);

		inFile.getline(ioString, 128, '/');	
		node.nodeZ = atof(ioString);

		inFile.getline(ioString, 128, '/');
		node.nodeFSSize = atoi(ioString);
		node.nodeFS.resize(node.nodeFSSize);
		for (int i = 0; i < node.nodeFS.size(); i++)
		{
			inFile.getline(ioString, 128, '/');
			node.nodeFS[i].first = atoi(ioString);
			inFile.getline(ioString, 128, '/');
			node.nodeFS[i].second = atof(ioString);
		}

		_resourceTable.insert(make_pair(node.infoName, node));
	}
	inFile.close();
}

void ioSaveNodeManager::saveFile(string filePath, vector<tagSaveNode>& vecT)
{
	memset(ioString, 0, sizeof(ioString));

	sprintf_s(ioString, "%s.map", filePath.c_str());

	ofstream outFile(ioString);
	outFile << "노드" << endl << endl;

	for (int i = 0; i < vecT.size(); i++)
	{
		if (i == 0)
		{
			outFile
				<< vecT[i].infoName.c_str() << '/'
				<< vecT[i].Inumber << '/'
				<< vecT[i].nodeX << '/'
				<< vecT[i].nodeY << '/'
				<< vecT[i].nodeZ << '/'
				<< vecT[i].nodeFSSize << '/';
			for (int j = 0; j < vecT[i].nodeFS.size(); j++)
			{
				if (j == vecT[i].nodeFS.size() - 1)
				{
					outFile
						<< vecT[i].nodeFS[j].first << '/'
						<< vecT[i].nodeFS[j].second << endl;
					break;
				}
				outFile
					<< vecT[i].nodeFS[j].first << '/'
					<< vecT[i].nodeFS[j].second << '/';
			}
		}
		
		else
		{
			outFile << '/'
				<< vecT[i].infoName.c_str() << '/'
				<< vecT[i].Inumber << '/'
				<< vecT[i].nodeX << '/'
				<< vecT[i].nodeY << '/'
				<< vecT[i].nodeZ << '/'
				<< vecT[i].nodeFS.size() << '/';
			for (int j = 0; j < vecT[i].nodeFS.size(); j++)
			{
				if (j == vecT[i].nodeFS.size() - 1)
				{
					outFile
						<< vecT[i].nodeFS[j].first << '/'
						<< vecT[i].nodeFS[j].second << endl;
					break;
				}
				outFile
					<< vecT[i].nodeFS[j].first << '/'
					<< vecT[i].nodeFS[j].second << '/';
			}
		}		
	}
	outFile.close();
}
