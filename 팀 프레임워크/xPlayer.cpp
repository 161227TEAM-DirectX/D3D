#include "stdafx.h"
#include "xPlayer.h"
#include "monster.h"


HRESULT xPlayer::init()
{
	
	//메시 로딩
	_state = P_STAND;
	_prevState = P_STAND;
	Equipments = A_PLATE;
	Weapons = W_BLACK_WING;

	_Hp = 10;

	_damagedTime = 0.0f;
	_stunnedTime = 0.0f;
	_castingTime = 0.0f;
	_playSpeed = 1.0f;

	_isOnBattle = false;

	_jumpHeight = 0;

	//데이터를 로딩해 이전의 스테이터스와 장비상태를 초기화한다.
	LoadData();
	xMeshSkinned* pSkinned;
	D3DXMATRIXA16 matCorrection;
	D3DXMATRIXA16 matScale;
	D3DXMATRIXA16 matRotate;
	D3DXMatrixScaling(&matScale, 1, 1, 1);
	D3DXMatrixRotationY(&matRotate, D3DXToRadian(180));
	matCorrection = matRotate*matScale;


	switch (Equipments)
	{
	case A_NONE:
		pSkinned =
			RM_SKINNED->getResource("Resources/Player/FHUMAN_NONE/FHUMAN.X", &matCorrection);
		break;

	case A_LEATHER:

		pSkinned =
			RM_SKINNED->getResource("Resources/Player/FHUMAN_LEATHER/FHUMAN.X", &matCorrection);
		break;

	case A_ROBE:

		pSkinned =
			RM_SKINNED->getResource("Resources/Player/FHUMAN_ROBE/FHUMAN.X", &matCorrection);
		break;

	case A_PLATE:

		pSkinned =
			RM_SKINNED->getResource("Resources/Player/FHUMAN_PLATE/FHUMAN.X", &matCorrection);
		break;

	default:
		return E_FAIL;
		break;
	}

	_playerObject = new baseObject;
	_playerObject->setMesh(pSkinned);
	_playerObject->setActive(true);

	float tempY = linkTerrain->getHeight(_playerObject->_transform->GetWorldPosition().x, _playerObject->_transform->GetWorldPosition().z);

	_playerObject->_transform->SetWorldPosition(D3DXVECTOR3(_playerObject->_transform->GetWorldPosition().x, tempY, _playerObject->_transform->GetWorldPosition().z));
	

	_renderObjects.push_back(_playerObject);
	dx::transform* playerTrans = _playerObject->_transform;
	D3DXVECTOR3 pos = playerTrans->GetWorldPosition();
	
	_playerObject->_boundBox.setBound(&D3DXVECTOR3(pos.x, pos.y + 0.5f, pos.z), &D3DXVECTOR3(0.3, 0.5, 0.3));
	
	_attackTrans.SetWorldPosition(pos.x, pos.y + 0.5f, pos.z + 0.8);

	_attackBound.setBound(&_attackTrans.GetWorldPosition(), &D3DXVECTOR3(0.5, 0.5, 0.5));

	//소켓 설정
	BONE* handF = _playerObject->_skinnedAnim->getSkinnedMesh()->GetFineBONE("humanfemale_Bone121_CSR");
	BONE* HEAD = _playerObject->_skinnedAnim->getSkinnedMesh()->GetFineBONE("humanfemale_Bone102");
	BONE* ShoulderR = _playerObject->_skinnedAnim->getSkinnedMesh()->GetFineBONE("humanfemale_Bone99");
	BONE* ShoulderL = _playerObject->_skinnedAnim->getSkinnedMesh()->GetFineBONE("humanfemale_Bone98");
	BONE* Shield = _playerObject->_skinnedAnim->getSkinnedMesh()->GetFineBONE("humanfemale_Bone110");
	BONE* handF2 = _playerObject->_skinnedAnim->getSkinnedMesh()->GetFineBONE("humanfemale_Bone113");

	_EquipSocket.insert(make_pair("RHAND", handF));
	_EquipSocket.insert(make_pair("HEAD", HEAD));
	_EquipSocket.insert(make_pair("RSHOULDER", ShoulderR));
	_EquipSocket.insert(make_pair("LSHOULDER", ShoulderL));
	_EquipSocket.insert(make_pair("SHIELD", Shield));
	_EquipSocket.insert(make_pair("LHAND", handF2));

	//무기로딩 및 보정행렬 적용
	D3DXMATRIXA16 matCorrection2;
	D3DXMatrixIdentity(&matCorrection2);
	D3DXMatrixRotationY(&matCorrection2, D3DXToRadian(270));
	xMeshStatic* pSkinned2;


	//웨폰 오브젝트 초기화 디폴트로 블랙윙을 가져오고 w_none이면 액티브 하지 않는다.
	_weaponObject = new baseObject;
	pSkinned2 = RM_XMESH->getResource("Resources/Weapons/sword_2h_blackwing_a_02.X", &matCorrection2);
	_weaponObject->setMesh(pSkinned2);

	switch (Weapons)
	{
	case W_BLACK_WING:
		_weaponObject->setActive(true);
		_renderObjects.push_back(_weaponObject);
		break;
	case W_NONE:
		_weaponObject->setActive(false);
		_renderObjects.push_back(_weaponObject);
		//_weaponObject->setActive(false);
		break;
	default:
		break;
	}

	_playerObject->_skinnedAnim->Play("S", 0.3F);
	return S_OK;
}

