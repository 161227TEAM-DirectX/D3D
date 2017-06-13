#include "stdafx.h"
#include "xPlayer.h"
#include "monster.h"


HRESULT xPlayer::init()
{

	//�޽� �ε�
	_state = P_STAND;
	_prevState = P_STAND;
	Equipments = A_PLATE;
	Weapons = W_WOOD;
	Shields = SH_BUCKLER;

	_Hp = 10;

	_damagedTime = 0.0f;
	_stunnedTime = 0.0f;
	_castingTime = 0.0f;
	_playSpeed = 1.0f;
	_degree = 0.0f;
	_baseHeight = 0.0f;
	_jumpPower = 2.0f;
	_jumpSpeed = 1.0f;
	_jumpHeight = 0.0f;

	_isOnBattle = false;



	//�����͸� �ε��� ������ �������ͽ��� �����¸� �ʱ�ȭ�Ѵ�.
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

	float tempY = linkTerrain->getHeight(_playerObject->_transform->GetWorldPosition().x, _playerObject->_transform->GetWorldPosition().z);

	_playerObject->_transform->SetWorldPosition(D3DXVECTOR3(_playerObject->_transform->GetWorldPosition().x, tempY, _playerObject->_transform->GetWorldPosition().z));


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


	//���� ������Ʈ �ʱ�ȭ ����Ʈ�� ������ �������� w_none�̸� ��Ƽ�� ���� �ʴ´�.
	_weaponObject = new baseObject;

	switch (Weapons)
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
	_shieldObject = new baseObject;

	switch (Shields)
	{
	case SH_NONE:
		pSkinned3 = RM_XMESH->getResource("Resources/item/Shield/shield01/shield01.X", &matCorrection3);
		_shieldObject->setActive(false);
		_renderObjects.push_back(_shieldObject);
		break;
	case SH_SPIKE:
		D3DXMatrixRotationY(&matRotate3, D3DXToRadian(270));//�ǵ� 1, 2
		D3DXMatrixScaling(&matScale3, 0.25f, 0.25f, 0.25f);
		matCorrection3 = matRotate3 * matScale3;

		pSkinned3 = RM_XMESH->getResource("Resources/item/Shield/shield01/shield01.X", &matCorrection3);
		_shieldObject->setActive(true);
		_renderObjects.push_back(_shieldObject);
		break;
	case SH_BUCKLER:
		D3DXMatrixRotationY(&matRotate3, D3DXToRadian(270));//�ǵ� 1, 2
		D3DXMatrixScaling(&matScale3, 0.2f, 0.2f, 0.2f);
		matCorrection3 = matRotate3 * matScale3;

		pSkinned3 = RM_XMESH->getResource("Resources/item/Shield/shield02/shield02.X", &matCorrection3);
		_shieldObject->setActive(true);
		_renderObjects.push_back(_shieldObject);
		break;
	case SH_BRONZE:
		D3DXMatrixRotationZ(&matRotate3, D3DXToRadian(270));//�ǵ� 3, 4, 5
		D3DXMatrixScaling(&matScale3, 0.5f, 0.5f, 0.5f);
		matCorrection3 = matRotate3 * matScale3;

		pSkinned3 = RM_XMESH->getResource("Resources/item/Shield/shield03/shield03.X", &matCorrection3);
		_shieldObject->setActive(true);
		_renderObjects.push_back(_shieldObject);
		break;
	case SH_CROSS:
		D3DXMatrixRotationZ(&matRotate3, D3DXToRadian(270));//�ǵ� 3, 4, 5
		D3DXMatrixScaling(&matScale3, 0.25f, 0.25f, 0.25f);
		matCorrection3 = matRotate3 * matScale3;

		pSkinned3 = RM_XMESH->getResource("Resources/item/Shield/shield04/shield04.X", &matCorrection3);
		_shieldObject->setActive(true);
		_renderObjects.push_back(_shieldObject);
		break;
	case SH_KITE:
		D3DXMatrixRotationZ(&matRotate3, D3DXToRadian(270));//�ǵ� 3, 4, 5
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

	float tempY = linkTerrain->getHeight(_playerObject->_transform->GetWorldPosition().x, _playerObject->_transform->GetWorldPosition().z);
	_playerObject->_transform->SetWorldPosition(D3DXVECTOR3(_playerObject->_transform->GetWorldPosition().x, tempY, _playerObject->_transform->GetWorldPosition().z));


	_playerObject->_skinnedAnim->SetPlaySpeed(_playSpeed);

	//�÷��̾� ������Ʈ ������Ʈ
	_playerObject->update();



	if (Weapons != W_NONE)
	{
		D3DXMATRIX matHand = _EquipSocket.find("RHAND")->second->CombinedTransformationMatrix;
		_weaponObject->_transform->SetWorldMatrix(matHand);
		_weaponObject->update();
	}

	if (Shields != SH_NONE)
	{
		D3DXMATRIX matShield = _EquipSocket.find("SHIELD")->second->CombinedTransformationMatrix;
		_shieldObject->_transform->SetWorldMatrix(matShield);
		_shieldObject->update();
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

	FONTMANAGER->fontOut("base : " + to_string(_baseHeight), 500, 25, 0xffffffff);

	FONTMANAGER->fontOut("Degree : " + to_string(_degree), 500, 50, 0xffffffff);
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
	//�÷��̾� ������ �̱��� �Լ��� ���� �����͸� �����Ѵ�.
}

void xPlayer::setHeight(float height)//�������� ���� ��ġ�� �����´�.
{
	D3DXVECTOR3 pos = _playerObject->_transform->GetWorldPosition();
	_playerObject->_transform->SetWorldPosition(pos.x, height, pos.z);
}

//�ܺ��� �Է¿� ���� �÷��̾��� �̵��� ���°�, �ִϸ��̼� ���� �����Ѵ�.
void xPlayer::userPlayerControl()
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		//������, �����ð�, ����Ȯ��, ����Ȯ��, ���Ͻð� 
		playerDamaged(1, 0.5, 100.0, 0.0, 0.0);
	}

	if (KEYMANAGER->isOnceKeyDown('V'))
	{
		playerDamaged(1, 0.5, 100.0, 100.0, 2.0);
	}

	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		_state = P_JUMPUP;
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		_state = P_JUMP;
	}
	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		_state = P_JUMPDOWN;
	}

	//�ӽ� ��Ʈ�ѿ� �ڵ�
	if (_state == P_DEATH || _state == P_STUN || _state == P_ATTACK || _state == P_ATTACK2 || _state == P_ATTACK3 || _state == P_ATTACK4 || _state == P_ATTACK5 || _state == P_DAMAGED) { return; }

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
		if (_state != P_JUMP && _state != P_JUMPUP)
		{
			this->_state = P_RUN;
		}
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		if (_state == P_STAND || _state == P_READYTOATTACK)
		{
			_state = P_RUN;
		}
		if (_state == P_RUN || _state == P_JUMP || _state == P_JUMPUP)
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
		if (_state != P_JUMP && _state != P_JUMPUP)
		{
			this->_state = P_WALKBACK;
		}
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		if (_state == P_WALKBACK || _state == P_JUMP || _state == P_JUMPUP)
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

