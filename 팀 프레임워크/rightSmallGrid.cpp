#include "stdafx.h"
#include "rightSmallGrid.h"


rightSmallGrid::rightSmallGrid()
{
}


rightSmallGrid::~rightSmallGrid()
{
}

HRESULT rightSmallGrid::init()
{
	//��� �ʱ�ȭ 
	D3DXMatrixIdentity(&_world);

	//���ʸ�� 1/4�� ���ʸ�簢���� ������� �����.
	_line = 20;
	//ũ�� ��� �����ϸ��(�ظ��ϸ� 1.0f�� ���� �س���)
	_lineWidth = 1.0f;
	//�� �̷��� �ϴ��� �߸𸣰����� �ؿ� for���� ���鼭 ����غ��鼭�ϸ� �������ȴ�.
	_linePlus = _line * _lineWidth;

	//���࿡ _line��  10 �̰�  _lineWidth 1.0f�̴� ���ϸ� 1�̴�.
	//�̷��� �ϸ� ��� �߽��� ��´�.
	//�׸��� D3DPT_LINELIST �� ���� �ߴ´�.
	_colorLine = D3DCOLOR_XRGB(0, 0, 255);
	_gridVertex.push_back(gridVertex(D3DXVECTOR3(0, 0, -(_linePlus)), _colorLine));
	_gridVertex.push_back(gridVertex(D3DXVECTOR3(0, 0, (_linePlus)), _colorLine));

	/*_colorLine = D3DCOLOR_XRGB(0, 255, 0);
	_gridVertex.push_back(gridVertex(D3DXVECTOR3(0, -(_linePlus / 2), 0), _colorLine));
	_gridVertex.push_back(gridVertex(D3DXVECTOR3(0, (_linePlus / 2), 0), _colorLine));*/

	_colorLine = D3DCOLOR_XRGB(255, 0, 0);
	_gridVertex.push_back(gridVertex(D3DXVECTOR3(-(_linePlus), 0, 0), _colorLine));
	_gridVertex.push_back(gridVertex(D3DXVECTOR3((_linePlus), 0, 0), _colorLine));


	//  i <= _line �ϋ��� : ������ �ٱ��ٱ��� �׷�����.
	//  i <  _line �ϋ��� : ������ �ٱ����� �׷� �����ʴ´�.
	for (int i = 1; i <= _line; i++)
	{
		//5ĭ���� �������� �׷����ٴ� �׷��ǹ�
		if (i % 5 == 0) _colorLine = D3DCOLOR_XRGB(255, 255, 255);
		//ĭ���ٰ� �ƴϸ� �������� ȸ������ �ǹ��Ѵ�.
		else _colorLine = D3DCOLOR_XRGB(128, 128, 128);

		//X�� ���ڷ� �׾����� �� (�׷����鼭 �ϸ� ���� ���ص�.)
		//(���� ��)
		_gridVertex.push_back(gridVertex(D3DXVECTOR3(-_linePlus, 0, i), _colorLine));
		_gridVertex.push_back(gridVertex(D3DXVECTOR3(_linePlus, 0, i), _colorLine));
		//(�Ʒ� ��)
		_gridVertex.push_back(gridVertex(D3DXVECTOR3(-_linePlus, 0, -i), _colorLine));
		_gridVertex.push_back(gridVertex(D3DXVECTOR3(_linePlus, 0, -i), _colorLine));

		//Z�� ���ڷ� �׾����� �� (�׷����鼭 �ϸ� ���� ���ص�.)
		//(������)
		_gridVertex.push_back(gridVertex(D3DXVECTOR3(i, 0, -_linePlus), _colorLine));
		_gridVertex.push_back(gridVertex(D3DXVECTOR3(i, 0, _linePlus), _colorLine));
		//(������)
		_gridVertex.push_back(gridVertex(D3DXVECTOR3(-i, 0, -_linePlus), _colorLine));
		_gridVertex.push_back(gridVertex(D3DXVECTOR3(-i, 0, _linePlus), _colorLine));
	}


	return S_OK;
}

void rightSmallGrid::release()
{
}

void rightSmallGrid::update()
{
}

void rightSmallGrid::render()
{
	//�������
	_device->SetTransform(D3DTS_WORLD, &_world);
	//FVF ����
	_device->SetFVF((D3DFVF_XYZ | D3DFVF_DIFFUSE));
	//�׸���(���ؽ��θ� �׸���)
	_device->DrawPrimitiveUP(
		D3DPT_LINELIST,       //���� ���� ���� �׾ �׸� 
		_gridVertex.size() / 2,//D3DPT_LINELIST�� ������������ �������� 2���ε� ���� 1���׾�����(�׷��� ������ ������ 2�� ���ش�)
							   //TRIANGLELIST�� �׸��ٰ� �ϸ� �������� 3���ε� �ﰢ���� �ϳ� �׷����⋚���� �Ƹ� ������ 3�� ����� �Ұ��̴�.
		&_gridVertex[0],      //��ó������������ �׸��ٴ� �ǹ̸� ��Ƶΰ��ִ�.
		sizeof(gridVertex));
}
