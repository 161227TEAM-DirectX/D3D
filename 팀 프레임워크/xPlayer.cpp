#include "stdafx.h"
#include "xPlayer.h"
#include "monster.h"


HRESULT xPlayer::init()
{
	//�׽�Ʈ�� ����Ʈ ��ų
	//_lightSkill = new SK_Boss00;
	//_skillTrans = new dx::transform;
	//_lightSkill->init();
	//_lightSkill->Reset();
	

	//�޽� �ε�
	_state = P_STAND;
	_prevState = P_STAND;
	PLAYERMANAGER->SetArmor(A_PLATE);
	PLAYERMANAGER->SetWeapon(W_KATANA);
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



	//�����͸� �ε��� ������ �������ͽ��� �����¸� �ʱ�ȭ�Ѵ�.
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

	//���� ����
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

	//����ε� �� ������� ����
	D3DXMATRIXA16 matCorrection2, matScale2, matRotate2;
	D3DXMatrixIdentity(&matCorrection2);
	//D3DXMatrixRotationY(&matRotate2, D3DXToRadian(270)); //1, 2
	D3DXMatrixRotationZ(&matRotate2, D3DXToRadian(0)); // 3,4,5
	//D3DXMatrixScaling(&matScale2, 0.25, 0.25, 0.25); // 2
	D3DXMatrixScaling(&matScale2, 0.5, 0.5, 0.5); // 1,3,4,5
	matCorrection2 = matRotate2*matScale2;

	xMeshStatic* pSkinned2;
	pSkinned2 = new xMeshStatic;

	//���� ������Ʈ �ʱ�ȭ ����Ʈ�� ������ �������� w_none�̸� ��Ƽ�� ���� �ʴ´�.
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
		D3DXMatrixRotationY(&matRotate3, D3DXToRadian(270));//�ǵ� 1, 2
		D3DXMatrixScaling(&matScale3, 0.25f, 0.25f, 0.25f);
		matCorrection3 = matRotate3 * matScale3;

		pSkinned3 = RM_XMESH->getResource("Resource/item/Shield/shield01/shield01.X", &matCorrection3);
		_shieldObject->setActive(true);
		_renderObjects.push_back(_shieldObject);
		break;
	case SH_BUCKLER:
		D3DXMatrixRotationY(&matRotate3, D3DXToRadian(270));//�ǵ� 1, 2
		D3DXMatrixScaling(&matScale3, 0.2f, 0.2f, 0.2f);
		matCorrection3 = matRotate3 * matScale3;

		pSkinned3 = RM_XMESH->getResource("Resource/item/Shield/shield02/shield02.X", &matCorrection3);
		_shieldObject->setActive(true);
		_renderObjects.push_back(_shieldObject);
		break;
	case SH_BRONZE:
		D3DXMatrixRotationZ(&matRotate3, D3DXToRadian(270));//�ǵ� 3, 4, 5
		D3DXMatrixScaling(&matScale3, 0.5f, 0.5f, 0.5f);
		matCorrection3 = matRotate3 * matScale3;

		pSkinned3 = RM_XMESH->getResource("Resource/item/Shield/shield03/shield03.X", &matCorrection3);
		_shieldObject->setActive(true);
		_renderObjects.push_back(_shieldObject);
		break;
	case SH_CROSS:
		D3DXMatrixRotationZ(&matRotate3, D3DXToRadian(270));//�ǵ� 3, 4, 5
		D3DXMatrixScaling(&matScale3, 0.25f, 0.25f, 0.25f);
		matCorrection3 = matRotate3 * matScale3;

		pSkinned3 = RM_XMESH->getResource("Resource/item/Shield/shield04/shield04.X", &matCorrection3);
		_shieldObject->setActive(true);
		_renderObjects.push_back(_shieldObject);
		break;
	case SH_KITE:
		D3DXMatrixRotationZ(&matRotate3, D3DXToRadian(270));//�ǵ� 3, 4, 5
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

	
	drawBladeLight();
	//_lightSkill->render();
	//�������� ���� ����������Ʈ�� �Ѱ� ó���Ѵ�.
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
	//�÷��̾� ������ �̱��� �Լ��� ���� �����͸� �����Ѵ�.
}


void xPlayer::userPlayerControl()//�� ģ���� ���°��� ���� ���̶��?
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

