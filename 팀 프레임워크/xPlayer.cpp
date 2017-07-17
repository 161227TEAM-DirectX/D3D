#include "stdafx.h"
#include "xPlayer.h"
#include "monster.h"
#include "damageText.h"

HRESULT xPlayer::init()
{
	_dmText = new damageText;

	_handTrans = new dx::transform;
	_edgeTrans = new dx::transform;

	monsterCenter = new dx::transform;

	_nowSelectedSkill = SKILL_NONE;

	//�޽� �ε�
	_state = P_STAND;
	_prevState = P_STAND;

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

	_BladeLength = 1.0f;//Į�� ���� �˱��� ���̸� �����Ѵ� 1�� �⺻��. �Ǹ��� 0.5 īŸ�� 0.7, ��ε�ҵ� 0.7 ������ 1.0

	_isOnBattle = false;
	_isJump = false;
	
	_isMount = false;
	_isInvincible = false;

	//�����͸� �ε��� ������ �������ͽ��� �����¸� �ʱ�ȭ�Ѵ�.
	LoadData();

	xMeshSkinned* pSkinned;
	D3DXMATRIXA16 matCorrection;
	D3DXMATRIXA16 matScale;
	D3DXMATRIXA16 matRotate;
	D3DXMatrixScaling(&matScale, 0.5, 0.5, 0.5);
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
			RM_SKINNED->getResource("Resource/Player/FHUMAN_NEW/FHUMAN.X", &matCorrection);
		break;
	default:
		return E_FAIL;
		break;
	}


	_playerObject = new baseObject;
	_playerObject->setMesh(pSkinned);
	_playerObject->setActive(true);

	//����� ��ġ�� �ҷ��´�


	_renderObjects.push_back(_playerObject);

	//dx::transform* playerTrans = _playerObject->_transform;
	D3DXVECTOR3 pos = PLAYERMANAGER->GetPos();

	_playerObject->_transform->SetWorldPosition(pos);

	_playerObject->_boundBox.setBound(&D3DXVECTOR3(0, 0.5f, 0), &D3DXVECTOR3(0.3, 0.5, 0.3));

	_attackTrans.SetWorldPosition(0, 0.5f, 0.8);

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

	PLAYERMANAGER->SetWeapon(W_BLACK_WING);

	switch (PLAYERMANAGER->GetWeapon())
	{
	case W_NONE:
		D3DXMatrixRotationY(&matRotate2, D3DXToRadian(270));
		D3DXMatrixScaling(&matScale2, 0.5, 0.5, 0.5);
		matCorrection2 = matRotate2*matScale2;
		pSkinned2 = RM_XMESH->getResource("Resource/item/Sword/weapon01/weapon01.X", &matCorrection2);
		_weaponObject->setActive(false);
		_renderObjects.push_back(_weaponObject);
		_BladeLength = 0.0f;
		break;
	case W_BLACK_WING:
		D3DXMatrixRotationY(&matRotate2, D3DXToRadian(270));
		D3DXMatrixScaling(&matScale2, 0.5, 0.5, 0.5);
		matCorrection2 = matRotate2*matScale2;
		pSkinned2 = RM_XMESH->getResource("Resource/item/Sword/weapon01/weapon01.X", &matCorrection2);
		_weaponObject->setActive(true);
		_renderObjects.push_back(_weaponObject);
		_BladeLength = 1.0f;
		break;
	case W_BROAD:
		D3DXMatrixRotationY(&matRotate2, D3DXToRadian(270));
		D3DXMatrixScaling(&matScale2, 0.25, 0.25, 0.25);
		matCorrection2 = matRotate2*matScale2;

		pSkinned2 = RM_XMESH->getResource("Resource/item/Sword/weapon02/weapon02.X", &matCorrection2);
		_weaponObject->setActive(true);
		_renderObjects.push_back(_weaponObject);
		_BladeLength = 0.7f;
		break;
	case W_DEAMON:
		D3DXMatrixRotationZ(&matRotate2, D3DXToRadian(0));
		D3DXMatrixScaling(&matScale2, 0.5, 0.5, 0.5);
		matCorrection2 = matRotate2*matScale2;

		pSkinned2 = RM_XMESH->getResource("Resource/item/Sword/weapon03/weapon03.X", &matCorrection2);
		_weaponObject->setActive(true);
		_renderObjects.push_back(_weaponObject);
		_BladeLength = 0.72f;
		break;
	case W_KATANA:
		D3DXMatrixRotationZ(&matRotate2, D3DXToRadian(0));
		D3DXMatrixScaling(&matScale2, 0.5, 0.5, 0.5);
		matCorrection2 = matRotate2*matScale2;

		pSkinned2 = RM_XMESH->getResource("Resource/item/Sword/weapon04/weapon04.X", &matCorrection2);
		_weaponObject->setActive(true);
		_renderObjects.push_back(_weaponObject);
		_BladeLength = 0.5f;
		break;
	case W_WOOD:
		D3DXMatrixRotationZ(&matRotate2, D3DXToRadian(0));
		D3DXMatrixScaling(&matScale2, 0.33, 0.33, 0.33);
		matCorrection2 = matRotate2*matScale2;

		pSkinned2 = RM_XMESH->getResource("Resource/item/Sword/weapon05/weapon05.X", &matCorrection2);
		_weaponObject->setActive(true);
		_renderObjects.push_back(_weaponObject);
		_BladeLength = 0.4f;
		break;
	case W_END:
		break;
	default:
		break;
	}

	_weaponObject->setMesh(pSkinned2);
	//_playerObject->_skinnedAnim->AddBoneTransform("humanfemale_Bone121_CSR", _weaponObject->_transform);

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

		pSkinned3 = RM_XMESH->getResource("Resource/Player/FHUMAN_NEW/Shoulder.X", &matCorrection3);//Resource/Player/FHUMAN_NEW/Shoulder.X
		_shieldObject->setActive(true);
		_renderObjects.push_back(_shieldObject);
		break;
	case SH_END:
		break;
	default:
		break;
	}

	_shieldObject->setMesh(pSkinned3);
	//_playerObject->_skinnedAnim->AddBoneTransform("humanfemale_Bone110", _shieldObject->_transform);


	D3DXMATRIX matCorrectionL, matRotateL, matScaleL;
	D3DXMATRIX matCorrectionR, matRotateR, matScaleR;

	D3DXMatrixRotationY(&matRotateL, D3DXToRadian(270));
	D3DXMatrixRotationY(&matRotateR, D3DXToRadian(90));
	D3DXMatrixScaling(&matScaleL, 0.5, 0.5, 0.5);
	D3DXMatrixScaling(&matScaleR, 0.5, 0.5, 0.5);
	matCorrectionL = matRotateL * matScaleL;
	matCorrectionR = matRotateR * matScaleR;

	xMeshStatic* xShoulderL;
	xMeshStatic* xShoulderR;



	xShoulderL = RM_XMESH->getResource("Resource/Player/FHUMAN_NEW/ShoulderL.X", &matCorrectionL);
	_shoulderL = new baseObject;
	_shoulderL->setMesh(xShoulderL);
	_shoulderL->setActive(true);

	xShoulderR = RM_XMESH->getResource("Resource/Player/FHUMAN_NEW/ShoulderR.X", &matCorrectionR);
	_shoulderR = new baseObject;
	_shoulderR->setMesh(xShoulderR);
	_shoulderR->setActive(true);


	//_shoulderL->_transform->SetWorldMatrix(_EquipSocket.find("LSHOULDER")->second->CombinedTransformationMatrix);
	//_shoulderR->_transform->SetWorldMatrix(_EquipSocket.find("RSHOULDER")->second->CombinedTransformationMatrix);

	_playerObject->_skinnedAnim->AddBoneTransform("humanfemale_Bone99", _shoulderL->_transform);

	_playerObject->_skinnedAnim->AddBoneTransform("humanfemale_Bone98", _shoulderR->_transform);

	_playerObject->_skinnedAnim->Play("S", 0.3F);

	setBladeLight();

	_playerObject->_skinnedAnim->AddBoneTransform("humanfemale_Bone121_CSR", _handTrans);
	_edgeTrans->SetWorldPosition(_handTrans->GetWorldPosition() + _handTrans->GetRight() * _BladeLength);
	_handTrans->AddChild(_edgeTrans);

	BladePosInit();

	targetMonster = NULL;

	_renderObjects.push_back(_shoulderL);
	_renderObjects.push_back(_shoulderR);

	initMount();

	return S_OK;
}

