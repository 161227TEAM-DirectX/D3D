#include "stdafx.h"
#include "spriteManager.h"

HRESULT spriteManager::init(void)
{
	//스프라이트 생성
	if (FAILED(D3DXCreateSprite(_device, &_sprite))) return E_FAIL;
	return S_OK;
}

void spriteManager::release(void)
{
	//스프라이트 해제
	SAFE_RELEASE(_sprite);
}

//스프라이트 렌더 시작시 호출
void spriteManager::beginSpriteRender()
{
	_sprite->Begin(D3DXSPRITE_ALPHABLEND);
}
void spriteManager::beginSpriteBillRender()
{
	_sprite->Begin(D3DXSPRITE_OBJECTSPACE | D3DXSPRITE_BILLBOARD);
}
//스프라이트 렌더 종료시 호출
void spriteManager::endSpriteRender()
{
	_sprite->End();
}

void spriteManager::RenderFont(camera* mainCamera, string str, D3DXVECTOR3& pos)
{
	D3DXMATRIX matScale;
	D3DXMATRIX matTrans;
	D3DXMATRIX mat;

	D3DXMatrixScaling(&matScale, 0.01f, 0.01f, 0.01f);
	D3DXMatrixTranslation(&matTrans, pos.x, pos.y, pos.z);
	mat = matScale * matTrans;
	D3DXVECTOR3 test(1, 1, 1);
	_sprite->SetWorldViewLH(nullptr, &mainCamera->getViewMatrix());
	beginSpriteBillRender();
	
	_sprite->SetTransform(&mat);
	
	FONTMANAGER->fontOut(_sprite, str);
	//_sprite->Draw(RM_TEXTURE->getResource("Resource/이미지/리자몽.png"), nullptr, nullptr, &test, D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0xff));
	endSpriteRender();
}

//일반렌더(텍스쳐, 그릴영역렉트, 위치좌표 x, y, 섞이는 색상, 이미지중심점)
void spriteManager::renderTexture(LPDIRECT3DTEXTURE9 texture, LPRECT rcSour, float posX, float posY, DWORD color, D3DXVECTOR3 * center)
{
	//화면 절대 좌표로 그리기때문에 transform을 초기화 해줘야 한다
	D3DXMATRIXA16 matFinal;
	D3DXMatrixIdentity(&matFinal);
	_sprite->SetTransform(&matFinal);

	//그릴화면 위치
	D3DXVECTOR3 pos(posX, posY, 0.0f);

	//스프라이트 사용 시작
	_sprite->Begin(D3DXSPRITE_ALPHABLEND);

	//이곳에서 스프라이트 그리자
	_sprite->Draw(
		texture,	//그릴 텍스쳐
		rcSour,		//그릴 텍스쳐 소스 영역
		(center == NULL) ? &D3DXVECTOR3(0, 0, 0) : center, //이미지 중심위치
		&pos,		//그릴 화면 위치좌표
		color);		//컬러(이미지에 원하는 색을 덧입혀서 화면에 출력된다 // 셀로판지)

	//스프라이트 사용 종료
	_sprite->End();
}

void spriteManager::renderRectTexture(LPDIRECT3DTEXTURE9 texture, LPRECT rcSour, LPRECT colRc, float RectStartX, float RectStartY, float RectSizeWidth, float RectSizeHeight, float posX, float posY, DWORD color, D3DXVECTOR3 * center)
{
	//TIP) 
	//텍스쳐 이미지 크기는 무조건 128.256.512
	//2진수가 아니면 텍스쳐 이미지가 짤려서 이상하기 뜬다.

	//화면 절대 좌표로 그리기때문에 transform을 초기화 해줘야 한다
	D3DXMATRIXA16 matFinalRect;
	D3DXMatrixIdentity(&matFinalRect);
	_sprite->SetTransform(&matFinalRect);

	//그릴화면 위치
	D3DXVECTOR3 pos(posX, posY, 0.0f);

	//렉트 사이즈 
	rcSour->left = RectStartX;
	rcSour->top = RectStartY;
	rcSour->right = RectSizeWidth;
	rcSour->bottom = RectSizeHeight;

	//스프라이트 사용 시작
	_sprite->Begin(D3DXSPRITE_ALPHABLEND);

	//이곳에서 스프라이트 그리자
	_sprite->Draw(
		texture,	//그릴 텍스쳐
		rcSour,		//그릴 텍스쳐 소스 영역
		&D3DXVECTOR3(0, 0, 0), //이미지 중심위치
		&pos,		//그릴 화면 위치좌표
		color);		//컬러(이미지에 원하는 색을 덧입혀서 화면에 출력된다 // 셀로판지)

	//스프라이트 사용 종료
	_sprite->End();
}

//스프라이트 크기 및 회전가능
void spriteManager::renderTexture(LPDIRECT3DTEXTURE9 texture, LPRECT rcSour, float posX, float posY, float scaleX, float scaleY, float rotate, DWORD color, D3DXVECTOR3 * center)
{
	//이미지 기준점
	D3DXVECTOR3 pivot = (center == NULL) ? D3DXVECTOR3(0, 0, 0) : *center;

	//스케일 행렬
	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling(&matScale, scaleX, scaleY, 1.0f);
	
	//회전 행렬
	D3DXMATRIXA16 matRot;
	D3DXMatrixRotationZ(&matRot, rotate);

	//이동 행렬
	D3DXMATRIXA16 matTrans;
	D3DXMatrixTranslation(&matTrans, posX, posY, 0.0f);

	//최종행렬
	D3DXMATRIXA16 matFinal;
	//크기, 회전, 이동 => 순서대로 곱해줘야 한다 (SRT)
	matFinal = matScale * matRot * matTrans;

	_sprite->SetTransform(&matFinal);

	//스프라이트 사용 시작
	_sprite->Begin(D3DXSPRITE_ALPHABLEND);

	//이곳에서 스프라이트 그리자
	_sprite->Draw(
		texture,				//그릴 텍스쳐
		rcSour,					//그릴 텍스쳐 소스 영역
		&pivot,					//이미지 중심위치
		&D3DXVECTOR3(0, 0, 0),	//그릴 화면 위치좌표
		color);					//컬러(이미지에 원하는 색을 덧입혀서 화면에 출력된다 // 셀로판지)

	//스프라이트 사용 종료
	_sprite->End();
}

