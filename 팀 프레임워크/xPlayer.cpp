#include "stdafx.h"
#include "xPlayer.h"
#include "monster.h"


HRESULT xPlayer::init()
{
	_handTrans = new dx::transform;
	_edgeTrans = new dx::transform;

	//테스트용 라이트 스킬
	//_lightSkill = new SK_Boss00;
	//_skillTrans = new dx::transform;
	//_lightSkill->init();
	//_lightSkill->Reset();

	D3DXVECTOR3 pos4[4] = { D3DXVECTOR3(-1,-1,-2),D3DXVECTOR3(1,1,1),D3DXVECTOR3(2,2,2),D3DXVECTOR3(3,3,3) };

	D3DXVECTOR3 pos1 = { 0,0,0 };

	D3DXVec3CatmullRom(&pos1, &pos4[0], &pos4[1], &pos4[2], &pos4[3], -1.0f);

	//-1.0~2.0





	//메시 로딩
	_state = P_STAND;
	_prevState = P_STAND;
	PLAYERMANAGER->SetArmor(A_PLATE);
	PLAYERMANAGER->SetWeapon(W_BROAD);
	PLAYERMANAGER->SetShield(SH_CROSS);
	PLAYERMANAGER->Setatt(1000000);
	PLAYERMANAGER->SetHp(100000000);
	PLAYERMANAGER->SetCrit(20.0f);

	_damagedTime = 0.0f;
	_stunnedTime = 0.0f;
	_castingTime = 0.0f;
	_playSpeed = 1.0f;

	_baseHeight = 0.0f;
	_jumpPower = 3.0f;
	_jumpSpeed = 3.0f;
	_jumpHeight = 0.0f;
	_degree = 0;

	_moveSpeed = 1.5;

	_isOnBattle = false;
	_isJump = false;
	_isBladePosInit = false;


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
			RM_SKINNED->getResource("Resource/Player/FHUMAN_NONE/FHUMAN.X", &matCorrection);
		break;

	case A_ROBE:
		pSkinned =
			RM_SKINNED->getResource("Resource/Player/FHUMAN_ROBE/FHUMAN.X", &matCorrection);
		break;

	case A_LEATHER:
		pSkinned =
			RM_SKINNED->getResource("Resource/Player/FHUMAN_LEATHER/FHUMAN.X", &matCorrection);
		break;

	case A_PLATE:
		pSkinned =
			RM_SKINNED->getResource("Resource/Player/FHUMAN_PLATE/FHUMAN.X", &matCorrection);
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
		pSkinned2 = RM_XMESH->getResource("Resource/item/Sword/weapon01/weapon01.X", &matCorrection2);
		_weaponObject->setActive(false);
		_renderObjects.push_back(_weaponObject);
		break;
	case W_BLACK_WING:
		D3DXMatrixRotationY(&matRotate2, D3DXToRadian(270));
		D3DXMatrixScaling(&matScale2, 0.5, 0.5, 0.5);
		matCorrection2 = matRotate2*matScale2;
		pSkinned2 = RM_XMESH->getResource("Resource/item/Sword/weapon01/weapon01.X", &matCorrection2);
		_weaponObject->setActive(true);
		_renderObjects.push_back(_weaponObject);
		break;
	case W_BROAD:
		D3DXMatrixRotationY(&matRotate2, D3DXToRadian(270));
		D3DXMatrixScaling(&matScale2, 0.25, 0.25, 0.25);
		matCorrection2 = matRotate2*matScale2;

		pSkinned2 = RM_XMESH->getResource("Resource/item/Sword/weapon02/weapon02.X", &matCorrection2);
		_weaponObject->setActive(true);
		_renderObjects.push_back(_weaponObject);
		break;
	case W_DEAMON:
		D3DXMatrixRotationZ(&matRotate2, D3DXToRadian(0));
		D3DXMatrixScaling(&matScale2, 0.5, 0.5, 0.5);
		matCorrection2 = matRotate2*matScale2;

		pSkinned2 = RM_XMESH->getResource("Resource/item/Sword/weapon03/weapon03.X", &matCorrection2);
		_weaponObject->setActive(true);
		_renderObjects.push_back(_weaponObject);
		break;
	case W_KATANA:
		D3DXMatrixRotationZ(&matRotate2, D3DXToRadian(0));
		D3DXMatrixScaling(&matScale2, 0.5, 0.5, 0.5);
		matCorrection2 = matRotate2*matScale2;

		pSkinned2 = RM_XMESH->getResource("Resource/item/Sword/weapon04/weapon04.X", &matCorrection2);
		_weaponObject->setActive(true);
		_renderObjects.push_back(_weaponObject);
		break;
	case W_WOOD:
		D3DXMatrixRotationZ(&matRotate2, D3DXToRadian(0));
		D3DXMatrixScaling(&matScale2, 0.33, 0.33, 0.33);
		matCorrection2 = matRotate2*matScale2;

		pSkinned2 = RM_XMESH->getResource("Resource/item/Sword/weapon05/weapon05.X", &matCorrection2);
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
		pSkinned3 = RM_XMESH->getResource("Resource/item/Shield/shield01/shield01.X", &matCorrection3);
		_shieldObject->setActive(false);
		_renderObjects.push_back(_shieldObject);
		break;
	case SH_SPIKE:
		D3DXMatrixRotationY(&matRotate3, D3DXToRadian(270));//실드 1, 2
		D3DXMatrixScaling(&matScale3, 0.25f, 0.25f, 0.25f);
		matCorrection3 = matRotate3 * matScale3;

		pSkinned3 = RM_XMESH->getResource("Resource/item/Shield/shield01/shield01.X", &matCorrection3);
		_shieldObject->setActive(true);
		_renderObjects.push_back(_shieldObject);
		break;
	case SH_BUCKLER:
		D3DXMatrixRotationY(&matRotate3, D3DXToRadian(270));//실드 1, 2
		D3DXMatrixScaling(&matScale3, 0.2f, 0.2f, 0.2f);
		matCorrection3 = matRotate3 * matScale3;

		pSkinned3 = RM_XMESH->getResource("Resource/item/Shield/shield02/shield02.X", &matCorrection3);
		_shieldObject->setActive(true);
		_renderObjects.push_back(_shieldObject);
		break;
	case SH_BRONZE:
		D3DXMatrixRotationZ(&matRotate3, D3DXToRadian(270));//실드 3, 4, 5
		D3DXMatrixScaling(&matScale3, 0.5f, 0.5f, 0.5f);
		matCorrection3 = matRotate3 * matScale3;

		pSkinned3 = RM_XMESH->getResource("Resource/item/Shield/shield03/shield03.X", &matCorrection3);
		_shieldObject->setActive(true);
		_renderObjects.push_back(_shieldObject);
		break;
	case SH_CROSS:
		D3DXMatrixRotationZ(&matRotate3, D3DXToRadian(270));//실드 3, 4, 5
		D3DXMatrixScaling(&matScale3, 0.25f, 0.25f, 0.25f);
		matCorrection3 = matRotate3 * matScale3;

		pSkinned3 = RM_XMESH->getResource("Resource/item/Shield/shield04/shield04.X", &matCorrection3);
		_shieldObject->setActive(true);
		_renderObjects.push_back(_shieldObject);
		break;
	case SH_KITE:
		D3DXMatrixRotationZ(&matRotate3, D3DXToRadian(270));//실드 3, 4, 5
		D3DXMatrixScaling(&matScale3, 0.25f, 0.25f, 0.25f);
		matCorrection3 = matRotate3 * matScale3;

		pSkinned3 = RM_XMESH->getResource("Resource/item/Shield/shield05/shield05.X", &matCorrection3);
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

	setBladeLight();

	_playerObject->_skinnedAnim->AddBoneTransform("humanfemale_Bone121_CSR", _handTrans);
	_edgeTrans->SetWorldPosition(_handTrans->GetWorldPosition() + _handTrans->GetRight() * 0.7);
	_handTrans->AddChild(_edgeTrans);

	return S_OK;
}

