#pragma once
#include "gameNode.h"

class directionTestScene : public gameNode
{
private:
	LPDIRECT3DVERTEXBUFFER9 _planeVB;		//����� ���� ����
	
	float _yawAngle;							//ȸ������
	float _yawSpeed;							//ȸ���ӵ�	
	float _moveSpeed;

	D3DXVECTOR3	_pos;						//����� ��ġ
	D3DXMATRIXA16 _matPlane;				//����� �������
	
	D3DXVECTOR3	_pos2;						//����� ��ġ
	D3DXMATRIXA16 _matPlane2;				//����� �������

	D3DXMATRIXA16 mat;	//��Ʈ���� Ȯ�ο�

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	directionTestScene() {}
	~directionTestScene() {}
};