void xPlayer::update()
{

	float tempY = linkTerrain->getHeight(_playerObject->_transform->GetWorldPosition().x, _playerObject->_transform->GetWorldPosition().z);
	_playerObject->_transform->SetWorldPosition(D3DXVECTOR3(_playerObject->_transform->GetWorldPosition().x, tempY, _playerObject->_transform->GetWorldPosition().z));


	_playerObject->_skinnedAnim->SetPlaySpeed(_playSpeed);

	//플레이어 오브젝트 업데이트
	_playerObject->update();



	if (Weapons != W_NONE)
	{
		D3DXMATRIX matHand = _EquipSocket.find("RHAND")->second->CombinedTransformationMatrix;
		_weaponObject->_transform->SetWorldMatrix(matHand);
		_weaponObject->update();
	}

	if (!KEYMANAGER->isToggleKey(VK_CAPITAL))
	{
		userPlayerControl();

		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			playerAttack();
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			playerSkillOmni(1.0f);
		}

	}
	playerStateManager();
	playerAnimationManager();
	_prevState = _state;
}

void xPlayer::render()
{
	for (int i = 0; i < this->_renderObjects.size(); i++)
	{
		this->_renderObjects[i]->render();
	}

	if (KEYMANAGER->isToggleKey(VK_F7))
	{
		_playerObject->_boundBox.renderGizmo(_playerObject->_transform);
		_attackBound.renderGizmo(_playerObject->_transform);
	}
	//_playerObject->_skinnedAnim->getSkinnedMesh()->ShowAnimationName(0,20);

	FONTMANAGER->fontOut(to_string(_state), 100, 0, 0xffffffff);

	FONTMANAGER->fontOut("HP : " + to_string(_Hp), 500, 0, 0xffffffff);
}

void xPlayer::release(void)
{
	for (int i = 0; i < this->_renderObjects.size(); i++)
	{
		SAFE_DELETE(this->_renderObjects[i]);
	}
}

void xPlayer::LoadData()
{
	//플레이어 데이터 싱글톤 함수로 부터 데이터를 복사한다.
}

void xPlayer::setHeight(float height)//지형으로 부터 위치를 가져온다.
{
	D3DXVECTOR3 pos = _playerObject->_transform->GetWorldPosition();
	_playerObject->_transform->SetWorldPosition(pos.x, height, pos.z);
}

//외부의 입력에 대해 플레이어의 이동과 상태값, 애니메이션 등을 제어한다.
void xPlayer::userPlayerControl()
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		//데미지, 경직시간, 경직확률, 스턴확률, 스턴시간 
		playerDamaged(1, 0.5, 100.0, 0.0, 0.0);
	}

	if (KEYMANAGER->isOnceKeyDown('V'))
	{
		playerDamaged(1, 0.5, 100.0, 100.0, 2.0);
	}

	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		_Hp++;
	}

	//임시 컨트롤용 코드
	if (_state == P_DEATH || _state == P_STUN || _state == P_ATTACK || _state == P_DAMAGED) { return; }

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		_isOnBattle = true;
		if (_state == P_STAND)
		{
			_state = P_READYTOATTACK;
		}
	}
	else
	{
		_isOnBattle = false;
		if (_state == P_READYTOATTACK)
		{
			_state = P_STAND;
		}
	}

	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		this->_state = P_RUN;
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		if (_state == P_RUN)
		{
			_playerObject->_transform->MovePositionWorld(_playerObject->_transform->GetForward()*0.05);
		}
	}
	if (KEYMANAGER->isOnceKeyUp('W'))
	{
		if (_isOnBattle)
		{
			this->_state = P_READYTOATTACK;
		}
		else
		{
			this->_state = P_STAND;
		}
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_playerObject->_transform->RotateSelf(0.0f, -D3DXToRadian(3), 0.0f);
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_playerObject->_transform->RotateSelf(0.0f, D3DXToRadian(3), 0.0f);
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		this->_state = P_WALKBACK;
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		if (_state == P_WALKBACK)
		{
			_playerObject->_transform->MovePositionWorld(-_playerObject->_transform->GetForward()*0.025);
		}
	}
	if (KEYMANAGER->isOnceKeyUp('S'))
	{
		if (_isOnBattle)
		{
			this->_state = P_READYTOATTACK;
		}
		else
		{
			this->_state = P_STAND;
		}
	}

}