void xPlayer::update()
{
	if (KEYMANAGER->isOnceKeyDown('0'))
	{
		if (_isInvincible)
		{
			_isInvincible = false;
		}
		else
		{
			_isInvincible = true;
		}
	}

	updateEquipments();


	setHeight(getPlayerObject()->_transform);


	PLAYERMANAGER->SetPos(_playerObject->_transform->GetWorldPosition());

	//_lightSkill->update();

	_playerObject->_skinnedAnim->SetPlaySpeed(_playSpeed);
	if (_isMount)
	{
		_mountObject->_skinnedAnim->SetPlaySpeed(_playSpeed);
	}

	if (!KEYMANAGER->isToggleKey(VK_OEM_3) && !g_isChat)
	{
		PlayerInputControl();
	}
	playerStateManager();
	playerAnimationManager();

	useNowSkill();

	if (targetMonster != nullptr)
	{
		yPosition += 0.01f;
		_dmText->setPos(D3DXVECTOR3(targetMonster->_transform->GetWorldPosition().x, yPosition, targetMonster->_transform->GetWorldPosition().z));
		_dmText->update();
	}

	_prevState = _state;
}

void xPlayer::render()
{

	//_sitPos->RenderGimozo();
	//_handTrans->RenderGimozo();
	//_edgeTrans->RenderGimozo();
	//_mountObject->_transform->RenderGimozo();

	//if (targetMonster != NULL)
	//{
	//	FONTMANAGER->fontOut("����HP : " + to_string(targetMonster->getHP()), 300, 300, 0xffffffff);
	//	FONTMANAGER->fontOut("���ݷ� : " + to_string(PLAYERMANAGER->Getatt()), 300, 350, 0xffffffff);
	//	
	//}
	if (targetMonster != NULL)
	{
		targetMonster->setIsRender(true);
	}
	
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

		RM_SKINNED->getResource("Resource/Player/FHUMAN_NEW/FHUMAN.X")->ShowAnimationName(0, 0);

		if (NULL != targetMonster)
		{
			targetMonster->_boundBox.renderGizmo(targetMonster->_transform);
		}

		_mountObject->_transform->RenderGimozo();
	}

	if (!_isMount && _nowSelectedSkill != SKILL_WHIRLWIND)
	{
		drawBladeLight();
	}


	if (_dmText->getStrLength())
	{
		_dmText->render();
	}
}

void xPlayer::release(void)
{
	/*
	for (int i = 0; i < this->_renderObjects.size(); i++)
	{
		SAFE_DELETE(this->_renderObjects[i]);
	}*/

	SAFE_RELEASE(_myVertexbuffer);
	SAFE_RELEASE(_myIndexBuffer);
	SAFE_RELEASE(_texture);
}

void xPlayer::LoadData()
{
	//�÷��̾� ������ �̱��� �Լ��� �����͸� �ʱ�ȭ ��Ų��. �̰� �� �÷��̾� Ŭ�������� �ұ�?
	//PLAYERMANAGER->SetArmor(A_PLATE);
	PLAYERMANAGER->SetWeapon(W_NONE);
	PLAYERMANAGER->SetShield(SH_NONE);

	_weaponCurrent = W_NONE;
	_shieldCurrent = SH_NONE;
}


