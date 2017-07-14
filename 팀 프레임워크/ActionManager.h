#pragma once

class Action;
class terrain;
class baseObject;
class xPlayer;
class camera;

#define ACMANAGER ActionManager::GetInstance()

class ActionManager
{
private:
	vector<string> actionName;
	terrain* land;
	vector<baseObject*>* objectVector;
	vector<baseObject*> tempObjectVector;
	xPlayer*	player;
	camera* mainCamera;
public:
	ActionManager();
	~ActionManager();

	//����, ������Ʈ����, �÷��̾�, ���ͺ���
	void Init(terrain& temp, vector<baseObject*>& object, xPlayer& player)
	{
		linkTerrain(temp);
		linkObjectVector(object);
		linkPlayer(player);
	}

	//���� ������Ʈ����, �÷��̾�, ����ī�޶�
	void Init(terrain& temp, xPlayer& player, camera& mainCamera)
	{
		linkTerrain(temp);
		linkPlayer(player);
		linkCamera(mainCamera);
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
	void linkCamera(camera& temp) { this->mainCamera = &temp; }
	Action* getAction(string, baseObject&);
	void clearAction(void);

public:
	SINGLETWO(ActionManager);
};

