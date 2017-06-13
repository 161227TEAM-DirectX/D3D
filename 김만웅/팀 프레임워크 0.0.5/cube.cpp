#include "stdafx.h"
#include "cube.h"

HRESULT cube::init(D3DXVECTOR3 size, D3DXMATRIXA16 * mat)
{
	/*이걸 안해주면 아무것도 안나옴 ㅋㅋ*/
	//게임오브젝트 초기화
	gameObject::init();

	D3DCOLOR color = D3DCOLOR_XRGB(255, 0, 0);
	// 버텍스를 집어 넣는다.
	vector<D3DXVECTOR3> vecVertex;
	vecVertex.push_back(D3DXVECTOR3(-size.x / 2.0f, -size.y / 2.0f, -size.z / 2.0f));
	vecVertex.push_back(D3DXVECTOR3(-size.x / 2.0f, size.y / 2.0f, -size.z / 2.0f));
	vecVertex.push_back(D3DXVECTOR3(size.x / 2.0f, size.y / 2.0f, -size.z / 2.0f));
	vecVertex.push_back(D3DXVECTOR3(size.x / 2.0f, -size.y / 2.0f, -size.z / 2.0f));
	vecVertex.push_back(D3DXVECTOR3(-size.x / 2.0f, -size.y / 2.0f, size.z / 2.0f));
	vecVertex.push_back(D3DXVECTOR3(-size.x / 2.0f, size.y / 2.0f, size.z / 2.0f));
	vecVertex.push_back(D3DXVECTOR3(size.x / 2.0f, size.y / 2.0f, size.z / 2.0f));
	vecVertex.push_back(D3DXVECTOR3(size.x / 2.0f, -size.y / 2.0f, size.z / 2.0f));

	if (mat)
	{
		for (size_t i = 0; i < vecVertex.size(); i++)
		{
			D3DXVec3TransformCoord(&vecVertex[i], &vecVertex[i], mat);
		}
	}

	color = D3DCOLOR_XRGB(rand() % 255, rand() % 255, rand() % 255);
	_vecVertex.push_back(MYVERTEX(vecVertex[0], color));
	_vecVertex.push_back(MYVERTEX(vecVertex[1], color));
	_vecVertex.push_back(MYVERTEX(vecVertex[2], color));
	_vecVertex.push_back(MYVERTEX(vecVertex[0], color));
	_vecVertex.push_back(MYVERTEX(vecVertex[2], color));
	_vecVertex.push_back(MYVERTEX(vecVertex[3], color));

	color = D3DCOLOR_XRGB(rand() % 255, rand() % 255, rand() % 255);
	_vecVertex.push_back(MYVERTEX(vecVertex[4], color));
	_vecVertex.push_back(MYVERTEX(vecVertex[6], color));
	_vecVertex.push_back(MYVERTEX(vecVertex[5], color));
	_vecVertex.push_back(MYVERTEX(vecVertex[4], color));
	_vecVertex.push_back(MYVERTEX(vecVertex[7], color));
	_vecVertex.push_back(MYVERTEX(vecVertex[6], color));

	color = D3DCOLOR_XRGB(rand() % 255, rand() % 255, rand() % 255);
	_vecVertex.push_back(MYVERTEX(vecVertex[4], color));
	_vecVertex.push_back(MYVERTEX(vecVertex[5], color));
	_vecVertex.push_back(MYVERTEX(vecVertex[1], color));
	_vecVertex.push_back(MYVERTEX(vecVertex[4], color));
	_vecVertex.push_back(MYVERTEX(vecVertex[1], color));
	_vecVertex.push_back(MYVERTEX(vecVertex[0], color));

	color = D3DCOLOR_XRGB(rand() % 255, rand() % 255, rand() % 255);
	_vecVertex.push_back(MYVERTEX(vecVertex[3], color));
	_vecVertex.push_back(MYVERTEX(vecVertex[2], color));
	_vecVertex.push_back(MYVERTEX(vecVertex[6], color));
	_vecVertex.push_back(MYVERTEX(vecVertex[3], color));
	_vecVertex.push_back(MYVERTEX(vecVertex[6], color));
	_vecVertex.push_back(MYVERTEX(vecVertex[7], color));

	color = D3DCOLOR_XRGB(rand() % 255, rand() % 255, rand() % 255);
	_vecVertex.push_back(MYVERTEX(vecVertex[1], color));
	_vecVertex.push_back(MYVERTEX(vecVertex[5], color));
	_vecVertex.push_back(MYVERTEX(vecVertex[6], color));
	_vecVertex.push_back(MYVERTEX(vecVertex[1], color));
	_vecVertex.push_back(MYVERTEX(vecVertex[6], color));
	_vecVertex.push_back(MYVERTEX(vecVertex[2], color));

	color = D3DCOLOR_XRGB(rand() % 255, rand() % 255, rand() % 255);
	_vecVertex.push_back(MYVERTEX(vecVertex[4], color));
	_vecVertex.push_back(MYVERTEX(vecVertex[0], color));
	_vecVertex.push_back(MYVERTEX(vecVertex[3], color));
	_vecVertex.push_back(MYVERTEX(vecVertex[4], color));
	_vecVertex.push_back(MYVERTEX(vecVertex[3], color));
	_vecVertex.push_back(MYVERTEX(vecVertex[7], color));

	return S_OK;
}

void cube::release(void)
{
}

void cube::update(void)
{
}

void cube::render(void)
{
	//게임오브젝트 렌더
	gameObject::render();

	_device->SetTransform(D3DTS_WORLD, &_matWorld);

	_device->SetFVF(MYVERTEX::FVF);

	_device->DrawPrimitiveUP(
		D3DPT_TRIANGLELIST,
		_vecVertex.size() / 3,
		&_vecVertex[0],
		sizeof(MYVERTEX));
}
