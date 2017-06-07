#pragma once
#include "dxParticle.h"
#include "dxModule.h"
#include "dxModuleKit.h"

enum EMITTER_TYPE
{
	ET_POINT,
	ET_PLANE,
	ET_BOARD,
	ET_MESH
};
#define ET_POINT	ET_POINT
#define ET_PLANE	ET_PLANE
#define ET_BOARD	ET_BOARD
#define ET_MESH		ET_MESH

class dxEmitter
{
protected:
	//��ƼŬ �Ӽ���
	//list<tagDxAttribute> _ptcList;
	vector<tagDxAttribute> _ptcList;
	dxModuleKit* _module;

	//��ƼŬ Ÿ��
	EMITTER_TYPE _EmitterType;

	dx::transform* _trans;
	
	LPDIRECT3DTEXTURE9		_texture;			//�ؽ���

	//D3DXVECTOR3             _origin;		

	//BoundingBox			 _boundingBox;	//�����ڴ� ��ƼŬ�� �̵��� �� �ִ� ���Ǹ� �����ϴ� �� �̿�ȴ�.

	//float   _size;			//�ý��� �� ��� ��ƼŬ�� ũ��
	//LPDIRECT3DVERTEXBUFFER9 _vb;				//���ؽ�����
	//WORD _vbSize;			// ���ؽ����۰� �ѹ��� ������ �� �ִ� ��ƼŬ�� ��.
							// �� ���� ��ƼŬ �ý����� ���� �� �ִ� ��ƼŬ�� ���ʹ� �������̴�.
	float _constPaticleSize;

protected:
	//��ƼŬ ���� �� �ð� ����
	int		_onePtcNum;					//������ ������ �ѹ��� �վ�� ��ƼŬ ����
	DWORD	_totalPtcNum;				//�� ��ƼŬ ����

	bool	_startDelayTimeOn;			//ó�� ���� ������ ��뿩��
	float	_startDelayTime;			//ó�� ���� ������ �Ѱ�ð� ����
	float	_currentDelayTime;			//ó�� ���� ������ ����ð�

	float	_spawnTime;					//����
	float	_spawnCurrentTime;			//����Ÿ��

	int		_drawPtcNum;				//�׸� ��ƼŬ ����	


public:		//�Լ�

	//���� �����Լ�
	//virtual HRESULT init(string textureFileName, int particleNumber) = 0;
	virtual HRESULT init(string textureFileName, int OneTimePaticleNum, float spawnTime, int totalParticlenum) = 0;
	virtual void update() = 0;
	virtual void render() = 0;
	//virtual void reset() = 0;

public:	//����
	virtual void release();
	//virtual void CopyInit() = 0;

public:
	dxModuleKit* Module(void) { return _module; };
	dx::transform*	Transform() { return _trans; }

public:
	//�ʱ� �����۵��ð� ����
	void InitStartDelayTime(float time) { _startDelayTime = time; _spawnCurrentTime = 0.0f; _startDelayTimeOn = true; }
	//��ġ�� ���� ���⼺ �ӵ�
	void InitRandomPosDirectionVelocity(float min, float max) { _module->InitRandomPosDirectionVelocity(min, max); }

public: //=======================================================================================================================
		//��ġ Ÿ�� ����
	void SetPositionType(PTC_POSITION_TYPE posType) { _module->SetPositionType(posType); }
	void InitRandomPosSphereRadius(float min, float max) { _module->InitRandomPosSphereRadius(min, max); }

	//��ġ
	void InitRandomPositionX(float min, float max) { _module->InitRandomPositionX(min, max); }
	void InitRandomPositionY(float min, float max) { _module->InitRandomPositionY(min, max); }
	void InitRandomPositionZ(float min, float max) { _module->InitRandomPositionZ(min, max); }

	//��ġ�� ���� ���⼺ �ӵ� �׷��� ����
	void addPosDirectVelGraph(float point, float min, float max) { _module->addPosDirectVelGraph(point, min, max); }

public:  //=======================================================================================================================
		 //�ӵ�
	void InitRandomVelocityX(float min, float max) { _module->InitRandomVelocityX(min, max); }
	void InitRandomVelocityY(float min, float max) { _module->InitRandomVelocityY(min, max); }
	void InitRandomVelocityZ(float min, float max) { _module->InitRandomVelocityZ(min, max); }

	//�ӵ� �׷���
	void addVelocityGraphX(float point, float min, float max) { _module->addVelocityGraphX(point, min, max); }
	void addVelocityGraphY(float point, float min, float max) { _module->addVelocityGraphY(point, min, max); }
	void addVelocityGraphZ(float point, float min, float max) { _module->addVelocityGraphZ(point, min, max); }

public:  //=======================================================================================================================
		 //���ӵ�
	void InitRandomAccelerationX(float min, float max) { _module->InitRandomAccelerationX(min, max); }
	void InitRandomAccelerationY(float min, float max) { _module->InitRandomAccelerationY(min, max); }
	void InitRandomAccelerationZ(float min, float max) { _module->InitRandomAccelerationZ(min, max); }

public:  //=======================================================================================================================
		 //��
	void InitRandomColorR(float min, float max) { _module->InitRandomColorR(min, max); }
	void InitRandomColorG(float min, float max) { _module->InitRandomColorG(min, max); }
	void InitRandomColorB(float min, float max) { _module->InitRandomColorB(min, max); }

