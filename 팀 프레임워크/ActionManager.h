#pragma once

class Action;
class terrain;
class baseObject;

#define ACMANAGER ActionManager::GetInstance()

class ActionManager
{
private:
	vector<string> actionName;
	terrain* land;
	vector<baseObject*> objectVector;
	baseObject* player;
public:
	ActionManager();
	~ActionManager();

	//����, ������Ʈ����, �÷��̾�, ���ͺ���
	void Init(terrain& temp, vector<baseObject*>& object, baseObject& player)
	{
		linkTerrain(temp);
		linkObjectVector(object);
		linkPlayer(player);
	}

	void linkTerrain(terrain& temp) { this->land = &temp; }
	void linkObjectVector(vector<baseObject*>& temp) { objectVector = temp; }
	void linkPlayer(baseObject& temp) { this->player = &temp; }

	Action* getAction(string, baseObject&);
	void clearAction(void);

public:
	SINGLETWO(ActionManager);
};