//플레이어의 자동적인 상태변화를 관리한다.
//이 부분에서 플레이어의 애니메이션을 변화시키지 않아야 함. -> 과연 그럴까?
//시간이 지남에 따라 혹은 수치값의 변동에 따라 자동적으로 변화해야 하는 경우를 지정한다.
void xPlayer::playerStateManager()
{
	if (_Hp <= 0) _state = P_DEATH;
	string aa = _playerObject->_skinnedAnim->getAnimationSet()->GetName();
	switch (_state)
	{
	case P_STAND:
		//서있는다고 시간지나도 변할거 없음.
		break;
	case P_RUN:
		//시간지나도 변할게 없음.
		break;
	case P_MOVE:
		//시간지나도 변할게 없음.
		break;
	case P_READYTOATTACK:

		break;
	case P_ATTACK:

		if (aa == "AT2H")
		{
			if (_playerObject->_skinnedAnim->getAnimFactor() > 0.95)//애니메이션 다 재생했으면
			{
				if (PHYSICSMANAGER->isOverlap(_playerObject->_transform, &_attackBound, targetMonster->_transform, &targetMonster->_boundBox))
				{
					exit(0);
				}

				if (_isOnBattle)
				{
					_state = P_READYTOATTACK;
				}
				else
				{
					_state = P_STAND;
				}
			}
		}
		break;
	case P_READYSPELL:
		if (_castingTime < 0)
		{
			_state = P_CASTSPELL;
		}
		_castingTime -= _timeDelta;

		break;
	case P_CASTSPELL:
		if (aa == "SPCD")
		{
			if (_playerObject->_skinnedAnim->getAnimFactor() > 0.95)//애니메이션 다 재생했으면
			{
				if (_isOnBattle)
				{
					_state = P_READYTOATTACK;
				}
				else
				{
					_state = P_STAND;
				}
			}
		}

		break;
	case P_READYOMNI:
		if (_castingTime < 0)
		{
			_state = P_CASTOMNI;
		}
		_castingTime -= _timeDelta;

		break;
	case P_CASTOMNI:
		if (aa == "SPCO")
		{
			if (_playerObject->_skinnedAnim->getAnimFactor() > 0.95)//애니메이션 다 재생했으면
			{
				if (_isOnBattle)
				{
					_state = P_READYTOATTACK;
				}
				else
				{
					_state = P_STAND;
				}
			}
		}
		break;
	case P_JUMPUP:

		break;
	case P_JUMP:

		break;
	case P_JUMPDOWN:

		break;
	case P_STUN:
		if (_stunnedTime < 0)
		{
			if (_isOnBattle)
			{
				_state = P_READYTOATTACK;
			}
			else
			{
				_state = P_STAND;
			}
		}
		_stunnedTime -= _timeDelta;

		break;
	case P_DEATH:
		if (_Hp > 0) _state = P_STAND;
		break;
	case P_MOUNT:

		break;
	case P_WALKBACK:

		break;
	case P_DAMAGED:
		if (_damagedTime < 0)
		{
			if (_isOnBattle)
			{
				_state = P_READYTOATTACK;
			}
			else
			{
				_state = P_STAND;
			}
		}
		_damagedTime -= _timeDelta;

		break;
	case P_END:

		break;
	default:
		break;
	}
}

