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
	//행렬 초기화 
	D3DXMatrixIdentity(&_world);

	//한쪽면당 1/4의 한쪽면사각형의 갯수라고 보면됨.
	_line = 20;
	//크기 라고 생각하면됨(왠만하면 1.0f로 설정 해놓자)
	_lineWidth = 1.0f;
	//왜 이렇게 하는지 잘모르겠으면 밑에 for문을 보면서 계산해보면서하면 왜인지안다.
	_linePlus = _line * _lineWidth;

	//만약에 _line이  10 이고  _lineWidth 1.0f이니 곱하면 1이다.
	//이렇게 하면 가운데 중심을 잡는다.
	//그리고 D3DPT_LINELIST 로 선을 긋는다.
	_colorLine = D3DCOLOR_XRGB(0, 0, 255);
	_gridVertex.push_back(gridVertex(D3DXVECTOR3(0, 0, -(_linePlus)), _colorLine));
	_gridVertex.push_back(gridVertex(D3DXVECTOR3(0, 0, (_linePlus)), _colorLine));

	/*_colorLine = D3DCOLOR_XRGB(0, 255, 0);
	_gridVertex.push_back(gridVertex(D3DXVECTOR3(0, -(_linePlus / 2), 0), _colorLine));
	_gridVertex.push_back(gridVertex(D3DXVECTOR3(0, (_linePlus / 2), 0), _colorLine));*/

	_colorLine = D3DCOLOR_XRGB(255, 0, 0);
	_gridVertex.push_back(gridVertex(D3DXVECTOR3(-(_linePlus), 0, 0), _colorLine));
	_gridVertex.push_back(gridVertex(D3DXVECTOR3((_linePlus), 0, 0), _colorLine));


	//  i <= _line 일떄는 : 마지막 바깥줄까지 그려진다.
	//  i <  _line 일떄는 : 마지막 바깥줄이 그려 지지않는다.
	for (int i = 1; i <= _line; i++)
	{
		//5칸마다 검은줄이 그련진다는 그런의미
		if (i % 5 == 0) _colorLine = D3DCOLOR_XRGB(255, 255, 255);
		//칸마다가 아니면 나머지는 회색줄을 의미한다.
		else _colorLine = D3DCOLOR_XRGB(128, 128, 128);

		//X로 일자로 그어지는 줄 (그려보면서 하면 쉽다 이해됨.)
		//(위에 줄)
		_gridVertex.push_back(gridVertex(D3DXVECTOR3(-_linePlus, 0, i), _colorLine));
		_gridVertex.push_back(gridVertex(D3DXVECTOR3(_linePlus, 0, i), _colorLine));
		//(아래 줄)
		_gridVertex.push_back(gridVertex(D3DXVECTOR3(-_linePlus, 0, -i), _colorLine));
		_gridVertex.push_back(gridVertex(D3DXVECTOR3(_linePlus, 0, -i), _colorLine));

		//Z로 일자로 그어지는 줄 (그려보면서 하면 쉽다 이해됨.)
		//(오른줄)
		_gridVertex.push_back(gridVertex(D3DXVECTOR3(i, 0, -_linePlus), _colorLine));
		_gridVertex.push_back(gridVertex(D3DXVECTOR3(i, 0, _linePlus), _colorLine));
		//(왼쪽줄)
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
	//행렬적용
	_device->SetTransform(D3DTS_WORLD, &_world);
	//FVF 적용
	_device->SetFVF((D3DFVF_XYZ | D3DFVF_DIFFUSE));
	//그리기(버텍스로만 그리기)
	_device->DrawPrimitiveUP(
		D3DPT_LINELIST,       //맵은 점과 점을 그어서 그림 
		_gridVertex.size() / 2,//D3DPT_LINELIST로 선을그을려면 꼭지점은 2개인데 선은 1개그어진다(그렇게 떄문에 나누기 2를 해준다)
							   //TRIANGLELIST로 그린다고 하면 꼭지점은 3개인데 삼각형은 하나 그려지기떄문에 아마 나누기 3을 해줘야 할것이다.
		&_gridVertex[0],      //맨처음꼭지점부터 그린다는 의미를 담아두고있다.
		sizeof(gridVertex));
}