void xPlayer::PlayerInputControl()//�� ģ���� ���°��� ���� ���̶��?
{


	switch (_state)
	{
	case P_STAND:
		skilltrigger();
		rotateControl(_playerObject->_transform);

		if (!_isJump)
		{
			moveControl(_playerObject->_transform);
			jumpControl();
			attackControl();
			skillControl();
			summonControl();
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

		rotateControl(_playerObject->_transform);
		moveControl(_playerObject->_transform);
		attackControl();
		skillControl();
		jumpControl();
		summonControl();
		skilltrigger();

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
		skilltrigger();
		rotateControl(_playerObject->_transform);

		if (!_isJump)
		{
			moveControl(_playerObject->_transform);
			attackControl();
			skillControl();
			jumpControl();
			summonControl();
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
	case P_ATTACK6:
		break;
	case P_SLAM:
		break;
	case P_WHIRLWIND:
		moveControl(_playerObject->_transform);
		rotateControl(_playerObject->_transform);
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
		rotateControl(_playerObject->_transform);
		moveControl(_playerObject->_transform);
		attackControl();
		skillControl();
		break;
	case P_JUMP:

		rotateControl(_playerObject->_transform);
		moveControl(_playerObject->_transform);
		attackControl();
		skillControl();
		break;
	case P_JUMPDOWN:
		break;
	case P_STUN:
		break;
	case P_DEATH:
		break;
	case P_MOUNT_S:
		moveControl(_mountObject->_transform);
		rotateControl(_mountObject->_transform);
		summonControl();
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			_state = P_MOUNT_R;
		}
		if (KEYMANAGER->isStayKeyDown('S'))
		{
			_state = P_MOUNT_WB;
		}
		break;
	case P_MOUNT_R:
		moveControl(_mountObject->_transform);
		rotateControl(_mountObject->_transform);
		summonControl();
		if (!KEYMANAGER->isStayKeyDown('W'))
		{
			this->_state = P_MOUNT_S;
		}
		break;
	case P_MOUNT_WB:
		moveControl(_mountObject->_transform);
		rotateControl(_mountObject->_transform);
		summonControl();
		if (!KEYMANAGER->isStayKeyDown('S'))
		{
			this->_state = P_MOUNT_S;
		}
		break;
	case P_WALKBACK:
		rotateControl(_playerObject->_transform);
		moveControl(_playerObject->_transform);
		attackControl();
		jumpControl();
		skillControl();
		summonControl();

		//actionControl();
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

	/*if (_state != P_WHIRLWIND)
	{
		SOUNDMANAGER->stop("������");
	}*/

	if (_state != P_RUN && _state != P_WALKBACK)
		SOUNDMANAGER->stop("�����Ҹ�1");

	if (_state != P_MOUNT_R && _state != P_MOUNT_WB)
	{
		SOUNDMANAGER->stop("���߱��Ҹ�1");
	}

	if (PLAYERMANAGER->GetHp() <= 0) _state = P_DEATH;
	string animName = _playerObject->_skinnedAnim->getAnimationSet()->GetName();
	D3DXVECTOR3 pos = _playerObject->_transform->GetWorldPosition();


	//�̷��� �ϸ� ���� ������ �پ� ���� �� ����.
	//���߿� �߷� ���������� ��������. ����?
	//�ٵ� �׷��� ������ �� �����ٵ�...
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
		if (!_isMount)
		{

			_playerObject->_transform->SetWorldPosition(pos.x, _baseHeight, pos.z);
		}
		else
		{

			_mountObject->_transform->SetWorldPosition(_mountObject->_transform->GetWorldPosition().x, _baseHeight, _mountObject->_transform->GetWorldPosition().z);
			_playerObject->_transform->LookDirection(_sitPos->GetRight());
		}
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
				if (_playerObject->_skinnedAnim->getAnimFactor() > _moveSpeed / 25)//�ִϸ��̼� �� ���������
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
		if (animName == "AT2H")
		{
			if (_playerObject->_skinnedAnim->getAnimFactor() > 0.2 && _playerObject->_skinnedAnim->getAnimFactor() < 0.3)
			{
				
				if (!SOUNDMANAGER->isPlaySound("����1"))
				{
					SOUNDMANAGER->play("����1", 0.7f);
				}
			}

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
			else if (_playerObject->_skinnedAnim->getAnimFactor() > 0.5)//�ִϸ��̼� �� ���������
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
	case P_ATTACK6:
		if (animName == "AT1H2")
		{
			if (_playerObject->_skinnedAnim->getAnimFactor() > 0.5 && _playerObject->_skinnedAnim->getAnimFactor() < 0.6)//�ִϸ��̼� �� ���������
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
	case P_SLAM:
		skillProcesser();
		if (animName == "SLAM")
		{
			if (_playerObject->_skinnedAnim->getAnimFactor() > 0.5 && _playerObject->_skinnedAnim->getAnimFactor() < 0.8)//�ִϸ��̼� �� ���������
			{
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
	case P_WHIRLWIND:
		skillProcesser();
		if (animName == "WW")
		{
			if (!SOUNDMANAGER->isPlaySound("������"))
			{
				SOUNDMANAGER->play("������", 0.7f);
			}

			if (_playerObject->_skinnedAnim->getAnimFactor() > 1.0)
			{
				normalAttackDamageProcessing();
				_playerObject->_skinnedAnim->Play("WW");
			}
			_playSpeed = 2;
		}
		break;
	case P_BATTLEROAR:
		if (animName == "BR")
		{
			if (_playerObject->_skinnedAnim->getAnimFactor() > 0.80)//�ִϸ��̼� �� ���������
			{
				normalAttackDamageProcessing();
				normalAttackDamageProcessing();
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
		skillProcesser();
		if (animName == "SPCD")
		{
			//if (_playerObject->_skinnedAnim->getAnimFactor() > 0.95)//�ִϸ��̼� �� ���������
			//{
			//	//_skillTrans->SetWorldMatrix(_EquipSocket.find("LHAND")->second->CombinedTransformationMatrix);
			//	//_lightSkill->setPlayer(_skillTrans);
			//	//_lightSkill->setPlayerDir(_playerObject->_transform);
			//	//_lightSkill->Start();

			//	if (_isOnBattle)
			//	{
			//		_state = P_READYTOATTACK;
			//	}
			//	else
			//	{
			//		_state = P_STAND;
			//	}
			//}
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
		skillProcesser();
		if (animName == "SPCO")
		{

			//if (_playerObject->_skinnedAnim->getAnimFactor() > 0.95)//�ִϸ��̼� �� ���������
			//{
			//	if (_isOnBattle)
			//	{
			//		_state = P_READYTOATTACK;
			//	}
			//	else
			//	{
			//		_state = P_STAND;
			//	}
			//}
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
			else if (pos.y <= _baseHeight)
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

			pos = getPlayerObject()->_transform->GetWorldPosition();

			if (pos.y <= _baseHeight)
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
	case P_MOUNT_S:

		break;
	case P_MOUNT_R:
		if (!SOUNDMANAGER->isPlaySound("���߱��Ҹ�1"))
		{
			SOUNDMANAGER->play("���߱��Ҹ�1", 0.3f);
			SOUNDMANAGER->setMusicSpeed("���߱��Ҹ�", _moveSpeed);
		}

		break;
	case P_MOUNT_WB:
		if (!SOUNDMANAGER->isPlaySound("���߱��Ҹ�1"))
		{
			SOUNDMANAGER->play("���߱��Ҹ�1", 0.1f);
			SOUNDMANAGER->setMusicSpeed("���߱��Ҹ�", _moveSpeed * 0.5);
		}
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
	//dx::transform* _testTrans = new dx::transform;
	//_testTrans->SetWorldPosition(RandomFloatRange(-5.0f, 5.0f), RandomFloatRange(0.0f, 3.0f), RandomFloatRange(5.0f, 8.0f));

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
		SOUNDMANAGER->play("����1", 0.7f);
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
	case P_ATTACK6:
		SOUNDMANAGER->play("����1", 0.7f);
		_playerObject->_skinnedAnim->Play("AT1H2", 0.3f);
		break;
	case P_SLAM:
		SOUNDMANAGER->play("����1", 0.7f);
		_playerObject->_skinnedAnim->Play("SLAM", 0.3f);
		break;
	case P_WHIRLWIND:

		_playerObject->_skinnedAnim->Play("WW", 0.3f);
		break;
	case P_BATTLEROAR:
		SOUNDMANAGER->play("Ǫ���δ�!");
		_playSpeed = 3.0;
		_playerObject->_skinnedAnim->Play("BR", 0.3f);
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
		_playSpeed = 1.0f;
		_playerObject->_skinnedAnim->PlayOneShotAfterHold("SPCO", 0.2f);
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
		_playerObject->_skinnedAnim->Play("JUMPED", 0.2f);
		break;
	case P_STUN:
		_isMount = false;
		_playerObject->_skinnedAnim->Play("STUN");
		break;
	case P_DEATH:
		_playerObject->_skinnedAnim->PlayOneShotAfterHold("D", 0.2f);
		break;
	case P_MOUNT_S:
		_mountObject->setActive(true);
		_mountObject->_skinnedAnim->Play("S", 0.3f);
		_playerObject->_skinnedAnim->Play("M");
		_playerObject->_skinnedAnim->Stop();
		break;
	case P_MOUNT_R:
		_playSpeed = _moveSpeed * 0.66;
		_mountObject->setActive(true);
		_mountObject->_skinnedAnim->Play("R", 0.3f);
		_playerObject->_skinnedAnim->Stop();
		break;
	case P_MOUNT_WB:
		_playSpeed = _moveSpeed * 0.5;
		_mountObject->setActive(true);
		_mountObject->_skinnedAnim->Play("WB");
		_playerObject->_skinnedAnim->Stop();
		break;
	case P_WALKBACK:
		_playSpeed = _moveSpeed * 0.5;
		_playerObject->_skinnedAnim->Play("WB", 0.2f);
		break;
	case P_DAMAGED:
		_isMount = false;
		_playerObject->_skinnedAnim->Play("DM", 0.2f);
		break;
	case P_END:
		break;
	default:
		break;
	}
}




//�ܺ��� �Է¿� ���� �÷��̾��� �̵��� ����.
void xPlayer::moveControl(dx::transform * trans)
{
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		trans->MovePositionWorld(trans->GetForward()*0.05*_moveSpeed);
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		trans->MovePositionWorld(-trans->GetForward()*0.02*_moveSpeed);
	}
}

void xPlayer::rotateControl(dx::transform * trans)
{
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		if (_playerObject->_transform->GetAngleY() <= -360)
		{
			_playerObject->_transform->SetAngleY(0);
		}
		_playerObject->_transform->SetAngleY(_playerObject->_transform->GetAngleY() - 3);

		trans->RotateSelf(0.0f, -D3DXToRadian(3), 0.0f);
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		if (_playerObject->_transform->GetAngleY() >= 360)
		{
			_playerObject->_transform->SetAngleY(0);
		}
		_playerObject->_transform->SetAngleY(_playerObject->_transform->GetAngleY() + 3);

		trans->RotateSelf(0.0f, D3DXToRadian(3), 0.0f);
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

void xPlayer::skillControl()
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
		//playerSkillOmni(1.0f);
		_nowSelectedSkill = SKILL_HEAL;
	}

	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		//playerSkillDirect(1.0);
		//playerDamaged(1, 0.5, 100.0, 100.0, 2.0);
		_nowSelectedSkill = SKILL_MAGICMISSILE;
	}

	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		_nowSelectedSkill = SKILL_LIGHTNING;
	}

	if (KEYMANAGER->isOnceKeyDown('4'))
	{
		//_nowSelectedSkill = SKILL_ROAR;
		_nowSelectedSkill = SKILL_SKYSWD;
	}

	if (KEYMANAGER->isOnceKeyDown('5'))
	{
		//_nowSelectedSkill = SKILL_WHIRLWIND;
		_nowSelectedSkill = SKILL_FIRE;
	}

	if (KEYMANAGER->isOnceKeyDown('6'))
	{
		//_nowSelectedSkill = SKILL_SLAM;
		_nowSelectedSkill = SKILL_SHIELD;
	}

	if (KEYMANAGER->isOnceKeyDown('7'))
	{
		//_nowSelectedSkill = SKILL_SLAM;
		_nowSelectedSkill = SKILL_METEOR;
	}

	if (KEYMANAGER->isOnceKeyDown('8'))
	{
		_nowSelectedSkill = SKILL_WHIRLWIND;
	}


}

void xPlayer::summonControl()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LSHIFT))
	{
		if (!_isMount)
		{
			summonMount();
		}
		else
		{
			unSummonMount();
		}
	}
	if (_isMount)
	{
		_playerObject->_transform->SetWorldPosition(_sitPos->GetWorldPosition());
	}
}

//���
void xPlayer::actionControl()
{
	//moveControl();

	rotateControl(getPlayerObject()->_transform);

	attackControl();

	jumpControl();

	skillControl();
}

//�÷��̾� ������ ����
void xPlayer::playerAttack()
{
	//BladePosInit();
	//�ش���°� �ƴϸ� �ൿ���� ���ƶ�.
	//if (!(_state == P_STAND || _state == P_RUN || _state == P_MOVE || _state == P_WALKBACK || _state == P_READYTOATTACK)) { return; }

	//�˱� ��ġ �ʱ�ȭ.
	_isOnBattle = true;

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
		if (rand > 80.0f)
		{
			_state = P_ATTACK;//AT1H
			_playSpeed = 1.5f;

		}
		else if (rand > 60.0f)
		{
			_state = P_ATTACK2;//AT2H
			_playSpeed = 1.5f;
		}
		else if (rand > 40.0f)
		{
			_state = P_ATTACK3;//AT2HL
			_playSpeed = 2.0f;
		}
		else if (rand > 20.f)
		{
			_state = P_ATTACK5;//AT2HL2
			_playSpeed = 2.5f;
		}
		else
		{
			_state = P_ATTACK6;
			_playSpeed = 2.0f;
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
	if (_state == P_DEATH) return;

	if (_isInvincible) return;

	if (_isMount)
	{
		_isMount = false;
		this->unSummonMount();
	}

	_isOnBattle = true;

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

void xPlayer::setHeight(dx::transform * trans)
{
	D3DXVECTOR3 pos = trans->GetWorldPosition();
	if (linkTerrain != nullptr) _baseHeight = linkTerrain->getHeight(pos.x, pos.z);
}

void xPlayer::out_ItemUpdate()
{

	if (_weaponCurrent != W_NONE)
	{


		D3DXMATRIX matHand = _EquipSocket.find("RHAND")->second->CombinedTransformationMatrix;
		_weaponObject->_transform->SetWorldMatrix(matHand);
		//_weaponObject->update();
	}

	if (_shieldCurrent != SH_NONE)
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
			if (PHYSICSMANAGER->isOverlap(this->_playerObject->_transform, &this->_attackBound, (*iter)->_transform, &(*iter)->_boundBox))
			{
				targetMonster = (*iter);
				(*iter)->setHP((*iter)->getHP() - PLAYERMANAGER->Getatt());
				_dmText->init(PLAYERMANAGER->Getatt(), LHS::FONTCOLOR::FONT_BLUE);
				yPosition = targetMonster->_boundBox.getLocalMaxPos().y;
				_dmText->setPos(D3DXVECTOR3(targetMonster->_transform->GetWorldPosition().x, yPosition, targetMonster->_transform->GetWorldPosition().z));

				monsterCenter->SetWorldPosition((*iter)->_transform->GetWorldPosition());

				D3DXVECTOR3 pos = monsterCenter->GetWorldPosition();

				pos.y += (*iter)->_boundBox.getHalfSize().y;

				monsterCenter->SetWorldPosition(pos);

				EFFECT->findEffect("�ǰ�")->setLimitTime(0.5f);
				EFFECT->findEffect("�ǰ�")->Start(monsterCenter);

				/*if ((*iter)->getHP() < 0)
				{
					exit(0);
				}*/
				//FONTMANAGER->fontOut("���Ⱦ�!", WINSIZEX / 2, WINSIZEY / 2, 0xffffffff);
			}
		}
	}
}

void xPlayer::setBladeLight()
{

	vertexNum = 45;//�� ���ô� ���ؽ� ����

	primitives = vertexNum - 2;



	idx = new DWORD[vertexNum];

	D3DXVECTOR3 nowEdgePos = _edgeTrans->GetWorldPosition();
	D3DXVECTOR3 nowHandPos = _handTrans->GetWorldPosition();

	//_vertexDeque.clear();//���� ����ִ�.

						 //���� ��ġ�� �޴´�!
						 //�� ������ ��� ���� �Ǹ�!
	//_vecPosEdge.push_front(nowEdgePos);//��ġ������ ��װ� ����ִ�! ���� ��� ����ش�.
	//_vecPosHand.push_front(nowHandPos);

	//if (_vecPosEdge.size() > vertexNum / 2)
	//{
	//	_vecPosEdge.pop_back();
	//	_vecPosHand.pop_back();
	//}


	////���� ���� ����
	//_device->CreateVertexBuffer(
	//	sizeof(MYLIGHTVERTEX) * vertexNum,
	//	D3DUSAGE_WRITEONLY,
	//	MYLIGHTVERTEX::FVF,
	//	D3DPOOL_DEFAULT,
	//	&_myVertexbuffer,
	//	NULL);


	////�ε��� ���� ����
	//_device->CreateIndexBuffer(
	//	sizeof(DWORD) * vertexNum,
	//	D3DUSAGE_WRITEONLY,
	//	D3DFMT_INDEX32,
	//	D3DPOOL_DEFAULT,
	//	&_myIndexBuffer,
	//	NULL);
	// 1---2 //�������. 2 <-> 3
	// |  /|	
	// | / |								
	// 0---3
	//UV�� �����ϰ� �����Ѵٰ� �����Ͽ�����.

	//LPMYLIGHTVERTEX pVertices;

	float maxX = 5;
	float minX = -5;



	//memset(pVertices, 0, sizeof(MYLIGHTVERTEX)*vertexNum);
	for (int i = 0; i < vertexNum / 2; i++)
	{
		//0,2,4....
		//float x = 0;
		//x = nowEdgePos; //((i * 2 + 1) * ((maxX - minX) / (vertexNum - 2)) + minX);

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

		tempVertex.pos = nowHandPos;//D3DXVECTOR3(x, -5, 0);//posHand +
		tempVertex.uv = D3DXVECTOR2(u, 1);
		_vertexDeque.push_back(tempVertex);

		//1,3,5
		//float y = 0;
		//y = ((i * 2) * ((maxX - minX) / (vertexNum - 2)) + minX);

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
		tempVertex2.pos = nowEdgePos;//D3DXVECTOR3(y, 5, 0);//posHand +
		tempVertex2.uv = D3DXVECTOR2(z, 0);

		_vertexDeque.push_back(tempVertex2);
	}


	//_myVertexbuffer->Lock(0, 0, (void**)&pVertices, 0);


	pVertices = new MYLIGHTVERTEX[vertexNum];

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

//�ؽ��� �ε�
	D3DXCreateTextureFromFile(
		_device,
		"�˱�_001.png",
		&_texture);


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
	////����ġ ��ŭ ����.
	//�켱 �׸���. ����.
	//dx::transform* boneTrans = new dx::transform;
	//boneTrans->SetWorldMatrix(CloneSkinned->getSkinnedMesh()->GetFineBONE("humanfemale_Bone121_CSR")->CombinedTransformationMatrix);
	//pv3��
	//DESC3.Position = nowPeriod * 1.0;
	//playerAnim.setTrackDesc0(DESC3);
	/*CloneSkinned->setTrackDesc0(DESC_ORIGIN);
	playerAnim.updateBone();
	playerAnim.getSkinnedMesh()->GetFineBONE("humanfemale_Bone121_CSR")->CombinedTransformationMatrix;
	if (boneTrans->GetFinalMatrix() != playerAnim.getSkinnedMesh()->GetFineBONE("humanfemale_Bone121_CSR")->CombinedTransformationMatrix)
	{
	int a = 0;
	}*/
	//pv2��

}


void xPlayer::BladePosInit()
{
	//���� ���� �ʱ�ȭ
	_vecPosEdge.clear();
	_vecPosHand.clear();



}

//������ ȣ�����ش�.
void xPlayer::out_setTargetByMouse(camera* mainCamera)
{
	if (_monsterPool != nullptr && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (targetMonster != nullptr) targetMonster->setIsRender(false);
		targetMonster = NULL;//Ÿ���� ������ ����.
		for (int i = 0; i < _monsterPool->size(); i++)
		{
			Ray ray;

			D3DXVECTOR2 ptmouse = { (float)GetMousePos().x, (float)GetMousePos().y };
			mainCamera->computeRay(&ray, &ptmouse);

			if (PHYSICSMANAGER->isRayHitBound(&ray, &(*_monsterPool)[i]->_boundBox, (*_monsterPool)[i]->_transform, NULL, NULL))
			{

				if (NULL != targetMonster)
				{
					D3DXVECTOR3 LengthVector = targetMonster->_transform->GetWorldPosition() - _playerObject->_transform->GetWorldPosition();
					float Now = D3DXVec3Length(&LengthVector);
					LengthVector = (*_monsterPool)[i]->_transform->GetWorldPosition() - _playerObject->_transform->GetWorldPosition();
					float New = D3DXVec3Length(&LengthVector);

					if (Now > New)//���� ��ġ ��
					{
						//���߿� �������� ����
						targetMonster = (*_monsterPool)[i];
					}
				}
				else
				{
					//������� �� �ֱ�.
					targetMonster = (*_monsterPool)[i];
				}
			}
		}
	}
}

void xPlayer::initMount()
{
	D3DXMATRIX matCorrection, matScale, matRotate;
	D3DXMatrixScaling(&matScale, 0.5, 0.5, 0.5);
	D3DXMatrixRotationY(&matRotate, D3DXToRadian(180));
	matCorrection = matScale*matRotate;
	xMeshSkinned* mountMesh = RM_SKINNED->getResource("Resource/Player/MOUNT/MOUNT.X", &matCorrection);
	_mountObject = new baseObject;
	_mountObject->setMesh(mountMesh);
	_mountObject->setActive(false);
	_sitPos = new dx::transform;
	_mountObject->_skinnedAnim->AddBoneTransform("mount_Bone53", _sitPos);
	_renderObjects.push_back(_mountObject);

}

void xPlayer::summonMount()
{
	_isMount = true;
	_mountObject->setActive(true);
	_mountObject->_transform->SetWorldPosition(_playerObject->_transform->GetWorldPosition());//�÷��̾ �������̿� ���̱� ���� ���� �÷��̾��� ��ġ�� ��ȯ����.
	_playerObject->_transform->SetWorldPosition(_sitPos->GetWorldPosition());
	_mountObject->_transform->LookPosition(_playerObject->_transform->GetForward() + _mountObject->_transform->GetWorldPosition());
	_sitPos->AddChild(_playerObject->_transform);
	//������. �ʱ�ȭ �� ������ ������ �ùٸ� ���Ⱚ�� ������ ���� ����.
	//���� ������ ��ġ�� �����ϰ� �ʱ�ȭ�� �������� �÷��̾ ���Ⱚ�� �����޾ƾ� ��.
	//_playerObject->_transform->look
	_state = P_MOUNT_S;
	_moveSpeed = 3.0f;
}

void xPlayer::unSummonMount()
{
	_isMount = false;
	_mountObject->setActive(false);
	_playerObject->_transform->ReleaseParent();
	_playerObject->_transform->SetRotateWorld(_mountObject->_transform->GetWorldRotateMatrix());
	_state = P_JUMPDOWN;
	_moveSpeed = 1.5f;
}



//��Ƽ�
void xPlayer::skilltrigger()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON, false))
	{
		switch (_nowSelectedSkill)
		{
		case SKILL_NONE:
			break;
		case SKILL_HEAL:
			playerSkillOmni(1.0f);
			//_state = P_READYOMNI;
			break;
		case SKILL_MAGICMISSILE:
			if (targetMonster != NULL)
			{
				playerSkillDirect(1.0f);
			}
			//_state = P_READYSPELL;
			break;
		case SKILL_LIGHTNING:
			if (targetMonster != NULL)
			{
				playerSkillOmni(1.0f);
			}
			//_state = P_READYOMNI;
			break;
		case SKILL_SKYSWD:
			if (targetMonster != NULL)
			{
				playerSkillDirect(2.0F);
			}
			break;
		case SKILL_FIRE:
			if (targetMonster != NULL)
			{
				playerSkillDirect(2.0F);
			}
			break;
		case SKILL_SHIELD:
			playerSkillDirect(1.0F);
			break;
		case SKILL_METEOR:
			if (targetMonster != NULL)
			{
				playerSkillDirect(2.0F);
			}
			break;
		case SKILL_ROAR:
			_state = P_BATTLEROAR;
			break;
		case SKILL_WHIRLWIND:
			_state = P_WHIRLWIND;
			SKM->findSK("���ۺ���")->setSkillPosTrans(this->_playerObject->_transform);
			SKM->findSK("���ۺ���")->Start();
			//���ݹ��� ����
			_attackTrans.SetWorldPosition(0.0f, 0.5f, 0.0f);
			_attackBound.setBound(&_attackTrans.GetWorldPosition(), &D3DXVECTOR3(1.0, 0.5, 1.0));

			break;
		case SKILL_SLAM:
			_state = P_SLAM;
			break;
		case SKILL_END:
			break;
		default:
			break;
		}
	}
	//_nowSelectedSkill = SKILL_NONE;
}