//�÷��̾��� �ڵ����� ���º�ȭ�� �����Ѵ�.
//�� �κп��� �÷��̾��� �ִϸ��̼��� ��ȭ��Ű�� �ʾƾ� ��. -> ���� �׷���?
//�ð��� ������ ���� Ȥ�� ��ġ���� ������ ���� �ڵ������� ��ȭ�ؾ� �ϴ� ��츦 �����Ѵ�.
void xPlayer::playerStateManager()
{

	


	if (_state != P_RUN && _state != P_WALKBACK)
		SOUNDMANAGER->stop("�����Ҹ�1");

	if (PLAYERMANAGER->GetHp() <= 0) _state = P_DEATH;
	string animName = _playerObject->_skinnedAnim->getAnimationSet()->GetName();
	D3DXVECTOR3 pos = _playerObject->_transform->GetWorldPosition();


	//�̷��� �ϸ� ���� ������ �پ� ���� �� ����.
	if (_isJump)//�������ΰ�?
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
		//���ִ´ٰ� �ð������� ���Ұ� ����.
		break;
	case P_RUN:

		if (!SOUNDMANAGER->isPlaySound("�����Ҹ�1"))
		{
			if (animName == "R")
			{
				if (_playerObject->_skinnedAnim->getAnimFactor() > _moveSpeed/25)//�ִϸ��̼� �� ���������
				{
					SOUNDMANAGER->play("�����Ҹ�1", 0.7f);
					SOUNDMANAGER->setMusicSpeed("�����Ҹ�1", _moveSpeed);
				}
			}
		}
		break;
	case P_MOVE:

		break;
	case P_READYTOATTACK:

		break;
	case P_ATTACK:
		if (animName == "AT1H")
		{
			if (_playerObject->_skinnedAnim->getAnimFactor() > 0.6)//�ִϸ��̼� �� ���������
			{
				normalAttackDamageProcessing();
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
		if (!SOUNDMANAGER->isPlaySound("����1"))
		{
			if (animName == "AT2H")
			{
				if (_playerObject->_skinnedAnim->getAnimFactor() > 0.1 &&  _playerObject->_skinnedAnim->getAnimFactor() < 0.3)//�ִϸ��̼� �� ���������
				{
					SOUNDMANAGER->play("����1", 0.7f);
					SOUNDMANAGER->setMusicSpeed("�����Ҹ�1", _moveSpeed);
				}
			}
		}

		if (animName == "AT2H")
		{
			if (_playerObject->_skinnedAnim->getAnimFactor() > 0.80)//�ִϸ��̼� �� ���������
			{
				//if (PHYSICSMANAGER->isOverlap(_playerObject->_transform, &_attackBound, targetMonster->_transform, &targetMonster->_boundBox))
				//{
				//	//exit(0);
				//}
				normalAttackDamageProcessing();
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
		if (animName == "AT2HL")
		{
			if (_playerObject->_skinnedAnim->getAnimFactor() > 0.7)//�ִϸ��̼� �� ���������
			{
				//if (PHYSICSMANAGER->isOverlap(_playerObject->_transform, &_attackBound, targetMonster->_transform, &targetMonster->_boundBox))
				//{
				//	//exit(0);
				//}
				normalAttackDamageProcessing();
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

		if (animName == "AT2H2")
		{
			if (_playerObject->_skinnedAnim->getAnimFactor() > 0.2  && _playerObject->_skinnedAnim->getAnimFactor() < 0.45)//�ִϸ��̼� �� ���������
			{
				//if (PHYSICSMANAGER->isOverlap(_playerObject->_transform, &_attackBound, targetMonster->_transform, &targetMonster->_boundBox))
				//{
				//	//exit(0);
				//}
				_playSpeed = 1.8f;

			}
			else if (_playerObject->_skinnedAnim->getAnimFactor() > 0.4)//�ִϸ��̼� �� ���������
			{
				normalAttackDamageProcessing();
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
		if (animName == "AT2HL2")
		{
			if (_playerObject->_skinnedAnim->getAnimFactor() > 0.5 && _playerObject->_skinnedAnim->getAnimFactor() < 0.8)//�ִϸ��̼� �� ���������
			{
				//if (PHYSICSMANAGER->isOverlap(_playerObject->_transform, &_attackBound, targetMonster->_transform, &targetMonster->_boundBox))
				//{
				//	//exit(0);
				//}
				_playSpeed = 1.0f;
			}
			else if (_playerObject->_skinnedAnim->getAnimFactor() > 0.8)
			{
				normalAttackDamageProcessing();
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


			if (_playerObject->_skinnedAnim->getAnimFactor() > 0.95)//�ִϸ��̼� �� ���������
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
			if (_playerObject->_skinnedAnim->getAnimFactor() > 0.95)//�ִϸ��̼� �� ���������
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
			// x == 0 �϶� y == 0 �̷��� 
			//-x^2 + 2ax -a^2 + b = 0; 
			//-a^2 + b = 0;
			//b = a^2;

			//_degree += _jumpSpeed * _timeDelta;
			
			//_jumpHeight = _baseHeight - pow(_degree - sqrt(_jumpPower), 2.0) + _jumpPower;
			//_playerObject->_transform->SetWorldPosition(pos.x, _jumpHeight, pos.z);

			pos = _playerObject->_transform->GetWorldPosition();

			if (_playerObject->_skinnedAnim->getAnimFactor() > 0.90)//�ִϸ��̼� �� ���������
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
			if (_playerObject->_skinnedAnim->getAnimFactor() > 0.5)//�ִϸ��̼� �� ���������
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
		

		if (!SOUNDMANAGER->isPlaySound("�����Ҹ�1"))
		{
			if (animName == "WB")
			{
				if (_playerObject->_skinnedAnim->getAnimFactor() > 0.0)//�ִϸ��̼� �� ���������
				{
					SOUNDMANAGER->play("�����Ҹ�1", 0.1f);
					SOUNDMANAGER->setMusicSpeed("�����Ҹ�1", _moveSpeed * 0.5);
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

//�÷��̾��� ���¿� ���� �ִϸ��̼��� ó��
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
		_playSpeed = _moveSpeed * 0.66f;//���̻� �ǵ帮�� ����..
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
		//SOUNDMANAGER->setMusicSpeed("����1", _moveSpeed);
		SOUNDMANAGER->play("����1", 0.7f);
		_playerObject->_skinnedAnim->Play("AT1H", 0.3f);
		break;
	case P_ATTACK2:

		//SOUNDMANAGER->play("����1", 0.7f);
		_playerObject->_skinnedAnim->Play("AT2H", 0.3f);
		break;
	case P_ATTACK3:
		SOUNDMANAGER->play("����1", 0.7f);
		_playerObject->_skinnedAnim->Play("AT2HL", 0.3f);
		break;
	case P_ATTACK4:
		SOUNDMANAGER->play("����1", 0.7f);
		_playerObject->_skinnedAnim->Play("AT2H2", 0.3f);
		break;
	case P_ATTACK5:
		SOUNDMANAGER->play("����1", 0.7f);
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
		SOUNDMANAGER->play("�����Ҹ�1one", 1.0f);
		_playerObject->_skinnedAnim->Play("JUMPST", 0.2f);
		break;
	case P_JUMP:
		_playerObject->_skinnedAnim->Play("JUMP");
		break;
	case P_JUMPDOWN:
		SOUNDMANAGER->play("�����Ҹ�1one", 1.0f);
		_playerObject->_skinnedAnim->Play("JUMPED" , 0.2f);
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

//�ܺ��� �Է¿� ���� �÷��̾��� �̵��� ����.
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
		//������, �����ð�, ����Ȯ��, ����Ȯ��, ���Ͻð� 
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

//�÷��̾� ������ ����
void xPlayer::playerAttack()
{
	//�ش���°� �ƴϸ� �ൿ���� ���ƶ�.
	//if (!(_state == P_STAND || _state == P_RUN || _state == P_MOVE || _state == P_WALKBACK || _state == P_READYTOATTACK)) { return; }

	float rand = RandomFloatRange(0, 100);
	if (rand < PLAYERMANAGER->GetCrit())
	{
		_state = P_ATTACK4;//AT2H2 //ũ��Ƽ�� ����!
		_playSpeed = 1.5f;
		return;
	}
	else//�Ϲݰ���
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
	//�ش���°� �ƴϸ� �ൿ���� ���ƶ�.
	if (!(_state == P_STAND || _state == P_RUN || _state == P_MOVE || _state == P_WALKBACK || _state == P_READYTOATTACK)) { return; }

	//ĳ���� Ÿ�� ����.
	_castingTime = castingTime;
	_playSpeed = 1.0f / castingTime;
	_state = P_READYSPELL;

}

void xPlayer::playerSkillOmni(float castingTime)
{
	//�ش���°� �ƴϸ� �ൿ���� ���ƶ�.
	if (!(_state == P_STAND || _state == P_RUN || _state == P_MOVE || _state == P_WALKBACK || _state == P_READYTOATTACK)) { return; }
	_castingTime = castingTime;
	_playSpeed = 1.0f / castingTime;
	_state = P_READYOMNI;

}


//�÷��̾� �ǰݽ� ó�� �� ����ó��.
//�ǰݽð� �ִ� 0.6��
//���Ͻð� �ִ� 2�ʰ� �ڿ�������. �� �̻��� �� ���ڿ�����.
void xPlayer::playerDamaged(int damage, float damagedTime, float delayRate, float StunRate, float StunedTime)
{
	PLAYERMANAGER->SetHp(PLAYERMANAGER->GetHp() - damage);

	//���ſ� ����! ������ �ɷȴ�.
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
				//FONTMANAGER->fontOut("���Ⱦ�!", WINSIZEX / 2, WINSIZEY / 2, 0xffffffff);
			}
		}
	}
}

void xPlayer::setBladeLight()
{

	vertexNum = 80;

	primitives = vertexNum - 2;
	handTrans = new dx::transform;


	idx = new DWORD[vertexNum];

	//���� ���� ����
	_device->CreateVertexBuffer(
		sizeof(MYLIGHTVERTEX) * vertexNum,
		D3DUSAGE_WRITEONLY,
		MYLIGHTVERTEX::FVF,
		D3DPOOL_DEFAULT,
		&_myVertexbuffer,
		NULL);


	//�ε��� ���� ����
	_device->CreateIndexBuffer(
		sizeof(DWORD) * vertexNum,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX32,
		D3DPOOL_DEFAULT,
		&_myIndexBuffer,
		NULL);
	// 1---2 //�������. 2 <-> 3
	// |  /|	
	// | / |								
	// 0---3
	//UV�� �����ϰ� �����Ѵٰ� �����Ͽ�����.

	LPMYLIGHTVERTEX pVertices;
	_myVertexbuffer->Lock(0, 0, (void**)&pVertices, 0);

	float maxX = 5;
	float minX = -5;

	for (int i = 1; i < vertexNum; i += 2)
	{
		float x = 0;
		x = ((i - 1) * ((maxX - minX) / (vertexNum - 2)) + minX);
		//1-> 0 
		//3-> 2 * 10/4 +5 =...10

		pVertices[i].pos = D3DXVECTOR3(x + 11, 5, 0);//posHand + 

		float u = 0;

		if (i == 1)
		{
			u = 0;
		}
		else
		{
			u = ((float)(i - 1) / (float)(vertexNum - 2));
		}
		pVertices[i].uv = D3DXVECTOR2(u, 0);
	}

	for (int i = 0; i < vertexNum; i += 2)
	{
		float x = 0;
		x = (i * ((maxX - minX) / (vertexNum - 2)) + minX);

		pVertices[i].pos = D3DXVECTOR3(x, -5, 0);//posHand + 

		float u = 0;
		if (i == 0)
		{
			u = 0;
		}
		else
		{
			u = ((float)i / (float)(vertexNum - 2));

		}
		pVertices[i].uv = D3DXVECTOR2(u, 1);
	}

	_myVertexbuffer->Unlock();




	//tagIndex* idx = new tagIndex[rects];



	for (int i = 0; i < vertexNum; i++)
	{
		idx[i] = i;
	}

	void* pIndices = NULL;
	_myIndexBuffer->Lock(0, 0, &pIndices, 0);
	memcpy(pIndices, idx, sizeof(DWORD) * vertexNum);
	_myIndexBuffer->Unlock();


	//�ؽ��� �ε�
	D3DXCreateTextureFromFile(
		_device,
		"�׽�Ʈ.jpg",
		&_texture);
}

void xPlayer::updateBladeLight()
{
	handTrans->SetWorldMatrix(getPlayerObject()->_skinnedAnim->getSkinnedMesh()->GetFineBONE("humanfemale_Bone121_CSR")->CombinedTransformationMatrix);

	//���� �� ��.
	posHand = handTrans->GetWorldPosition();
	posEdge = handTrans->GetWorldPosition() + handTrans->GetForward();



	// 1---3---5   7 UV��ǥ��� ������ ��ǥ��� �Ȱ��� 
	// |  /|   |	���ʻ���� 0,0 ������� 1,0 �����ϴ� 0,1 �����ϴ� 1,1
	// | / |   |								
	// 0---2---4   6
	// 0, 0.33 0.66 1



}

void xPlayer::drawBladeLight()
{


	////����Ʈ����� ��� ������
	////====================================================================
	////			## �ؽ��� Wrap ��� ##
	////====================================================================
	//


	_device->SetRenderState(D3DRS_LIGHTING, FALSE);
	_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	////�ݺ������� ���´� 1 �Ѿ�� UV ��ǥ�� 1�� ���� �ٽ� 0���� ����
	_device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	_device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//�׸��� ���� �ε��� �ؽ��ĸ� �����ϱ�
	_device->SetTexture(0, _texture);

	//���� �׸���
	_device->SetStreamSource(0, _myVertexbuffer, 0, sizeof(MYLIGHTVERTEX));
	_device->SetFVF(MYLIGHTVERTEX::FVF);
	_device->SetIndices(_myIndexBuffer);
	
	_device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, vertexNum, 0, primitives);
	//�ؽ��� ��������

	_device->SetTexture(0, NULL);





	//typedef struct tagBladeLightVertex
	//{
	//	D3DXVECTOR3 pos;			//���� ��ġ
	//	DWORD color;				//���� �÷�
	////	D3DXVECTOR2 uv;				//���� UV
	//	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };//| D3DFVF_TEX1 
	//}BLADE_VERTEX, *LPBLADE_VERTEX;

	///*���� ��ġ...
	//���� �����ġ = COMBINEDMATRIX... RHAND * INVERSE(INVERSE(PLAYERTRNAS->MATWORLD));
	//���� �����ġ�� B.TRANSFORM
	//�˳��� �����ġ = B.TRANSFORM.POS - (B.TRANSFORM.FORWARD * ���� ����);
	//�� ģ������ P0.*/

	////�ִϸ��̼ǿ� ���� ��ȭ�� ���� ��ġ.
	////D3DXVec3CatmullRom(...)

	////�ִϸ��̼� ���� �ӽ�����
	//skinnedAnimation playerAnim = this->getPlayerObject()->getSkinnedAnim();//��������
	//skinnedAnimation playerAnim2 = playerAnim;//�������� (��ü ���� ������ ����..)

	//float tempAnimFactor = playerAnim.getTrackDesc0().Position;

	//float nowPeriod = playerAnim.getNowPlayAnimSet()->GetPeriod();

	////����ġ ��ŭ ����.

	////�켱 �׸���. ����.
	//D3DXTRACK_DESC DESC_ORIGIN = playerAnim.getTrackDesc0();
	//D3DXTRACK_DESC DESC3 = playerAnim.getTrackDesc0();
	//D3DXTRACK_DESC DESC2 = playerAnim.getTrackDesc0();
	//D3DXTRACK_DESC DESC1 = playerAnim.getTrackDesc0();
	//D3DXTRACK_DESC DESC0 = playerAnim.getTrackDesc0();


	//dx::transform* boneTrans = new dx::transform;
	//boneTrans->SetWorldMatrix(playerAnim.getSkinnedMesh()->GetFineBONE("humanfemale_Bone121_CSR")->CombinedTransformationMatrix);

	////pv3��
	////DESC3.Position = nowPeriod * 1.0;
	////playerAnim.setTrackDesc0(DESC3);
	//playerAnim.setTrackDesc0(DESC_ORIGIN);

	//playerAnim.updateBone();
	//playerAnim.getSkinnedMesh()->GetFineBONE("humanfemale_Bone121_CSR")->CombinedTransformationMatrix;

	//if (boneTrans->GetFinalMatrix() != playerAnim.getSkinnedMesh()->GetFineBONE("humanfemale_Bone121_CSR")->CombinedTransformationMatrix)
	//{
	//	int a = 0;
	//}
	//
	////pv2��
	//DESC2.Position = nowPeriod * 0.66;

	////pv1��
	//DESC1.Position = nowPeriod * 0.33;

	////pv0��
	//DESC0.Position = nowPeriod * 0.0;


	//
	//playerAnim.setTrackDesc0(DESC_ORIGIN);


}