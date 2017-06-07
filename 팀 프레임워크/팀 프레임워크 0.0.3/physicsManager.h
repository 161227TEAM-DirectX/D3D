#pragma once
#include "singletonBase.h"
#include "boundBox.h"
#include "baseObject.h"

class physicsManager : public singletonBase <physicsManager>
{
public:
	HRESULT init(void);
	void release(void);

	//���̰� �ٿ�忡 �浹�ߴ��� Ȯ��
	bool isRayHitBound(
		LPRay ray,					//����
		boundSphere* bound,			//�ٿ�屸
		dx::transform* boundTrans,		//�ٿ��Ʈ������
		D3DXVECTOR3* hitPos,		//��Ʈ ��ġ (NULL�̸� ���Ծȵ�)
		D3DXVECTOR3* hitNormal);	//��Ʈ �븻 (NULL�̸� ���Ծȵ�)

	//���̰� �ٿ�忡 �浹�ߴ��� Ȯ��
	bool isRayHitBound(
		LPRay ray,					//����
		boundBox* bound,			//�ٿ��ڽ�
		dx::transform* boundTrans,		//�ٿ��Ʈ������
		D3DXVECTOR3* hitPos,		//��Ʈ ��ġ (NULL�̸� ���Ծȵ�)
		D3DXVECTOR3* hitNormal);	//��Ʈ �븻 (NULL�̸� ���Ծȵ�)

	//���̰� ������Ʈ�� �浹�ߴ��� Ȯ��
	bool isRayHitStaticMeshObject(
		LPRay ray,					//����
		baseObject* object,			//������Ʈ
		D3DXVECTOR3* hitPos,		//��Ʈ ��ġ (NULL�̸� ���Ծȵ�)
		D3DXVECTOR3* hitNormal);	//��Ʈ �븻 (NULL�̸� ���Ծȵ�)
	
	//���̰� ���� �浹�ߴ��� Ȯ��
	bool isRayHitSphere(
		LPRay ray,
		D3DXVECTOR3* pCenter,
		float radius,
		D3DXVECTOR3* hitPos,		//Hit ��ġ ( NULL �̸� ���� �ȵ� )
		D3DXVECTOR3* hitNormal		//Hit �� �븻 ( NULL �̸� ���� �ȵ� )
	);
							
	//�ΰ��� ������Ʈ�� ���ƴ��� Ȯ��
	bool isOverlap(baseObject* objA, baseObject* objB);
	
	//�ΰ��� �ٿ�忡 ���� �浹������ Ȯ��
	bool isOverlap(dx::transform* transA, boundSphere* boundA, dx::transform* transB, boundSphere* boundB);
	bool isOverlap(dx::transform* transA, boundBox* boundA, dx::transform* transB, boundBox* boundB);
	bool isOverlap(dx::transform* transA, boundSphere* boundA, dx::transform* transB, boundBox* boundB);
	bool isOverlap(dx::transform* transA, boundBox* boundA, dx::transform* transB, boundSphere* boundB);

	bool isBlocking(baseObject* objA, baseObject* objB, float moveFactor = 0.0f);
	bool isBlocking(
		dx::transform* transA, boundSphere* boundA,
		dx::transform* transB, boundSphere* boundB,
		float moveFactor = 0.0f);
	bool isBlocking(
		dx::transform* transA, boundBox* boundA,
		dx::transform* transB, boundBox* boundB,
		float moveFactor = 0.0f);

	//�� 3���� ���� ��� �����
	void createPlane(LPD3DXPLANE pOutPlane, D3DXVECTOR3* p0, D3DXVECTOR3* p1, D3DXVECTOR3* p2);
	//���ǿ� �������� �������� �ִܰŸ�
	float planeDot(LPD3DXPLANE plane, D3DXVECTOR3* point);
	//�������� ����� �浹��ġ
	bool intersectRayToPlane(D3DXVECTOR3* pOut, LPRay ray, LPD3DXPLANE plane, bool checkToSide = false);

	physicsManager() {}
	~physicsManager() {}
};