void xPlayer::useNowSkill()
{
	if ((_state == P_CASTOMNI && _prevState != P_CASTOMNI) || (_state == P_CASTSPELL && _prevState != P_CASTSPELL))//
	{
		switch (_nowSelectedSkill)
		{
		case SKILL_NONE:
			break;
		case SKILL_HEAL:
			SKM->findSK("��")->setSkillPosTrans(_playerObject->_transform);
			SKM->findSK("��")->Start();

			SOUNDMANAGER->play("����", 0.7f);
			SOUNDMANAGER->setMusicSpeed("����", 1.0f);
			break;
		case SKILL_MAGICMISSILE:
			if (targetMonster != NULL)
			{
				SKM->findSK("��������")->setSkillPosTrans(this->_playerObject->_transform);
				//		SKM->findSK("��������")->setSkillDirTrans(_testTrans);
				SKM->findSK("��������")->setOneTargetTrans(targetMonster->_transform);
				SKM->findSK("��������")->Start();
				//SKM->findSK("��������")->setOneTargetTrans(targetMonster->_transform);
				SOUNDMANAGER->play("��������");
			}
			break;
		case SKILL_LIGHTNING:
			if (targetMonster != NULL)
			{
				SKM->findSK("����Ʈ��")->setSkillPosTrans(this->_playerObject->_transform);
				SKM->findSK("����Ʈ��")->setSkillDirTrans(this->_playerObject->_transform);
				SKM->findSK("����Ʈ��")->setOneTargetTrans(targetMonster->_transform);
				SKM->findSK("����Ʈ��")->Start();
				SOUNDMANAGER->play("����");
			}
			break;
		case SKILL_SKYSWD:
			if (targetMonster != NULL)
			{
				SKM->findSK("�ϴ���_���")->setSkillPosTrans(this->_playerObject->_transform);
				SKM->findSK("�ϴ���_���")->setSkillDirTrans(this->_playerObject->_transform);
				SKM->findSK("�ϴ���_���")->setOneTargetTrans(targetMonster->_transform);
				SKM->findSK("�ϴ���_���")->Start();
			}
			break;
		case SKILL_FIRE:
			if (targetMonster != NULL)
			{
				SKM->findSK("���̾����")->setSkillPosTrans(this->_playerObject->_transform);
				SKM->findSK("���̾����")->setSkillDirTrans(this->_playerObject->_transform);
				SKM->findSK("���̾����")->setOneTargetTrans(targetMonster->_transform);
				SKM->findSK("���̾����")->Start();

				SOUNDMANAGER->play("�Ҳ�");
				//SOUNDMANAGER->setMusicSpeed("�Ҳ�",1.0f);
			}
			break;
		case SKILL_SHIELD:
			_isInvincible = true;
			SKM->findSK("��������")->setSkillPosTrans(_playerObject->_transform);
			SKM->findSK("��������")->Start();
			SOUNDMANAGER->play("����1");
			break;
		case SKILL_METEOR:
			if (targetMonster != NULL)
			{
				SKM->findSK("����_������")->setSkillPosTrans(this->_playerObject->_transform);
				SKM->findSK("����_������")->setSkillDirTrans(this->_playerObject->_transform);
				SKM->findSK("����_������")->setOneTargetTrans(targetMonster->_transform);
				SKM->findSK("����_������")->Start();
				SOUNDMANAGER->play("����");
			}
			break;
		case SKILL_WHIRLWIND:


			break;
		case SKILL_END:
			break;
		default:
			break;
		}
	}
}

