#include "stdafx.h"
#include "grid.h"

HRESULT grid::init(int line, float interval)
{
	float max = line * interval;

	D3DCOLOR color;
	for (int i = 1; i < line; i++)
	{
		if (i % 5 == 0) color = D3DCOLOR_XRGB(0, 0, 0);
		else color = D3DCOLOR_XRGB(128, 128, 128);

		_vVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(max, 0, -i), color));
		_vVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(-max, 0, -i), color));
		_vVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(max, 0, i), color));
		_vVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(-max, 0, i), color));
		_vVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(i, 0, max), color));
		_vVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(i, 0, -max), color));
		_vVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(-i, 0, max), color));
		_vVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(-i, 0, -max), color));
	}
	//x축 관련 선
	color = D3DCOLOR_XRGB(255, 0, 0);
	_vVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(max, 0, 0), color));
	_vVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(-max, 0, 0), color));

	//y축 관련 선
	color = D3DCOLOR_XRGB(0, 255, 0);
	_vVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(0, max, 0), color));
	_vVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(0, -max, 0), color));

	//z축 관련 선
	color = D3DCOLOR_XRGB(0, 0, 255);
	_vVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(0, 0, max), color));
	_vVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(0, 0, -max), color));

	return S_OK;
}

void grid::render(void)
{
	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);

	_device->SetTransform(D3DTS_WORLD, &mat);
	_device->SetFVF(ST_PC_VERTEX::FVF);
	_device->DrawPrimitiveUP(
		D3DPT_LINELIST,
		_vVertex.size() / 2,
		&_vVertex[0],
		sizeof(ST_PC_VERTEX));
}
