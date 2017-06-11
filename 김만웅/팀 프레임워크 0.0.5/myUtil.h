#pragma once

#define EPSILON		0.0001f		//float �� �Ҷ� �̰� ������ ������ ���ٰ� �Ǵ��Ѵ�
//c = 0.0001f
//a = 10.00001f
//b = 10.00008f
//(abs(a - b) < c) => ����

//a �� b �� ����?
#define FLOATEQUAL(a, b) (abs((a) - (b)) < EPSILON)
//���� 0���� ����?
#define FLOATZERO(a) (abs(a) < EPSILON)
//���� ���ͳ�?
#define VECTORZERO(v) (FLOATZERO((v).x) && FLOATZERO((v).y) && FLOATZERO((v).z))

//���� ����ü
typedef struct tagRay
{
	tagRay() { this->origin = D3DXVECTOR3(0.0f, 0.0f, 0.0f); this->direction = D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	tagRay(D3DXVECTOR3& origin, D3DXVECTOR3& direction) { this->origin = origin; this->direction = direction; }
	D3DXVECTOR3 origin;		//������ ������ġ
	D3DXVECTOR3	direction;	//������ ����(����ȭ �Ǿ� �־�� ��)
}Ray, *LPRay;

namespace myUtil
{
	//�̹漺 ���͸� �ִ�ܰ�
	extern DWORD maxAnisotropic;
	//��¥ �߿���, �� ����̽��� ���� �� �����Ѵٰ� �����ϸ��!!!
	//�̳��� �Ŀ��� HDC�ʹ� �񱳺Ұ�
	extern LPDIRECT3DDEVICE9 device;	//����̽� (�ܺο��� ��밡��)

	HRESULT CreateDevice();				//����̽� �����Լ�
	void ReleaseDevice();				//����̽� �����Լ�

	POINT GetMousePos();				//���콺 ��ġ
	void SetMousePos(int x, int y);		//���콺 ��ġ ����

	float Clamp(float value, float min, float max);	//value���� min max���̷� ���߱�
	float Clamp01(float value);			//value���� 0 ~ 1 ���̷� ���߱�
	float ClampMinusOnePlusOne(float value); //value���� -1 ~ 0 ���̷� ���߱�

	//float ��������
	//(t�� 0 ~ 1 ������ ���� �޴µ�..)
	//(t�� 0�� ���� from ����� ���� ���ϵǰ�)
	//(t�� 1�� ���� to ����� ���� ���ϵȴ�)
	float Lerp(float from, float to, float t);

	//float �������� �ݴ�
	//value ���� head�� rear���̿� ������� ��ġ�� �ִ���
	//0 ~ 1������ ������ �����Ѵ�
	float InverseLerp(float head, float rear, float value);
	//���� ��������
	D3DXVECTOR3 VecLerp(D3DXVECTOR3& from, D3DXVECTOR3& to, float t);

	//Random
	void SetRandomSeed();
	float RandomFloatRange(float min, float max);
	int RandomIntRange(int min, int max);

	//������ �븻�� ������ִ� �Լ�
	void ComputeNormal(
		D3DXVECTOR3* pNorams,			//����� ���� �븻���� �迭 ������ ( �븻������ �迭�� ���� ���� �迭�� ���� ���� )
		const D3DXVECTOR3* pVertices,	//��꿡 ���� ������ġ �迭 ������
		int verticesNum,				//���� ����
		const DWORD* pIndices,			//�ε��� �迭������ ( �ϴ� �ε����� DWORD �� �뵿�ܰ� )
		int indicesNum					//�ε��� �迭������ ����
	);

	//ź��Ʈ�� ���̳븻 ���
	void ComputeTangentBinormal(
		D3DXVECTOR3* outTangets,			//��� Tangent �迭
		D3DXVECTOR3* outBinormals,			//��� Binormal �迭
		const D3DXVECTOR3* pPositions,		//���� ��ġ �迭
		const D3DXVECTOR3* pNormals,		//���� �븻 �迭
		const D3DXVECTOR2* pUVs,			//������ UV �迭
		const DWORD* pIndices,				//�ε��� �迭
		DWORD NumTris,						//�ﰢ�� ����		
		DWORD NumVertices 					//���� ����
	);

	//�÷��� ��Ʈ���� �ս����� ����ü DWORD ������ ��ȯ
	DWORD FloatToDWORD(float f);
}

