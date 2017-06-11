#include "stdafx.h"
#include "skill00.h"

HRESULT skill00::init()
{
	////���۵� �ʱ�ȭ
	//_skillStartOn = false;
	//_skillActionOn = false;
	//_skillFinshOn = false;
	//_skillReset = false;
	////�ð� �ʱ�ȭ
	//_currentResetTime = 0.0f;
	//_resetTime = 0.0f;

	this->setActionPS("����");
	this->setFinishPS("����");

	/*PSM->initPS(_actionPS, "����");
	PSM->initPS(_finshPS, "����");
	*/

	_actionSphereCollision = new boundSphere;
	_actionSphereCollision->setBound(&_actionPS->Transform()->GetWorldPosition(), &D3DXVECTOR3(0.1f, 0.1f, 0.1f));
	_targetSphereCollision = new boundSphere;
	_targetSphereCollision->setBound(&_targetTrans->GetWorldPosition(), &D3DXVECTOR3(0.1f, 0.1f, 0.1f));


	this->setArrayActionPS("����",5);

	_SkillRenderType = SR_One;

	_resetTime = 0.3f;

	return S_OK;
}

void skill00::release()
{

}
//
//void skill00::update(transform * playerTrans, transform * tagetTrans)
//{
//	//_playerTrans = playerTrans;
//	//_targetTrans = playerTrans;
//
//	if (_testTime >= 0.3f)
//	{
//		_skillStartOn = false;
//		_skillFinshOn = false;
//		_actionPS->reset();
//		_finshPS->reset();
//		_testTime = 0.0f;
//	}
//
//
//	/*if (_skillStartOn)
//	{*/
//		this->Prepare();
//		//playerTrans->GetWorldPosition();
//		
//		//_actionPS->Transform()->MovePositionSelf(0.0f, 0.0f, 6.0f*_timeDelta);
//		_actionPS->Transform()->LookPosition(tagetTrans->GetWorldPosition());
//		//tagetTrans->GetWorldPosition();
//		//�浹 ��� ����
//		//_playerSphereCollisoin._localCenter = _actionPS->Transform()->GetWorldPosition();
//		//_playerSphereCollisoin._halfSize = D3DXVECTOR3(0.1f,3.0f,3.0f);
//		
//		//_targetSphereCollisoin._localCenter = tagetTrans->GetWorldPosition();
//		//_targetSphereCollisoin._halfSize = D3DXVECTOR3(0.1f, 0.0f, 0.0f);
//		//_targetTrans = tagetTrans;
//
//
//		if (_skillStartOn)
//		{
//			if (PHYSICSMANAGER->isOverlap(_actionPS->Transform(), &_playerSphereCollisoin, tagetTrans, &_targetSphereCollisoin))
//			{
//				_skillFinshOn = true; _skillStartOn = false;
//			}
//
//			//_actionPS->Transform()->DefaultMyControl(_timeDelta);
//			_actionPS->Transform()->MovePositionSelf(0.0f, 0.0f, 20.0f*_timeDelta);
//			//_actionPS->Transform()->MovePositionWorld(0.0f,0.0f,2.0f*_timeDelta);
//
//			_actionPS->update();
//			//_testTime += _timeDelta;
//			
//			
//		}
//		
//
//		if (_skillFinshOn)
//		{
//			_finshPS->Transform()->SetWorldPosition(_actionPS->Transform()->GetWorldPosition());
//			_finshPS->update();
//			_testTime += _timeDelta;
//		}
//	//}
//}

bool skill00::Prepare()
{
	return FALSE;
}

bool skill00::Action()
{
	_actionPS->Transform()->LookPosition(_targetTrans->GetWorldPosition());

	_actionPS->Transform()->MovePositionSelf(0.0f, 0.0f, 20.0f*_timeDelta);
	_actionPS->update();
	if (PHYSICSMANAGER->isOverlap(_actionPS->Transform(), _actionSphereCollision, _targetTrans, _targetSphereCollision))
	{
		return FALSE;
	}
	return TRUE;
	/*for (int i = 0; i < 5; i++)
	{
		(_arrayActionPS + i)->update();
	}
	return TRUE;*/
}
void skill00::Finsh()
{
	_finishPS->Transform()->SetWorldPosition(_actionPS->Transform()->GetWorldPosition());
	_finishPS->update();

}

void skill00::Reset()
{
	
}
//
//void skill00::RenderAction()
//{
//}
//
