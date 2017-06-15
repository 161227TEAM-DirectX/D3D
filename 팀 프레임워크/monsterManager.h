#pragma once
#include "monster.h"
class monsterManager
{
private:
	vector<baseObject*> monsterList;
	const float SCALE;
public:
	monsterManager();
	~monsterManager();

	void addMonster(int MonsterNum, D3DXVECTOR3 genPos);
	
	vector<baseObject*>& getList(void) { return monsterList; }
};

