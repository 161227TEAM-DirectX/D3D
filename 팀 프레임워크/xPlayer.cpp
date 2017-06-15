#include "stdafx.h"
#include "xPlayer.h"
#include "monster.h"


HRESULT xPlayer::init()
{

	//테스트용 라이트 스킬
	_lightSkill = new SK_Boss00;
	_skillTrans = new dx::transform;
	_lightSkill->init();
	//_lightSkill->Reset();
	

	//메시 로딩
	_state = P_STAND;
	_prevState = P_STAND;
	PLAYERMANAGER->SetArmor(A_LEATHER);
	PLAYERMANAGER->SetWeapon(W_BROAD);
	PLAYERMANAGER->SetShield(SH_KITE);
	PLAYERMANAGER->SetHp(10);

	_damagedTime = 0.0f;
	_stunnedTime = 0.0f;
	_castingTime = 0.0f;
	_playSpeed = 1.0f;
	_degree = 0.0f;
	_baseHeight = 0.0f;
	_jumpPower = 5.0f;
	_jumpSpeed = 3.0f;
	_jumpHeight = 0.0f;

	_moveSpeed = 0.5f;

	_isOnBattle = false;



	//데이터를 로딩해 이전의 스테이터스와 장비상태를 초기화한다.
	LoadData();
	xMeshSkinned* pSkinned;
	D3DXMATRIXA16 matCorrection;
	D3DXMATRIXA16 matScale;
	D3DXMATRIXA16 matRotate;
	D3DXMatrixScaling(&matScale, 1, 1, 1);
	D3DXMatrixRotationY(&matRotate, D3DXToRadian(180));
	matCorrection = matRotate*matScale;


	switch (PLAYERMANAGER->GetArmor())
	{
	case A_NONE:
		pSkinned =
			RM_SKINNED->getResource("Resources/Player/FHUMAN_NONE/FHUMAN.X", &matCorrection);
		break;

	case A_ROBE:
		pSkinned =
			RM_SKINNED->getResource("Resources/Player/FHUMAN_ROBE/FHUMAN.X", &matCorrection);
		break;

	case A_LEATHER:
		pSkinned =
			RM_SKINNED->getResource("Resources/Player/FHUMAN_LEATHER/FHUMAN.X", &matCorrection);
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

	//float tempY = linkTerrain->getHeight(_playerObject->_transform->GetWorldPosition().x, _playerObject->_transform->GetWorldPosition().z);

	//_playerObject->_transform->SetWorldPosition(D3DXVECTOR3(_playerObject->_transform->GetWorldPosition().x, tempY, _playerObject->_transform->GetWorldPosition().z));


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
	D3DXMATRIXA16 matCorrection2, matScale2, matRotate2;
	D3DXMatrixIdentity(&matCorrection2);
	//D3DXMatrixRotationY(&matRotate2, D3DXToRadian(270)); //1, 2
	D3DXMatrixRotationZ(&matRotate2, D3DXToRadian(0)); // 3,4,5
	//D3DXMatrixScaling(&matScale2, 0.25, 0.25, 0.25); // 2
	D3DXMatrixScaling(&matScale2, 0.5, 0.5, 0.5); // 1,3,4,5
	matCorrection2 = matRotate2*matScale2;

	xMeshStatic* pSkinned2;
	pSkinned2 = new xMeshStatic;

	//웨폰 오브젝트 초기화 디폴트로 블랙윙을 가져오고 w_none이면 액티브 하지 않는다.
	_weaponObject = new baseObject;

	switch (PLAYERMANAGER->GetWeapon())
	{
	case W_NONE:
		pSkinned2 = RM_XMESH->getResource("Resources/item/Sword/weapon01/weapon01.X", &matCorrection2);
		_weaponObject->setActive(false);
		_renderObjects.push_back(_weaponObject);
		break;
	case W_BLACK_WING:
		D3DXMatrixRotationY(&matRotate2, D3DXToRadian(270));
		D3DXMatrixScaling(&matScale2, 0.5, 0.5, 0.5);
		matCorrection2 = matRotate2*matScale2;
		pSkinned2 = RM_XMESH->getResource("Resources/item/Sword/weapon01/weapon01.X", &matCorrection2);
		_weaponObject->setActive(true);
		_renderObjects.push_back(_weaponObject);
		break;
	case W_BROAD:
		D3DXMatrixRotationY(&matRotate2, D3DXToRadian(270));
		D3DXMatrixScaling(&matScale2, 0.25, 0.25, 0.25);
		matCorrection2 = matRotate2*matScale2;

		pSkinned2 = RM_XMESH->getResource("Resources/item/Sword/weapon02/weapon02.X", &matCorrection2);
		_weaponObject->setActive(true);
		_renderObjects.push_back(_weaponObject);
		break;
	case W_DEAMON:
		D3DXMatrixRotationZ(&matRotate2, D3DXToRadian(0));
		D3DXMatrixScaling(&matScale2, 0.5, 0.5, 0.5);
		matCorrection2 = matRotate2*matScale2;

		pSkinned2 = RM_XMESH->getResource("Resources/item/Sword/weapon03/weapon03.X", &matCorrection2);
		_weaponObject->setActive(true);
		_renderObjects.push_back(_weaponObject);
		break;
	case W_KATANA:
		D3DXMatrixRotationZ(&matRotate2, D3DXToRadian(0));
		D3DXMatrixScaling(&matScale2, 0.5, 0.5, 0.5);
		matCorrection2 = matRotate2*matScale2;

		pSkinned2 = RM_XMESH->getResource("Resources/item/Sword/weapon04/weapon04.X", &matCorrection2);
		_weaponObject->setActive(true);
		_renderObjects.push_back(_weaponObject);
		break;
	case W_WOOD:
		D3DXMatrixRotationZ(&matRotate2, D3DXToRadian(0));
		D3DXMatrixScaling(&matScale2, 0.33, 0.33, 0.33);
		matCorrection2 = matRotate2*matScale2;

		pSkinned2 = RM_XMESH->getResource("Resources/item/Sword/weapon05/weapon05.X", &matCorrection2);
		_weaponObject->setActive(true);
		_renderObjects.push_back(_weaponObject);
		break;
	case W_END:
		break;
	default:
		break;
	}

	_weaponObject->setMesh(pSkinned2);


	D3DXMATRIXA16 matCorrection3, matScale3, matRotate3;
	D3DXMatrixIdentity(&matCorrection3);
	D3DXMatrixRotationY(&matRotate3, D3DXToRadian(270));
	D3DXMatrixScaling(&matScale3, 0.25f, 0.25f, 0.25f);
	matCorrection3 = matRotate3 * matScale3;
	xMeshStatic* pSkinned3;
	pSkinned3 = new xMeshStatic;
	_shieldObject = new baseObject;

	switch (PLAYERMANAGER->GetShield())
	{
	case SH_NONE:
		pSkinned3 = RM_XMESH->getResource("Resources/item/Shield/shield01/shield01.X", &matCorrection3);
		_shieldObject->setActive(false);
		_renderObjects.push_back(_shieldObject);
		break;
	case SH_SPIKE:
		D3DXMatrixRotationY(&matRotate3, D3DXToRadian(270));//실드 1, 2
		D3DXMatrixScaling(&matScale3, 0.25f, 0.25f, 0.25f);
		matCorrection3 = matRotate3 * matScale3;

		pSkinned3 = RM_XMESH->getResource("Resources/item/Shield/shield01/shield01.X", &matCorrection3);
		_shieldObject->setActive(true);
		_renderObjects.push_back(_shieldObject);
		break;
	case SH_BUCKLER:
		D3DXMatrixRotationY(&matRotate3, D3DXToRadian(270));//실드 1, 2
		D3DXMatrixScaling(&matScale3, 0.2f, 0.2f, 0.2f);
		matCorrection3 = matRotate3 * matScale3;

		pSkinned3 = RM_XMESH->getResource("Resources/item/Shield/shield02/shield02.X", &matCorrection3);
		_shieldObject->setActive(true);
		_renderObjects.push_back(_shieldObject);
		break;
	case SH_BRONZE:
		D3DXMatrixRotationZ(&matRotate3, D3DXToRadian(270));//실드 3, 4, 5
		D3DXMatrixScaling(&matScale3, 0.5f, 0.5f, 0.5f);
		matCorrection3 = matRotate3 * matScale3;

		pSkinned3 = RM_XMESH->getResource("Resources/item/Shield/shield03/shield03.X", &matCorrection3);
		_shieldObject->setActive(true);
		_renderObjects.push_back(_shieldObject);
		break;
	case SH_CROSS:
		D3DXMatrixRotationZ(&matRotate3, D3DXToRadian(270));//실드 3, 4, 5
		D3DXMatrixScaling(&matScale3, 0.25f, 0.25f, 0.25f);
		matCorrection3 = matRotate3 * matScale3;

		pSkinned3 = RM_XMESH->getResource("Resources/item/Shield/shield04/shield04.X", &matCorrection3);
		_shieldObject->setActive(true);
		_renderObjects.push_back(_shieldObject);
		break;
	case SH_KITE:
		D3DXMatrixRotationZ(&matRotate3, D3DXToRadian(270));//실드 3, 4, 5
		D3DXMatrixScaling(&matScale3, 0.25f, 0.25f, 0.25f);
		matCorrection3 = matRotate3 * matScale3;

		pSkinned3 = RM_XMESH->getResource("Resources/item/Shield/shield05/shield05.X", &matCorrection3);
		_shieldObject->setActive(true);
		_renderObjects.push_back(_shieldObject);
		break;
	case SH_END:
		break;
	default:
		break;
	}

	_shieldObject->setMesh(pSkinned3);


	_playerObject->_skinnedAnim->Play("S", 0.3F);
	return S_OK;
}

void xPlayer::update()
{
	PLAYERMANAGER->SetPos(_playerObject->_transform->GetWorldPosition());

	_lightSkill->update();

	_playerObject->_skinnedAnim->SetPlaySpeed(_playSpeed);
	
	if (!KEYMANAGER->isToggleKey(VK_CAPITAL))
	{
		userPlayerControl();
	}
	playerStateManager();
	playerAnimationManager();

	_prevState = _state;
}

void xPlayer::render()
{
	_lightSkill->render();
	//렌더링은 씬에 렌더오브젝트를 넘겨 처리한다.
	if (KEYMANAGER->isToggleKey(VK_F7))
	{
		_playerObject->_boundBox.renderGizmo(_playerObject->_transform);
		_attackBound.renderGizmo(_playerObject->_transform);

		FONTMANAGER->fontOut(to_string(_state), 100, 0, 0xffffffff);

		FONTMANAGER->fontOut("HP : " + to_string(PLAYERMANAGER->GetHp()), 300, 0, 0xffffffff);

		FONTMANAGER->fontOut("base : " + to_string(_baseHeight), 300, 25, 0xffffffff);

		FONTMANAGER->fontOut("Degree : " + to_string(_degree), 300, 50, 0xffffffff);

		FONTMANAGER->fontOut("posX : " + to_string(_playerObject->_transform->GetWorldPosition().x), 600, 0, 0xffff0000);

		FONTMANAGER->fontOut("posY : " + to_string(_playerObject->_transform->GetWorldPosition().y), 600, 25, 0xff00ff00);

		FONTMANAGER->fontOut("posZ : " + to_string(_playerObject->_transform->GetWorldPosition().z), 600, 50, 0xff0000ff);
	

		RM_SKINNED->getResource("Resources/Player/FHUMAN_PLATE/FHUMAN.X")->ShowAnimationName(0, 0);
	}
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


void xPlayer::userPlayerControl()//이 친구가 상태값에 종속 적이라면?
{
	switch (_state)
	{
	case P_STAND:
		moveControl();
		actionControl();
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			_state = P_RUN;
		}
		if (KEYMANAGER->isStayKeyDown('S'))
		{
			_state = P_WALKBACK;
		}
		break;
	case P_RUN:
		moveControl();
		actionControl();
		if (!KEYMANAGER->isStayKeyDown('W'))
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
		break;
	case P_MOVE:

		break;
	case P_READYTOATTACK:
		moveControl();
		actionControl();
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			_state = P_RUN;
		}
		if (KEYMANAGER->isStayKeyDown('S'))
		{
			_state = P_WALKBACK;
		}
		break;
	case P_ATTACK:
		break;
	case P_ATTACK2:
		break;
	case P_ATTACK3:
		break;
	case P_ATTACK4:
		break;
	case P_ATTACK5:
		break;
	case P_READYSPELL:
		break;
	case P_CASTSPELL:
		break;
	case P_READYOMNI:
		break;
	case P_CASTOMNI:
		break;
	case P_JUMPUP:
		moveControl();
		break;
	case P_JUMP:
		moveControl();
		break;
	case P_JUMPDOWN:
		break;
	case P_STUN:
		break;
	case P_DEATH:
		break;
	case P_MOUNT:
		break;
	case P_WALKBACK:
		moveControl();
		actionControl();
		if (!KEYMANAGER->isStayKeyDown('S'))
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
		break;
	case P_DAMAGED:
		break;
	case P_END:
		break;
	default:
		break;
	}


	
}

