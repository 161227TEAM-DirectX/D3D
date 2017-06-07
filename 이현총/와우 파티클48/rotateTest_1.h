#pragma once
#include "gameNode.h"

class rotateTest_1 : public gameNode
{
private:
	LPDIRECT3DVERTEXBUFFER9		_vb;		//��������
	LPDIRECT3DINDEXBUFFER9		_ib;		//�ε�������
	D3DXMATRIXA16				_matWorld;	//�������

	//�繰�� �� (��� ���� ���⿡ ���� ������ �����Ѵ�)
	//���⺤��
	D3DXVECTOR3	_forward;	//�繰�� ���� ����
	D3DXVECTOR3 _right;		//�繰�� ������ ����
	D3DXVECTOR3 _up;		//�繰�� ��溤��
	//��ġ����
	D3DXVECTOR3 _pos;		//�繰�� ��ġ
	//�ٶ󺸴� ��ġ
	D3DXVECTOR3 _targetPos;	//Ÿ�� ��ġ

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void CreateCube(void);

	rotateTest_1() {}
	~rotateTest_1() {}
};

