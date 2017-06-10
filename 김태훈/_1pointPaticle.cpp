#include "stdafx.h"
#include "_1pointPaticle.h"

HRESULT _1pointPaticle::init(void)
{
	//메인카메라 위치 세팅
	_mainCamera->SetWorldPosition(0, 1, -5);

	//정점 위치
	_particleVertex[0].pos = D3DXVECTOR3(-3, 0, 0);
	_particleVertex[1].pos = D3DXVECTOR3(0, 0, 0);
	_particleVertex[2].pos = D3DXVECTOR3(3, 0, 0);

	//정점 사이즈
	_particleVertex[0].size = 2.0f;
	_particleVertex[1].size = 2.0f;
	_particleVertex[2].size = 2.0f;

	//정점 컬러
	_particleVertex[0].color = 0xffff0000;
	_particleVertex[1].color = 0xff00ff00;
	_particleVertex[2].color = 0xff0000ff;

	//정점에 사용될 텍스쳐 가져오자
	_texture = RM_TEXTURE->getResource("Resources/Textures/particle_0.png");

	return S_OK;
}

void _1pointPaticle::release(void)
{
}

void _1pointPaticle::update(void)
{
}

void _1pointPaticle::render(void)
{
	_device->SetRenderState(D3DRS_LIGHTING, false);						//라이팅을 끈다
	_device->SetRenderState(D3DRS_POINTSPRITEENABLE, true);				//포인트 스프라이트 활성화
	_device->SetRenderState(D3DRS_POINTSCALEENABLE, true);				//포인트의 스케일 값을 먹이겠다. FVF 에 D3DFVF_PSIZE 있는경우
	_device->SetRenderState(D3DRS_POINTSIZE_MIN, FloatToDWORD(0.0f));	//포인트의 최소 크기(화면기준)
	_device->SetRenderState(D3DRS_POINTSIZE_MAX, FloatToDWORD(500.0f));	//포인트의 최대 크기(화면기준)

	//출력되는 POINT size 
	//finalSize = viewportHeight * pointSize *  sqrt( 1 / ( A + B(D) + C(D^2) )  );
	//아래와 같이 하면 자연스러운 거리에 따른 스케일이 나타남
	_device->SetRenderState(D3DRS_POINTSCALE_A, FloatToDWORD(0.0f));
	_device->SetRenderState(D3DRS_POINTSCALE_B, FloatToDWORD(0.0f));
	_device->SetRenderState(D3DRS_POINTSCALE_C, FloatToDWORD(1.0f));

	//Texture 의 값과 Diffuse 여기서는 정점컬러의 알파값 을 섞어 최종 출력을 한다.
	_device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	_device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
	_device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);

/////////////////////////////////////////////////////////////////////////////////
	//알파 블렌딩 세팅 
	_device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	////1.다음과 같은 알파블렌딩 옵션은 일반 적인 알파블렌딩 ( 알파소팅이 필요할수 있다 )
	//_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//2.다음과 같은 알파블렌딩 옵션은 색을 태운다 ( 불 화염 레이져 같은거 표현 ) ( 알파소팅이 필요 없다 )
	_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	_device->SetRenderState(D3DRS_ZWRITEENABLE, false);	//z 버퍼의 쓰기를 막는다.

///////////////////////////////////////////////////////////////////////////////////

	//파티클 Texture 세팅
	_device->SetTexture(0, _texture);

	//파티클 정점 출력
	_device->SetFVF(PARTICLE_VERTEX::FVF);

	//버퍼통하지 않고 바로 그린다 ( 자주움직이는 정점에 대해 쓰기편하고 좋다 )
	_device->DrawPrimitiveUP(
		D3DPT_POINTLIST,		//PT
		3,						//그릴갯수 점이 3개다
		_particleVertex,		//VERTEX 배열 
		sizeof(PARTICLE_VERTEX)	//VERTEX 하나 Size 
	);

	//다시 돌려놔
	_device->SetRenderState(D3DRS_LIGHTING, true);
	_device->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	_device->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	_device->SetRenderState(D3DRS_ZWRITEENABLE, true);
}
