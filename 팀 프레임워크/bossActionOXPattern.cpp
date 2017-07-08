#include "stdafx.h"
#include "bossActionOXPattern.h"


bossActionOXPattern::bossActionOXPattern()
	:chargeTime(0.0f)
{
}


bossActionOXPattern::~bossActionOXPattern()
{
}

int bossActionOXPattern::Start()
{
	owner->getSkinnedAnim().Play("Animation_48");
	emergency = RM_TEXTURE->getResource(FILEPATH_MANAGER->GetFilepath("emergency"));

	_device->CreateVertexBuffer(4 * sizeof(SCENE_VERTEX), 0, SCENE_VERTEX::FVF, D3DPOOL_MANAGED, &vb, nullptr);

	LPSCENE_VETEX vertices;
	vb->Lock(0, 0, (void**)&vertices, 0);

	vertices[0].pos = D3DXVECTOR3(0.0f, 0.2f, -50.0f);
	vertices[0].uv = D3DXVECTOR2(0.0f, 1.0f);

	vertices[1].pos = D3DXVECTOR3(0.0f, 0.2f, 50.0f);
	vertices[1].uv = D3DXVECTOR2(0.0f, 0.0f);

	vertices[2].pos = D3DXVECTOR3(50.0f, 0.2f, 50.0f);
	vertices[2].uv = D3DXVECTOR2(1.0f, 0.0f);
	
	vertices[3].pos = D3DXVECTOR3(0.0f, 0.2f, -50.0f);
	vertices[3].uv = D3DXVECTOR2(1.0f, 1.0f);

	vb->Unlock();

	return LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionOXPattern::Update()
{
	string temp;
	temp = owner->getSkinnedAnim().getAnimationSet()->GetName();
	chargeTime += 0.01f;
	if (chargeTime >= 5.0f)
	{
		if (!strcmp("Animation_48", temp.c_str()))
		{
			owner->getSkinnedAnim().Play("Animation_0", 0.5f);
		}
	}
	else
	{
		
	}
	return 0;
}
