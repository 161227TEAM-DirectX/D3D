#pragma once
#include "dxModule.h"
#include "dxPositionModule.h"
#include "dxVelocityModule.h"
#include "dxAccelerationModule.h"
#include "dxColorModule.h"
#include "dxSizeModule.h"
#include "dxLifeTimeModule.h"
#include "dxCircleModule.h"

#include "dxRotationModule.h"
#include "dxUVModule.h"

//����� ������!!
class dxModuleKit
{
private:
	dxPositionModule*		_posMD;		//��ġ
	dxVelocityModule*		_velMD;		//�ӵ�
	dxAccelerationModule*	_accelMD;	//���ӵ�
	dxColorModule*			_colorMD;	//����
	dxSizeModule*			_sizeMD;	//������
	dxLifeTimeModule*		_lifeMD;	//����ð�
	dxCircleModule*			_circleMD;	//��ȸ��

	dxRotationModule*		_rotateMD;	//ȸ��
	dxUVModule*				_uvMD;

public:
	virtual HRESULT init();
	virtual void relese();
	/*virtual void InitUpdate(list<tagDxAttribute>::iterator iter);
	virtual void ActiveUpdate(list<tagDxAttribute>::iterator iter);*/

	virtual void InitUpdate(vector<tagDxAttribute>::iterator iter);
	virtual void ActiveUpdate(vector<tagDxAttribute>::iterator iter);

public:	//=======================================================================================================================
	//��ġ Ÿ�� ����
	void SetPositionType(PTC_POSITION_TYPE posType) { _posMD->SetPositionType(posType); }
	void InitRandomPosSphereRadius(float min, float max) { _posMD->InitRandomPosSphereRadius(min, max); }

	//��ġ
	void InitRandomPositionX(float min, float max) { _posMD->InitRandomPositionX(min, max);}
	void InitRandomPositionY(float min, float max) { _posMD->InitRandomPositionY(min, max);}
	void InitRandomPositionZ(float min, float max) { _posMD->InitRandomPositionZ(min, max);}

	//��ġ�� ���� ���⼺ �ӵ�
	void InitRandomPosDirectionVelocity(float min, float max) { _posMD->InitRandomPosDirectionVelocity(min, max); }

	//��ġ�� ���� ���⼺ �ӵ� �׷��� ����
	void addPosDirectVelGraph(float point, float min, float max) { _posMD->addPosDirectVelGraph(point, min, max); };


public:	//=======================================================================================================================
	//�ӵ�
	void InitRandomVelocityX(float min, float max) { _velMD->InitRandomVelocityX(min, max); }
	void InitRandomVelocityY(float min, float max) { _velMD->InitRandomVelocityY(min, max); }
	void InitRandomVelocityZ(float min, float max) { _velMD->InitRandomVelocityZ(min, max); }

	//�ӵ� �׷��� ����
	void addVelocityGraphX(float point, float min, float max) { _velMD->addVelocityGraphX(point, min, max); }
	void addVelocityGraphY(float point, float min, float max) { _velMD->addVelocityGraphY(point, min, max); }
	void addVelocityGraphZ(float point, float min, float max) { _velMD->addVelocityGraphZ(point, min, max); }


public:	//=======================================================================================================================

	//���ӵ�
	void InitRandomAccelerationX(float min, float max) { _accelMD->InitRandomAccelerationX(min, max); }
	void InitRandomAccelerationY(float min, float max) { _accelMD->InitRandomAccelerationY(min, max); }
	void InitRandomAccelerationZ(float min, float max) { _accelMD->InitRandomAccelerationZ(min, max); }


public:	//=======================================================================================================================
	//�ʱ��
	void InitRandomColorR(float min, float max) { _colorMD->InitRandomColorR(min, max); }
	void InitRandomColorG(float min, float max) { _colorMD->InitRandomColorG(min, max); }
	void InitRandomColorB(float min, float max) { _colorMD->InitRandomColorB(min, max); }

	//�� �Ҹ�
	void InitRandomColorFadeR(float min, float max) { _colorMD->InitRandomColorFadeR(min, max); }
	void InitRandomColorFadeG(float min, float max) { _colorMD->InitRandomColorFadeG(min, max); }
	void InitRandomColorFadeB(float min, float max) { _colorMD->InitRandomColorFadeB(min, max); }

