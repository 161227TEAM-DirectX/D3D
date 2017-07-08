#include "stdafx.h"
#include "bossActionOXPattern.h"

bossActionOXPattern::bossActionOXPattern()
	:chargeTime(0.0f), randomOX(0), rangeC(1.0f)
{
	rangeX.first.first = 0.0f;
	rangeX.first.second = 0.0f;
	rangeX.second.first = 0.0f;
	rangeX.second.second = 0.0f;

	rangeZ.first.first = 1.0f;
	rangeZ.first.second = -1.0f;
	rangeZ.second.first = 100.0f;
	rangeZ.second.second = -100.0f;
}


bossActionOXPattern::~bossActionOXPattern()
{
}

int bossActionOXPattern::Start()
{
	randomOX = myUtil::RandomIntRange(1, 2);
	owner->getSkinnedAnim().Play("Animation_48");
	emergency = RM_TEXTURE->getResource(FILEPATH_MANAGER->GetFilepath("emergency"));

	_device->CreateVertexBuffer(6 * sizeof(SCENE_VERTEX), 0, SCENE_VERTEX::FVF, D3DPOOL_MANAGED, &vb, nullptr);

	vertexInit();

	return LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionOXPattern::Update()
{
	string temp;
	temp = owner->getSkinnedAnim().getAnimationSet()->GetName();
	chargeTime += 0.01f;
	rangeC += rangeX.second.first / 0.01f;
	updateRangeC();

	//�ִϸ��̼� ������
	if (chargeTime >= 5.0f)
	{
		if (!strcmp("Animation_48", temp.c_str()))
		{
			owner->getSkinnedAnim().Play("Animation_0", 0.5f);
		}
	}
	else
	{
		updateVertex();
	}
	return 0;
}

void bossActionOXPattern::Render()
{
	DWORD FVF;
	_device->GetFVF(&FVF);

	_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	_device->SetRenderState(D3DRS_LIGHTING, false);
	_device->SetTexture(0, emergency);

	_device->SetStreamSource(0, vb, 0, sizeof(SCENE_VERTEX));
	_device->SetFVF(SCENE_VERTEX::FVF);
	_device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

	_device->SetRenderState(D3DRS_LIGHTING, true);
	_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	_device->SetFVF(FVF);
}

void bossActionOXPattern::updateRangeC(void)
{
	if ((rangeX.first.first + rangeC) > rangeX.second.first)rangeX.first.first = rangeX.second.first;
	else rangeX.first.first += rangeC;
	if ((rangeX.first.second - rangeC) < rangeX.second.second) rangeX.first.second = rangeX.second.second;
	else rangeX.first.second -= rangeC;
	if ((rangeZ.first.first + rangeC) > rangeZ.second.first) rangeZ.first.first = rangeZ.second.first;
	else rangeZ.first.first += rangeC;
	if ((rangeZ.first.second - rangeC) < rangeZ.second.second) rangeZ.first.second = rangeZ.second.second;
	else rangeZ.first.second -= rangeC;
}

void bossActionOXPattern::updateVertex(void)
{
	LPSCENE_VETEX vertices;
	vb->Lock(0, 0, (void**)&vertices, 0);

	switch (randomOX)
	{
	case 1:
		vertices[0].pos = D3DXVECTOR3(rangeX.first.second, 0.2f, rangeZ.first.second);
		vertices[0].uv = D3DXVECTOR2(0.0f, 1.0f);

		vertices[1].pos = D3DXVECTOR3(rangeX.first.second, 0.2f, rangeZ.first.first);
		vertices[1].uv = D3DXVECTOR2(0.0f, 0.0f);

		vertices[2].pos = D3DXVECTOR3(rangeX.first.first, 0.2f, rangeZ.first.first);
		vertices[2].uv = D3DXVECTOR2(1.0f, 0.0f);

		//-----------------------------------------------------------------

		vertices[3].pos = D3DXVECTOR3(rangeX.first.second, 0.2f, rangeZ.first.second);
		vertices[3].uv = D3DXVECTOR2(0.0f, 1.0f);

		vertices[4].pos = D3DXVECTOR3(rangeX.first.first, 0.2f, rangeZ.first.first);
		vertices[4].uv = D3DXVECTOR2(1.0f, 0.0f);

		vertices[5].pos = D3DXVECTOR3(rangeX.first.first, 0.2f, rangeZ.first.second);
		vertices[5].uv = D3DXVECTOR2(1.0f, 1.0f);
		break;
	case 2:
		vertices[0].pos = D3DXVECTOR3(rangeX.first.second, 0.2f, rangeZ.first.second);
		vertices[0].uv = D3DXVECTOR2(0.0f, 1.0f);

		vertices[1].pos = D3DXVECTOR3(rangeX.first.second, 0.2f, rangeZ.first.first);
		vertices[1].uv = D3DXVECTOR2(0.0f, 0.0f);

		vertices[2].pos = D3DXVECTOR3(rangeX.first.first, 0.2f, rangeZ.first.first);
		vertices[2].uv = D3DXVECTOR2(1.0f, 0.0f);

		//-----------------------------------------------------------------

		vertices[3].pos = D3DXVECTOR3(rangeX.first.second, 0.2f, rangeZ.first.second);
		vertices[3].uv = D3DXVECTOR2(0.0f, 1.0f);

		vertices[4].pos = D3DXVECTOR3(rangeX.first.first, 0.2f, rangeZ.first.first);
		vertices[4].uv = D3DXVECTOR2(1.0f, 0.0f);

		vertices[5].pos = D3DXVECTOR3(rangeX.first.first, 0.2f, rangeZ.first.second);
		vertices[5].uv = D3DXVECTOR2(1.0f, 1.0f);
		break;
	}

	vb->Unlock();
}

void bossActionOXPattern::vertexInit(void)
{
	LPSCENE_VETEX vertices;
	vb->Lock(0, 0, (void**)&vertices, 0);

	switch (randomOX)
	{
	case 1:
		rangeX.first.first = 76.0f;
		rangeX.first.second = 74.0f;
		rangeX.second.first = 150.0f;
		rangeX.second.second = 0.0f;

		vertices[0].pos = D3DXVECTOR3(rangeX.first.second, 0.2f, rangeZ.first.second);
		vertices[0].uv = D3DXVECTOR2(0.0f, 1.0f);

		vertices[1].pos = D3DXVECTOR3(rangeX.first.second, 0.2f, rangeZ.first.first);
		vertices[1].uv = D3DXVECTOR2(0.0f, 0.0f);

		vertices[2].pos = D3DXVECTOR3(rangeX.first.first, 0.2f, rangeZ.first.first);
		vertices[2].uv = D3DXVECTOR2(1.0f, 0.0f);

		//-----------------------------------------------------------------

		vertices[3].pos = D3DXVECTOR3(rangeX.first.second, 0.2f, rangeZ.first.second);
		vertices[3].uv = D3DXVECTOR2(0.0f, 1.0f);

		vertices[4].pos = D3DXVECTOR3(rangeX.first.first, 0.2f, rangeZ.first.first);
		vertices[4].uv = D3DXVECTOR2(1.0f, 0.0f);

		vertices[5].pos = D3DXVECTOR3(rangeX.first.first, 0.2f, rangeZ.first.second);
		vertices[5].uv = D3DXVECTOR2(1.0f, 1.0f);
		break;
	case 2:
		rangeX.first.first = -74.0f;
		rangeX.first.second = -76.0f;
		rangeX.second.first = 0.0f;
		rangeX.second.second = -150.0f;

		vertices[0].pos = D3DXVECTOR3(rangeX.first.second, 0.2f, rangeZ.first.second);
		vertices[0].uv = D3DXVECTOR2(0.0f, 1.0f);

		vertices[1].pos = D3DXVECTOR3(rangeX.first.second, 0.2f, rangeZ.first.first);
		vertices[1].uv = D3DXVECTOR2(0.0f, 0.0f);

		vertices[2].pos = D3DXVECTOR3(rangeX.first.first, 0.2f, rangeZ.first.first);
		vertices[2].uv = D3DXVECTOR2(1.0f, 0.0f);

		//-----------------------------------------------------------------

		vertices[3].pos = D3DXVECTOR3(rangeX.first.second, 0.2f, rangeZ.first.second);
		vertices[3].uv = D3DXVECTOR2(0.0f, 1.0f);

		vertices[4].pos = D3DXVECTOR3(rangeX.first.first, 0.2f, rangeZ.first.first);
		vertices[4].uv = D3DXVECTOR2(1.0f, 0.0f);

		vertices[5].pos = D3DXVECTOR3(rangeX.first.first, 0.2f, rangeZ.first.second);
		vertices[5].uv = D3DXVECTOR2(1.0f, 1.0f);
		break;
	}

	vb->Unlock();
}