	//�� �Ҹ�
	void InitRandomColorFadeR(float min, float max) { _module->InitRandomColorFadeR(min, max); }
	void InitRandomColorFadeG(float min, float max) { _module->InitRandomColorFadeG(min, max); }
	void InitRandomColorFadeB(float min, float max) { _module->InitRandomColorFadeB(min, max); }

	//����
	void InitRandomAlpha(float min, float max) { _module->InitRandomAlpha(min, max); }
	void InitRandomAlphaFade(float min, float max) { _module->InitRandomAlphaFade(min, max); }

	//���� �׷���
	void addAlphaGraph(float point, float min, float max) { _module->addAlphaGraph(point, min, max); };

public:
	//����
	void InitRandomLifeTime(float min, float max) { _module->InitRandomLiftTime(min, max); }

public:	//=======================================================================================================================
		//������ ����
	void InitRandomSize(float min, float max) { _module->InitRandomSize(min, max); }
	void InitRandomSizeEnd(float min, float max) { _module->InitRandomSizeEnd(min, max); }

	//������ �׷��� ����
	void InitConstSize(float size) { _constPaticleSize = size; }

	void addSizeGraph(float point, float min, float max) { _module->addSizeGraph(point, min, max); };


public:	//=======================================================================================================================
		//�� ȸ�� ������ �ʱ�ȭ
	void InitRandomRadiusX(float min, float max) { _module->InitRandomRadiusX(min, max); }
	void InitRandomRadiusY(float min, float max) { _module->InitRandomRadiusY(min, max); }
	void InitRandomRadiusZ(float min, float max) { _module->InitRandomRadiusZ(min, max); }
	//�� ȸ�� ���ǵ�
	void InitCircleAngleSpeedX(float min, float max) { _module->InitCircleAngleSpeedX(min, max); }
	void InitCircleAngleSpeedY(float min, float max) { _module->InitCircleAngleSpeedY(min, max); }
	void InitCircleAngleSpeedZ(float min, float max) { _module->InitCircleAngleSpeedZ(min, max); }
	//�� ȸ�� ���۰���								  
	void InitCircleStartAngleX(float min, float max) { _module->InitCircleStartAngleX(min, max); }
	void InitCircleStartAngleY(float min, float max) { _module->InitCircleStartAngleY(min, max); }
	void InitCircleStartAngleZ(float min, float max) { _module->InitCircleStartAngleZ(min, max); }
	//��ȸ�� ������ ������
	void InitRandomRadiusEndX(float min, float max) { _module->InitRandomRadiusEndX(min, max); }
	void InitRandomRadiusEndY(float min, float max) { _module->InitRandomRadiusEndY(min, max); }
	void InitRandomRadiusEndZ(float min, float max) { _module->InitRandomRadiusEndZ(min, max); }


public:	//=======================================================================================================================
	//ȸ������ ����
	void InitRotateStartAngleX(float min, float max) { _module->InitRotateStartAngleX(min, max); }
	void InitRotateStartAngleY(float min, float max) { _module->InitRotateStartAngleY(min, max); }
	void InitRotateStartAngleZ(float min, float max) { _module->InitRotateStartAngleZ(min, max); }

	//ȸ������ ���ǵ�
	void InitRotateAngleSpeedX(float min, float max) { _module->InitRotateAngleSpeedX(min, max); }
	void InitRotateAngleSpeedY(float min, float max) { _module->InitRotateAngleSpeedY(min, max); }
	void InitRotateAngleSpeedZ(float min, float max) { _module->InitRotateAngleSpeedZ(min, max); }

public:	//=======================================================================================================================
	//���μ���
	void InitConstVH(float vertical, float horizontal) { _module->InitConstVH(vertical, horizontal); }

public:	//=======================================================================================================================
	//UV�ִϸ��̼�
	void InitAnimation(int inFrameMaxX, int inFrameMaxY, int inTotalFrame = 0) { _module->InitAnimation(inFrameMaxX, inFrameMaxY, inTotalFrame); }

	//�ִϸ��̼� �����
	void InitConstAniReactivateNum(int inReactiveateNum) { _module->InitConstAniReactivateNum(inReactiveateNum); }

	//void InitRandomSpawnTime(float min, float max) { init(_textureFileName, _onePtcNum, RandomFloatRange(min, max)); }
	//void InitRandomDirectionVelocity(float min, float max) { _module->InitRandomDirectionVelocity(min, max); }


public:
	//Ư���Լ�
	DWORD FtoDw(float f) { return *((DWORD*)&f); }
	//Ÿ���Լ�
	EMITTER_TYPE GetType(void) { return this->_EmitterType; };

	public:
	//����
	void reset()
	{
		_ptcList.clear();
		_ptcList.resize(_totalPtcNum);
		_currentDelayTime = 0.0f;
		//_spawnCurrentTime = _spawnTime;
		if (_startDelayTimeOn)
		{
			_spawnCurrentTime = 0.0f;
		}
		else
		{
			_spawnCurrentTime = _spawnTime;
		}
	}

public:
	dxEmitter() {};
	~dxEmitter() {};

	
	
};