	//���� �׷��� ����
	void addColorGraphR(float point, float min, float max) { _colorMD->addColorGraphR(point,min, max); }
	void addColorGraphG(float point, float min, float max) { _colorMD->addColorGraphG(point,min, max); }
	void addColorGraphB(float point, float min, float max) { _colorMD->addColorGraphB(point,min, max); }

	//����
	void InitRandomAlpha(float min, float max) { _colorMD->InitRandomAlpha(min, max); }
	void InitRandomAlphaFade(float min, float max) { _colorMD->InitRandomAlphaFade(min, max); }

	//���� �׷��� ����
	void addAlphaGraph(float point, float min, float max) { _colorMD->addAlphaGraph(point, min, max); }


public:	//=======================================================================================================================
	//������ ����
	void InitRandomSize(float min, float max) { _sizeMD->InitRandomSize(min, max); }
	void InitRandomSizeEnd(float min, float max) { _sizeMD->InitRandomSizeEnd(min, max); }
	//������ �׷��� ����
	void addSizeGraph(float point, float min, float max) { _sizeMD->addSizeGraph(point, min, max); }


public:	//=======================================================================================================================
	//������ ����
	void InitRandomLiftTime(float min, float max) { _lifeMD->InitRandomLiftTime(min, max); }
	

public:	//=======================================================================================================================

	//������ �׷��� ����
	void addRadiusGraph(float point, float min, float max) { _circleMD->addRadiusGraph(point, min, max); }


	//������
	void InitRandomRadiusX(float min, float max) { _circleMD->InitRandomRadiusX(min, max); }
	void InitRandomRadiusY(float min, float max) { _circleMD->InitRandomRadiusY(min, max); }
	void InitRandomRadiusZ(float min, float max) { _circleMD->InitRandomRadiusZ(min, max); }

	//���� ���ǵ�
	void InitCircleAngleSpeedX(float min, float max) { _circleMD->InitCircleAngleSpeedX(min, max); }
	void InitCircleAngleSpeedY(float min, float max) { _circleMD->InitCircleAngleSpeedY(min, max); }
	void InitCircleAngleSpeedZ(float min, float max) { _circleMD->InitCircleAngleSpeedZ(min, max); }

	//���� ����
	void InitCircleStartAngleX(float min, float max) { _circleMD->InitCircleStartAngleX(min, max); }
	void InitCircleStartAngleY(float min, float max) { _circleMD->InitCircleStartAngleY(min, max); }
	void InitCircleStartAngleZ(float min, float max) { _circleMD->InitCircleStartAngleZ(min, max); }

	//������ ������
	void InitRandomRadiusEndX(float min, float max) { _circleMD->InitRandomRadiusEndX(min, max); }
	void InitRandomRadiusEndY(float min, float max) { _circleMD->InitRandomRadiusEndY(min, max); }
	void InitRandomRadiusEndZ(float min, float max) { _circleMD->InitRandomRadiusEndZ(min, max); }
	
public:	//=======================================================================================================================
	//ȸ������ ����
	void InitRotateStartAngleX(float min, float max) { _rotateMD->InitRotateStartAngleX(min, max); }
	void InitRotateStartAngleY(float min, float max) { _rotateMD->InitRotateStartAngleY(min, max); }
	void InitRotateStartAngleZ(float min, float max) { _rotateMD->InitRotateStartAngleZ(min, max); }

	//ȸ������ ���ǵ�
	void InitRotateAngleSpeedX(float min, float max) { _rotateMD->InitRotateAngleSpeedX(min, max); }
	void InitRotateAngleSpeedY(float min, float max) { _rotateMD->InitRotateAngleSpeedY(min, max); }
	void InitRotateAngleSpeedZ(float min, float max) { _rotateMD->InitRotateAngleSpeedZ(min, max); }

public:	//=======================================================================================================================
	//���μ���
	void InitConstVH(float vertical, float horizontal) { _sizeMD->InitConstVH(vertical, horizontal); }

public:	//=======================================================================================================================
	//UV�ִϸ��̼�
	void InitAnimation(int inFrameMaxX, int inFrameMaxY, int inTotalFrame) { _uvMD->InitAnimation(inFrameMaxX, inFrameMaxY, inTotalFrame); }
	//�ִϸ��̼� �����
	void InitConstAniReactivateNum(int inReactiveateNum) { _uvMD->InitConstAniReactivateNum(inReactiveateNum); }


public:
	dxModuleKit() {};
	virtual ~dxModuleKit() {};
};