//플레이어의 자동적인 상태변화를 관리한다.
//이 부분에서 플레이어의 애니메이션을 변화시키지 않아야 함. -> 과연 그럴까?
//시간이 지남에 따라 혹은 수치값의 변동에 따라 자동적으로 변화해야 하는 경우를 지정한다.
void xPlayer::playerStateManager()
{
	if (PLAYERMANAGER->GetHp() <= 0) _state = P_DEATH;
	string animName = _playerObject->_skinnedAnim->getAnimationSet()->GetName();
	D3DXVECTOR3 pos = _playerObject->_transform->GetWorldPosition();
	switch (_state)
	{
	case P_STAND:
		setHeight();
		//서있는다고 시간지나도 변할거 없음.
		break;
	case P_RUN:
		setHeight();
		//시간지나도 변할게 없음.
		break;
	case P_MOVE:
		setHeight();
		//시간지나도 변할게 없음.
		break;
	case P_READYTOATTACK:

		break;
	case P_ATTACK:

		if (animName == "AT1H")
		{
			if (_playerObject->_skinnedAnim->getAnimFactor() > 0.95)//애니메이션 다 재생했으면
			{
				//if (PHYSICSMANAGER->isOverlap(_playerObject->_transform, &_attackBound, targetMonster->_transform, &targetMonster->_boundBox))
				//{
				//	//exit(0);
				//}

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
	case P_ATTACK2:
		if (animName == "AT2H")
		{
			if (_playerObject->_skinnedAnim->getAnimFactor() > 0.95)//애니메이션 다 재생했으면
			{
				//if (PHYSICSMANAGER->isOverlap(_playerObject->_transform, &_attackBound, targetMonster->_transform, &targetMonster->_boundBox))
				//{
				//	//exit(0);
				//}

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
	case P_ATTACK3:
		if (animName == "AT2HL")
		{
			if (_playerObject->_skinnedAnim->getAnimFactor() > 0.95)//애니메이션 다 재생했으면
			{
				//if (PHYSICSMANAGER->isOverlap(_playerObject->_transform, &_attackBound, targetMonster->_transform, &targetMonster->_boundBox))
				//{
				//	//exit(0);
				//}

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
	case P_ATTACK4:

		if (animName == "AT2H2")
		{
			if (_playerObject->_skinnedAnim->getAnimFactor() > 0.95)//애니메이션 다 재생했으면
			{
				//if (PHYSICSMANAGER->isOverlap(_playerObject->_transform, &_attackBound, targetMonster->_transform, &targetMonster->_boundBox))
				//{
				//	//exit(0);
				//}

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
	case P_ATTACK5:

		if (animName == "AT2HL2")
		{
			if (_playerObject->_skinnedAnim->getAnimFactor() > 0.95)//애니메이션 다 재생했으면
			{
				//if (PHYSICSMANAGER->isOverlap(_playerObject->_transform, &_attackBound, targetMonster->_transform, &targetMonster->_boundBox))
				//{
				//	//exit(0);
				//}

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
		if (animName == "SPCD")
		{


			if (_playerObject->_skinnedAnim->getAnimFactor() > 0.95)//애니메이션 다 재생했으면
			{



				_skillTrans->SetWorldMatrix(_EquipSocket.find("LHAND")->second->CombinedTransformationMatrix);
				_lightSkill->setPlayer(_skillTrans);
				_lightSkill->setPlayerDir(_playerObject->_transform);
				_lightSkill->Start();
/*
				if (_isOnBattle)
				{
					_state = P_READYTOATTACK;
				}
				else
				{
					_state = P_STAND;
				}*/
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
		if (animName == "SPCO")
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

		if (animName == "JUMPST")
		{
		
			// -(x - a)^2 + b = y 
			// x == 0 일때 y == 0 이려면 
			//-x^2 + 2ax -a^2 + b = 0; 
			//-a^2 + b = 0;
			//b = a^2;

			_degree += _jumpSpeed * _timeDelta;
			_jumpHeight = _baseHeight - pow(_degree - sqrt(_jumpPower), 2.0) + _jumpPower;
			_playerObject->_transform->SetWorldPosition(pos.x, _jumpHeight, pos.z);
			
			pos = _playerObject->_transform->GetWorldPosition();

			if (_playerObject->_skinnedAnim->getAnimFactor() > 0.90)//애니메이션 다 재생했으면
			{
				_state = P_JUMP;
			}
			else if(pos.y < linkTerrain->getHeight(pos.x, pos.z))
			{
				_degree = 0;
				_state = P_JUMPDOWN;
				_playerObject->_transform->SetWorldPosition(pos.x, linkTerrain->getHeight(pos.x, pos.z), pos.z);
			}

		}


		break;
	case P_JUMP:
		if (animName == "JUMP")
		{
			_degree += _jumpSpeed * _timeDelta;
			_jumpHeight = _baseHeight - pow(_degree - sqrt(_jumpPower), 2.0) + _jumpPower;

			_playerObject->_transform->SetWorldPosition(pos.x, _jumpHeight, pos.z);

			pos = _playerObject->_transform->GetWorldPosition();

			if (pos.y < linkTerrain->getHeight(pos.x, pos.z))
			{
				_degree = 0;
				_state = P_JUMPDOWN;
				_playerObject->_transform->SetWorldPosition(pos.x, linkTerrain->getHeight(pos.x, pos.z), pos.z);
			}
		}
		break;
	case P_JUMPDOWN:
		if (animName == "JUMPED")
		{
			if (_playerObject->_skinnedAnim->getAnimFactor() > 0.5)//애니메이션 다 재생했으면
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
		if (PLAYERMANAGER->GetHp() > 0) _state = P_STAND;
		break;
	case P_MOUNT:

		break;
	case P_WALKBACK:
		setHeight();
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
		_playSpeed = 1.0f;
		_playerObject->_skinnedAnim->Play("RD1H", 0.3f);
		break;
	case P_ATTACK:
		_playerObject->_skinnedAnim->Play("AT1H", 0.3f);
		break;
	case P_ATTACK2:
		_playerObject->_skinnedAnim->Play("AT2H", 0.3f);
		break;
	case P_ATTACK3:
		_playerObject->_skinnedAnim->Play("AT2HL", 0.3f);
		break;
	case P_ATTACK4:
		_playerObject->_skinnedAnim->Play("AT2H2", 0.3f);
		break;
	case P_ATTACK5:
		_playerObject->_skinnedAnim->Play("AT2HL2", 0.3f);
		break;
	case P_READYSPELL:
		_playerObject->_skinnedAnim->Play("RDSD", 0.2f);
		break;
	case P_CASTSPELL:
		_playSpeed = 1.0f;
		_playerObject->_skinnedAnim->PlayOneShotAfterHold("SPCD", 0.2f);
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
		_playerObject->_skinnedAnim->Play("JUMP");
		break;
	case P_JUMPDOWN:
		_playerObject->_skinnedAnim->Play("JUMPED");
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


//외부의 입력에 대해 플레이어의 이동을 제어.
void xPlayer::moveControl()
{
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		_playerObject->_transform->MovePositionWorld(_playerObject->_transform->GetForward()*0.05 *_moveSpeed);
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		_playerObject->_transform->MovePositionWorld(-_playerObject->_transform->GetForward()*0.025*_moveSpeed);
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_playerObject->_transform->RotateSelf(0.0f, -D3DXToRadian(3), 0.0f);
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_playerObject->_transform->RotateSelf(0.0f, D3DXToRadian(3), 0.0f);
	}
}

void xPlayer::actionControl()
{


	if (KEYMANAGER->isOnceKeyDown(VK_TAB))
	{
		if (_isOnBattle == true)
		{
			_isOnBattle = false;
			_state = P_STAND;
		}
		else
		{
			_isOnBattle = true;
			_state = P_READYTOATTACK;
		}
	}

	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		//데미지, 경직시간, 경직확률, 스턴확률, 스턴시간 
		//playerDamaged(1, 0.5, 100.0, 0.0, 0.0);
		playerSkillDirect(1.0f);

	}

	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		playerDamaged(1, 0.5, 100.0, 100.0, 2.0);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		//_moveSpeed = _jumpPower;
		_state = P_JUMPUP;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		playerAttack();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		
		//playerSkillDirect(1.0f);
	}
}

//플레이어 공격을 제어
void xPlayer::playerAttack()
{
	//해당상태가 아니면 행동하지 말아라.
	if (!(_state == P_STAND || _state == P_RUN || _state == P_MOVE || _state == P_WALKBACK || _state == P_READYTOATTACK)) { return; }

	float rand = RandomFloatRange(0, 100);
	if (rand > 80.0f)
	{
		_state = P_ATTACK;//AT1H
	}
	else if (rand > 60.0f)
	{
		_state = P_ATTACK2;//AT2H
		_playSpeed = 1.5f;
	}
	else if (rand > 40.0f)
	{
		_state = P_ATTACK3;//AT2HL
		_playSpeed = 1.5f;
	}
	else if (rand > 20.0f)
	{
		_state = P_ATTACK4;//AT2H2
		_playSpeed = 1.5f;
	}
	else
	{
		_state = P_ATTACK5;//AT2HL2
		_playSpeed = 1.5f;
	}

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


//플레이어 피격시 처리 및 스턴처리.
//피격시간 최대 0.6초
//스턴시간 최대 2초가 자연스러움. 그 이상은 좀 부자연스럽.
void xPlayer::playerDamaged(int damage, float damagedTime, float delayRate, float StunRate, float StunedTime)
{
	PLAYERMANAGER->SetHp(PLAYERMANAGER->GetHp() - damage);

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

void xPlayer::setHeight()
{
	D3DXVECTOR3 pos = _playerObject->_transform->GetWorldPosition();
	_baseHeight = linkTerrain->getHeight(pos.x, pos.z);
	_playerObject->_transform->SetWorldPosition(pos.x, _baseHeight, pos.z);
}

void xPlayer::itemUpdate()
{

	if (PLAYERMANAGER->GetWeapon() != W_NONE)
	{
		D3DXMATRIX matHand = _EquipSocket.find("RHAND")->second->CombinedTransformationMatrix;
		_weaponObject->_transform->SetWorldMatrix(matHand);
		//_weaponObject->update();
	}

	if (PLAYERMANAGER->GetShield() != SH_NONE)
	{
		D3DXMATRIX matShield = _EquipSocket.find("SHIELD")->second->CombinedTransformationMatrix;
		_shieldObject->_transform->SetWorldMatrix(matShield);
		//_shieldObject->update();
	}
}