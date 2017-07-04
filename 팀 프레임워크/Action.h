#pragma once

class Action;
class baseObject;
class terrain;
class xPlayer;

class iActionDelegate
{
public:
	//�׼��� ���� �ɶ� ȣ��Ǵ� �Լ� - ��ӹ޴� Ŭ������ ������ �����ؾ� �Ѵ�.
	virtual void OnActionFinish(Action* pSender) = 0;
	virtual void OnActionFinish(Action* pSender, bool isCollision) = 0;
};

class Action
{
protected:
	baseObject*				owner;				// �׼��� ��ü(baseObject)
	iActionDelegate*		deleGate;			// �׼� ����� ȣ��� �Լ��� ���� Ŭ��������
	terrain*				rand;				// �׼� �� �̵� �� ���̰��� �������� ���� ����
	vector<baseObject*>*	object;				// ������Ʈ ����, ��ֹ�
	xPlayer*				enemy;				// �÷��̾� ����
	baseObject*				playerObject;		// �÷��̾� ������Ʈ ����

	float _oldTimeDelta;
	const float Gap;
	const float LENGTHGAP;
	const float PLAYERDISTANCE;
public:
	Action();
	virtual ~Action();
	//������ ��ü ����
	inline baseObject* getOwner(void) { return owner; }
	//������ ��ü ����
	inline void setOwner(baseObject& tempOwner) { owner = &tempOwner; }

	//��������Ʈ?? ����
	inline iActionDelegate* getDelegate(void) { return deleGate; }
	inline void setDelegate(iActionDelegate* tempDele) { deleGate = tempDele; }

	inline void setObject(vector<baseObject*>& temp) { this->object = &temp; }

	inline void setRand(terrain& temp) { this->rand = &temp; }

	inline void setEnemy(xPlayer& temp) 
	{ 
		this->enemy = &temp;
	}

	inline void setPlayerObject(baseObject& temp) { this->playerObject = &temp; }

	//�׼��� ������ �����ϴ� �Լ� - ���������Լ�
	virtual int Start() = 0;
	//�׼��� �����ϴ� �Լ� - ���������Լ�
	virtual int Update() = 0;
	//�׼��߿� ������ �ʿ��ϸ� �����ϴ� �Լ�.
	virtual void Render() {}
};

