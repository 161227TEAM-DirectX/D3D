#include "stdafx.h"
#include "skBoss_PatternOX.h"

HRESULT skBoss_PatternOX::init()
{
	_SkillRenderType = SR_Big;

	setMaxNumPreparePS(1);

	//setPvActionPS(0, "먼지_퍼짐", 1);
	setPvPreparePS(0, "OX패턴", 4);

	for (int i = 0; i < _pvPrepaerPS[0].size(); i++)
	{
		_pvPrepaerPS[0][i]->SetLimitTime(16.0f);
	}
	
	//for (int i = 0; i < 4; i++)
	//{
	//	D3DXMatrixIdentity(&_matPos[i]);
	//	D3DXMatrixIdentity(&_matRot[i]);
	//}

	_oneSetting = true;

	return S_OK;
}

void skBoss_PatternOX::release()
{

}

bool skBoss_PatternOX::Prepare()
{

	D3DXVECTOR3 pos = _skillPosTrans->GetWorldPosition();

	


	if (_oneSetting)
	{
		

		_pvPrepaerPS[0][0]->Transform()->RotateSelf(0.0f, 0.0f, 0.0f);
		_pvPrepaerPS[0][1]->Transform()->RotateSelf(0.0f, D3DXToRadian(90.0f), 0.0f);
		_pvPrepaerPS[0][2]->Transform()->RotateSelf(0.0f, D3DXToRadian(-90.0f), 0.0f);
		_pvPrepaerPS[0][3]->Transform()->RotateSelf(0.0f, D3DXToRadian(180.0f), 0.0f);

		/*_pvPrepaerPS[0][0]->Transform()->SetWorldPosition(pos.x - 25.0f, pos.y, pos.z + 25.0f);
		_pvPrepaerPS[0][1]->Transform()->SetWorldPosition(pos.x + 25.0f, pos.y, pos.z + 25.0f);
		_pvPrepaerPS[0][2]->Transform()->SetWorldPosition(pos.x - 25.0f, pos.y, pos.z - 25.0f);
		_pvPrepaerPS[0][3]->Transform()->SetWorldPosition(pos.x + 25.0f, pos.y, pos.z - 25.0f);*/

		_pvPrepaerPS[0][0]->Transform()->SetWorldPosition(pos.x - 75.0f ,pos.y,pos.z + 100.0f);
		_pvPrepaerPS[0][1]->Transform()->SetWorldPosition(pos.x + 75.0f, pos.y, pos.z + 100.0f);
		_pvPrepaerPS[0][2]->Transform()->SetWorldPosition(pos.x - 75.0f, pos.y, pos.z - 100.0f);
		_pvPrepaerPS[0][3]->Transform()->SetWorldPosition(pos.x + 75.0f, pos.y, pos.z - 100.0f);

		
	/*	D3DXMatrixTranslation(&_matPos[0], pos.x - 25.0f, pos.y, pos.z + 25.0f);
		D3DXMatrixTranslation(&_matPos[1], pos.x + 25.0f, pos.y, pos.z + 25.0f);
		D3DXMatrixTranslation(&_matPos[2], pos.x - 25.0f, pos.y, pos.z - 25.0f);
		D3DXMatrixTranslation(&_matPos[3], pos.x + 25.0f, pos.y, pos.z - 25.0f);

		D3DXMatrixRotationY(&_matRot[0], 0.0f);
		D3DXMatrixRotationY(&_matRot[1], 90.0f);
		D3DXMatrixRotationY(&_matRot[2], -90.0f);
		D3DXMatrixRotationY(&_matRot[3], 180.0f);


		for (int i = 0; i < _pvPrepaerPS[0].size(); i++)
		{
			_pvPrepaerPS[0][i]->Transform()->SetWorldMatrix(_matRot[i] * _matPos[i]);
		}*/
		



		//_pvPrepaerPS[0][0]->Transform()->LookDirection(_skillDirTrans->GetForward());
		

		_oneSetting = false;
	}
	
	for (int i = 0; i < _pvPrepaerPS[0].size(); i++)
	{
		_pvPrepaerPS[0][i]->update();

		if (_pvPrepaerPS[0][i]->autoTimeReset(false))
		{
			_skillResetOn = true;
		}
	}
	

	


	return false;
}

bool skBoss_PatternOX::Action()
{
	return false;
}

void skBoss_PatternOX::Finsh()
{
}

void skBoss_PatternOX::Reset()
{
	_oneSetting = true;
}