void xPlayer::skillProcesser() {
	switch (_nowSelectedSkill)
	{
	case SKILL_NONE:
		break;
	case SKILL_HEAL:
		if (SKM->findSK("��")->getEnd())
		{
			if (PLAYERMANAGER->GetMaxHp() < PLAYERMANAGER->GetHp() + PLAYERMANAGER->Getatt())
			{
				PLAYERMANAGER->SetHp(PLAYERMANAGER->GetMaxHp());
			}
			else
			{
				PLAYERMANAGER->SetHp(PLAYERMANAGER->GetHp() + PLAYERMANAGER->Getatt());
			}
			if (_isOnBattle)
			{
				this->_state = P_READYTOATTACK;
			}
			else
			{
				this->_state = P_STAND;
			}
			_nowSelectedSkill = SKILL_NONE;
		}
		break;
	case SKILL_MAGICMISSILE:
		if (targetMonster != nullptr)
		{
			if (SKM->findSK("��������")->getCollision())
			{
				targetMonster->setHP(targetMonster->getHP() - PLAYERMANAGER->Getatt());

			}
		}
		if (SKM->findSK("��������")->getEnd())
		{
			if (_isOnBattle)
			{
				this->_state = P_READYTOATTACK;
			}
			else
			{
				this->_state = P_STAND;
			}
			_nowSelectedSkill = SKILL_NONE;
		}

		//if (targetMonster != NULL)
		//{
		//	SKM->findSK("��������")->setSkillPosTrans(this->_playerObject->_transform);
		//	//		SKM->findSK("��������")->setSkillDirTrans(_testTrans);
		//	SKM->findSK("��������")->setOneTargetTrans(targetMonster->_transform);
		//	SKM->findSK("��������")->Start();
		//	//SKM->findSK("��������")->setOneTargetTrans(targetMonster->_transform);
		//}
		break;
	case SKILL_LIGHTNING:
		if (targetMonster != nullptr)
		{
			if (SKM->findSK("����Ʈ��")->getCollision())
			{
				targetMonster->setHP(targetMonster->getHP() - PLAYERMANAGER->Getatt());
			}
		}
		if (SKM->findSK("����Ʈ��")->getEnd())
		{
			if (_isOnBattle)
			{
				this->_state = P_READYTOATTACK;
			}
			else
			{
				this->_state = P_STAND;
			}
			_nowSelectedSkill = SKILL_NONE;
			SOUNDMANAGER->stop("����");
		}

		//if (SKM->isEnd?)
			//_state = P_STAND or P_;

		/*SKM->findSK("�ǵ�")->setSkillPosTrans(_playerObject->_transform);
		SKM->findSK("�ǵ�")->Start();*/
		break;

	case SKILL_SKYSWD:
		if (targetMonster != nullptr)
		{
			if (SKM->findSK("�ϴ���_���")->getCollision())
			{
				targetMonster->setHP(0);
			}
		}

		if (SKM->findSK("�ϴ���_���")->getEnd())
		{
			if (_isOnBattle)
			{
				this->_state = P_READYTOATTACK;
			}
			else
			{
				this->_state = P_STAND;
			}
			_nowSelectedSkill = SKILL_NONE;
		}

		break;
	case SKILL_FIRE:
		if (targetMonster != nullptr)
		{
			if (SKM->findSK("���̾����")->getCollision())
			{
				targetMonster->setHP(0);
			}
		}

		if (SKM->findSK("���̾����")->getEnd())
		{
			if (_isOnBattle)
			{
				this->_state = P_READYTOATTACK;
			}
			else
			{
				this->_state = P_STAND;
			}
			_nowSelectedSkill = SKILL_NONE;
			SOUNDMANAGER->stop("�Ҳ�");
		}

		break;
	case SKILL_SHIELD:
		if (SKM->findSK("��������")->getEnd())
		{
			_isInvincible = false;
			if (_isOnBattle)
			{
				this->_state = P_READYTOATTACK;
			}
			else
			{
				this->_state = P_STAND;
			}
			_nowSelectedSkill = SKILL_NONE;
			SOUNDMANAGER->stop("����1");
		}
		break;
	case SKILL_METEOR:
		if (targetMonster != nullptr)
		{
			if (SKM->findSK("����_������")->getCollision())
			{
				targetMonster->setHP(targetMonster->getHP() - PLAYERMANAGER->Getatt());
			}
		}

		if (SKM->findSK("����_������")->getEnd())
		{
			if (_isOnBattle)
			{
				this->_state = P_READYTOATTACK;
			}
			else
			{
				this->_state = P_STAND;
			}
			_nowSelectedSkill = SKILL_NONE;
			SOUNDMANAGER->stop("����");
		}

		break;
	case SKILL_WHIRLWIND:
		if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
		{
			normalAttackDamageProcessing();
		}
		else
		{
			//SKM->findSK("���ۺ���")->setResetOn();

			SKM->findSK("���ۺ���")->InitActiveSettingOn();
			SKM->findSK("���ۺ���")->resetTimeOn();
			if (_isOnBattle)
			{
				this->_state = P_READYTOATTACK;
			}
			else
			{
				this->_state = P_STAND;
			}
			_nowSelectedSkill = SKILL_NONE;

			_attackTrans.SetWorldPosition(0, 0.5f, 0.8);
			_attackBound.setBound(&_attackTrans.GetWorldPosition(), &D3DXVECTOR3(0.5, 0.5, 0.5));

			SOUNDMANAGER->stop("������");
		}
		break;
	case SKILL_END:
		break;
	default:
		break;
	}
}

