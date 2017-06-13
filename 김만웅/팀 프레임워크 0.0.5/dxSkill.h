#pragma once
#include "dxParticleSystem.h"
#include "transform.h"

class dxSkill
{
protected:
	enum SKILL_RENDER_TYPE
	{
		SR_One,
		SR_Array,
		SR_Custom
	
	};

#define SR_One		SR_One
#define	SR_Array	SR_Array
#define SR_Custom	SR_Custom
protected:
	//���� Ÿ�� �����
	SKILL_RENDER_TYPE _SkillRenderType;



	//Ʈ������
	dx::transform* _playerTrans;
	dx::transform* _actionTrans;
	dx::transform* _targetTrans;

	//���� �Ұ�
	bool _skillStartOn;
	bool _skillPrepareOn;
	bool _skillActionOn;
	bool _skillFinshOn;
	bool _skillResetOn;

	//��ƼŬ �ý���
	dxParticleSystem* _preparePS;
	dxParticleSystem* _actionPS;
	dxParticleSystem* _finishPS;

	//��ƼŬ �ý��� ����
	vector<dxParticleSystem*> _vPrepaerPS;
	vector<dxParticleSystem*> _vActionPS;
	vector<dxParticleSystem*> _vFinishPS;

	//��ƼŬ �ý��� �迭
	/*dxParticleSystem* _arrayPreparePS;
	dxParticleSystem* _arrayActionPS;
	dxParticleSystem* _arrayFinishPS;*/

	//��ƼŬ �ý��� �迭����
	int _PrepareSize;
	int _ActionSize;
	int _FinishSize;

	boundSphere* _actionSphereCollision;
	boundSphere* _targetSphereCollision;

	//������ �ð�
	float _resetTime;
	float _currentResetTime;
	
	//����Ʈ ���� ����
	//bool _defualtRendrOn;

public:
	virtual HRESULT init();
	virtual void release();
	//virtual void update(transform* playerTrans, transform* tagetTrans) = 0;
	//virtual void update(transform* playerTrans, transform* tagetTrans);
	void update();	//NO�����....�θ� ������Ʈ��.
	void render();

public:
	//���� ����
	void Start() { _skillStartOn = true; }
	//������Ʈ ����
	virtual bool Prepare() = 0;
	virtual bool Action() = 0;
	virtual void Finsh() = 0;
	virtual void Reset() = 0;

public:
	//���� ����
	virtual void RenderPrepare() { }
	virtual void RenderAction() { }
	virtual void RenderFinsh() { }

public:
	virtual void setPlayer(dx::transform* inPlayerTrans) { _playerTrans = inPlayerTrans; };
	virtual void setTarget(dx::transform* inTargetTrans) { _targetTrans = inTargetTrans; };
	//virtual void setAction(transform* inTargetTrans) { _actionTrans = inTargetTrans; };

	void setPreparePS(string psName) { PSM->initPS(_preparePS, psName); }
	void setActionPS(string psName)  { PSM->initPS(_actionPS, psName); }
	void setFinishPS(string psName)  { PSM->initPS(_finishPS, psName); }

	void setArrayPreparePS(string psName, int arrayNum) { PSM->initArrayPS(_vPrepaerPS, arrayNum, psName); }
	void setArrayActionPS(string psName, int arrayNum) { PSM->initArrayPS(_vActionPS, arrayNum, psName); }
	void setArrayFinishPS(string psName, int arrayNum) { PSM->initArrayPS(_vFinishPS, arrayNum, psName); }
	
protected:
	//������ ���
	struct tagBezierPoint
	{
		D3DXVECTOR3 P0;
		D3DXVECTOR3 P1;
		D3DXVECTOR3 P2;
		D3DXVECTOR3 P3;

		tagBezierPoint()
		{
			P0 = P1 = P2 = P3 = D3DXVECTOR3(0,0,0);
		}
	};

	int RandomTwoNum(int min,int max)
	{
		int result;
		while (true)
		{
			result = RandomIntRange(min, max);
			if (result == min || result == max) { break; }
		}
		return result;
	}

	//3�� ������ � ����
	D3DXVECTOR3 BezierP3Cube(D3DXVECTOR3 P0, D3DXVECTOR3 P1, D3DXVECTOR3 P2, D3DXVECTOR3 P3,float timePos, D3DXVECTOR3& outBP = D3DXVECTOR3(0,0,0))
	{
		D3DXVECTOR3 BezierPoint;

		BezierPoint = P0*powf((1.0f - timePos), 3) + 3 * P1*timePos*powf((1.0f - timePos), 2) + 3 * P2*powf(timePos, 2)*(1.0f - timePos) + P3*powf(timePos, 3);
		outBP = BezierPoint;

		return BezierPoint;
	}
	D3DXVECTOR3 BezierP3Cube(tagBezierPoint inBP, float timePos, D3DXVECTOR3& outBP = D3DXVECTOR3(0, 0, 0))
	{
		D3DXVECTOR3 BezierPoint;

		BezierPoint = inBP.P0*powf((1.0f - timePos), 3) + 3.0f * inBP.P1*timePos*powf((1.0f - timePos), 2) + 3.0f * inBP.P2*powf(timePos, 2)*(1.0f - timePos) + inBP.P3*powf(timePos, 3);
		outBP = BezierPoint;

		return BezierPoint;
	}


public:
	//������
	dxSkill()
	{
		//���۵� �ʱ�ȭ
		_skillStartOn = false;
		_skillActionOn = false;
		_skillFinshOn = false;
		_skillResetOn = false;
		//�ð� �ʱ�ȭ
		_currentResetTime = 0.0f;
		_resetTime = 0.0f;

		//��ƼŬ �ʱ�ȭ
		_preparePS = NULL;
		_actionPS = NULL;
		_finishPS = NULL;

		_SkillRenderType = SR_One;

	};
	~dxSkill() {};
};