//렉트의 영역만큼 렌더
void spriteManager::renderArea(LPDIRECT3DTEXTURE9 texture, LPRECT rcSour, LPRECT rcDest, DWORD color)
{
	float destWidth = rcDest->right - rcDest->left;
	float destHeight = rcDest->bottom - rcDest->top;

	float sourWidth = rcSour->right - rcSour->left;
	float sourHeight = rcSour->bottom - rcSour->top;

	//영역 비율에 의한 스케일 값
	float scaleX = destWidth / sourWidth;
	float scaleY = destHeight / sourHeight;

	//스케일 행렬
	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling(&matScale, scaleX, scaleY, 1.0f);

	//이동 행렬
	D3DXMATRIXA16 matTrans;
	D3DXMatrixTranslation(&matTrans, rcDest->left, rcDest->top, 0.0f);

	//최종 행렬
	D3DXMATRIXA16 matFinal = matScale * matTrans;

	_sprite->SetTransform(&matFinal);

	//스프라이트 사용 시작
	_sprite->Begin(D3DXSPRITE_ALPHABLEND);

	//이곳에서 스프라이트 그리자
	_sprite->Draw(
		texture,				//그릴 텍스쳐
		rcSour,					//그릴 텍스쳐 소스 영역
		&D3DXVECTOR3(0, 0, 0),	//이미지 중심위치
		&D3DXVECTOR3(0, 0, 0),	//그릴 화면 위치좌표
		color);					//컬러(이미지에 원하는 색을 덧입혀서 화면에 출력된다 // 셀로판지)

	//스프라이트 사용 종료
	_sprite->End();
}

//나인패치
void spriteManager::renderNinePatch(LPDIRECT3DTEXTURE9 texture, LPRECT rcSour, LPRECT rcDest, LPRECT rcCenter, DWORD color, bool isDrawCenter)
{
	//lt, top, rt
	//lc, center, rc
	//lb, bottom, rb

	// ___|___|___
	// ___|___|___
	// ___|___|___

	//소스영역
	RECT rcSourLT = { 0, 0, rcCenter->left, rcCenter->top };
	RECT rcSourTop = { rcCenter->left, 0, rcCenter->right, rcCenter->top };
	RECT rcSourRT = { rcCenter->right, 0, rcSour->right, rcCenter->top };
	
	RECT rcSourLC = { 0, rcCenter->top, rcCenter->left, rcCenter->bottom };
	RECT rcSourCenter = { rcCenter->top, rcCenter->top, rcCenter->right, rcCenter->bottom };
	RECT rcSourRC = { rcCenter->right, rcCenter->top, rcSour->right, rcCenter->bottom };

	RECT rcSourLB = { 0, rcCenter->bottom, rcCenter->left, rcSour->bottom };
	RECT rcSourBottom = { rcCenter->left, rcCenter->bottom, rcSour->right, rcSour->bottom };
	RECT rcSourRB = { rcCenter->right, rcCenter->bottom, rcSour->right, rcSour->bottom };

	//그리는 영역
	float left = rcDest->left;
	float top = rcDest->top;
	float right = rcDest->right;
	float bottom = rcDest->bottom;

	float centerLeft = rcDest->left + (rcCenter->left - rcSour->left);
	float centerRight = rcDest->right - (rcSour->right - rcCenter->right);
	float centerTop = rcDest->top + (rcCenter->top - rcSour->top);
	float centerBottom = rcDest->bottom - (rcSour->bottom - rcCenter->bottom);

	RECT rcDestLT = { left, top, centerLeft, centerTop };
	RECT rcDestTop = { centerLeft, top, centerRight, centerTop };
	RECT rcDestRT = { centerRight, top, right, centerTop };

	RECT rcDestLC = { left, centerTop, centerLeft, centerBottom };
	RECT rcDestCenter = { centerLeft, centerTop, centerRight, centerBottom };
	RECT rcDestRC = { centerRight, centerTop, right, centerBottom };

	RECT rcDestLB = { left, centerBottom, centerLeft, bottom };
	RECT rcDestBottom = { centerLeft, centerBottom, centerRight, bottom };
	RECT rcDestRB = { centerRight, centerBottom, right, bottom };

	//9개의 렉트영역을 렌더
	renderArea(texture, &rcSourLT, &rcDestLT, color);
	renderArea(texture, &rcSourTop, &rcDestTop, color);
	renderArea(texture, &rcSourRT, &rcDestRT, color);
	renderArea(texture, &rcSourLC, &rcDestLC, color);
	//가운데는 true 일때만 그린다
	if(isDrawCenter) renderArea(texture, &rcSourCenter, &rcDestCenter, color);
	renderArea(texture, &rcSourRC, &rcDestRC, color);
	renderArea(texture, &rcSourLB, &rcDestLB, color);
	renderArea(texture, &rcSourBottom, &rcDestBottom, color);
	renderArea(texture, &rcSourRB, &rcDestRB, color);
}
