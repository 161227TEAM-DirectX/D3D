#pragma once

class Action;
class terrain;
class baseObject;

#define ACMANAGER ActionManager::GetInstance()

class ActionManager
{
private:
	typedef map<string, Action*> MAP_ACTION;
	typedef map<string, Action*>::iterator MAP_ACTION_ITER;
private:
	MAP_ACTION actionMap;
	MAP_ACTION_ITER actionMapIter;
	terrain* land;
	vector<baseObject*> objectVector;
	baseObject* player;
	vector<baseObject*> monsterVector;
	baseObject* singleMonster;
public:
	ActionManager();
	~ActionManager();

	//지형, 오브젝트벡터, 플레이어, 몬스터
	void Init(terrain& temp, vector<baseObject*>& object, baseObject& player, baseObject& monster)
	{
		linkTerrain(temp);
		linkObjectVector(object);
		linkPlayer(player);
		linkMonster(monster);
	}
	//지형, 오브젝트벡터, 플레이어, 몬스터벡터
	void Init(terrain& temp, vector<baseObject*>& object, baseObject& player, vector<baseObject*>& monster)
	{
		linkTerrain(temp);
		linkObjectVector(object);
		linkPlayer(player);
		linkMonsterVector(monster);
	}

	void linkTerrain(terrain& temp) { this->land = &temp; }
	void linkObjectVector(vector<baseObject*>& temp) { objectVector = temp; }
	void linkPlayer(baseObject& temp) { this->player = &temp; }
	void linkMonster(baseObject& temp) { this->singleMonster = &temp; }
	void linkMonsterVector(vector<baseObject*>& temp) { this->monsterVector = temp; }

	Action* getAction(string);
	void clearAction(void);

public:
	SINGLETWO(ActionManager);
};

