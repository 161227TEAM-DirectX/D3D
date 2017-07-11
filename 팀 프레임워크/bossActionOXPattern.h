#pragma once
#include "Action.h"
class bossActionOXPattern : public Action
{
private:
	dx::transform rotateTemp;
	LPDIRECT3DTEXTURE9 emergency;
	LPDIRECT3DVERTEXBUFFER9 vb;
	boundBox		damageBox;
	dx::transform boxTransform;
private:
	int randomOX;
	pair<pair<float, float>, pair<float, float>> rangeX;
	pair<pair<float, float>, pair<float, float>> rangeZ;
	float rangeC;
	float chargeTime;
	float ActionTime;
	float damageTime;
private:
	void updateRangeC(void);
	void updateVertex(void);
	void vertexInit(void);
public:
	bossActionOXPattern();
	~bossActionOXPattern();

	//�׼��� ������ �����ϴ� �Լ� - ���������Լ�
	int Start() override;
	//�׼��� �����ϴ� �Լ� - ���������Լ�
	int Update() override;

	void Render() override;
};