void xPlayer::update()
{
	
	/*for (int i = 0; i < this->_renderObjects.size(); i++)
	{
		this->_renderObjects[i]->render();
	}*/

	PLAYERMANAGER->SetPos(_playerObject->_transform->GetWorldPosition());

	//_lightSkill->update();

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
	_handTrans->RenderGimozo();
	_edgeTrans->RenderGimozo();

	drawBladeLight();
	//_lightSkill->render();
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

		FONTMANAGER->fontOut("Height : " + to_string(_jumpHeight), 600, 75, 0xffffffff);

		RM_SKINNED->getResource("Resource/Player/FHUMAN_PLATE/FHUMAN.X")->ShowAnimationName(0, 0);
	}

	//for (int i = 0; i < this->_renderObjects.size(); i++)
	//{
	//	this->_renderObjects[i]->render();
	//	if (_renderObjects[i] == getPlayerObject())
	//	{
	//		itemUpdate();
	//	}
	//}


}

void xPlayer::release(void)
{
	for (int i = 0; i < this->_renderObjects.size(); i++)
	{
		SAFE_DELETE(this->_renderObjects[i]);
	}

	SAFE_RELEASE(_myVertexbuffer);
	SAFE_RELEASE(_myIndexBuffer);
	SAFE_RELEASE(_texture);
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
		rotateControl();

		if (!_isJump)
		{
			//moveControl();
			jumpControl();
			attackControl();
			if (KEYMANAGER->isStayKeyDown('W'))
			{
				_state = P_RUN;
			}
			if (KEYMANAGER->isStayKeyDown('S'))
			{
				_state = P_WALKBACK;
			}
		}
		else
		{
			_state = P_JUMP;
		}
		break;
	case P_RUN:
		rotateControl();
		moveControl();
		attackControl();
		jumpControl();
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
		rotateControl();

		if (!_isJump)
		{
			moveControl();
			attackControl();
			jumpControl();
			if (KEYMANAGER->isStayKeyDown('W'))
			{
				_state = P_RUN;
			}
			if (KEYMANAGER->isStayKeyDown('S'))
			{
				_state = P_WALKBACK;
			}
		}
		else
		{
			_state = P_JUMP;
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
		rotateControl();
		moveControl();
		attackControl();
		break;
	case P_JUMP:

		rotateControl();
		moveControl();
		attackControl();
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




	if (_state != P_RUN && _state != P_WALKBACK)
		SOUNDMANAGER->stop("걸음소리1");

	if (PLAYERMANAGER->GetHp() <= 0) _state = P_DEATH;
	string animName = _playerObject->_skinnedAnim->getAnimationSet()->GetName();
	D3DXVECTOR3 pos = _playerObject->_transform->GetWorldPosition();


	//이렇게 하면 높은 곳에서 뛰어 내릴 수 없음.
	if (_isJump)//점프중인가?
	{
		_degree += _jumpSpeed * _timeDelta;
		_jumpHeight = _baseHeight - pow(_degree - sqrt(_jumpPower), 2.0) + _jumpPower;
		_playerObject->_transform->SetWorldPosition(pos.x, _jumpHeight, pos.z);

		if (_playerObject->_transform->GetWorldPosition().y < _baseHeight)
		{
			_playerObject->_transform->SetWorldPosition(pos.x, _baseHeight, pos.z);
			_isJump = false;
		}
	}
	else
	{
		_degree = 0;
		_playerObject->_transform->SetWorldPosition(pos.x, _baseHeight, pos.z);
	}

	switch (_state)
	{
	case P_STAND:
		//서있는다고 시간지나도 변할거 없음.
		break;
	case P_RUN:

		if (!SOUNDMANAGER->isPlaySound("걸음소리1"))
		{
			if (animName == "R")
			{
				if (_playerObject->_skinnedAnim->getAnimFactor() > _moveSpeed / 25)//애니메이션 다 재생했으면
				{
					SOUNDMANAGER->play("걸음소리1", 0.7f);
					SOUNDMANAGER->setMusicSpeed("걸음소리1", _moveSpeed);
				}
			}
		}
		break;
	case P_MOVE:

		break;
	case P_READYTOATTACK:

		break;
	case P_ATTACK:
		updateBladeLight();
		if (animName == "AT1H")
		{
			if (_playerObject->_skinnedAnim->getAnimFactor() > 0.6)//애니메이션 다 재생했으면
			{
				//normalAttackDamageProcessing();
				//if (PHYSICSMANAGER->isOverlap(_playerObject->_transform, &_attackBound, targetMonster->_transform, &targetMonster->_boundBox))
				//{
				//	//exit(0);
				//}
				if (!_isJump)
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
				else
				{
					_state = P_JUMPDOWN;
				}
			}
		}
		break;
	case P_ATTACK2:
		updateBladeLight();
		if (!SOUNDMANAGER->isPlaySound("공격1"))
		{
			if (animName == "AT2H")
			{
				if (_playerObject->_skinnedAnim->getAnimFactor() > 0.1 &&  _playerObject->_skinnedAnim->getAnimFactor() < 0.3)//애니메이션 다 재생했으면
				{
					SOUNDMANAGER->play("공격1", 0.7f);
					SOUNDMANAGER->setMusicSpeed("걸음소리1", _moveSpeed);
				}
			}
		}

		if (animName == "AT2H")
		{
			if (_playerObject->_skinnedAnim->getAnimFactor() > 0.80)//애니메이션 다 재생했으면
			{
				//if (PHYSICSMANAGER->isOverlap(_playerObject->_transform, &_attackBound, targetMonster->_transform, &targetMonster->_boundBox))
				//{
				//	//exit(0);
				//}
				//normalAttackDamageProcessing();
				if (!_isJump)
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
				else
				{
					_state = P_JUMPDOWN;
				}
			}
		}
		break;
	case P_ATTACK3:
		updateBladeLight();
		if (animName == "AT2HL")
		{
			if (_playerObject->_skinnedAnim->getAnimFactor() > 0.7)//애니메이션 다 재생했으면
			{
				//if (PHYSICSMANAGER->isOverlap(_playerObject->_transform, &_attackBound, targetMonster->_transform, &targetMonster->_boundBox))
				//{
				//	//exit(0);
				//}
				//normalAttackDamageProcessing();
				if (!_isJump)
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
				else
				{
					_state = P_JUMPDOWN;
				}
			}
		}
		break;
	case P_ATTACK4:
		updateBladeLight();
		if (animName == "AT2H2")
		{
			if (_playerObject->_skinnedAnim->getAnimFactor() > 0.2  && _playerObject->_skinnedAnim->getAnimFactor() < 0.45)//애니메이션 다 재생했으면
			{
				//if (PHYSICSMANAGER->isOverlap(_playerObject->_transform, &_attackBound, targetMonster->_transform, &targetMonster->_boundBox))
				//{
				//	//exit(0);
				//}
				_playSpeed = 1.8f;

			}
			else if (_playerObject->_skinnedAnim->getAnimFactor() > 0.4)//애니메이션 다 재생했으면
			{
				//normalAttackDamageProcessing();
				if (_isOnBattle)
				{
					_state = P_ATTACK;

					//_state = P_READYTOATTACK;
				}
				else
				{
					_state = P_ATTACK;

					//_state = P_STAND;
				}
			}
		}
		break;
	case P_ATTACK5:
		updateBladeLight();
		if (animName == "AT2HL2")
		{
			if (_playerObject->_skinnedAnim->getAnimFactor() > 0.5 && _playerObject->_skinnedAnim->getAnimFactor() < 0.8)//애니메이션 다 재생했으면
			{
				//if (PHYSICSMANAGER->isOverlap(_playerObject->_transform, &_attackBound, targetMonster->_transform, &targetMonster->_boundBox))
				//{
				//	//exit(0);
				//}
				_playSpeed = 1.0f;
			}
			else if (_playerObject->_skinnedAnim->getAnimFactor() > 0.8)
			{
				//normalAttackDamageProcessing();
				if (!_isJump)
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
				else
				{
					_state = P_JUMPDOWN;
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
				//_skillTrans->SetWorldMatrix(_EquipSocket.find("LHAND")->second->CombinedTransformationMatrix);
				//_lightSkill->setPlayer(_skillTrans);
				//_lightSkill->setPlayerDir(_playerObject->_transform);
				//_lightSkill->Start();
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

			//_degree += _jumpSpeed * _timeDelta;

			//_jumpHeight = _baseHeight - pow(_degree - sqrt(_jumpPower), 2.0) + _jumpPower;
			//_playerObject->_transform->SetWorldPosition(pos.x, _jumpHeight, pos.z);

			pos = _playerObject->_transform->GetWorldPosition();

			if (_playerObject->_skinnedAnim->getAnimFactor() > 0.90)//애니메이션 다 재생했으면
			{
				_state = P_JUMP;
			}
			else if (pos.y <= linkTerrain->getHeight(pos.x, pos.z))
			{
				//_degree = 0;
				_state = P_JUMPDOWN;
				//_playerObject->_transform->SetWorldPosition(pos.x, linkTerrain->getHeight(pos.x, pos.z), pos.z);
			}

		}


		break;
	case P_JUMP:
		if (animName == "JUMP")
		{
			if (pos.y <= linkTerrain->getHeight(pos.x, pos.z))
			{
				//_degree = 0;
				_state = P_JUMPDOWN;
				//_playerObject->_transform->SetWorldPosition(pos.x, linkTerrain->getHeight(pos.x, pos.z), pos.z);
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


		if (!SOUNDMANAGER->isPlaySound("걸음소리1"))
		{
			if (animName == "WB")
			{
				if (_playerObject->_skinnedAnim->getAnimFactor() > 0.0)//애니메이션 다 재생했으면
				{
					SOUNDMANAGER->play("걸음소리1", 0.1f);
					SOUNDMANAGER->setMusicSpeed("걸음소리1", _moveSpeed * 0.5);
				}
			}
		}



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
		_playSpeed = _moveSpeed * 0.66f;//더이상 건드리지 마라..
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
		//SOUNDMANAGER->setMusicSpeed("공격1", _moveSpeed);
		SOUNDMANAGER->play("공격1", 0.7f);
		_playerObject->_skinnedAnim->Play("AT1H", 0.3f);
		
		break;
	case P_ATTACK2:
		//SOUNDMANAGER->play("공격1", 0.7f);
		_playerObject->_skinnedAnim->Play("AT2H", 0.3f);
		

		break;
	case P_ATTACK3:
		SOUNDMANAGER->play("공격1", 0.7f);
		_playerObject->_skinnedAnim->Play("AT2HL", 0.3f);
		
		break;
	case P_ATTACK4:
		SOUNDMANAGER->play("공격1", 0.7f);
		_playerObject->_skinnedAnim->Play("AT2H2", 0.3f);
		
		break;
	case P_ATTACK5:
		SOUNDMANAGER->play("공격1", 0.7f);
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
		SOUNDMANAGER->play("걸음소리1one", 1.0f);
		_playerObject->_skinnedAnim->Play("JUMPST", 0.2f);
		break;
	case P_JUMP:
		_playerObject->_skinnedAnim->Play("JUMP");
		break;
	case P_JUMPDOWN:
		SOUNDMANAGER->play("걸음소리1one", 1.0f);
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
		_playSpeed = _moveSpeed * 0.5;
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
		_playerObject->_transform->MovePositionWorld(-_playerObject->_transform->GetForward()*0.02*_moveSpeed);
	}

}

void xPlayer::rotateControl()
{
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_playerObject->_transform->RotateSelf(0.0f, -D3DXToRadian(3), 0.0f);
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_playerObject->_transform->RotateSelf(0.0f, D3DXToRadian(3), 0.0f);
	}
}

void xPlayer::attackControl()
{
	if (KEYMANAGER->isOnceKeyDown('V'))
	{
		playerAttack();
	}
}

void xPlayer::jumpControl()
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		//_moveSpeed = _jumpPower;
		//degree = 0;

		_isJump = true;
		_state = P_JUMPUP;
	}
}

void xPlayer::testControl()
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


	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{

		//playerSkillDirect(1.0f);
	}
}

void xPlayer::actionControl()
{
	moveControl();

	rotateControl();

	attackControl();

	jumpControl();

	testControl();
}

//플레이어 공격을 제어
void xPlayer::playerAttack()
{
	BladePosInit();
	//해당상태가 아니면 행동하지 말아라.
	//if (!(_state == P_STAND || _state == P_RUN || _state == P_MOVE || _state == P_WALKBACK || _state == P_READYTOATTACK)) { return; }

	//검광 위치 초기화.


	float rand = RandomFloatRange(0, 100);
	if (rand < PLAYERMANAGER->GetCrit())
	{
		_state = P_ATTACK4;//AT2H2 //크리티컬 어택!
		_playSpeed = 1.5f;

		return;
	}
	else//일반공격
	{
		rand = RandomFloatRange(0, 100);
		if (rand > 75.0f)
		{
			_state = P_ATTACK;//AT1H
			_playSpeed = 1.5f;

		}
		else if (rand > 50.0f)
		{
			_state = P_ATTACK2;//AT2H
			_playSpeed = 1.5f;
		}
		else if (rand > 25.0f)
		{
			_state = P_ATTACK3;//AT2HL
			_playSpeed = 2.0f;
		}
		else
		{
			_state = P_ATTACK5;//AT2HL2
			_playSpeed = 2.5f;
		}
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

void xPlayer::normalAttackDamageProcessing()
{
	vector<monster*>::iterator iter;

	if (_monsterPool != NULL)
	{
		for (iter = _monsterPool->begin(); iter != _monsterPool->end(); ++iter)
		{
			if (PHYSICSMANAGER->isOverlap(this->_playerObject, *iter))
			{
				(*iter)->setHP((*iter)->getHP() - PLAYERMANAGER->Getatt());
				if ((*iter)->getHP() < 0)
				{
					exit(0);
				}
				//FONTMANAGER->fontOut("때렸어!", WINSIZEX / 2, WINSIZEY / 2, 0xffffffff);
			}
		}
	}
}

void xPlayer::setBladeLight()
{

	vertexNum = 60;//한 샘플당 버텍스 개수
	//maxNum = vertexNum * 19;//전체 샘플을 그리기 위한 버텍스 개수

							//primitives = maxNum - 2;
	primitives = vertexNum - 2;

	maxNum = vertexNum;

	idx = new DWORD[vertexNum];

	////정점 버퍼 생성
	//_device->CreateVertexBuffer(
	//	sizeof(MYLIGHTVERTEX) * vertexNum,
	//	D3DUSAGE_WRITEONLY,
	//	MYLIGHTVERTEX::FVF,
	//	D3DPOOL_DEFAULT,
	//	&_myVertexbuffer,
	//	NULL);


	////인덱스 버퍼 생성
	//_device->CreateIndexBuffer(
	//	sizeof(DWORD) * vertexNum,
	//	D3DUSAGE_WRITEONLY,
	//	D3DFMT_INDEX32,
	//	D3DPOOL_DEFAULT,
	//	&_myIndexBuffer,
	//	NULL);
	// 1---2 //변경됬음. 2 <-> 3
	// |  /|	
	// | / |								
	// 0---3
	//UV를 동일하게 적용한다고 가정하였을때.

	//LPMYLIGHTVERTEX pVertices;

	float maxX = 5;
	float minX = -5;



	//memset(pVertices, 0, sizeof(MYLIGHTVERTEX)*vertexNum);

	for (int i = 0; i < vertexNum / 2; i++)
	{
		//0,2,4....
		float x = 0;
		x = ((i * 2 + 1) * ((maxX - minX) / (vertexNum - 2)) + minX);

		float u = 0;

		if (i == 0)
		{
			u = 0;
		}
		else
		{
			u = ((float)(i * 2) / (float)(vertexNum - 2));
		}
		MYLIGHTVERTEX tempVertex;

		tempVertex.pos = D3DXVECTOR3(x, -5, 0);//posHand +
		tempVertex.uv = D3DXVECTOR2(u, 1);
		_vertexDeque.push_back(tempVertex);

		//1,3,5
		float y = 0;
		y = ((i * 2) * ((maxX - minX) / (vertexNum - 2)) + minX);

		float  z = 0;
		if (i == 1)
		{
			z = 0;
		}
		else
		{
			z = ((float)(i * 2 + 1) / (float)(vertexNum - 2));
		}

		MYLIGHTVERTEX tempVertex2;
		tempVertex2.pos = D3DXVECTOR3(y, 5, 0);//posHand +
		tempVertex2.uv = D3DXVECTOR2(z, 0);

		_vertexDeque.push_back(tempVertex2);

	}


	//_myVertexbuffer->Lock(0, 0, (void**)&pVertices, 0);


	pVertices = new MYLIGHTVERTEX[_vertexDeque.size()];

	for (int i = 0; i < _vertexDeque.size(); i++)
	{
		pVertices[i] = _vertexDeque[i];
	}

	primitives = _vertexDeque.size() - 2;


	//	_myVertexbuffer->Unlock();


	for (int i = 0; i < vertexNum; i++)
	{
		idx[i] = i;
	}

	/*void* pIndices = NULL;
	_myIndexBuffer->Lock(0, 0, &pIndices, 0);
	memcpy(pIndices, idx, sizeof(DWORD) * vertexNum);
	_myIndexBuffer->Unlock();
*/

//텍스쳐 로딩
	D3DXCreateTextureFromFile(
		_device,
		"테스트.jpg",
		&_texture);


	//typedef struct tagBladeLightVertex
	//{
	//	D3DXVECTOR3 pos;			//정점 위치
	//	DWORD color;				//정점 컬러
	////	D3DXVECTOR2 uv;				//정점 UV
	//	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };//| D3DFVF_TEX1 
	//}BLADE_VERTEX, *LPBLADE_VERTEX;
	///*검의 위치...
	//검의 상대위치 = COMBINEDMATRIX... RHAND * INVERSE(INVERSE(PLAYERTRNAS->MATWORLD));
	//검의 상대위치의 B.TRANSFORM
	//검끝의 상대위치 = B.TRANSFORM.POS - (B.TRANSFORM.FORWARD * 검의 길이);
	//이 친구들이 P0.*/
	////애니메이션에 의해 변화된 현재 위치.
	////D3DXVec3CatmullRom(...)
	////애니메이션 펙터 임시저장
	//skinnedAnimation playerAnim = this->getPlayerObject()->getSkinnedAnim();//얕은복사
	//skinnedAnimation playerAnim2 = playerAnim;//깊은복사 (객체 새로 생성은 개뿔..)
	//float tempAnimFactor = playerAnim.getTrackDesc0().Position;
	////가중치 만큼 가라.
	//우선 그린다. 정점.
	//dx::transform* boneTrans = new dx::transform;
	//boneTrans->SetWorldMatrix(CloneSkinned->getSkinnedMesh()->GetFineBONE("humanfemale_Bone121_CSR")->CombinedTransformationMatrix);
	//pv3용
	//DESC3.Position = nowPeriod * 1.0;
	//playerAnim.setTrackDesc0(DESC3);
	/*CloneSkinned->setTrackDesc0(DESC_ORIGIN);
	playerAnim.updateBone();
	playerAnim.getSkinnedMesh()->GetFineBONE("humanfemale_Bone121_CSR")->CombinedTransformationMatrix;
	if (boneTrans->GetFinalMatrix() != playerAnim.getSkinnedMesh()->GetFineBONE("humanfemale_Bone121_CSR")->CombinedTransformationMatrix)
	{
	int a = 0;
	}*/
	//pv2용

}


void xPlayer::BladePosInit()
{
	//벡터 정보 초기화
	_vecPosEdge.clear();
	_vecPosHand.clear();
}

void xPlayer::updateBladeLight()
{
	_vertexDeque.clear();//덱은 비어있다.
	//현재 위치를 받는다!
	//이 정보가 계속 누적 되리!
	_vecPosEdge.push_back(_edgeTrans->GetWorldPosition());//위치정보는 얘네가 들고있다! 덱은 계속 비워준다.
	_vecPosHand.push_back(_handTrans->GetWorldPosition());

	for (int i = 0; i < _vecPosEdge.size(); i++)
	{
		MYLIGHTVERTEX tempVertex1;

		//0,2,4
		float u = 0;

		if (i == 0)
		{
			u = 0;
		}
		else
		{
			u = ((float)(i * 2) / (float)(vertexNum - 2));
		}
		//MYLIGHTVERTEX tempVertex;

		tempVertex1.pos = _vecPosHand[i]; //D3DXVECTOR3(x, 5, 0);//posHand +
		tempVertex1.uv = D3DXVECTOR2(u, 1);
		

		//1,3,5
		u = 0;
		if (i == 1)
		{
			u = 0;
		}
		else
		{
			u = ((float)(i * 2 + 1) / (float)(vertexNum - 2));
		}

		MYLIGHTVERTEX tempVertex2;
		tempVertex2.pos = _vecPosEdge[i];//posHand +
		tempVertex2.uv = D3DXVECTOR2(u, 0);

		_vertexDeque.push_back(tempVertex1);
		_vertexDeque.push_back(tempVertex2);

		////앞에거 넣기!
		//tempVertex1.pos = _vecPosEdge[1];


		//tempVertex1.uv = D3DXVECTOR2(0, 0);//칼끝!


		//_vertexDeque.push_back(tempVertex1);

		//MYLIGHTVERTEX tempVertex2;

		////앞에거 넣기!
		//tempVertex2.pos = _vecPosHand[0];
		//tempVertex2.uv = D3DXVECTOR2(0, 1);//손!

		//_vertexDeque.push_back(tempVertex2);

	}
	//memset(&pVertices, 0, sizeof(MYLIGHTVERTEX)*vertexNum);

	//pVertices = new MYLIGHTVERTEX[_vertexDeque.size()];

	for (int i = 0; i < _vertexDeque.size(); i++)
	{
		pVertices[i] = _vertexDeque[i];//정점정보 복사!
	}

	primitives = _vertexDeque.size() - 2;

	maxNum = _vertexDeque.size();

	for (int i = 0; i < _vertexDeque.size(); i++)
	{
		idx[i] = i;
		if (pVertices[i].uv.y == 0 && i / 2 == 0)
		{
			int a = 0;
		}
	}

	

	//==========================================================

	_vecPosEdge.push_back(_edgeTrans->GetWorldPosition());
	_vecPosHand.push_back(_handTrans->GetWorldPosition());
	if (_vecPosEdge.size() > vertexNum / 2)
	{
		_vecPosEdge.pop_front();
		_vecPosHand.pop_front();
	}

	primitives = _vecPosEdge.size() + _vecPosHand.size() - 2;

	for (int i = 0; i < _vecPosHand.size(); i++)
	{
		pVertices[i * 2 + 1].pos = _vecPosEdge[i];
		pVertices[i * 2].pos = _vecPosHand[i];



		float u = 0;
		if (i == 0)
		{
			u = 0;
		}
		else
		{
			u = ((float)i / (float)(vertexNum - 2));
		}

		pVertices[i * 2 + 1].uv = D3DXVECTOR2(u, 1);
	}





}

void xPlayer::drawBladeLight()
{


	////라이트기능은 잠시 꺼두자
	////====================================================================
	////			## 텍스쳐 Wrap 모드 ##
	////====================================================================
	//

	for (int i = 0; i < _vertexDeque.size(); i++)
	{
		pVertices[i].pos;
		pVertices[i].uv;
	}


	_device->SetRenderState(D3DRS_LIGHTING, FALSE);
	_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	////반복적으로 나온다 1 넘어가는 UV 좌표는 1을 빼서 다시 0부터 시작
	_device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	_device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//그리기 전에 로딩된 텍스쳐를 세팅하기
	_device->SetTexture(0, _texture);

	//정점 그리기
	//_device->SetStreamSource(0, _myVertexbuffer, 0, sizeof(MYLIGHTVERTEX));
	_device->SetFVF(MYLIGHTVERTEX::FVF);
	//_device->SetIndices(_myIndexBuffer);

	_device->DrawIndexedPrimitiveUP(D3DPT_TRIANGLESTRIP, 0, maxNum, primitives, idx, D3DFMT_INDEX32, pVertices, sizeof(MYLIGHTVERTEX));
	//텍스쳐 세팅해제

	_device->SetTexture(0, NULL);

	_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

}