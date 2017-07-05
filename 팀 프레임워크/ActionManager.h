#pragma once

class Action;
class terrain;
class baseObject;
class xPlayer;

#define ACMANAGER ActionManager::GetInstance()

class ActionManager
{
private:
	vector<string> actionName;
	terrain* land;
	vector<baseObject*>* objectVector;
	vector<baseObject*> tempObjectVector;
	xPlayer*	player;
public:
	ActionManager();
	~ActionManager();

	//지형, 오브젝트벡터, 플레이어, 몬스터벡터
	void Init(terrain& temp, vector<baseObject*>& object, xPlayer& player)
	{
		linkTerrain(temp);
		linkObjectVector(object);
		linkPlayer(player);
	}

	void Init(terrain& temp, xPlayer& player)
	{
		linkTerrain(temp);
		linkPlayer(player);
	}

	void Init(xPlayer& player)
	{
		linkPlayer(player);
	}

	void linkTerrain(terrain& temp) { this->land = &temp; }
	void linkObjectVector(vector<baseObject*>& temp) { objectVector = &temp; }
	void linkPlayer(xPlayer& temp) { this->player = &temp; }

	Action* getAction(string, baseObject&);
	void clearAction(void);

public:
	SINGLETWO(ActionManager);
};

