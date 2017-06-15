#include "stdafx.h"
#include "monsterManager.h"


monsterManager::monsterManager()
	:SCALE(0.1f)
{
}


monsterManager::~monsterManager()
{
}

void monsterManager::addMonster(int MonsterNum, D3DXVECTOR3 genPos)
{
	D3DXMATRIX matRotate;
	D3DXMatrixRotationY(&matRotate, D3DXToRadian(180));
	monster* temp = new monster;
	temp->_transform->SetScale(SCALE, SCALE, SCALE);
	temp->_transform->SetWorldPosition(genPos);
	temp->setRegenPosition(genPos);
	switch (MonsterNum)
	{
	case 0:
		temp->setMesh(RM_SKINNED->getResource("Resources/Meshes/monster/arcanegolem_ok/x/golem2.x", matRotate));
		
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		break;
	}
}