void xPlayer::updateEquipments()
{
	if (_weaponCurrent != PLAYERMANAGER->GetWeapon())
	{
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
		//_weaponObject = new baseObject;

		PL_WEAPON AA = PLAYERMANAGER->GetWeapon();

		switch (PLAYERMANAGER->GetWeapon())
		{
		case W_NONE:
			D3DXMatrixRotationY(&matRotate2, D3DXToRadian(270));
			D3DXMatrixScaling(&matScale2, 0.5, 0.5, 0.5);
			matCorrection2 = matRotate2*matScale2;
			pSkinned2 = RM_XMESH->getResource("Resource/item/Sword/weapon01/weapon01.X", &matCorrection2);
			_weaponObject->setActive(false);
			_BladeLength = 0.0f;
			break;
		case W_BLACK_WING:
			D3DXMatrixRotationY(&matRotate2, D3DXToRadian(270));
			D3DXMatrixScaling(&matScale2, 0.5, 0.5, 0.5);
			matCorrection2 = matRotate2*matScale2;
			pSkinned2 = RM_XMESH->getResource("Resource/item/Sword/weapon01/weapon01.X", &matCorrection2);
			_weaponObject->setActive(true);

			_BladeLength = 1.0f;
			break;
		case W_BROAD:
			D3DXMatrixRotationY(&matRotate2, D3DXToRadian(270));
			D3DXMatrixScaling(&matScale2, 0.25, 0.25, 0.25);
			matCorrection2 = matRotate2*matScale2;

			pSkinned2 = RM_XMESH->getResource("Resource/item/Sword/weapon02/weapon02.X", &matCorrection2);
			_weaponObject->setActive(true);

			_BladeLength = 0.7f;
			break;
		case W_DEAMON:
			D3DXMatrixRotationZ(&matRotate2, D3DXToRadian(0));
			D3DXMatrixScaling(&matScale2, 0.5, 0.5, 0.5);
			matCorrection2 = matRotate2*matScale2;

			pSkinned2 = RM_XMESH->getResource("Resource/item/Sword/weapon03/weapon03.X", &matCorrection2);
			_weaponObject->setActive(true);

			_BladeLength = 0.72f;
			break;
		case W_KATANA:
			D3DXMatrixRotationZ(&matRotate2, D3DXToRadian(0));
			D3DXMatrixScaling(&matScale2, 0.5, 0.5, 0.5);
			matCorrection2 = matRotate2*matScale2;

			pSkinned2 = RM_XMESH->getResource("Resource/item/Sword/weapon04/weapon04.X", &matCorrection2);
			_weaponObject->setActive(true);

			_BladeLength = 0.5f;
			break;
		case W_WOOD:
			D3DXMatrixRotationZ(&matRotate2, D3DXToRadian(0));
			D3DXMatrixScaling(&matScale2, 0.33, 0.33, 0.33);
			matCorrection2 = matRotate2*matScale2;

			pSkinned2 = RM_XMESH->getResource("Resource/item/Sword/weapon05/weapon05.X", &matCorrection2);
			_weaponObject->setActive(true);

			_BladeLength = 0.0f;
			break;
		case W_END:
			break;
		default:
			break;
		}
		_weaponObject->setMesh(pSkinned2);

		_edgeTrans->SetWorldPosition(_handTrans->GetWorldPosition() + _handTrans->GetRight() * _BladeLength);
		_handTrans->AddChild(_edgeTrans);

		_weaponCurrent = PLAYERMANAGER->GetWeapon();
	}

	if (_shieldCurrent != PLAYERMANAGER->GetShield())
	{

		D3DXMATRIXA16 matCorrection3, matScale3, matRotate3;
		D3DXMatrixIdentity(&matCorrection3);
		D3DXMatrixRotationY(&matRotate3, D3DXToRadian(270));
		D3DXMatrixScaling(&matScale3, 0.25f, 0.25f, 0.25f);
		matCorrection3 = matRotate3 * matScale3;
		xMeshStatic* pSkinned3;
		pSkinned3 = new xMeshStatic;
		//_shieldObject = new baseObject;

		switch (PLAYERMANAGER->GetShield())
		{
		case SH_NONE:
			pSkinned3 = RM_XMESH->getResource("Resource/item/Shield/shield01/shield01.X", &matCorrection3);
			_shieldObject->setActive(false);

			break;
		case SH_SPIKE:
			D3DXMatrixRotationY(&matRotate3, D3DXToRadian(270));//�ǵ� 1, 2
			D3DXMatrixScaling(&matScale3, 0.25f, 0.25f, 0.25f);
			matCorrection3 = matRotate3 * matScale3;

			pSkinned3 = RM_XMESH->getResource("Resource/item/Shield/shield01/shield01.X", &matCorrection3);
			_shieldObject->setActive(true);

			break;
		case SH_BUCKLER:
			D3DXMatrixRotationY(&matRotate3, D3DXToRadian(270));//�ǵ� 1, 2
			D3DXMatrixScaling(&matScale3, 0.2f, 0.2f, 0.2f);
			matCorrection3 = matRotate3 * matScale3;

			pSkinned3 = RM_XMESH->getResource("Resource/item/Shield/shield02/shield02.X", &matCorrection3);
			_shieldObject->setActive(true);

			break;
		case SH_BRONZE:
			D3DXMatrixRotationZ(&matRotate3, D3DXToRadian(270));//�ǵ� 3, 4, 5
			D3DXMatrixScaling(&matScale3, 0.5f, 0.5f, 0.5f);
			matCorrection3 = matRotate3 * matScale3;

			pSkinned3 = RM_XMESH->getResource("Resource/item/Shield/shield03/shield03.X", &matCorrection3);
			_shieldObject->setActive(true);

			break;
		case SH_CROSS:
			D3DXMatrixRotationZ(&matRotate3, D3DXToRadian(270));//�ǵ� 3, 4, 5
			D3DXMatrixScaling(&matScale3, 0.25f, 0.25f, 0.25f);
			matCorrection3 = matRotate3 * matScale3;

			pSkinned3 = RM_XMESH->getResource("Resource/item/Shield/shield04/shield04.X", &matCorrection3);
			_shieldObject->setActive(true);

			break;
		case SH_KITE:
			D3DXMatrixRotationZ(&matRotate3, D3DXToRadian(270));//�ǵ� 3, 4, 5
			D3DXMatrixScaling(&matScale3, 0.25f, 0.25f, 0.25f);
			matCorrection3 = matRotate3 * matScale3;

			pSkinned3 = RM_XMESH->getResource("Resource/Player/FHUMAN_NEW/Shoulder.X", &matCorrection3);// //Resource/item/Shield/shield05/shield05.X
			_shieldObject->setActive(true);

			break;
		case SH_END:
			break;
		default:
			break;
		}

		_shieldObject->setMesh(pSkinned3);

		_shieldCurrent = PLAYERMANAGER->GetShield();
	}
}