//�÷��̾��� �ڵ����� ���º�ȭ�� �����Ѵ�.
//�� �κп��� �÷��̾��� �ִϸ��̼��� ��ȭ��Ű�� �ʾƾ� ��. -> ���� �׷���?
//�ð��� ������ ���� Ȥ�� ��ġ���� ������ ���� �ڵ������� ��ȭ�ؾ� �ϴ� ��츦 �����Ѵ�.
void xPlayer::playerStateManager()
{
	if (_Hp <= 0) _state = P_DEATH;
	string aa = _playerObject->_skinnedAnim->getAnimationSet()->GetName();
	D3DXVECTOR3 pos = _playerObject->_transform->GetWorldPosition();
	switch (_state)
	{
	case P_STAND:
		//���ִ´ٰ� �ð������� ���Ұ� ����.
		break;
	case P_RUN:
		//�ð������� ���Ұ� ����.
		break;
	case P_MOVE:
		//�ð������� ���Ұ� ����.
		break;
	case P_READYTOATTACK:

		break;
	case P_ATTACK:

		if (aa == "AT1H")
		{
			if (_playerObject->_skinnedAnim->getAnimFactor() > 0.95)//�ִϸ��̼� �� ���������
			{
				if (PHYSICSMANAGER->isOverlap(_playerObject->_transform, &_attackBound, targetMonster->_transform, &targetMonster->_boundBox))
				{
					//exit(0);
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
	case P_ATTACK2:

		if (aa == "AT2H")
		{
			if (_playerObject->_skinnedAnim->getAnimFactor() > 0.95)//�ִϸ��̼� �� ���������
			{
				if (PHYSICSMANAGER->isOverlap(_playerObject->_transform, &_attackBound, targetMonster->_transform, &targetMonster->_boundBox))
				{
					//exit(0);
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
		break; case P_ATTACK3:

			if (aa == "AT2HL")
			{
				if (_playerObject->_skinnedAnim->getAnimFactor() > 0.95)//�ִϸ��̼� �� ���������
				{
					if (PHYSICSMANAGER->isOverlap(_playerObject->_transform, &_attackBound, targetMonster->_transform, &targetMonster->_boundBox))
					{
						//exit(0);
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
		case P_ATTACK4:

			if (aa == "AT2H2")
			{
				if (_playerObject->_skinnedAnim->getAnimFactor() > 0.95)//�ִϸ��̼� �� ���������
				{
					if (PHYSICSMANAGER->isOverlap(_playerObject->_transform, &_attackBound, targetMonster->_transform, &targetMonster->_boundBox))
					{
						//exit(0);
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
		case P_ATTACK5:

			if (aa == "AT2HL2")
			{
				if (_playerObject->_skinnedAnim->getAnimFactor() > 0.95)//�ִϸ��̼� �� ���������
				{
					if (PHYSICSMANAGER->isOverlap(_playerObject->_transform, &_attackBound, targetMonster->_transform, &targetMonster->_boundBox))
					{
						//exit(0);
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

			if (aa == "JUMPST")
			{

				_degree += _timeDelta;
				_jumpHeight = _baseHeight + _jumpPower * sinf(D3DXToRadian(90.0f * _degree * _jumpSpeed));
				if (_playerObject->_skinnedAnim->getAnimFactor() < 0.05)
				{
					_baseHeight = linkTerrain->getHeight(pos.x, pos.z);
				}
				if (_playerObject->_skinnedAnim->getAnimFactor() > 0.95)//�ִϸ��̼� �� ���������
				{
					_state = P_JUMP;
					_playerObject->_transform->SetWorldPosition(pos.x, _jumpHeight, pos.z);
				}
				else if (pos.y < linkTerrain->getHeight(pos.x, pos.z))
				{
					_state = P_JUMPDOWN;
					_playerObject->_transform->SetWorldPosition(pos.x, _jumpHeight, pos.z);
				}
				else
				{
					_playerObject->_transform->SetWorldPosition(pos.x, _jumpHeight, pos.z);
				}
			}


			break;
		case P_JUMP:
			if (aa == "JUMP")
			{
				_degree += _timeDelta;
				_jumpHeight = _baseHeight + _jumpPower * sinf(D3DXToRadian(90.0f * _degree * _jumpSpeed));

				if (_degree > 2.0f)
				{
					_degree = 0;
					_state = P_JUMPDOWN;
				}
				else if (pos.y < linkTerrain->getHeight(pos.x, pos.z))
				{
					_degree = 0;
					_state = P_JUMPDOWN;
					_playerObject->_transform->SetWorldPosition(pos.x, linkTerrain->getHeight(pos.x, pos.z), pos.z);
				}
				else
				{
					_playerObject->_transform->SetWorldPosition(pos.x, _jumpHeight, pos.z);
				}
			}
			break;
		case P_JUMPDOWN:
			if (aa == "JUMPED")
			{
				if (_playerObject->_skinnedAnim->getAnimFactor() > 0.7)//�ִϸ��̼� �� ���������
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


void xPlayer::playerAttack()
{
	//�ش���°� �ƴϸ� �ൿ���� ���ƶ�.
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

void xPlayer::playerJump()
{
	if (!(_state == P_STAND || _state == P_RUN || _state == P_MOVE || _state == P_WALKBACK || _state == P_READYTOATTACK)) { return; }
	//������ ����
	//�������� �������� ������ ���� ������� �������ߵ�.
	//�ϴ� ���� �ϸ� �� ����..? ���� ���� �غ���.
}

//�÷��̾� �ǰݽ� ó�� �� ����ó��.
//�ǰݽð� �ִ� 0.6��
//���Ͻð� �ִ� 2�ʰ� �ڿ�������. �� �̻��� �� ���ڿ�����.
void xPlayer::playerDamaged(int damage, float damagedTime, float delayRate, float StunRate, float StunedTime)
{
	this->_Hp = this->_Hp - damage;

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