//플레이어의 상태에 따른 애니메이션의 처리
void xPlayer::playerAnimationManager()
{
	if (_prevState == _state) return;
	switch (_state)
	{
	case P_STAND:
		_playSpeed = 1.0f;
		_playerObject->_skinnedAnim->Play("S", 0.2f);
		break;
	case P_RUN:
		_playerObject->_skinnedAnim->Play("R", 0.2f);
		break;
	case P_MOVE:
		_playerObject->_skinnedAnim->Play("W", 0.2f);
		break;
	case P_READYTOATTACK:
		_playerObject->_skinnedAnim->Play("RD1H", 0.3f);
		break;
	case P_ATTACK:
		_playerObject->_skinnedAnim->Play("AT2H", 0.3f);
		break;
	case P_READYSPELL:
		_playerObject->_skinnedAnim->Play("RDSD", 0.2f);
		break;
	case P_CASTSPELL:
		_playSpeed = 1.0f;
		_playerObject->_skinnedAnim->Play("SPCD", 0.2f);
		break;
	case P_READYOMNI:
		_playerObject->_skinnedAnim->Play("RDSO", 0.2f);
		break;
	case P_CASTOMNI:
		_playerObject->_skinnedAnim->Play("SPCO", 0.2f);
		break;
	case P_JUMPUP:
		_playerObject->_skinnedAnim->Play("JUMPST", 0.2f);
		break;
	case P_JUMP:
		_playerObject->_skinnedAnim->Play("JUMP", 0.2f);
		break;
	case P_JUMPDOWN:
		_playerObject->_skinnedAnim->Play("JUMPED", 0.2f);
		break;
	case P_STUN:
		_playerObject->_skinnedAnim->Play("STUN");
		break;
	case P_DEATH:
		_playerObject->_skinnedAnim->PlayOneShotAfterHold("D", 0.2f);
		break;
	case P_MOUNT:
		_playerObject->_skinnedAnim->Play("M", 0.2f);
		break;
	case P_WALKBACK:
		_playerObject->_skinnedAnim->Play("WB", 0.2f);
		break;
	case P_DAMAGED:
		_playerObject->_skinnedAnim->Play("DM", 0.2f);
		break;
	case P_END:
		break;
	default:
		break;
	}
}


void xPlayer::playerAttack()
{
	//해당상태가 아니면 행동하지 말아라.
	if (!(_state == P_STAND || _state == P_RUN || _state == P_MOVE || _state == P_WALKBACK || _state == P_READYTOATTACK)) { return; }

	_state = P_ATTACK;
}

void xPlayer::playerSkillDirect(float castingTime)
{
	//해당상태가 아니면 행동하지 말아라.
	if (!(_state == P_STAND || _state == P_RUN || _state == P_MOVE || _state == P_WALKBACK || _state == P_READYTOATTACK)) { return; }

	//캐스팅 타임 저장.
	_castingTime = castingTime;
	_playSpeed = 1.0f / castingTime;
	_state = P_READYSPELL;

}

void xPlayer::playerSkillOmni(float castingTime)
{
	//해당상태가 아니면 행동하지 말아라.
	if (!(_state == P_STAND || _state == P_RUN || _state == P_MOVE || _state == P_WALKBACK || _state == P_READYTOATTACK)) { return; }
	_castingTime = castingTime;
	_playSpeed = 1.0f / castingTime;
	_state = P_READYOMNI;

}

void xPlayer::playerJump()
{
	if (!(_state == P_STAND || _state == P_RUN || _state == P_MOVE || _state == P_WALKBACK || _state == P_READYTOATTACK)) { return; }
	//점프의 조건
	//지형에서 떨어지면 지형의 값과 상관없이 움직여야됨.
	//일단 보류 하면 뭘 하지..? 지형 부터 해보자.
}

//플레이어 피격시 처리 및 스턴처리.
//피격시간 최대 0.6초
//스턴시간 최대 2초가 자연스러움. 그 이상은 좀 부자연스럽.
void xPlayer::playerDamaged(int damage, float damagedTime, float delayRate, float StunRate, float StunedTime)
{
	this->_Hp = this->_Hp - damage;

	//무거운 공격! 경직에 걸렸다.
	if (delayRate > RandomFloatRange(0, 100.0))
	{
		_state = P_DAMAGED;
		_playSpeed = (float)(_playerObject->_skinnedAnim->getSkinnedMesh()->getAnimMap().find("DM")->second->GetPeriod() - 0.2) / damagedTime;
		this->_damagedTime = damagedTime;
	}

	if (StunRate > RandomFloatRange(0, 100.0))
	{
		_state = P_STUN;
		_playSpeed = (float)(_playerObject->_skinnedAnim->getSkinnedMesh()->getAnimMap().find("STUN")->second->GetPeriod() - 0.2) / StunedTime;
		this->_stunnedTime = StunedTime;
	}
}