void xPlayer::out_updateBladeLight()
{
	D3DXVECTOR3 nowEdgePos = _edgeTrans->GetWorldPosition();
	D3DXVECTOR3 nowHandPos = _handTrans->GetWorldPosition();

	_vertexDeque.clear();//���� ����ִ�.

	//���� ��ġ�� �޴´�!
	//�� ������ ��� ���� �Ǹ�!
	_vecPosEdge.push_front(nowEdgePos);//��ġ������ ��װ� ����ִ�! ���� ��� ����ش�.
	_vecPosHand.push_front(nowHandPos);

	if (_vecPosEdge.size() > vertexNum / 2)
	{
		_vecPosEdge.pop_back();
		_vecPosHand.pop_back();
	}


	for (int i = 0; i < _vecPosEdge.size(); i++)
	{
		//0,2,4
		float u = 0;

		if (i == 0)
		{
			u = 0;
		}
		else
		{
			u = ((float)(i * 2) / (float)(vertexNum));
		}

		MYLIGHTVERTEX tempVertex1;
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
			u = ((float)(i * 2 + 1) / (float)(vertexNum));
		}

		MYLIGHTVERTEX tempVertex2;
		tempVertex2.pos = _vecPosEdge[i];//posHand +
		tempVertex2.uv = D3DXVECTOR2(u, 0);

		_vertexDeque.push_back(tempVertex1);
		_vertexDeque.push_back(tempVertex2);

		int DequeSizeOver = _vertexDeque.size() - vertexNum;
		MYLIGHTVERTEX tempUV[2];
		for (int v = 0; v < DequeSizeOver; v++)
		{
			_vertexDeque.pop_front();
			_vertexDeque.pop_front();
		}
	}

	//i = 0; ���� 
	//i += 2;
	//i + 2 = i;����
	//i + 1 + 2 = i + 1;


	for (int i = 0; i < _vertexDeque.size(); i++)
	{
		pVertices[i] = _vertexDeque[i];//�������� ����!
	}

	for (int i = 0; i < _vertexDeque.size(); i++)
	{
		idx[i] = i;
	}


	//==========================================================

	//primitives = _ - 2;

	//for (int i = 0; i < _vecPosHand.size(); i++)
	//{
	//	//pVertices[i * 2 + 1].pos = _vecPosEdge[i];
	//	//pVertices[i * 2].pos = _vecPosHand[i];



	//	float u = 0;
	//	if (i == 0)
	//	{
	//		u = 0;
	//	}
	//	else
	//	{
	//		u = ((float)i / (float)(vertexNum - 2));
	//	}

	//	pVertices[i * 2 + 1].uv = D3DXVECTOR2(u, 1);
	//}





}

