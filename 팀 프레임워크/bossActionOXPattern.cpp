#include "stdafx.h"
#include "bossActionOXPattern.h"
#include "xPlayer.h"
#include "bossMonster.h"

bossActionOXPattern::bossActionOXPattern()
	:Action(), chargeTime(0.0f), randomOX(0), rangeC(0.2f), damageTime(0.0f), ActionTime(0.0f)
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
	RM_TEXTURE->removeResource(FILEPATH_MANAGER->GetFilepath("emergency"));
	SAFE_RELEASE(emergency);
	SAFE_RELEASE(vb);
}

int bossActionOXPattern::Start()
{
	randomOX = myUtil::RandomIntRange(1, 2);

	bossMonster* temp = dynamic_cast<bossMonster*>(owner);

	switch (randomOX)
	{
	case 1:
		damageBox.setBound(&D3DXVECTOR3(75.0f, 0.0f, 0.0), &D3DXVECTOR3(75.0f, 0.1f, 75.0f));
		temp->getOXPattern().SetWorldPosition(damageBox.getLocalCenter());
		SKM->findSK("패턴")->setSkillPosTrans(&temp->getOXPattern());
		break;
	case 2:
		damageBox.setBound(&D3DXVECTOR3(-75.0f, 0.0f, 0.0), &D3DXVECTOR3(75.0f, 0.1f, 75.0f));
		temp->getOXPattern().SetWorldPosition(damageBox.getLocalCenter());
		SKM->findSK("패턴")->setSkillPosTrans(&temp->getOXPattern());
		break;
	}
	owner->getSkinnedAnim().Play("Animation_48",0.5f);
	emergency = RM_TEXTURE->getResource(FILEPATH_MANAGER->GetFilepath("emergency"));

	_device->CreateVertexBuffer(6 * sizeof(SCENE_VERTEX), 0, SCENE_VERTEX::FVF, D3DPOOL_MANAGED, &vb, nullptr);

	vertexInit();

	return LHS::ACTIONRESULT::ACTION_SAFE;
}

int bossActionOXPattern::Update()
{
	string temp;
	temp = owner->getSkinnedAnim().getAnimationSet()->GetName();
	bossMonster* tempOwner = dynamic_cast<bossMonster*>(owner);
	chargeTime += 0.01f;

	updateRangeC();

	//애니메이션 변경점
	if (chargeTime >= 5.0f)
	{
		if (!strcmp("Animation_48", temp.c_str()))
		{
			owner->getSkinnedAnim().Play("Animation_0", 0.5f);
		}

		if (!strcmp("Animation_0", temp.c_str()))
		{
			SKM->findSK("패턴")->Start();
			ActionTime += _timeDelta;
			if (ActionTime >= 8.0f)
			{
				SKM->findSK("패턴")->InitActiveSettingOn();
				return LHS::ACTIONRESULT::ACTION_LANDING;
			}
			//브레스 출력
			//데미지 적용.
			if (PHYSICSMANAGER->isOverlap(&boxTransform, &damageBox, playerObject->_transform, &playerObject->_boundBox))
			{
				damageTime += _timeDelta;
				if (damageTime >= 1.0f)
				{
					enemy->playerDamaged(300000);
					damageTime = 0.0f;
				}
			}
		}
	}
	else
	{
		updateVertex();
	}

	return LHS::ACTIONRESULT::ACTION_SAFE;
}

void bossActionOXPattern::Render()
{
	damageBox.renderGizmo(&boxTransform);
	DWORD FVF;
	_device->GetFVF(&FVF);

	_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	_device->SetRenderState(D3DRS_LIGHTING, false);
	_device->SetTexture(0, emergency);

	_device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	_device->SetStreamSource(0, vb, 0, sizeof(SCENE_VERTEX));
	_device->SetFVF(SCENE_VERTEX::FVF);
	_device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

	_device->SetRenderState(D3DRS_LIGHTING, true);
	_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	_device->SetFVF(FVF);
}

void bossActionOXPattern::updateRangeC(void)
{
	//x축 증가값
	if ((rangeX.first.first + rangeC) > rangeX.second.first)rangeX.first.first = rangeX.second.first;
	else rangeX.first.first += rangeC;
	//x축 감소값
	if ((rangeX.first.second - rangeC) < rangeX.second.second) rangeX.first.second = rangeX.second.second;
	else rangeX.first.second -= rangeC;
	//y축 증가값
	if ((rangeZ.first.first + rangeC) > rangeZ.second.first) rangeZ.first.first = rangeZ.second.first;
	else rangeZ.first.first += rangeC;
	//y축 감소값
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

		//-------------------------------------------------------------------
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