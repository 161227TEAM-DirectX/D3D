#pragma once
#include "dxEmitter.h"


class dxPointEmitter : public dxEmitter
{
private:
	//dxModule* _module;

	D3DXMATRIX _matWorld;

	//tagDxParticle* ptcVtx;

	string _textureFileName;

	

	int _vbMaxStep;
	
	

	int limitCycle;
	int currentCycle;
	bool cycleOn;
	 
	tagDxParticle* _ptcVtx;
	tagDxParticle* _drawVtx;


public:
	virtual HRESULT init(string textureFileName, int OneTimePaticleNum = 10, float spawnTime = 1.0f, int totalPaticleNum = 0);
	//vietual HRESULT init(string textureFileName, int OneTimePaticleNum = 10, float spawnTime = 1.0f, int allPaticleNum = 200);
	virtual void relese();
	virtual void update();
	virtual void render();

//public:  
//	//�ʱ� �����۵��ð� ����
//	void InitStartDelayTime(float time) { _startDelayTime = time; _spawnCurrentTime = 0.0f; _startDelayTimeOn = true; }
//	//��ġ�� ���� ���⼺ �ӵ�
//	void InitRandomPosDirectionVelocity(float min, float max) { _module->InitRandomPosDirectionVelocity(min, max); }
//
//public: //=======================================================================================================================
//	//��ġ Ÿ�� ����
//	void SetPositionType(PTC_POSITION_TYPE posType) { _module->SetPositionType(posType); }
//	void InitRandomPosSphereRadius(float min, float max) { _module->InitRandomPosSphereRadius(min, max); }
//
//	//��ġ
//	void InitRandomPositionX(float min, float max) { _module->InitRandomPositionX(min, max); }
//	void InitRandomPositionY(float min, float max) { _module->InitRandomPositionY(min, max); }
//	void InitRandomPositionZ(float min, float max) { _module->InitRandomPositionZ(min, max); }
//
//	//��ġ�� ���� ���⼺ �ӵ� �׷��� ����
//	void addPosDirectVelGraph(float point, float min, float max) { _module->addPosDirectVelGraph(point, min, max); }
//
//public:  //=======================================================================================================================
//	//�ӵ�
//	void InitRandomVelocityX(float min, float max) { _module->InitRandomVelocityX(min, max); }
//	void InitRandomVelocityY(float min, float max) { _module->InitRandomVelocityY(min, max); }
//	void InitRandomVelocityZ(float min, float max) { _module->InitRandomVelocityZ(min, max); }
//
//	//�ӵ� �׷���
//	void addVelocityGraphX(float point, float min, float max) { _module->addVelocityGraphX(point, min, max); }
//	void addVelocityGraphY(float point, float min, float max) { _module->addVelocityGraphY(point, min, max); }
//	void addVelocityGraphZ(float point, float min, float max) { _module->addVelocityGraphZ(point, min, max); }
//
//public:  //=======================================================================================================================
//	//���ӵ�
//	void InitRandomAccelerationX(float min, float max) { _module->InitRandomAccelerationX(min, max); }
//	void InitRandomAccelerationY(float min, float max) { _module->InitRandomAccelerationY(min, max); }
//	void InitRandomAccelerationZ(float min, float max) { _module->InitRandomAccelerationZ(min, max); }
//
//public:  //=======================================================================================================================
//	//��
//	void InitRandomColorR(float min, float max) { _module->InitRandomColorR(min, max); }
//	void InitRandomColorG(float min, float max) { _module->InitRandomColorG(min, max); }
//	void InitRandomColorB(float min, float max) { _module->InitRandomColorB(min, max); }
//
//	//�� �Ҹ�
//	void InitRandomColorFadeR(float min, float max) { _module->InitRandomColorFadeR(min, max); }
//	void InitRandomColorFadeG(float min, float max) { _module->InitRandomColorFadeG(min, max); }
//	void InitRandomColorFadeB(float min, float max) { _module->InitRandomColorFadeB(min, max); }
//
//	//����
//	void InitRandomAlpha(float min, float max) { _module->InitRandomAlpha(min, max); }
//	void InitRandomAlphaFade(float min, float max) { _module->InitRandomAlphaFade(min, max); }
//
//	//���� �׷���
//	void addAlphaGraph(float point, float min, float max) { _module->addAlphaGraph(point, min, max); };
//
//public:
//	//����
//	void InitRandomLifeTime(float min, float max) { _module->InitRandomLiftTime(min, max); }
//
//public:	//=======================================================================================================================
//	//������ ����
//	void InitRandomSize(float min, float max) { _module->InitRandomSize(min, max); }
//	void InitRandomSizeEnd(float min, float max) { _module->InitRandomSizeEnd(min, max); }
//
//	//������ �׷��� ����
//	void InitConstSize(float size) { _constPaticleSize = size; }
//	
//	void addSizeGraph(float point, float min, float max) { _module->addSizeGraph(point, min, max); };
//	
//	
//public:	//=======================================================================================================================
//	//�� ȸ�� ������ �ʱ�ȭ
//	void InitRandomRadiusX(float min, float max) { _module->InitRandomRadiusX(min, max); }
//	void InitRandomRadiusY(float min, float max) { _module->InitRandomRadiusY(min, max); }
//	void InitRandomRadiusZ(float min, float max) { _module->InitRandomRadiusZ(min, max); }
//	//�� ȸ�� ���ǵ�
//	void InitRandomAngleSpeedX(float min, float max) { _module->InitRandomAngleSpeedX(min, max); }
//	void InitRandomAngleSpeedY(float min, float max) { _module->InitRandomAngleSpeedY(min, max); }
//	void InitRandomAngleSpeedZ(float min, float max) { _module->InitRandomAngleSpeedZ(min, max); }
//	//�� ȸ�� ���۰���								  
//	void InitRandomStartAngleX(float min, float max) { _module->InitRandomStartAngleX(min, max); }
//	void InitRandomStartAngleY(float min, float max) { _module->InitRandomStartAngleY(min, max); }
//	void InitRandomStartAngleZ(float min, float max) { _module->InitRandomStartAngleZ(min, max); }
//	//��ȸ�� ������ ������
//	void InitRandomRadiusEndX(float min, float max) { _module->InitRandomRadiusEndX(min, max); }
//	void InitRandomRadiusEndY(float min, float max) { _module->InitRandomRadiusEndY(min, max); }
//	void InitRandomRadiusEndZ(float min, float max) { _module->InitRandomRadiusEndZ(min, max); }
//
//
//	//void InitRandomSpawnTime(float min, float max) { init(_textureFileName, _onePtcNum, RandomFloatRange(min, max)); }
//	//void InitRandomDirectionVelocity(float min, float max) { _module->InitRandomDirectionVelocity(min, max); }
//	

public:
	////����
	//void reset()
	//{
	//	_ptcList.clear();
	//	_ptcList.resize(_totalPtcNum);
	//	_currentDelayTime = 0.0f;
	//	//_spawnCurrentTime = _spawnTime;
	//	if (_startDelayTimeOn)
	//	{
	//		_spawnCurrentTime = 0.0f;	
	//	}
	//	else 
	//	{	
	//		_spawnCurrentTime = _spawnTime; 
	//	}
	//}
public:
	/*void CopyInit()
	{
		_ptcVtx = NULL;
		_ptcVtx = new tagDxParticle[(int)_vbSize];
		_drawVtx = NULL;
		_drawVtx = new tagDxParticle[(int)_vbSize];
	}*/

public:
	dxPointEmitter()
	{
		//��� �ʱ�ȭ
		_module = new dxModuleKit;
		_trans = new transform;
		_module->init();
		//�̹��� Ÿ�� ����
		_EmitterType = ET_POINT;
		//_startDelayTimeOn = false;
	};
	~dxPointEmitter() {};
	
};