void xPlayer::drawBladeLight()
{


	////����Ʈ����� ��� ������
	////====================================================================
	////			## �ؽ��� Wrap ��� ##
	////====================================================================
	//

	for (int i = 0; i < _vertexDeque.size(); i++)
	{
		pVertices[i].pos;
		pVertices[i].uv;
	}

	_device->SetRenderState(D3DRS_LIGHTING, false);		//�������� ����.
	_device->SetRenderState(D3DRS_ZWRITEENABLE, false);	//z ������ ���⸦ ���´�.

	_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//���� ���� ����
	_device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//Texture �� ���� Diffuse ���⼭�� �����÷��� ���İ� �� ���� ���� ����� �Ѵ�.
	_device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	_device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
	_device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);



	////_device->SetRenderState(D3DRS_LIGHTING, true);
	//
	////_device->SetRenderState(D3DRS_ZWRITEENABLE, false);

	////���� ���� ����
	//_device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	////_device->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	////_device->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE);

	//_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


	//_device->SetRenderState(D3DRS_LIGHTING, FALSE);
	//_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);


	////Texture �� ���� Diffuse ���⼭�� �����÷��� ���İ� �� ���� ���� ����� �Ѵ�.
	//_device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	//_device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
	//_device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);

	//////�ݺ������� ���´� 1 �Ѿ�� UV ��ǥ�� 1�� ���� �ٽ� 0���� ����
	////_device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DPTADDRESSCAPS_WRAP);
	////_device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DPTADDRESSCAPS_WRAP);

	//�׸��� ���� �ε��� �ؽ��ĸ� �����ϱ�
	_device->SetTexture(0, _texture);

	//���� �׸���
	//_device->SetStreamSource(0, _myVertexbuffer, 0, sizeof(MYLIGHTVERTEX));
	_device->SetFVF(MYLIGHTVERTEX::FVF);
	//_device->SetIndices(_myIndexBuffer);

	_device->DrawIndexedPrimitiveUP(D3DPT_TRIANGLESTRIP, 0, vertexNum, primitives, idx, D3DFMT_INDEX32, pVertices, sizeof(MYLIGHTVERTEX));
	//�ؽ��� ��������

	_device->SetTexture(0, NULL);

	_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);


	_device->SetRenderState(D3DRS_LIGHTING, true);
	_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	_device->SetRenderState(D3DRS_ZWRITEENABLE, true);

}