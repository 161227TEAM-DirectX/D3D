#include "stdafx.h"
#include "rightView.h"
//
#include "objectClass.h"
#include "rightSmallGrid.h"

rightView::rightView()
	:boolTile1(false), boolTile2(false), boolTile3(false), boolTile4(false), boolRaw(false), numberTile1(0), numberTile2(0), numberTile3(0), numberTile4(0), numberRaw(0)
	, numberSplate(0), boolSplate(false), numberNodeInstal(0), numberNodelink(0), numberMonster(0), boolHeight(false)
{
}

rightView::~rightView()
{
}

HRESULT rightView::init(void)
{
	//작은 그리드
	_rightSmallGrid = new rightSmallGrid;
	_rightSmallGrid->init();

	_objectClass = new objectClass;
	_objectClass->init();

	//변화가 없는 UI
	_UIBACK.uiNumber = UISTAGE::UIOFF;
	_UIkind.uiNumber = UISTAGE::UIOFF;

	for (int i = 0; i < 2; i++)
	{
		_UIsize[i].uiNumber = UISTAGE::UIOFF;
		_UIcontrol[i].uiNumber = UISTAGE::UIOFF;
		_UIsizeHeight[i].uiNumber = UISTAGE::UIOFF;
	}
	
	_OBJGO.uiNumber = UISTAGE::UIOFF;
	_OBJback.uiNumber = UISTAGE::UIOFF;

	//ui컨트롤 버튼 메뉴
	for (int i = 0; i < 2; i++)
	{
		_heightContorol[i].uiNumber = UISTAGE::UIOFF;
		_nodeInstalContorol[i].uiNumber = UISTAGE::UIOFF;
		_nodeLinkContorol[i].uiNumber = UISTAGE::UIOFF;
	}

	//상단 메뉴
	_TOPbutton[0].uiNumber = UISTAGE::UION;
	_TOPbutton[1].uiNumber = UISTAGE::UIOFF;
	_TOPbutton[2].uiNumber = UISTAGE::UIOFF;

	//환경중단 메뉴 
	_ENVbutton.uiNumber = ENVSTAGE::WATERMIDDLE;
	//오브중단 메뉴
	_OBJbutton.uiNumber = OBSTAGE::STORMTOWN1;
	//지형중단 메뉴
	_TERRIANbutton.uiNumber = TERSTAGE::TILEMAP1;

	//오브하단 메뉴
	for (int i = 0; i < 5; i++)
	{
		_OBJstorm1Button[i].uiNumber = OBSTAGEDOWN::ONEOFF;
		_OBJstorm2Button[i].uiNumber = OBSTAGEDOWN::ONEOFF;
	}

	for (int i = 0; i < 7; i++)
	{
		_OBJruinButton[i].uiNumber = OBSTAGEDOWN::ONEOFF;
	}

	for (int i = 0; i < 4; i++)
	{
		_OBJpiramidButton[i].uiNumber = OBSTAGEDOWN::ONEOFF;
	}
	//환경하단 메뉴 
	for (int i = 0; i < DEFENV; i++)
	{
		_ENVwaterButton[i].uiNumber = UISTAGE::UIOFF;
		_ENVskyButton[i].uiNumber = UISTAGE::UIOFF;
	}

	//몬스터 메뉴 하단
	for (int i = 0; i < DEFMONSTER; i++)
	{
		_ENVmonsterButton[i].uiNumber = UISTAGE::UIOFF;
	}

	//지형하단 메뉴
	for (int i = 0; i < DEFTER; i++)
	{
		_NumberTile1Button[i].uiNumber = UISTAGE::UIOFF;
		_NumberTile2Button[i].uiNumber = UISTAGE::UIOFF;
	}

	//지형하단 RAW 메뉴
	for (int i = 0; i < DEFTER; i++)
	{
		_NumberRawButton[i].uiNumber = UISTAGE::UIOFF;
	}

	_plus.uiNumber = UISTAGE::UIOFF;
	_minus.uiNumber = UISTAGE::UIOFF;

	//get넘겨줄 넘버
	numberEnv = 0;
	numberwater = 0;
	numberHeight = 0;
	scaleNumber = 0.1f;
	numberObject = 0;
	plusMinus = -25.0f;

	RotateAngle = 0.0f;
	RotateRadian = D3DXToRadian(15.0f);

	_mainCamera.SetRotateLocal(-D3DXToRadian(20), 0, 0);

	return S_OK;
}

void rightView::release(void)
{
}

void rightView::update(void)
{
	mouse = GetMousePos();

	_objectClass->update();

	numberObject = _objectClass->getnumberObject();

	this->EXKEY();

	if (mouse.x <= rightViewPort.X + rightViewPort.Width && mouse.x >= rightViewPort.X)
	{
		this->buttonTopUdate();
		this->buttonObUpdate();
		this->buttonENvUdate();
		this->buttonTerUdate();
	}


	if (_TOPbutton[0].uiNumber == UISTAGE::UION)
	{
		if (_OBJbutton.uiNumber == OBSTAGE::STORMTOWN1 ||
			_OBJbutton.uiNumber == OBSTAGE::STROMTOWN2 ||
			_OBJbutton.uiNumber == OBSTAGE::RUINSTAGE ||
			_OBJbutton.uiNumber == OBSTAGE::PIRAMID &&  _OBJGO.uiNumber == UISTAGE::UION)
		{

			if (_OBJstorm1Button[0].uiNumber == OBSTAGEDOWN::THREEOFF) _objectClass->objectUp(mouse, 0, 17);
			if (_OBJstorm1Button[1].uiNumber == OBSTAGEDOWN::THREEOFF) _objectClass->objectUp(mouse, 17, 26);
			if (_OBJstorm1Button[2].uiNumber == OBSTAGEDOWN::THREEOFF) _objectClass->objectUp(mouse, 26, 34);
			if (_OBJstorm1Button[3].uiNumber == OBSTAGEDOWN::THREEOFF) _objectClass->objectUp(mouse, 34, 50);
			if (_OBJstorm1Button[4].uiNumber == OBSTAGEDOWN::THREEOFF) _objectClass->objectUp(mouse, 50, 56);

			if (_OBJstorm2Button[0].uiNumber == OBSTAGEDOWN::THREEOFF) _objectClass->objectUp(mouse, 56, 62);
			if (_OBJstorm2Button[1].uiNumber == OBSTAGEDOWN::THREEOFF) _objectClass->objectUp(mouse, 62, 68);
			if (_OBJstorm2Button[2].uiNumber == OBSTAGEDOWN::THREEOFF) _objectClass->objectUp(mouse, 68, 74);
			if (_OBJstorm2Button[3].uiNumber == OBSTAGEDOWN::THREEOFF) _objectClass->objectUp(mouse, 74, 79);
			if (_OBJstorm2Button[4].uiNumber == OBSTAGEDOWN::THREEOFF) _objectClass->objectUp(mouse, 79, 84);

			if (_OBJruinButton[0].uiNumber == OBSTAGEDOWN::THREEOFF) _objectClass->objectUp(mouse, 84, 98);
			if (_OBJruinButton[1].uiNumber == OBSTAGEDOWN::THREEOFF) _objectClass->objectUp(mouse, 98, 112);
			if (_OBJruinButton[2].uiNumber == OBSTAGEDOWN::THREEOFF) _objectClass->objectUp(mouse, 112, 122);
			if (_OBJruinButton[3].uiNumber == OBSTAGEDOWN::THREEOFF) _objectClass->objectUp(mouse, 122, 128);
			if (_OBJruinButton[4].uiNumber == OBSTAGEDOWN::THREEOFF) _objectClass->objectUp(mouse, 128, 137);
			if (_OBJruinButton[5].uiNumber == OBSTAGEDOWN::THREEOFF) _objectClass->objectUp(mouse, 137, 141);
			if (_OBJruinButton[6].uiNumber == OBSTAGEDOWN::THREEOFF) _objectClass->objectUp(mouse, 141, 152);

			if (_OBJpiramidButton[0].uiNumber == OBSTAGEDOWN::THREEOFF) _objectClass->objectUp(mouse, 152, 165);
			if (_OBJpiramidButton[1].uiNumber == OBSTAGEDOWN::THREEOFF) _objectClass->objectUp(mouse, 165, 178);
			if (_OBJpiramidButton[2].uiNumber == OBSTAGEDOWN::THREEOFF) _objectClass->objectUp(mouse, 178, 183);
			if (_OBJpiramidButton[3].uiNumber == OBSTAGEDOWN::THREEOFF) _objectClass->objectUp(mouse, 183, 188);
		}
	}
}

void rightView::EXKEY(void)
{
	_mainCamera.SetWorldPosition(0.0f, 0.0f, plusMinus);

	//실험용 키설정
	if (KEYMANAGER->isStayKeyDown('O'))
	{
		if (plusMinus >= -2.0f)
		{
			plusMinus = -2.0f;
		}
		else
		{
			plusMinus += 0.3f;
		}
	}

	if (KEYMANAGER->isStayKeyDown('P'))
	{
		plusMinus -= 0.3f;
	}

	//확대축소체크 충돌
	if (PtInRect(&_plus.rc2, mouse))
	{
		_plus.uiNumber = UISTAGE::UION;

		if (plusMinus >= -2.0f)
		{
			plusMinus = -2.0f;
		}
		else
		{
			plusMinus += 0.3f;
		}
	}
	else
	{
		_plus.uiNumber = UISTAGE::UIOFF;
	}

	if (PtInRect(&_minus.rc2, mouse))
	{
		_minus.uiNumber = UISTAGE::UION;

		plusMinus -= 0.3f;
	}
	else
	{
		_minus.uiNumber = UISTAGE::UIOFF;
	}
}

void rightView::render(void)
{
	this->Render();
	this->buttonTop();
	this->buttonObMiddle();
	this->buttonENVMiddle();
	this->buttonTerMiddle();
}

void rightView::buttonTop()
{
	//UI 배경
	_UIBACK.tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/배경.png");
	SPRITEMANAGER->renderRectTexture(_UIBACK.tex, &_UIBACK.rc1, &_UIBACK.rc2, 0, 0, 512, 900, rightViewPort.X + (DWORD)0, rightViewPort.Y + (DWORD)0);

	//확대기능
	_plus.rc2 ={ (LONG)(rightViewPort.X + 30),(LONG)(rightViewPort.Y + 835),(LONG)(rightViewPort.X + 67),(LONG)(rightViewPort.Y + 872) };
	_plus.tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/확대축소.png");

	if (_plus.uiNumber == UISTAGE::UION)
	{
		SPRITEMANAGER->renderRectTexture(_plus.tex, &_plus.rc1, &_plus.rc2, 0, 0, 37, 37, rightViewPort.X + (DWORD)30, rightViewPort.Y + (DWORD)835);
	}
	else
	{
		SPRITEMANAGER->renderRectTexture(_plus.tex, &_plus.rc1, &_plus.rc2, 0, 37, 37, 74, rightViewPort.X + (DWORD)30, rightViewPort.Y + (DWORD)835);
	}

	//축소기능
	_minus.rc2 ={ (LONG)(rightViewPort.X + 75),(LONG)(rightViewPort.Y + 835),(LONG)(rightViewPort.X + 112),(LONG)(rightViewPort.Y + 872) };
	_minus.tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/확대축소.png");

	if (_minus.uiNumber == UISTAGE::UION)
	{
		SPRITEMANAGER->renderRectTexture(_minus.tex, &_minus.rc1, &_minus.rc2, 37, 0, 74, 37, rightViewPort.X + (DWORD)75, rightViewPort.Y + (DWORD)835);
	}
	else
	{
		SPRITEMANAGER->renderRectTexture(_minus.tex, &_minus.rc1, &_minus.rc2, 37, 37, 74, 74, rightViewPort.X + (DWORD)75, rightViewPort.Y + (DWORD)835);
	}

	//오브젝트 상단
	//충돌렉트위치
	_TOPbutton[0].rc2 ={ (LONG)(rightViewPort.X + 19),(LONG)(rightViewPort.Y + 15),(LONG)(rightViewPort.X + 129),(LONG)(rightViewPort.Y + 89) };
	if (_TOPbutton[0].uiNumber == UISTAGE::UION)
	{
		_TOPbutton[0].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/상단메뉴.png");
		SPRITEMANAGER->renderRectTexture(_TOPbutton[0].tex, &_TOPbutton[0].rc1, &_TOPbutton[0].rc2, 0, 0, 360, 80, rightViewPort.X + (DWORD)19, rightViewPort.Y + (DWORD)15);
	}

	//지형 상단
	//충돌렉트위치
	_TOPbutton[1].rc2 ={ (LONG)(rightViewPort.X + 141),(LONG)(rightViewPort.Y + 15),(LONG)(rightViewPort.X + 251),(LONG)(rightViewPort.Y + 89) };
	if (_TOPbutton[1].uiNumber == UISTAGE::UION)
	{
		_TOPbutton[1].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/상단메뉴.png");
		SPRITEMANAGER->renderRectTexture(_TOPbutton[1].tex, &_TOPbutton[1].rc1, &_TOPbutton[1].rc2, 0, 80, 360, 160, rightViewPort.X + (DWORD)19, rightViewPort.Y + (DWORD)15);
	}

	//환경 상단
	//충돌렉트위치
	_TOPbutton[2].rc2 ={ (LONG)(rightViewPort.X + 263),(LONG)(rightViewPort.Y + 15),(LONG)(rightViewPort.X + 373),(LONG)(rightViewPort.Y + 89) };
	if (_TOPbutton[2].uiNumber == UISTAGE::UION)
	{
		_TOPbutton[2].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/상단메뉴.png");
		SPRITEMANAGER->renderRectTexture(_TOPbutton[2].tex, &_TOPbutton[2].rc1, &_TOPbutton[2].rc2, 0, 160, 360, 240, rightViewPort.X + (DWORD)19, rightViewPort.Y + (DWORD)15);
	}

}

void rightView::buttonTopUdate()
{
	//오브젝트 상단 충돌
	if (PtInRect(&_TOPbutton[0].rc2, GetMousePos()))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			for (int i = 0; i < 2; i++)
			{
				//false시켜버리기
				numberHeight = 0; //높이조절 초기화
				_objectClass->setnumberObject(0);
				numberNodeInstal = 0;
				numberNodelink = 0;
				numberMonster = 0;
				_heightContorol[i].uiNumber = UISTAGE::UIOFF;
				_nodeInstalContorol[i].uiNumber = UISTAGE::UIOFF;
				_nodeLinkContorol[i].uiNumber = UISTAGE::UIOFF;
				_NumberRawButton[i].uiNumber = UISTAGE::UIOFF;
			}
			////////////////////////////////////////////////////
			_TOPbutton[0].uiNumber = UISTAGE::UION;
			_TOPbutton[1].uiNumber = UISTAGE::UIOFF;
			_TOPbutton[2].uiNumber = UISTAGE::UIOFF;
		}
	}

	//지형 상단 충돌
	if (PtInRect(&_TOPbutton[1].rc2, GetMousePos()))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			for (int i = 0; i < 2; i++)
			{
				//false시켜버리기
				numberHeight = 0; //높이조절 초기화
				_objectClass->setnumberObject(0);
				numberNodeInstal = 0;
				numberNodelink = 0;
				numberMonster = 0;
				_heightContorol[i].uiNumber = UISTAGE::UIOFF;
				_nodeInstalContorol[i].uiNumber = UISTAGE::UIOFF;
				_nodeLinkContorol[i].uiNumber = UISTAGE::UIOFF;
				_NumberRawButton[i].uiNumber = UISTAGE::UIOFF;
			}
			/////////////////////////////////////////////////////
			_TOPbutton[1].uiNumber = UISTAGE::UION;
			_TOPbutton[0].uiNumber = UISTAGE::UIOFF;
			_TOPbutton[2].uiNumber = UISTAGE::UIOFF;
		}
	}

	//환경 상단 충돌
	if (PtInRect(&_TOPbutton[2].rc2, GetMousePos()))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			for (int i = 0; i < 2; i++)
			{
				//false시켜버리기
				numberHeight = 0; //높이조절 초기화
				_objectClass->setnumberObject(0);
				numberNodeInstal = 0;
				numberNodelink = 0;
				numberMonster = 0;
				_heightContorol[i].uiNumber = UISTAGE::UIOFF;
				_nodeInstalContorol[i].uiNumber = UISTAGE::UIOFF;
				_nodeLinkContorol[i].uiNumber = UISTAGE::UIOFF;
				_NumberRawButton[i].uiNumber = UISTAGE::UIOFF;
			}
			///////////////////////////////////////////////////////
			_TOPbutton[2].uiNumber = UISTAGE::UION;
			_TOPbutton[0].uiNumber = UISTAGE::UIOFF;
			_TOPbutton[1].uiNumber = UISTAGE::UIOFF;
		}
	}
}

void rightView::buttonObMiddle()
{
	if (_TOPbutton[0].uiNumber == UISTAGE::UION)
	{
		//종류 유아이
		_UIkind.tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/종류.png");
		SPRITEMANAGER->renderRectTexture(_UIkind.tex, &_UIkind.rc1, &_UIkind.rc2, 0, 0, 127, 32, rightViewPort.X + (DWORD)135, rightViewPort.Y + (DWORD)162);

		//충돌체크 부분
		//렉트 충돌 위치
		_OBJbutton.rc2 ={ (LONG)(rightViewPort.X + 73),(LONG)(rightViewPort.Y + 95),(LONG)(rightViewPort.X + 100),(LONG)(rightViewPort.Y + 138) };
		_OBJbutton.rc3 ={ (LONG)(rightViewPort.X + 289),(LONG)(rightViewPort.Y + 95),(LONG)(rightViewPort.X + 317),(LONG)(rightViewPort.Y + 138) };
		if (_OBJbutton.uiNumber == OBSTAGE::STORMTOWN1)
		{
			_OBJbutton.tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/오브젝트중단.png");
			SPRITEMANAGER->renderRectTexture(_OBJbutton.tex, &_OBJbutton.rc1, &_OBJbutton.rc2, 0, 0, 244, 43, rightViewPort.X + (DWORD)73, rightViewPort.Y + (DWORD)95);
			if (_OBJGO.uiNumber == UISTAGE::UIOFF)
			{
				_OBJback.tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/오브젝트중단.png");
				SPRITEMANAGER->renderRectTexture(_OBJback.tex, &_OBJback.rc1, &_OBJback.rc2, 0, 0, 244, 43, rightViewPort.X + (DWORD)73, rightViewPort.Y + (DWORD)95);
				//충돌체크 영역
				_OBJstorm1Button[0].rc2 ={ (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 200),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 234) };
				_OBJstorm1Button[1].rc2 ={ (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 240),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 274) };
				_OBJstorm1Button[2].rc2 ={ (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 280),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 314) };
				_OBJstorm1Button[3].rc2 ={ (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 320),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 354) };
				_OBJstorm1Button[4].rc2 ={ (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 360),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 394) };

				if (_OBJstorm1Button[0].uiNumber == OBSTAGEDOWN::ONEOFF)
				{
					_OBJstorm1Button[0].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/스톰타운1메뉴.png");
					SPRITEMANAGER->renderRectTexture(_OBJstorm1Button[0].tex, &_OBJstorm1Button[0].rc1, &_OBJstorm1Button[0].rc2, 0, 0, 258, 34, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)200);
				}
				else if (_OBJstorm1Button[0].uiNumber == OBSTAGEDOWN::TWOOFF)
				{
					_OBJstorm1Button[0].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/스톰타운1메뉴.png");
					SPRITEMANAGER->renderRectTexture(_OBJstorm1Button[0].tex, &_OBJstorm1Button[0].rc1, &_OBJstorm1Button[0].rc2, 0, 34, 258, 68, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)200);
				}

				if (_OBJstorm1Button[1].uiNumber == OBSTAGEDOWN::ONEOFF)
				{
					_OBJstorm1Button[1].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/스톰타운1메뉴.png");
					SPRITEMANAGER->renderRectTexture(_OBJstorm1Button[1].tex, &_OBJstorm1Button[1].rc1, &_OBJstorm1Button[1].rc2, 0, 68, 258, 102, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)240);
				}
				else if (_OBJstorm1Button[1].uiNumber == OBSTAGEDOWN::TWOOFF)
				{
					_OBJstorm1Button[1].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/스톰타운1메뉴.png");
					SPRITEMANAGER->renderRectTexture(_OBJstorm1Button[1].tex, &_OBJstorm1Button[1].rc1, &_OBJstorm1Button[1].rc2, 0, 102, 258, 136, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)240);
				}

				if (_OBJstorm1Button[2].uiNumber == OBSTAGEDOWN::ONEOFF)
				{
					_OBJstorm1Button[2].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/스톰타운1메뉴.png");
					SPRITEMANAGER->renderRectTexture(_OBJstorm1Button[2].tex, &_OBJstorm1Button[2].rc1, &_OBJstorm1Button[2].rc2, 0, 136, 258, 170, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)280);
				}
				else if (_OBJstorm1Button[2].uiNumber == OBSTAGEDOWN::TWOOFF)
				{
					_OBJstorm1Button[2].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/스톰타운1메뉴.png");
					SPRITEMANAGER->renderRectTexture(_OBJstorm1Button[2].tex, &_OBJstorm1Button[2].rc1, &_OBJstorm1Button[2].rc2, 0, 170, 258, 204, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)280);
				}

				if (_OBJstorm1Button[3].uiNumber == OBSTAGEDOWN::ONEOFF)
				{
					_OBJstorm1Button[3].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/스톰타운1메뉴.png");
					SPRITEMANAGER->renderRectTexture(_OBJstorm1Button[3].tex, &_OBJstorm1Button[3].rc1, &_OBJstorm1Button[3].rc2, 0, 204, 258, 238, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)320);
				}
				else if (_OBJstorm1Button[3].uiNumber == OBSTAGEDOWN::TWOOFF)
				{
					_OBJstorm1Button[3].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/스톰타운1메뉴.png");
					SPRITEMANAGER->renderRectTexture(_OBJstorm1Button[3].tex, &_OBJstorm1Button[3].rc1, &_OBJstorm1Button[3].rc2, 0, 238, 258, 272, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)320);
				}

				if (_OBJstorm1Button[4].uiNumber == OBSTAGEDOWN::ONEOFF)
				{
					_OBJstorm1Button[4].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/스톰타운1메뉴.png");
					SPRITEMANAGER->renderRectTexture(_OBJstorm1Button[4].tex, &_OBJstorm1Button[4].rc1, &_OBJstorm1Button[4].rc2, 0, 272, 258, 306, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)360);
				}
				else if (_OBJstorm1Button[4].uiNumber == OBSTAGEDOWN::TWOOFF)
				{
					_OBJstorm1Button[4].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/스톰타운1메뉴.png");
					SPRITEMANAGER->renderRectTexture(_OBJstorm1Button[4].tex, &_OBJstorm1Button[4].rc1, &_OBJstorm1Button[4].rc2, 0, 306, 258, 340, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)360);
				}
			}

			if (_OBJGO.uiNumber == UISTAGE::UION)
			{
				//돌아가기 버튼
				_OBJback.rc2 ={ (LONG)(rightViewPort.X + 50),(LONG)(rightViewPort.Y + 450),(LONG)(rightViewPort.X + 98),(LONG)(rightViewPort.Y + 483) };
				_OBJback.tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/조절.png");
				SPRITEMANAGER->renderRectTexture(_OBJback.tex, &_OBJback.rc1, &_OBJback.rc2, 0, 68, 160, 102, rightViewPort.X + (DWORD)50, rightViewPort.Y + (DWORD)450);

				if (_OBJstorm1Button[0].uiNumber == OBSTAGEDOWN::THREEOFF)
				{
					_objectClass->storm1();
				}

				if (_OBJstorm1Button[1].uiNumber == OBSTAGEDOWN::THREEOFF)
				{
					_objectClass->storm2();
				}

				if (_OBJstorm1Button[2].uiNumber == OBSTAGEDOWN::THREEOFF)
				{
					_objectClass->storm3();
				}

				if (_OBJstorm1Button[3].uiNumber == OBSTAGEDOWN::THREEOFF)
				{
					_objectClass->storm4();
				}

				if (_OBJstorm1Button[4].uiNumber == OBSTAGEDOWN::THREEOFF)
				{
					_objectClass->storm5();
				}
			}
		}

		if (_OBJbutton.uiNumber == OBSTAGE::STROMTOWN2)
		{
			_OBJbutton.tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/오브젝트중단.png");
			SPRITEMANAGER->renderRectTexture(_OBJbutton.tex, &_OBJbutton.rc1, &_OBJbutton.rc2, 0, 43, 244, 86, rightViewPort.X + (DWORD)73, rightViewPort.Y + (DWORD)95);
			if (_OBJGO.uiNumber == UISTAGE::UIOFF)
			{

				//충돌체크 영역
				_OBJstorm2Button[0].rc2 ={ (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 200),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 234) };
				_OBJstorm2Button[1].rc2 ={ (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 240),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 274) };
				_OBJstorm2Button[2].rc2 ={ (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 280),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 314) };
				_OBJstorm2Button[3].rc2 ={ (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 320),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 354) };
				_OBJstorm2Button[4].rc2 ={ (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 360),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 394) };

				if (_OBJstorm2Button[0].uiNumber == OBSTAGEDOWN::ONEOFF)
				{
					_OBJstorm2Button[0].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/스톰타운2메뉴.png");
					SPRITEMANAGER->renderRectTexture(_OBJstorm2Button[0].tex, &_OBJstorm2Button[0].rc1, &_OBJstorm2Button[0].rc2, 0, 0, 258, 34, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)200);
				}
				else if (_OBJstorm2Button[0].uiNumber == OBSTAGEDOWN::TWOOFF)
				{
					_OBJstorm2Button[0].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/스톰타운2메뉴.png");
					SPRITEMANAGER->renderRectTexture(_OBJstorm2Button[0].tex, &_OBJstorm2Button[0].rc1, &_OBJstorm2Button[0].rc2, 0, 34, 258, 68, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)200);
				}

				if (_OBJstorm2Button[1].uiNumber == OBSTAGEDOWN::ONEOFF)
				{
					_OBJstorm2Button[1].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/스톰타운2메뉴.png");
					SPRITEMANAGER->renderRectTexture(_OBJstorm2Button[1].tex, &_OBJstorm2Button[1].rc1, &_OBJstorm2Button[1].rc2, 0, 68, 258, 102, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)240);
				}
				else if (_OBJstorm2Button[1].uiNumber == OBSTAGEDOWN::TWOOFF)
				{
					_OBJstorm2Button[1].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/스톰타운2메뉴.png");
					SPRITEMANAGER->renderRectTexture(_OBJstorm2Button[1].tex, &_OBJstorm2Button[1].rc1, &_OBJstorm2Button[1].rc2, 0, 102, 258, 136, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)240);
				}

				if (_OBJstorm2Button[2].uiNumber == OBSTAGEDOWN::ONEOFF)
				{
					_OBJstorm2Button[2].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/스톰타운2메뉴.png");
					SPRITEMANAGER->renderRectTexture(_OBJstorm2Button[2].tex, &_OBJstorm2Button[2].rc1, &_OBJstorm2Button[2].rc2, 0, 136, 258, 170, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)280);
				}
				else if (_OBJstorm2Button[2].uiNumber == OBSTAGEDOWN::TWOOFF)
				{
					_OBJstorm2Button[2].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/스톰타운2메뉴.png");
					SPRITEMANAGER->renderRectTexture(_OBJstorm2Button[2].tex, &_OBJstorm2Button[2].rc1, &_OBJstorm2Button[2].rc2, 0, 170, 258, 204, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)280);
				}


				if (_OBJstorm2Button[3].uiNumber == OBSTAGEDOWN::ONEOFF)
				{
					_OBJstorm2Button[3].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/스톰타운2메뉴.png");
					SPRITEMANAGER->renderRectTexture(_OBJstorm2Button[3].tex, &_OBJstorm2Button[3].rc1, &_OBJstorm2Button[3].rc2, 0, 204, 258, 238, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)320);
				}
				else if (_OBJstorm2Button[3].uiNumber == OBSTAGEDOWN::TWOOFF)
				{
					_OBJstorm2Button[3].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/스톰타운2메뉴.png");
					SPRITEMANAGER->renderRectTexture(_OBJstorm2Button[3].tex, &_OBJstorm2Button[3].rc1, &_OBJstorm2Button[3].rc2, 0, 238, 258, 272, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)320);
				}

				if (_OBJstorm2Button[4].uiNumber == OBSTAGEDOWN::ONEOFF)
				{
					_OBJstorm2Button[4].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/스톰타운2메뉴.png");
					SPRITEMANAGER->renderRectTexture(_OBJstorm2Button[4].tex, &_OBJstorm2Button[4].rc1, &_OBJstorm2Button[4].rc2, 0, 272, 258, 306, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)360);
				}
				else if (_OBJstorm2Button[4].uiNumber == OBSTAGEDOWN::TWOOFF)
				{
					_OBJstorm2Button[4].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/스톰타운2메뉴.png");
					SPRITEMANAGER->renderRectTexture(_OBJstorm2Button[4].tex, &_OBJstorm2Button[4].rc1, &_OBJstorm2Button[4].rc2, 0, 306, 258, 340, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)360);
				}
			}

			if (_OBJGO.uiNumber == UISTAGE::UION)
			{
				//돌아가기 버튼
				_OBJback.rc2 ={ (LONG)(rightViewPort.X + 50),(LONG)(rightViewPort.Y + 450),(LONG)(rightViewPort.X + 98),(LONG)(rightViewPort.Y + 483) };
				_OBJback.tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/조절.png");
				SPRITEMANAGER->renderRectTexture(_OBJback.tex, &_OBJback.rc1, &_OBJback.rc2, 0, 68, 160, 102, rightViewPort.X + (DWORD)50, rightViewPort.Y + (DWORD)450);
				if (_OBJstorm2Button[0].uiNumber == OBSTAGEDOWN::THREEOFF)
				{
					_objectClass->storm6();
				}

				if (_OBJstorm2Button[1].uiNumber == OBSTAGEDOWN::THREEOFF)
				{
					_objectClass->storm7();
				}

				if (_OBJstorm2Button[2].uiNumber == OBSTAGEDOWN::THREEOFF)
				{
					_objectClass->storm8();
				}

				if (_OBJstorm2Button[3].uiNumber == OBSTAGEDOWN::THREEOFF)
				{
					_objectClass->storm9();
				}

				if (_OBJstorm2Button[4].uiNumber == OBSTAGEDOWN::THREEOFF)
				{
					_objectClass->storm10();
				}
			}
		}

		if (_OBJbutton.uiNumber == OBSTAGE::RUINSTAGE)
		{
			_OBJbutton.tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/오브젝트중단.png");
			SPRITEMANAGER->renderRectTexture(_OBJbutton.tex, &_OBJbutton.rc1, &_OBJbutton.rc2, 0, 86, 244, 129, rightViewPort.X + (DWORD)73, rightViewPort.Y + (DWORD)95);

			if (_OBJGO.uiNumber == UISTAGE::UIOFF)
			{

				//충돌체크 영역
				_OBJruinButton[0].rc2 ={ (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 200),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 234) };
				_OBJruinButton[1].rc2 ={ (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 240),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 274) };
				_OBJruinButton[2].rc2 ={ (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 280),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 314) };
				_OBJruinButton[3].rc2 ={ (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 320),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 354) };
				_OBJruinButton[4].rc2 ={ (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 360),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 394) };
				_OBJruinButton[5].rc2 ={ (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 400),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 434) };
				_OBJruinButton[6].rc2 ={ (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 440),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 474) };

				if (_OBJruinButton[0].uiNumber == OBSTAGEDOWN::ONEOFF)
				{
					_OBJruinButton[0].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/폐허메뉴.png");
					SPRITEMANAGER->renderRectTexture(_OBJruinButton[0].tex, &_OBJruinButton[0].rc1, &_OBJruinButton[0].rc2, 0, 0, 258, 34, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)200);
				}
				else if (_OBJruinButton[0].uiNumber == OBSTAGEDOWN::TWOOFF)
				{
					_OBJruinButton[0].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/폐허메뉴.png");
					SPRITEMANAGER->renderRectTexture(_OBJruinButton[0].tex, &_OBJruinButton[0].rc1, &_OBJruinButton[0].rc2, 0, 34, 258, 68, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)200);
				}

				if (_OBJruinButton[1].uiNumber == OBSTAGEDOWN::ONEOFF)
				{
					_OBJruinButton[1].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/폐허메뉴.png");
					SPRITEMANAGER->renderRectTexture(_OBJruinButton[1].tex, &_OBJruinButton[1].rc1, &_OBJruinButton[1].rc2, 0, 68, 258, 102, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)240);
				}
				else if (_OBJruinButton[1].uiNumber == OBSTAGEDOWN::TWOOFF)
				{
					_OBJruinButton[1].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/폐허메뉴.png");
					SPRITEMANAGER->renderRectTexture(_OBJruinButton[1].tex, &_OBJruinButton[1].rc1, &_OBJruinButton[1].rc2, 0, 102, 258, 136, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)240);
				}

				if (_OBJruinButton[2].uiNumber == OBSTAGEDOWN::ONEOFF)
				{
					_OBJruinButton[2].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/폐허메뉴.png");
					SPRITEMANAGER->renderRectTexture(_OBJruinButton[2].tex, &_OBJruinButton[2].rc1, &_OBJruinButton[2].rc2, 0, 136, 258, 170, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)280);
				}
				else if (_OBJruinButton[2].uiNumber == OBSTAGEDOWN::TWOOFF)
				{
					_OBJruinButton[2].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/폐허메뉴.png");
					SPRITEMANAGER->renderRectTexture(_OBJruinButton[2].tex, &_OBJruinButton[2].rc1, &_OBJruinButton[2].rc2, 0, 170, 258, 204, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)280);
				}

				if (_OBJruinButton[3].uiNumber == OBSTAGEDOWN::ONEOFF)
				{
					_OBJruinButton[3].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/폐허메뉴.png");
					SPRITEMANAGER->renderRectTexture(_OBJruinButton[3].tex, &_OBJruinButton[3].rc1, &_OBJruinButton[3].rc2, 0, 204, 258, 238, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)320);
				}
				else if (_OBJruinButton[3].uiNumber == OBSTAGEDOWN::TWOOFF)
				{
					_OBJruinButton[3].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/폐허메뉴.png");
					SPRITEMANAGER->renderRectTexture(_OBJruinButton[3].tex, &_OBJruinButton[3].rc1, &_OBJruinButton[3].rc2, 0, 238, 258, 272, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)320);
				}

				if (_OBJruinButton[4].uiNumber == OBSTAGEDOWN::ONEOFF)
				{
					_OBJruinButton[4].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/폐허메뉴.png");
					SPRITEMANAGER->renderRectTexture(_OBJruinButton[4].tex, &_OBJruinButton[4].rc1, &_OBJruinButton[4].rc2, 0, 272, 258, 306, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)360);
				}
				else if (_OBJruinButton[4].uiNumber == OBSTAGEDOWN::TWOOFF)
				{
					_OBJruinButton[4].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/폐허메뉴.png");
					SPRITEMANAGER->renderRectTexture(_OBJruinButton[4].tex, &_OBJruinButton[4].rc1, &_OBJruinButton[4].rc2, 0, 306, 258, 340, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)360);
				}


				if (_OBJruinButton[5].uiNumber == OBSTAGEDOWN::ONEOFF)
				{
					_OBJruinButton[5].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/폐허메뉴.png");
					SPRITEMANAGER->renderRectTexture(_OBJruinButton[5].tex, &_OBJruinButton[5].rc1, &_OBJruinButton[5].rc2, 0, 340, 258, 374, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)400);
				}
				else if (_OBJruinButton[5].uiNumber == OBSTAGEDOWN::TWOOFF)
				{
					_OBJruinButton[5].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/폐허메뉴.png");
					SPRITEMANAGER->renderRectTexture(_OBJruinButton[5].tex, &_OBJruinButton[5].rc1, &_OBJruinButton[5].rc2, 0, 374, 258, 408, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)400);
				}

				if (_OBJruinButton[6].uiNumber == OBSTAGEDOWN::ONEOFF)
				{
					_OBJruinButton[6].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/폐허메뉴.png");
					SPRITEMANAGER->renderRectTexture(_OBJruinButton[6].tex, &_OBJruinButton[6].rc1, &_OBJruinButton[6].rc2, 0, 408, 258, 442, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)440);
				}
				else if (_OBJruinButton[6].uiNumber == OBSTAGEDOWN::TWOOFF)
				{
					_OBJruinButton[6].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/폐허메뉴.png");
					SPRITEMANAGER->renderRectTexture(_OBJruinButton[6].tex, &_OBJruinButton[6].rc1, &_OBJruinButton[6].rc2, 0, 442, 258, 476, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)440);
				}
			}

			if (_OBJGO.uiNumber == UISTAGE::UION)
			{
				//돌아가기 버튼
				_OBJback.rc2 ={ (LONG)(rightViewPort.X + 50),(LONG)(rightViewPort.Y + 450),(LONG)(rightViewPort.X + 98),(LONG)(rightViewPort.Y + 483) };
				_OBJback.tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/조절.png");
				SPRITEMANAGER->renderRectTexture(_OBJback.tex, &_OBJback.rc1, &_OBJback.rc2, 0, 68, 160, 102, rightViewPort.X + (DWORD)50, rightViewPort.Y + (DWORD)450);
				if (_OBJruinButton[0].uiNumber == OBSTAGEDOWN::THREEOFF)
				{
					_objectClass->ruinstage1();
				}

				if (_OBJruinButton[1].uiNumber == OBSTAGEDOWN::THREEOFF)
				{
					_objectClass->ruinstage2();
				}

				if (_OBJruinButton[2].uiNumber == OBSTAGEDOWN::THREEOFF)
				{
					_objectClass->ruinstage3();
				}

				if (_OBJruinButton[3].uiNumber == OBSTAGEDOWN::THREEOFF)
				{
					_objectClass->ruinstage4();
				}

				if (_OBJruinButton[4].uiNumber == OBSTAGEDOWN::THREEOFF)
				{
					_objectClass->ruinstage5();
				}

				if (_OBJruinButton[5].uiNumber == OBSTAGEDOWN::THREEOFF)
				{
					_objectClass->ruinstage6();
				}

				if (_OBJruinButton[6].uiNumber == OBSTAGEDOWN::THREEOFF)
				{
					_objectClass->ruinstage7();
				}
			}
		}

		if (_OBJbutton.uiNumber == OBSTAGE::PIRAMID)
		{
			_OBJbutton.tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/오브젝트중단.png");
			SPRITEMANAGER->renderRectTexture(_OBJbutton.tex, &_OBJbutton.rc1, &_OBJbutton.rc2, 0, 129, 244, 172, rightViewPort.X + (DWORD)73, rightViewPort.Y + (DWORD)95);

			if (_OBJGO.uiNumber == UISTAGE::UIOFF)
			{

				_OBJpiramidButton[0].rc2 ={ (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 200),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 234) };
				_OBJpiramidButton[1].rc2 ={ (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 240),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 274) };
				_OBJpiramidButton[2].rc2 ={ (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 280),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 314) };
				_OBJpiramidButton[3].rc2 ={ (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 320),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 354) };

				if (_OBJpiramidButton[0].uiNumber == OBSTAGEDOWN::ONEOFF)
				{
					_OBJpiramidButton[0].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/피라미드메뉴.png");
					SPRITEMANAGER->renderRectTexture(_OBJpiramidButton[0].tex, &_OBJpiramidButton[0].rc1, &_OBJpiramidButton[0].rc2, 0, 0, 258, 34, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)200);
				}
				else if (_OBJpiramidButton[0].uiNumber == OBSTAGEDOWN::TWOOFF)
				{
					_OBJpiramidButton[0].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/피라미드메뉴.png");
					SPRITEMANAGER->renderRectTexture(_OBJpiramidButton[0].tex, &_OBJpiramidButton[0].rc1, &_OBJpiramidButton[0].rc2, 0, 34, 258, 68, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)200);
				}

				if (_OBJpiramidButton[1].uiNumber == OBSTAGEDOWN::ONEOFF)
				{
					_OBJpiramidButton[1].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/피라미드메뉴.png");
					SPRITEMANAGER->renderRectTexture(_OBJpiramidButton[1].tex, &_OBJpiramidButton[1].rc1, &_OBJpiramidButton[1].rc2, 0, 68, 258, 102, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)240);
				}
				else if (_OBJpiramidButton[1].uiNumber == OBSTAGEDOWN::TWOOFF)
				{
					_OBJpiramidButton[1].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/피라미드메뉴.png");
					SPRITEMANAGER->renderRectTexture(_OBJpiramidButton[1].tex, &_OBJpiramidButton[1].rc1, &_OBJpiramidButton[1].rc2, 0, 102, 258, 136, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)240);
				}

				if (_OBJpiramidButton[2].uiNumber == OBSTAGEDOWN::ONEOFF)
				{
					_OBJpiramidButton[2].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/피라미드메뉴.png");
					SPRITEMANAGER->renderRectTexture(_OBJpiramidButton[2].tex, &_OBJpiramidButton[2].rc1, &_OBJpiramidButton[2].rc2, 0, 136, 258, 170, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)280);
				}
				else if (_OBJpiramidButton[2].uiNumber == OBSTAGEDOWN::TWOOFF)
				{
					_OBJpiramidButton[2].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/피라미드메뉴.png");
					SPRITEMANAGER->renderRectTexture(_OBJpiramidButton[2].tex, &_OBJpiramidButton[2].rc1, &_OBJpiramidButton[2].rc2, 0, 170, 258, 204, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)280);
				}

				if (_OBJpiramidButton[3].uiNumber == OBSTAGEDOWN::ONEOFF)
				{
					_OBJpiramidButton[3].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/피라미드메뉴.png");
					SPRITEMANAGER->renderRectTexture(_OBJpiramidButton[3].tex, &_OBJpiramidButton[3].rc1, &_OBJpiramidButton[3].rc2, 0, 204, 258, 238, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)320);
				}
				else if (_OBJpiramidButton[3].uiNumber == OBSTAGEDOWN::TWOOFF)
				{
					_OBJpiramidButton[3].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/피라미드메뉴.png");
					SPRITEMANAGER->renderRectTexture(_OBJpiramidButton[3].tex, &_OBJpiramidButton[3].rc1, &_OBJpiramidButton[3].rc2, 0, 238, 258, 272, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)320);
				}
			}

			if (_OBJGO.uiNumber == UISTAGE::UION)
			{
				//돌아가기 버튼
				_OBJback.rc2 ={ (LONG)(rightViewPort.X + 50),(LONG)(rightViewPort.Y + 450),(LONG)(rightViewPort.X + 98),(LONG)(rightViewPort.Y + 483) };
				_OBJback.tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/조절.png");
				SPRITEMANAGER->renderRectTexture(_OBJback.tex, &_OBJback.rc1, &_OBJback.rc2, 0, 68, 160, 102, rightViewPort.X + (DWORD)50, rightViewPort.Y + (DWORD)450);
				if (_OBJpiramidButton[0].uiNumber == OBSTAGEDOWN::THREEOFF)
				{
					_objectClass->piramid1();
				}

				if (_OBJpiramidButton[1].uiNumber == OBSTAGEDOWN::THREEOFF)
				{
					_objectClass->piramid2();
				}

				if (_OBJpiramidButton[2].uiNumber == OBSTAGEDOWN::THREEOFF)
				{
					_objectClass->piramid3();
				}

				if (_OBJpiramidButton[3].uiNumber == OBSTAGEDOWN::THREEOFF)
				{
					_objectClass->piramid4();
				}
			}
		}
	}
}

void rightView::buttonObUpdate()
{
	//오브 상단이 트루일때
	if (_TOPbutton[0].uiNumber == UISTAGE::UION)
	{
		if (_OBJGO.uiNumber == UISTAGE::UIOFF)
		{
			//왼쪽키
			if (PtInRect(&_OBJbutton.rc2, GetMousePos()))
			{
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					if (_OBJbutton.uiNumber <= 1)
					{
						_OBJbutton.uiNumber = OBSTAGE::STORMTOWN1;
					}
					else
					{
						_OBJbutton.uiNumber -= 1;
					}
				}
			}

			//오른쪽키
			if (PtInRect(&_OBJbutton.rc3, GetMousePos()))
			{
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					if (_OBJbutton.uiNumber >= 4)
					{
						_OBJbutton.uiNumber = OBSTAGE::PIRAMID;
					}
					else
					{
						_OBJbutton.uiNumber += 1;
					}
				}
			}
		}
	}

	//하단메뉴1충돌
	if (_TOPbutton[0].uiNumber == UISTAGE::UION)
	{
		if (_OBJbutton.uiNumber == OBSTAGE::STORMTOWN1)
		{
			if (_OBJGO.uiNumber == UISTAGE::UIOFF)
			{
				for (int i = 0; i < 5; i++)
				{
					if (PtInRect(&_OBJstorm1Button[i].rc2, GetMousePos()))
					{
						_OBJstorm1Button[i].uiNumber = OBSTAGEDOWN::TWOOFF;
						//누르면 번호 넘겨주는거 해야됨
						if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
						{
							_OBJGO.uiNumber = UISTAGE::UION;
							_OBJstorm1Button[i].uiNumber = OBSTAGEDOWN::THREEOFF;
						}
					}
					else
					{
						_OBJstorm1Button[i].uiNumber = OBSTAGEDOWN::ONEOFF;
					}
				}
			}
		}
	}

	//하단메뉴2충돌
	if (_TOPbutton[0].uiNumber == UISTAGE::UION)
	{
		if (_OBJbutton.uiNumber == OBSTAGE::STROMTOWN2)
		{
			if (_OBJGO.uiNumber == UISTAGE::UIOFF)
			{
				for (int i = 0; i < 5; i++)
				{
					if (PtInRect(&_OBJstorm2Button[i].rc2, GetMousePos()))
					{
						_OBJstorm2Button[i].uiNumber = OBSTAGEDOWN::TWOOFF;
						//누르면 번호 넘겨주는거 해야됨
						if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
						{
							_OBJGO.uiNumber = UISTAGE::UION;
							_OBJstorm2Button[i].uiNumber = OBSTAGEDOWN::THREEOFF;
						}
					}
					else
					{
						_OBJstorm2Button[i].uiNumber = OBSTAGEDOWN::ONEOFF;
					}
				}
			}
		}
	}

	//하단메뉴3충돌
	if (_TOPbutton[0].uiNumber == UISTAGE::UION)
	{
		if (_OBJbutton.uiNumber == OBSTAGE::RUINSTAGE)
		{
			if (_OBJGO.uiNumber == UISTAGE::UIOFF)
			{
				for (int i = 0; i < 7; i++)
				{
					if (PtInRect(&_OBJruinButton[i].rc2, GetMousePos()))
					{
						_OBJruinButton[i].uiNumber = OBSTAGEDOWN::TWOOFF;
						//누르면 번호 넘겨주는거 해야됨
						if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
						{
							_OBJGO.uiNumber = UISTAGE::UION;
							_OBJruinButton[i].uiNumber = OBSTAGEDOWN::THREEOFF;
						}
					}
					else
					{
						_OBJruinButton[i].uiNumber = OBSTAGEDOWN::ONEOFF;
					}
				}
			}
		}
	}

	//하단메뉴4충돌
	if (_TOPbutton[0].uiNumber == UISTAGE::UION)
	{
		if (_OBJbutton.uiNumber == OBSTAGE::PIRAMID)
		{
			if (_OBJGO.uiNumber == UISTAGE::UIOFF)
			{
				for (int i = 0; i < 7; i++)
				{
					if (PtInRect(&_OBJpiramidButton[i].rc2, GetMousePos()))
					{
						_OBJpiramidButton[i].uiNumber = OBSTAGEDOWN::TWOOFF;
						//누르면 번호 넘겨주는거 해야됨
						if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
						{
							_OBJGO.uiNumber = UISTAGE::UION;
							_OBJpiramidButton[i].uiNumber = OBSTAGEDOWN::THREEOFF;
						}
					}
					else
					{
						_OBJpiramidButton[i].uiNumber = OBSTAGEDOWN::ONEOFF;
					}
				}
			}
		}
	}

	if (_TOPbutton[0].uiNumber == UISTAGE::UION)
	{
		if (_OBJbutton.uiNumber == OBSTAGE::PIRAMID
			|| _OBJbutton.uiNumber == OBSTAGE::RUINSTAGE
			|| _OBJbutton.uiNumber == OBSTAGE::STORMTOWN1
			|| _OBJbutton.uiNumber == OBSTAGE::STROMTOWN2)
		{
			if (_OBJGO.uiNumber == UISTAGE::UION)
			{
				if (PtInRect(&_OBJback.rc2, GetMousePos()))
				{
					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						for (int i = 0; i < 5; i++)
						{
							_OBJstorm1Button[i].uiNumber = OBSTAGEDOWN::ONEOFF;
							_OBJstorm2Button[i].uiNumber = OBSTAGEDOWN::ONEOFF;
						}

						for (int i = 0; i < 7; i++)
						{
							_OBJruinButton[i].uiNumber = OBSTAGEDOWN::ONEOFF;
						}

						for (int i = 0; i < 4; i++)
						{
							_OBJpiramidButton[i].uiNumber = OBSTAGEDOWN::ONEOFF;
						}

						_OBJGO.uiNumber = UISTAGE::UIOFF;

					}
				}
			}
		}
	}
}

void rightView::buttonENVMiddle()
{
	//환경상단이 트루 일떄 
	if (_TOPbutton[2].uiNumber == UISTAGE::UION)
	{
		//종류 유아이
		_UIkind.tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/종류.png");
		SPRITEMANAGER->renderRectTexture(_UIkind.tex, &_UIkind.rc1, &_UIkind.rc2, 0, 0, 127, 32, rightViewPort.X + (DWORD)135, rightViewPort.Y + (DWORD)162);

		//렉트 충돌 위치
		_ENVbutton.rc2 ={ (LONG)(rightViewPort.X + 73),(LONG)(rightViewPort.Y + 95),(LONG)(rightViewPort.X + 100),(LONG)(rightViewPort.Y + 138) };
		_ENVbutton.rc3 ={ (LONG)(rightViewPort.X + 289),(LONG)(rightViewPort.Y + 95),(LONG)(rightViewPort.X + 317),(LONG)(rightViewPort.Y + 138) };

		if (_ENVbutton.uiNumber == ENVSTAGE::WATERMIDDLE)
		{
			_ENVbutton.tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/환경종류.png");
			SPRITEMANAGER->renderRectTexture(_ENVbutton.tex, &_ENVbutton.rc1, &_ENVbutton.rc2, 0, 0, 244, 43, rightViewPort.X + (DWORD)73, rightViewPort.Y + (DWORD)95);
		}

		if (_ENVbutton.uiNumber == ENVSTAGE::SKYMIDDLE)
		{
			_ENVbutton.tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/환경종류.png");
			SPRITEMANAGER->renderRectTexture(_ENVbutton.tex, &_ENVbutton.rc1, &_ENVbutton.rc2, 0, 43, 244, 86, rightViewPort.X + (DWORD)73, rightViewPort.Y + (DWORD)95);
		}

		if (_ENVbutton.uiNumber == ENVSTAGE::NODEINSTAL)
		{
			_ENVbutton.tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/환경종류.png");
			SPRITEMANAGER->renderRectTexture(_ENVbutton.tex, &_ENVbutton.rc1, &_ENVbutton.rc2, 0, 86, 244, 129, rightViewPort.X + (DWORD)73, rightViewPort.Y + (DWORD)95);
		}

		if (_ENVbutton.uiNumber == ENVSTAGE::NODELINK)
		{
			_ENVbutton.tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/환경종류.png");
			SPRITEMANAGER->renderRectTexture(_ENVbutton.tex, &_ENVbutton.rc1, &_ENVbutton.rc2, 0, 129, 244, 172, rightViewPort.X + (DWORD)73, rightViewPort.Y + (DWORD)95);
		}

		if (_ENVbutton.uiNumber == ENVSTAGE::MONSTER)
		{
			_ENVbutton.tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/환경종류.png");
			SPRITEMANAGER->renderRectTexture(_ENVbutton.tex, &_ENVbutton.rc1, &_ENVbutton.rc2, 0, 172, 244, 215, rightViewPort.X + (DWORD)73, rightViewPort.Y + (DWORD)95);
		}
	}

	//물중단 클릭 하단
	if (_TOPbutton[2].uiNumber == UISTAGE::UION)
	{
		if (_ENVbutton.uiNumber == ENVSTAGE::WATERMIDDLE)
		{
	
			//충돌체크
			_ENVwaterButton[0].rc2 = { (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 200),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 234) };
			_ENVwaterButton[1].rc2 = { (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 240),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 274) };
			_ENVwaterButton[2].rc2 = { (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 280),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 314) };
			_ENVwaterButton[3].rc2 = { (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 320),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 354) };
			_ENVwaterButton[4].rc2 = { (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 360),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 394) };
			_ENVwaterButton[5].rc2 = { (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 400),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 434) };

			for (int i = 0; i < 6; i++) _ENVwaterButton[i].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/하단버튼.png");;

			if (_ENVwaterButton[0].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_ENVwaterButton[0].tex, &_ENVwaterButton[0].rc1, &_ENVwaterButton[0].rc2, 0, 34, 258, 68, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)200);
			else SPRITEMANAGER->renderRectTexture(_ENVwaterButton[0].tex, &_ENVwaterButton[0].rc1, &_ENVwaterButton[0].rc2, 0, 0, 258, 34, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)200);

			if (_ENVwaterButton[1].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_ENVwaterButton[1].tex, &_ENVwaterButton[1].rc1, &_ENVwaterButton[1].rc2, 0, 102, 258, 136, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)240);
			else SPRITEMANAGER->renderRectTexture(_ENVwaterButton[1].tex, &_ENVwaterButton[1].rc1, &_ENVwaterButton[1].rc2, 0, 68, 258, 102, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)240);

			if (_ENVwaterButton[2].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_ENVwaterButton[2].tex, &_ENVwaterButton[2].rc1, &_ENVwaterButton[2].rc2, 0, 170, 258, 204, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)280);
			else SPRITEMANAGER->renderRectTexture(_ENVwaterButton[2].tex, &_ENVwaterButton[2].rc1, &_ENVwaterButton[2].rc2, 0, 136, 258, 170, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)280);

			if (_ENVwaterButton[3].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_ENVwaterButton[3].tex, &_ENVwaterButton[3].rc1, &_ENVwaterButton[3].rc2, 0, 238, 258, 272, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)320);

			else SPRITEMANAGER->renderRectTexture(_ENVwaterButton[3].tex, &_ENVwaterButton[3].rc1, &_ENVwaterButton[3].rc2, 0, 204, 258, 238, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)320);

			if (_ENVwaterButton[4].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_ENVwaterButton[4].tex, &_ENVwaterButton[4].rc1, &_ENVwaterButton[4].rc2, 0, 306, 258, 340, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)360);
			else SPRITEMANAGER->renderRectTexture(_ENVwaterButton[4].tex, &_ENVwaterButton[4].rc1, &_ENVwaterButton[4].rc2, 0, 272, 258, 306, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)360);

			if (_ENVwaterButton[5].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_ENVwaterButton[5].tex, &_ENVwaterButton[5].rc1, &_ENVwaterButton[5].rc2, 0, 374, 258, 408, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)400);
			else SPRITEMANAGER->renderRectTexture(_ENVwaterButton[5].tex, &_ENVwaterButton[5].rc1, &_ENVwaterButton[5].rc2, 0, 340, 258, 374, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)400);
		}

		if (_ENVbutton.uiNumber == ENVSTAGE::SKYMIDDLE)
		{
			//충돌체크
			_ENVskyButton[0].rc2 = { (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 200),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 234) };
			_ENVskyButton[1].rc2 = { (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 240),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 274) };
			_ENVskyButton[2].rc2 = { (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 280),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 314) };
			_ENVskyButton[3].rc2 = { (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 320),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 354) };
			_ENVskyButton[4].rc2 = { (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 360),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 394) };
			_ENVskyButton[5].rc2 = { (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 400),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 434) };

			for (int i = 0; i < 6; i++) _ENVskyButton[i].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/하단버튼.png");;

			if (_ENVskyButton[0].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_ENVskyButton[0].tex, &_ENVskyButton[0].rc1, &_ENVskyButton[0].rc2, 0, 34, 258, 68, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)200);
			else SPRITEMANAGER->renderRectTexture(_ENVskyButton[0].tex, &_ENVskyButton[0].rc1, &_ENVskyButton[0].rc2, 0, 0, 258, 34, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)200);

			if (_ENVskyButton[1].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_ENVskyButton[1].tex, &_ENVskyButton[1].rc1, &_ENVskyButton[1].rc2, 0, 102, 258, 136, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)240);
			else SPRITEMANAGER->renderRectTexture(_ENVskyButton[1].tex, &_ENVskyButton[1].rc1, &_ENVskyButton[1].rc2, 0, 68, 258, 102, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)240);

			if (_ENVskyButton[2].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_ENVskyButton[2].tex, &_ENVskyButton[2].rc1, &_ENVskyButton[2].rc2, 0, 170, 258, 204, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)280);
			else SPRITEMANAGER->renderRectTexture(_ENVskyButton[2].tex, &_ENVskyButton[2].rc1, &_ENVskyButton[2].rc2, 0, 136, 258, 170, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)280);

			if (_ENVskyButton[3].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_ENVskyButton[3].tex, &_ENVskyButton[3].rc1, &_ENVskyButton[3].rc2, 0, 238, 258, 272, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)320);

			else SPRITEMANAGER->renderRectTexture(_ENVskyButton[3].tex, &_ENVskyButton[3].rc1, &_ENVskyButton[3].rc2, 0, 204, 258, 238, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)320);

			if (_ENVskyButton[4].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_ENVskyButton[4].tex, &_ENVskyButton[4].rc1, &_ENVskyButton[4].rc2, 0, 306, 258, 340, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)360);
			else SPRITEMANAGER->renderRectTexture(_ENVskyButton[4].tex, &_ENVskyButton[4].rc1, &_ENVskyButton[4].rc2, 0, 272, 258, 306, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)360);

			if (_ENVskyButton[5].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_ENVskyButton[5].tex, &_ENVskyButton[5].rc1, &_ENVskyButton[5].rc2, 0, 374, 258, 408, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)400);
			else SPRITEMANAGER->renderRectTexture(_ENVskyButton[5].tex, &_ENVskyButton[5].rc1, &_ENVskyButton[5].rc2, 0, 340, 258, 374, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)400);
		}

		if (_ENVbutton.uiNumber == ENVSTAGE::NODEINSTAL)
		{
			_UInodeHeight[0].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/노드.png");
			SPRITEMANAGER->renderRectTexture(_UInodeHeight[0].tex, &_UInodeHeight[0].rc1, &_UInodeHeight[0].rc2, 0, 0, 90, 34, rightViewPort.X + (DWORD)100, rightViewPort.Y + (DWORD)250);

			_UInodeHeight[0].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/노드.png");
			SPRITEMANAGER->renderRectTexture(_UInodeHeight[0].tex, &_UInodeHeight[0].rc1, &_UInodeHeight[0].rc2, 0, 34, 90, 68, rightViewPort.X + (DWORD)100, rightViewPort.Y + (DWORD)350);
			
			//충돌체크
			_nodeInstalContorol[0].rc2 = { (LONG)(rightViewPort.X + 220),(LONG)(rightViewPort.Y + 250),(LONG)(rightViewPort.X + 268),(LONG)(rightViewPort.Y + 283) };
			if (_nodeInstalContorol[0].uiNumber == UISTAGE::UIOFF)
			{
				_nodeInstalContorol[0].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/높이값.png");
				SPRITEMANAGER->renderRectTexture(_nodeInstalContorol[0].tex, &_nodeInstalContorol[0].rc1, &_nodeInstalContorol[0].rc2, 0, 0, 48, 33, rightViewPort.X + (DWORD)220, rightViewPort.Y + (DWORD)250);
			}
			else
			{
				_nodeInstalContorol[0].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/높이값.png");
				SPRITEMANAGER->renderRectTexture(_nodeInstalContorol[0].tex, &_nodeInstalContorol[0].rc1, &_nodeInstalContorol[0].rc2, 0, 33, 48, 66, rightViewPort.X + (DWORD)220, rightViewPort.Y + (DWORD)250);
			}

			//충돌체크
			_nodeInstalContorol[1].rc2 = { (LONG)(rightViewPort.X + 220),(LONG)(rightViewPort.Y + 350),(LONG)(rightViewPort.X + 268),(LONG)(rightViewPort.Y + 383) };
			if (_nodeInstalContorol[1].uiNumber == UISTAGE::UIOFF)
			{
				_nodeInstalContorol[1].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/높이값.png");
				SPRITEMANAGER->renderRectTexture(_nodeInstalContorol[1].tex, &_nodeInstalContorol[1].rc1, &_nodeInstalContorol[1].rc2, 0, 0, 48, 33, rightViewPort.X + (DWORD)220, rightViewPort.Y + (DWORD)350);
			}
			else
			{
				_nodeInstalContorol[1].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/높이값.png");
				SPRITEMANAGER->renderRectTexture(_nodeInstalContorol[1].tex, &_nodeInstalContorol[1].rc1, &_nodeInstalContorol[1].rc2, 0, 33, 48, 66, rightViewPort.X + (DWORD)220, rightViewPort.Y + (DWORD)350);
			}
		}

		if (_ENVbutton.uiNumber == ENVSTAGE::NODELINK)
		{
			_UInodeHeight[0].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/노드.png");
			SPRITEMANAGER->renderRectTexture(_UInodeHeight[0].tex, &_UInodeHeight[0].rc1, &_UInodeHeight[0].rc2, 0, 0, 90, 34, rightViewPort.X + (DWORD)100, rightViewPort.Y + (DWORD)250);

			_UInodeHeight[1].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/노드.png");
			SPRITEMANAGER->renderRectTexture(_UInodeHeight[1].tex, &_UInodeHeight[1].rc1, &_UInodeHeight[1].rc2, 0, 34, 90, 68, rightViewPort.X + (DWORD)100, rightViewPort.Y + (DWORD)350);
			
			//충돌체크
			_nodeLinkContorol[0].rc2 = { (LONG)(rightViewPort.X + 220),(LONG)(rightViewPort.Y + 250),(LONG)(rightViewPort.X + 268),(LONG)(rightViewPort.Y + 283) };
			if (_nodeLinkContorol[0].uiNumber == UISTAGE::UIOFF)
			{
				_nodeLinkContorol[0].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/높이값.png");
				SPRITEMANAGER->renderRectTexture(_nodeLinkContorol[0].tex, &_nodeLinkContorol[0].rc1, &_nodeLinkContorol[0].rc2, 0, 0, 48, 33, rightViewPort.X + (DWORD)220, rightViewPort.Y + (DWORD)250);
			}
			else
			{
				_nodeLinkContorol[0].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/높이값.png");
				SPRITEMANAGER->renderRectTexture(_nodeLinkContorol[0].tex, &_nodeLinkContorol[0].rc1, &_nodeLinkContorol[0].rc2, 0, 33, 48, 66, rightViewPort.X + (DWORD)220, rightViewPort.Y + (DWORD)250);
			}

			//충돌체크
			_nodeLinkContorol[1].rc2 = { (LONG)(rightViewPort.X + 220),(LONG)(rightViewPort.Y + 350),(LONG)(rightViewPort.X + 268),(LONG)(rightViewPort.Y + 383) };
			if (_nodeLinkContorol[1].uiNumber == UISTAGE::UIOFF)
			{
				_nodeLinkContorol[1].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/높이값.png");
				SPRITEMANAGER->renderRectTexture(_nodeLinkContorol[1].tex, &_nodeLinkContorol[1].rc1, &_nodeLinkContorol[1].rc2, 0, 0, 48, 33, rightViewPort.X + (DWORD)220, rightViewPort.Y + (DWORD)350);
			}
			else
			{
				_nodeLinkContorol[1].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/높이값.png");
				SPRITEMANAGER->renderRectTexture(_nodeLinkContorol[1].tex, &_nodeLinkContorol[1].rc1, &_nodeLinkContorol[1].rc2, 0, 33, 48, 66, rightViewPort.X + (DWORD)220, rightViewPort.Y + (DWORD)350);
			}

			
		}

		if (_ENVbutton.uiNumber == ENVSTAGE::MONSTER)
		{
			//충돌체크
			_ENVmonsterButton[0].rc2 = { (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 200),(LONG)(rightViewPort.X + 199),(LONG)(rightViewPort.Y + 234) };
			_ENVmonsterButton[1].rc2 = { (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 240),(LONG)(rightViewPort.X + 199),(LONG)(rightViewPort.Y + 274) };
			_ENVmonsterButton[2].rc2 = { (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 280),(LONG)(rightViewPort.X + 199),(LONG)(rightViewPort.Y + 314) };
			_ENVmonsterButton[3].rc2 = { (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 320),(LONG)(rightViewPort.X + 199),(LONG)(rightViewPort.Y + 354) };
			_ENVmonsterButton[4].rc2 = { (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 360),(LONG)(rightViewPort.X + 199),(LONG)(rightViewPort.Y + 394) };
			_ENVmonsterButton[5].rc2 = { (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 400),(LONG)(rightViewPort.X + 199),(LONG)(rightViewPort.Y + 434) };
			_ENVmonsterButton[6].rc2 = { (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 440),(LONG)(rightViewPort.X + 199),(LONG)(rightViewPort.Y + 474) };

			for(int i=0; i<DEFMONSTER; i++) _ENVmonsterButton[i].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/몬스터버튼.png");;

			//왼쪽 버튼
			if (_ENVmonsterButton[0].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_ENVmonsterButton[0].tex, &_ENVmonsterButton[0].rc1, &_ENVmonsterButton[0].rc2, 0, 34, 258, 68, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)200);
			else SPRITEMANAGER->renderRectTexture(_ENVmonsterButton[0].tex, &_ENVmonsterButton[0].rc1, &_ENVmonsterButton[0].rc2, 0, 0, 129, 34, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)200);

			if (_ENVmonsterButton[1].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_ENVmonsterButton[1].tex, &_ENVmonsterButton[1].rc1, &_ENVmonsterButton[1].rc2, 0, 102, 258, 136, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)240);
			else SPRITEMANAGER->renderRectTexture(_ENVmonsterButton[1].tex, &_ENVmonsterButton[1].rc1, &_ENVmonsterButton[1].rc2, 0, 68, 129, 102, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)240);

			if (_ENVmonsterButton[2].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_ENVmonsterButton[2].tex, &_ENVmonsterButton[2].rc1, &_ENVmonsterButton[2].rc2, 0, 170, 258, 204, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)280);
			else SPRITEMANAGER->renderRectTexture(_ENVmonsterButton[2].tex, &_ENVmonsterButton[2].rc1, &_ENVmonsterButton[2].rc2, 0, 136, 129, 170, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)280);

			if (_ENVmonsterButton[3].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_ENVmonsterButton[3].tex, &_ENVmonsterButton[3].rc1, &_ENVmonsterButton[3].rc2, 0, 238, 258, 272, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)320);

			else SPRITEMANAGER->renderRectTexture(_ENVmonsterButton[3].tex, &_ENVmonsterButton[3].rc1, &_ENVmonsterButton[3].rc2, 0, 204, 129, 238, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)320);

			if (_ENVmonsterButton[4].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_ENVmonsterButton[4].tex, &_ENVmonsterButton[4].rc1, &_ENVmonsterButton[4].rc2, 0, 306, 258, 340, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)360);
			else SPRITEMANAGER->renderRectTexture(_ENVmonsterButton[4].tex, &_ENVmonsterButton[4].rc1, &_ENVmonsterButton[4].rc2, 0, 272, 129, 306, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)360);

			if (_ENVmonsterButton[5].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_ENVmonsterButton[5].tex, &_ENVmonsterButton[5].rc1, &_ENVmonsterButton[5].rc2, 0, 374, 258, 408, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)400);
			else SPRITEMANAGER->renderRectTexture(_ENVmonsterButton[5].tex, &_ENVmonsterButton[5].rc1, &_ENVmonsterButton[5].rc2, 0, 340, 129, 374, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)400);

			if (_ENVmonsterButton[6].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_ENVmonsterButton[6].tex, &_ENVmonsterButton[6].rc1, &_ENVmonsterButton[6].rc2, 0, 442, 258, 476, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)440);
			else SPRITEMANAGER->renderRectTexture(_ENVmonsterButton[6].tex, &_ENVmonsterButton[6].rc1, &_ENVmonsterButton[6].rc2, 0, 408, 129, 442, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)440);

			//충돌체크
			_ENVmonsterButton[7].rc2 = { (LONG)(rightViewPort.X + 215),(LONG)(rightViewPort.Y + 200),(LONG)(rightViewPort.X + 344),(LONG)(rightViewPort.Y + 234) };
			_ENVmonsterButton[8].rc2 = { (LONG)(rightViewPort.X + 215),(LONG)(rightViewPort.Y + 240),(LONG)(rightViewPort.X + 344),(LONG)(rightViewPort.Y + 274) };
			_ENVmonsterButton[9].rc2 = { (LONG)(rightViewPort.X + 215),(LONG)(rightViewPort.Y + 280),(LONG)(rightViewPort.X + 344),(LONG)(rightViewPort.Y + 314) };
			_ENVmonsterButton[10].rc2 = { (LONG)(rightViewPort.X + 215),(LONG)(rightViewPort.Y + 320),(LONG)(rightViewPort.X + 344),(LONG)(rightViewPort.Y + 354) };
			_ENVmonsterButton[11].rc2 = { (LONG)(rightViewPort.X + 215),(LONG)(rightViewPort.Y + 360),(LONG)(rightViewPort.X + 344),(LONG)(rightViewPort.Y + 394) };
			_ENVmonsterButton[12].rc2 = { (LONG)(rightViewPort.X + 215),(LONG)(rightViewPort.Y + 400),(LONG)(rightViewPort.X + 344),(LONG)(rightViewPort.Y + 434) };
			_ENVmonsterButton[13].rc2 = { (LONG)(rightViewPort.X + 215),(LONG)(rightViewPort.Y + 440),(LONG)(rightViewPort.X + 344),(LONG)(rightViewPort.Y + 474) };

			//오른쪽버튼
			if (_ENVmonsterButton[7].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_ENVmonsterButton[7].tex, &_ENVmonsterButton[7].rc1, &_ENVmonsterButton[7].rc2, 0, 510, 258, 544, rightViewPort.X + (DWORD)215, rightViewPort.Y + (DWORD)200);
			else SPRITEMANAGER->renderRectTexture(_ENVmonsterButton[7].tex, &_ENVmonsterButton[7].rc1, &_ENVmonsterButton[7].rc2, 0, 476, 129, 510, rightViewPort.X + (DWORD)215, rightViewPort.Y + (DWORD)200);

			if (_ENVmonsterButton[8].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_ENVmonsterButton[8].tex, &_ENVmonsterButton[8].rc1, &_ENVmonsterButton[8].rc2, 0, 578, 258, 612, rightViewPort.X + (DWORD)215, rightViewPort.Y + (DWORD)240);
			else SPRITEMANAGER->renderRectTexture(_ENVmonsterButton[8].tex, &_ENVmonsterButton[8].rc1, &_ENVmonsterButton[8].rc2, 0, 544, 129, 578, rightViewPort.X + (DWORD)215, rightViewPort.Y + (DWORD)240);

			if (_ENVmonsterButton[9].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_ENVmonsterButton[9].tex, &_ENVmonsterButton[9].rc1, &_ENVmonsterButton[9].rc2, 0, 646, 258, 680, rightViewPort.X + (DWORD)215, rightViewPort.Y + (DWORD)280);
			else SPRITEMANAGER->renderRectTexture(_ENVmonsterButton[9].tex, &_ENVmonsterButton[9].rc1, &_ENVmonsterButton[9].rc2, 0, 612, 129, 646, rightViewPort.X + (DWORD)215, rightViewPort.Y + (DWORD)280);

			if (_ENVmonsterButton[10].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_ENVmonsterButton[10].tex, &_ENVmonsterButton[10].rc1, &_ENVmonsterButton[10].rc2, 0, 714, 258, 748, rightViewPort.X + (DWORD)215, rightViewPort.Y + (DWORD)320);
			else SPRITEMANAGER->renderRectTexture(_ENVmonsterButton[10].tex, &_ENVmonsterButton[10].rc1, &_ENVmonsterButton[10].rc2, 0, 680, 129, 714, rightViewPort.X + (DWORD)215, rightViewPort.Y + (DWORD)320);

			if (_ENVmonsterButton[11].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_ENVmonsterButton[11].tex, &_ENVmonsterButton[11].rc1, &_ENVmonsterButton[11].rc2, 0, 782, 258, 816, rightViewPort.X + (DWORD)215, rightViewPort.Y + (DWORD)360);
			else SPRITEMANAGER->renderRectTexture(_ENVmonsterButton[11].tex, &_ENVmonsterButton[11].rc1, &_ENVmonsterButton[11].rc2, 0, 748, 129, 782, rightViewPort.X + (DWORD)215, rightViewPort.Y + (DWORD)360);

			if (_ENVmonsterButton[12].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_ENVmonsterButton[12].tex, &_ENVmonsterButton[12].rc1, &_ENVmonsterButton[12].rc2, 0, 850, 258, 884, rightViewPort.X + (DWORD)215, rightViewPort.Y + (DWORD)400);
			else SPRITEMANAGER->renderRectTexture(_ENVmonsterButton[12].tex, &_ENVmonsterButton[12].rc1, &_ENVmonsterButton[12].rc2, 0, 816, 129, 850, rightViewPort.X + (DWORD)215, rightViewPort.Y + (DWORD)400);

			if (_ENVmonsterButton[13].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_ENVmonsterButton[13].tex, &_ENVmonsterButton[13].rc1, &_ENVmonsterButton[13].rc2, 0, 918, 258, 952, rightViewPort.X + (DWORD)215, rightViewPort.Y + (DWORD)440);
			else SPRITEMANAGER->renderRectTexture(_ENVmonsterButton[13].tex, &_ENVmonsterButton[13].rc1, &_ENVmonsterButton[13].rc2, 0, 884, 129, 918, rightViewPort.X + (DWORD)215, rightViewPort.Y + (DWORD)440);


		}
	}
}

void rightView::buttonENvUdate()
{
	//환경 상단이 트루일때
	if (_TOPbutton[2].uiNumber == UISTAGE::UION)
	{
		//왼쪽키
		if (PtInRect(&_ENVbutton.rc2, GetMousePos()))
		{

			for (int i = 0; i < 2; i++)
			{
				//false시켜버리기
				numberNodeInstal = 0;
				numberNodelink = 0;
				numberMonster = 0;
				_nodeInstalContorol[i].uiNumber = UISTAGE::UIOFF;
				_nodeLinkContorol[i].uiNumber = UISTAGE::UIOFF;
			}

			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				if (_ENVbutton.uiNumber <= 1)
				{
					_ENVbutton.uiNumber = ENVSTAGE::WATERMIDDLE;
				}
				else
				{
					_ENVbutton.uiNumber -= 1;
				}
			}
		}

		//오른쪽키
		if (PtInRect(&_ENVbutton.rc3, GetMousePos()))
		{
			for (int i = 0; i < 2; i++)
			{
				//false시켜버리기
				numberNodeInstal = 0;
				numberNodelink = 0;
				numberMonster = 0;
				_nodeInstalContorol[i].uiNumber = UISTAGE::UIOFF;
				_nodeLinkContorol[i].uiNumber = UISTAGE::UIOFF;
			}

			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				if (_ENVbutton.uiNumber >= 5)
				{
					_ENVbutton.uiNumber = ENVSTAGE::MONSTER;
				}
				else
				{
					_ENVbutton.uiNumber += 1;
				}
			}
		}
	}

	if (_TOPbutton[2].uiNumber == UISTAGE::UION)
	{
		//물하단 클릭 충돌
		if (_ENVbutton.uiNumber == ENVSTAGE::WATERMIDDLE)
		{
			for (int i = 0; i < DEFENV; i++)
			{
				if (PtInRect(&_ENVwaterButton[i].rc2, GetMousePos()))
				{
					_ENVwaterButton[i].uiNumber = UISTAGE::UION;
					//누르면 번호 넘겨주는거 해야됨

					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						numberwater = i + 1;
					}
				}
				else
				{
					_ENVwaterButton[i].uiNumber = UISTAGE::UIOFF;
				}
			}
		}
		//스카의하단 클릭 충돌
		if (_ENVbutton.uiNumber == ENVSTAGE::SKYMIDDLE)
		{
			for (int i = 0; i < DEFENV; i++)
			{
				if (PtInRect(&_ENVskyButton[i].rc2, GetMousePos()))
				{
					_ENVskyButton[i].uiNumber = UISTAGE::UION;
					//누르면 번호 넘겨주는거 해야됨

					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						numberEnv = i + 1;
					}
				}
				else
				{
					_ENVskyButton[i].uiNumber = UISTAGE::UIOFF;
				}
			}
		}

		if (_ENVbutton.uiNumber == ENVSTAGE::NODEINSTAL)
		{
			if (PtInRect(&_nodeInstalContorol[0].rc2, GetMousePos()))
			{
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					_nodeInstalContorol[0].uiNumber = UISTAGE::UION;
					_nodeInstalContorol[1].uiNumber = UISTAGE::UIOFF;

					numberNodeInstal = 1;
				}
			}

			if (PtInRect(&_nodeInstalContorol[1].rc2, GetMousePos()))
			{
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					_nodeInstalContorol[1].uiNumber = UISTAGE::UION;
					_nodeInstalContorol[0].uiNumber = UISTAGE::UIOFF;

					numberNodeInstal = 2;
				}
			}
		}

		if (_ENVbutton.uiNumber == ENVSTAGE::NODELINK)
		{
			if (PtInRect(&_nodeLinkContorol[0].rc2, GetMousePos()))
			{
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					_nodeLinkContorol[0].uiNumber = UISTAGE::UION;
					_nodeLinkContorol[1].uiNumber = UISTAGE::UIOFF;

					numberNodelink = 1;
				}
			}

			if (PtInRect(&_nodeLinkContorol[1].rc2, GetMousePos()))
			{
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					_nodeLinkContorol[1].uiNumber = UISTAGE::UION;
					_nodeLinkContorol[0].uiNumber = UISTAGE::UIOFF;

					numberNodelink = 2;
				}
			}
		}

		if (_ENVbutton.uiNumber == ENVSTAGE::MONSTER)
		{
			for (int i = 0; i < DEFMONSTER; i++)
			{
				if (PtInRect(&_ENVmonsterButton[i].rc2, GetMousePos()))
				{
					_ENVmonsterButton[i].uiNumber = UISTAGE::UION;
					//누르면 번호 넘겨주는거 해야됨

					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						numberMonster = i + 1;
					}
				}
				else
				{
					_ENVmonsterButton[i].uiNumber = UISTAGE::UIOFF;
				}
			}
		}
		
	}
}

void rightView::buttonTerMiddle()
{
	//환경상단이 트루 일떄 
	if (_TOPbutton[1].uiNumber == UISTAGE::UION)
	{

		//렉트 충돌 위치
		_TERRIANbutton.rc2 ={ (LONG)(rightViewPort.X + 73),(LONG)(rightViewPort.Y + 95),(LONG)(rightViewPort.X + 100),(LONG)(rightViewPort.Y + 138) };
		_TERRIANbutton.rc3 ={ (LONG)(rightViewPort.X + 289),(LONG)(rightViewPort.Y + 95),(LONG)(rightViewPort.X + 317),(LONG)(rightViewPort.Y + 138) };

		if (_TERRIANbutton.uiNumber == TERSTAGE::TILEMAP1)
		{
			_TERRIANbutton.tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/중단버젼.png");
			SPRITEMANAGER->renderRectTexture(_TERRIANbutton.tex, &_TERRIANbutton.rc1, &_TERRIANbutton.rc2, 0, 0, 244, 43, rightViewPort.X + (DWORD)73, rightViewPort.Y + (DWORD)95);
		}

		if (_TERRIANbutton.uiNumber == TERSTAGE::TILEMAP2)
		{
			_TERRIANbutton.tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/중단버젼.png");
			SPRITEMANAGER->renderRectTexture(_TERRIANbutton.tex, &_TERRIANbutton.rc1, &_TERRIANbutton.rc2, 0, 43, 244, 86, rightViewPort.X + (DWORD)73, rightViewPort.Y + (DWORD)95);
		}

		if (_TERRIANbutton.uiNumber == TERSTAGE::TILEMAP3)
		{
			_TERRIANbutton.tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/중단버젼.png");
			SPRITEMANAGER->renderRectTexture(_TERRIANbutton.tex, &_TERRIANbutton.rc1, &_TERRIANbutton.rc2, 0, 86, 244, 129, rightViewPort.X + (DWORD)73, rightViewPort.Y + (DWORD)95);
		}

		if (_TERRIANbutton.uiNumber == TERSTAGE::TILEMAP4)
		{
			_TERRIANbutton.tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/중단버젼.png");
			SPRITEMANAGER->renderRectTexture(_TERRIANbutton.tex, &_TERRIANbutton.rc1, &_TERRIANbutton.rc2, 0, 129, 244, 172, rightViewPort.X + (DWORD)73, rightViewPort.Y + (DWORD)95);
		}

		if (_TERRIANbutton.uiNumber == TERSTAGE::SPLAT)
		{
			_TERRIANbutton.tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/중단버젼.png");
			SPRITEMANAGER->renderRectTexture(_TERRIANbutton.tex, &_TERRIANbutton.rc1, &_TERRIANbutton.rc2, 0, 172, 244, 215, rightViewPort.X + (DWORD)73, rightViewPort.Y + (DWORD)95);
		}

		if (_TERRIANbutton.uiNumber == TERSTAGE::TERHEIGHT)
		{
			_TERRIANbutton.tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/지형종류.png");
			SPRITEMANAGER->renderRectTexture(_TERRIANbutton.tex, &_TERRIANbutton.rc1, &_TERRIANbutton.rc2, 0, 86, 244, 129, rightViewPort.X + (DWORD)73, rightViewPort.Y + (DWORD)95);
		}

		if (_TERRIANbutton.uiNumber == TERSTAGE::TERRAWMAP)
		{
			_TERRIANbutton.tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/지형종류.png");
			SPRITEMANAGER->renderRectTexture(_TERRIANbutton.tex, &_TERRIANbutton.rc1, &_TERRIANbutton.rc2, 0, 129, 244, 172, rightViewPort.X + (DWORD)73, rightViewPort.Y + (DWORD)95);
		}
	}

	if (_TOPbutton[1].uiNumber == UISTAGE::UION)
	{
		//타일맵1
		if (_TERRIANbutton.uiNumber == TERSTAGE::TILEMAP1)
		{
			//종류 유아이
			_UIkind.tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/종류.png");
			SPRITEMANAGER->renderRectTexture(_UIkind.tex, &_UIkind.rc1, &_UIkind.rc2, 0, 0, 127, 32, rightViewPort.X + (DWORD)135, rightViewPort.Y + (DWORD)162);

			//충돌체크
			_NumberTile1Button[0].rc2 ={ (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 200),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 234) };
			_NumberTile1Button[1].rc2 ={ (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 240),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 274) };
			_NumberTile1Button[2].rc2 ={ (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 280),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 314) };
			_NumberTile1Button[3].rc2 ={ (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 320),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 354) };
			_NumberTile1Button[4].rc2 ={ (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 360),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 394) };
			_NumberTile1Button[5].rc2 ={ (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 400),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 434) };

			for (int i = 0; i < 6; i++) _NumberTile1Button[i].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/하단버튼.png");;

			if (_NumberTile1Button[0].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_NumberTile1Button[0].tex, &_NumberTile1Button[0].rc1, &_NumberTile1Button[0].rc2, 0, 34, 258, 68, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)200);
			else SPRITEMANAGER->renderRectTexture(_NumberTile1Button[0].tex, &_NumberTile1Button[0].rc1, &_NumberTile1Button[0].rc2, 0, 0, 258, 34, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)200);			

			if (_NumberTile1Button[1].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_NumberTile1Button[1].tex, &_NumberTile1Button[1].rc1, &_NumberTile1Button[1].rc2, 0, 102, 258, 136, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)240);
			else SPRITEMANAGER->renderRectTexture(_NumberTile1Button[1].tex, &_NumberTile1Button[1].rc1, &_NumberTile1Button[1].rc2, 0,68, 258, 102, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)240);
		
			if (_NumberTile1Button[2].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_NumberTile1Button[2].tex, &_NumberTile1Button[2].rc1, &_NumberTile1Button[2].rc2, 0, 170, 258, 204, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)280);
			else SPRITEMANAGER->renderRectTexture(_NumberTile1Button[2].tex, &_NumberTile1Button[2].rc1, &_NumberTile1Button[2].rc2, 0, 136, 258, 170, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)280);
		
			if (_NumberTile1Button[3].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_NumberTile1Button[3].tex, &_NumberTile1Button[3].rc1, &_NumberTile1Button[3].rc2, 0, 238, 258, 272, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)320);
			
			else SPRITEMANAGER->renderRectTexture(_NumberTile1Button[3].tex, &_NumberTile1Button[3].rc1, &_NumberTile1Button[3].rc2, 0, 204, 258, 238, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)320);
		
			if (_NumberTile1Button[4].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_NumberTile1Button[4].tex, &_NumberTile1Button[4].rc1, &_NumberTile1Button[4].rc2, 0, 306, 258, 340, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)360);
		   else SPRITEMANAGER->renderRectTexture(_NumberTile1Button[4].tex, &_NumberTile1Button[4].rc1, &_NumberTile1Button[4].rc2, 0, 272, 258, 306, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)360);
		
			if (_NumberTile1Button[5].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_NumberTile1Button[5].tex, &_NumberTile1Button[5].rc1, &_NumberTile1Button[5].rc2, 0, 374, 258, 408, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)400);
			else SPRITEMANAGER->renderRectTexture(_NumberTile1Button[5].tex, &_NumberTile1Button[5].rc1, &_NumberTile1Button[5].rc2, 0, 340, 258, 374, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)400);
		}

		//타일맵2
		if (_TERRIANbutton.uiNumber == TERSTAGE::TILEMAP2)
		{
			//종류 유아이
			_UIkind.tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/종류.png");
			SPRITEMANAGER->renderRectTexture(_UIkind.tex, &_UIkind.rc1, &_UIkind.rc2, 0, 0, 127, 32, rightViewPort.X + (DWORD)135, rightViewPort.Y + (DWORD)162);
			//체크충돌
			_NumberTile2Button[0].rc2 ={ (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 200),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 234) };
			_NumberTile2Button[1].rc2 ={ (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 240),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 274) };
			_NumberTile2Button[2].rc2 ={ (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 280),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 314) };
			_NumberTile2Button[3].rc2 ={ (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 320),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 354) };
			_NumberTile2Button[4].rc2 ={ (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 360),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 394) };
			_NumberTile2Button[5].rc2 ={ (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 400),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 434) };

			for (int i = 0; i < 6; i++) _NumberTile2Button[i].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/하단버튼.png");;
	
			if (_NumberTile2Button[0].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_NumberTile2Button[0].tex, &_NumberTile2Button[0].rc1, &_NumberTile2Button[0].rc2, 0, 34, 258, 68, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)200);
			else SPRITEMANAGER->renderRectTexture(_NumberTile2Button[0].tex, &_NumberTile2Button[0].rc1, &_NumberTile2Button[0].rc2, 0, 0, 258, 34, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)200);
		
			if (_NumberTile2Button[1].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_NumberTile2Button[1].tex, &_NumberTile2Button[1].rc1, &_NumberTile2Button[1].rc2, 0, 102, 258, 136, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)240);
			else SPRITEMANAGER->renderRectTexture(_NumberTile2Button[1].tex, &_NumberTile2Button[1].rc1, &_NumberTile2Button[1].rc2, 0, 68, 258, 102, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)240);
		
			if (_NumberTile2Button[2].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_NumberTile2Button[2].tex, &_NumberTile2Button[2].rc1, &_NumberTile2Button[2].rc2, 0, 170, 258, 204, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)280);
			else SPRITEMANAGER->renderRectTexture(_NumberTile2Button[2].tex, &_NumberTile2Button[2].rc1, &_NumberTile2Button[2].rc2, 0, 136, 258, 170, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)280);
			
			if (_NumberTile2Button[3].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_NumberTile2Button[3].tex, &_NumberTile2Button[3].rc1, &_NumberTile2Button[3].rc2, 0, 238, 258, 272, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)320);
			else SPRITEMANAGER->renderRectTexture(_NumberTile2Button[3].tex, &_NumberTile2Button[3].rc1, &_NumberTile2Button[3].rc2, 0, 204, 258, 238, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)320);
		
			if (_NumberTile2Button[4].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_NumberTile2Button[4].tex, &_NumberTile2Button[4].rc1, &_NumberTile2Button[4].rc2, 0, 306, 258, 340, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)360);
			else SPRITEMANAGER->renderRectTexture(_NumberTile2Button[4].tex, &_NumberTile2Button[4].rc1, &_NumberTile2Button[4].rc2, 0, 272, 258, 306, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)360);
	
			if (_NumberTile2Button[5].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_NumberTile2Button[5].tex, &_NumberTile2Button[5].rc1, &_NumberTile2Button[5].rc2, 0, 374, 258, 408, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)400);
			else SPRITEMANAGER->renderRectTexture(_NumberTile2Button[5].tex, &_NumberTile2Button[5].rc1, &_NumberTile2Button[5].rc2, 0, 340, 258, 374, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)400);
		}

		//타일맵3
		if (_TERRIANbutton.uiNumber == TERSTAGE::TILEMAP3)
		{
			//종류 유아이
			_UIkind.tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/종류.png");
			SPRITEMANAGER->renderRectTexture(_UIkind.tex, &_UIkind.rc1, &_UIkind.rc2, 0, 0, 127, 32, rightViewPort.X + (DWORD)135, rightViewPort.Y + (DWORD)162);
			//체크충돌
			_NumberTile3Button[0].rc2 = { (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 200),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 234) };
			_NumberTile3Button[1].rc2 = { (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 240),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 274) };
			_NumberTile3Button[2].rc2 = { (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 280),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 314) };
			_NumberTile3Button[3].rc2 = { (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 320),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 354) };
			_NumberTile3Button[4].rc2 = { (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 360),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 394) };
			_NumberTile3Button[5].rc2 = { (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 400),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 434) };

			for (int i = 0; i < 6; i++) _NumberTile3Button[i].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/하단버튼.png");;

			if (_NumberTile3Button[0].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_NumberTile3Button[0].tex, &_NumberTile3Button[0].rc1, &_NumberTile3Button[0].rc2, 0, 34, 258, 68, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)200);
			else SPRITEMANAGER->renderRectTexture(_NumberTile3Button[0].tex, &_NumberTile3Button[0].rc1, &_NumberTile3Button[0].rc2, 0, 0, 258, 34, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)200);

			if (_NumberTile3Button[1].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_NumberTile3Button[1].tex, &_NumberTile3Button[1].rc1, &_NumberTile3Button[1].rc2, 0, 102, 258, 136, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)240);
			else SPRITEMANAGER->renderRectTexture(_NumberTile3Button[1].tex, &_NumberTile3Button[1].rc1, &_NumberTile3Button[1].rc2, 0, 68, 258, 102, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)240);

			if (_NumberTile3Button[2].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_NumberTile3Button[2].tex, &_NumberTile3Button[2].rc1, &_NumberTile3Button[2].rc2, 0, 170, 258, 204, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)280);
			else SPRITEMANAGER->renderRectTexture(_NumberTile3Button[2].tex, &_NumberTile3Button[2].rc1, &_NumberTile3Button[2].rc2, 0, 136, 258, 170, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)280);

			if (_NumberTile3Button[3].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_NumberTile3Button[3].tex, &_NumberTile3Button[3].rc1, &_NumberTile3Button[3].rc2, 0, 238, 258, 272, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)320);
			else SPRITEMANAGER->renderRectTexture(_NumberTile3Button[3].tex, &_NumberTile3Button[3].rc1, &_NumberTile3Button[3].rc2, 0, 204, 258, 238, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)320);

			if (_NumberTile3Button[4].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_NumberTile3Button[4].tex, &_NumberTile3Button[4].rc1, &_NumberTile3Button[4].rc2, 0, 306, 258, 340, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)360);
			else SPRITEMANAGER->renderRectTexture(_NumberTile3Button[4].tex, &_NumberTile3Button[4].rc1, &_NumberTile3Button[4].rc2, 0, 272, 258, 306, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)360);

			if (_NumberTile3Button[5].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_NumberTile3Button[5].tex, &_NumberTile3Button[5].rc1, &_NumberTile3Button[5].rc2, 0, 374, 258, 408, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)400);
			else SPRITEMANAGER->renderRectTexture(_NumberTile3Button[5].tex, &_NumberTile3Button[5].rc1, &_NumberTile3Button[5].rc2, 0, 340, 258, 374, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)400);
		}

		//타일맵4
		if (_TERRIANbutton.uiNumber == TERSTAGE::TILEMAP4)
		{
			//종류 유아이
			_UIkind.tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/종류.png");
			SPRITEMANAGER->renderRectTexture(_UIkind.tex, &_UIkind.rc1, &_UIkind.rc2, 0, 0, 127, 32, rightViewPort.X + (DWORD)135, rightViewPort.Y + (DWORD)162);
			//체크충돌
			_NumberTile4Button[0].rc2 = { (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 200),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 234) };
			_NumberTile4Button[1].rc2 = { (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 240),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 274) };
			_NumberTile4Button[2].rc2 = { (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 280),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 314) };
			_NumberTile4Button[3].rc2 = { (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 320),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 354) };
			_NumberTile4Button[4].rc2 = { (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 360),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 394) };
			_NumberTile4Button[5].rc2 = { (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 400),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 434) };

			for (int i = 0; i < 6; i++) _NumberTile4Button[i].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/하단버튼.png");;

			if (_NumberTile4Button[0].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_NumberTile4Button[0].tex, &_NumberTile4Button[0].rc1, &_NumberTile4Button[0].rc2, 0, 34, 258, 68, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)200);
			else SPRITEMANAGER->renderRectTexture(_NumberTile4Button[0].tex, &_NumberTile4Button[0].rc1, &_NumberTile4Button[0].rc2, 0, 0, 258, 34, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)200);

			if (_NumberTile4Button[1].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_NumberTile4Button[1].tex, &_NumberTile4Button[1].rc1, &_NumberTile4Button[1].rc2, 0, 102, 258, 136, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)240);
			else SPRITEMANAGER->renderRectTexture(_NumberTile4Button[1].tex, &_NumberTile4Button[1].rc1, &_NumberTile4Button[1].rc2, 0, 68, 258, 102, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)240);

			if (_NumberTile4Button[2].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_NumberTile4Button[2].tex, &_NumberTile4Button[2].rc1, &_NumberTile4Button[2].rc2, 0, 170, 258, 204, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)280);
			else SPRITEMANAGER->renderRectTexture(_NumberTile4Button[2].tex, &_NumberTile4Button[2].rc1, &_NumberTile4Button[2].rc2, 0, 136, 258, 170, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)280);

			if (_NumberTile4Button[3].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_NumberTile4Button[3].tex, &_NumberTile4Button[3].rc1, &_NumberTile4Button[3].rc2, 0, 238, 258, 272, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)320);
			else SPRITEMANAGER->renderRectTexture(_NumberTile4Button[3].tex, &_NumberTile4Button[3].rc1, &_NumberTile4Button[3].rc2, 0, 204, 258, 238, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)320);

			if (_NumberTile4Button[4].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_NumberTile4Button[4].tex, &_NumberTile4Button[4].rc1, &_NumberTile4Button[4].rc2, 0, 306, 258, 340, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)360);
			else SPRITEMANAGER->renderRectTexture(_NumberTile4Button[4].tex, &_NumberTile4Button[4].rc1, &_NumberTile4Button[4].rc2, 0, 272, 258, 306, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)360);

			if (_NumberTile4Button[5].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_NumberTile4Button[5].tex, &_NumberTile4Button[5].rc1, &_NumberTile4Button[5].rc2, 0, 374, 258, 408, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)400);
			else SPRITEMANAGER->renderRectTexture(_NumberTile4Button[5].tex, &_NumberTile4Button[5].rc1, &_NumberTile4Button[5].rc2, 0, 340, 258, 374, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)400);
		}

		//스플랫트
		if (_TERRIANbutton.uiNumber == TERSTAGE::SPLAT)
		{
			//종류 유아이
			_UIkind.tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/종류.png");
			SPRITEMANAGER->renderRectTexture(_UIkind.tex, &_UIkind.rc1, &_UIkind.rc2, 0, 0, 127, 32, rightViewPort.X + (DWORD)135, rightViewPort.Y + (DWORD)162);
			//체크충돌
			_NumberSplatButton[0].rc2 = { (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 200),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 234) };
			_NumberSplatButton[1].rc2 = { (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 240),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 274) };
			_NumberSplatButton[2].rc2 = { (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 280),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 314) };
			_NumberSplatButton[3].rc2 = { (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 320),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 354) };
			_NumberSplatButton[4].rc2 = { (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 360),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 394) };
			_NumberSplatButton[5].rc2 = { (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 400),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 434) };

			for (int i = 0; i < 6; i++) _NumberSplatButton[i].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/하단버튼.png");;

			if (_NumberSplatButton[0].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_NumberSplatButton[0].tex, &_NumberSplatButton[0].rc1, &_NumberSplatButton[0].rc2, 0, 34, 258, 68, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)200);
			else SPRITEMANAGER->renderRectTexture(_NumberSplatButton[0].tex, &_NumberSplatButton[0].rc1, &_NumberSplatButton[0].rc2, 0, 0, 258, 34, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)200);

			if (_NumberSplatButton[1].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_NumberSplatButton[1].tex, &_NumberSplatButton[1].rc1, &_NumberSplatButton[1].rc2, 0, 102, 258, 136, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)240);
			else SPRITEMANAGER->renderRectTexture(_NumberSplatButton[1].tex, &_NumberSplatButton[1].rc1, &_NumberSplatButton[1].rc2, 0, 68, 258, 102, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)240);

			if (_NumberSplatButton[2].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_NumberSplatButton[2].tex, &_NumberSplatButton[2].rc1, &_NumberSplatButton[2].rc2, 0, 170, 258, 204, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)280);
			else SPRITEMANAGER->renderRectTexture(_NumberSplatButton[2].tex, &_NumberSplatButton[2].rc1, &_NumberSplatButton[2].rc2, 0, 136, 258, 170, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)280);

			if (_NumberSplatButton[3].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_NumberSplatButton[3].tex, &_NumberSplatButton[3].rc1, &_NumberSplatButton[3].rc2, 0, 238, 258, 272, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)320);
			else SPRITEMANAGER->renderRectTexture(_NumberSplatButton[3].tex, &_NumberSplatButton[3].rc1, &_NumberSplatButton[3].rc2, 0, 204, 258, 238, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)320);

			if (_NumberSplatButton[4].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_NumberSplatButton[4].tex, &_NumberSplatButton[4].rc1, &_NumberSplatButton[4].rc2, 0, 306, 258, 340, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)360);
			else SPRITEMANAGER->renderRectTexture(_NumberSplatButton[4].tex, &_NumberSplatButton[4].rc1, &_NumberSplatButton[4].rc2, 0, 272, 258, 306, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)360);

			if (_NumberSplatButton[5].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_NumberSplatButton[5].tex, &_NumberSplatButton[5].rc1, &_NumberSplatButton[5].rc2, 0, 374, 258, 408, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)400);
			else SPRITEMANAGER->renderRectTexture(_NumberSplatButton[5].tex, &_NumberSplatButton[5].rc1, &_NumberSplatButton[5].rc2, 0, 340, 258, 374, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)400);
		}

		//가로세로조절창
		if (_TERRIANbutton.uiNumber == TERSTAGE::TERRAWMAP)
		{
			//종류 유아이
			_UIkind.tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/종류.png");
			SPRITEMANAGER->renderRectTexture(_UIkind.tex, &_UIkind.rc1, &_UIkind.rc2, 0, 0, 127, 32, rightViewPort.X + (DWORD)135, rightViewPort.Y + (DWORD)162);

			//체크충돌
			_NumberRawButton[0].rc2 = { (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 200),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 234) };
			_NumberRawButton[1].rc2 = { (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 240),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 274) };
			_NumberRawButton[2].rc2 = { (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 280),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 314) };
			_NumberRawButton[3].rc2 = { (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 320),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 354) };
			_NumberRawButton[4].rc2 = { (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 360),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 394) };
			_NumberRawButton[5].rc2 = { (LONG)(rightViewPort.X + 70),(LONG)(rightViewPort.Y + 400),(LONG)(rightViewPort.X + 328),(LONG)(rightViewPort.Y + 434) };

			for (int i = 0; i < 6; i++) _NumberRawButton[i].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/하단버튼.png");;

			if (_NumberRawButton[0].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_NumberRawButton[0].tex, &_NumberRawButton[0].rc1, &_NumberRawButton[0].rc2, 0, 34, 258, 68, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)200);
			else SPRITEMANAGER->renderRectTexture(_NumberRawButton[0].tex, &_NumberRawButton[0].rc1, &_NumberRawButton[0].rc2, 0, 0, 258, 34, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)200);

			if (_NumberRawButton[1].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_NumberRawButton[1].tex, &_NumberRawButton[1].rc1, &_NumberRawButton[1].rc2, 0, 102, 258, 136, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)240);
			else SPRITEMANAGER->renderRectTexture(_NumberRawButton[1].tex, &_NumberRawButton[1].rc1, &_NumberRawButton[1].rc2, 0, 68, 258, 102, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)240);

			if (_NumberRawButton[2].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_NumberRawButton[2].tex, &_NumberRawButton[2].rc1, &_NumberRawButton[2].rc2, 0, 170, 258, 204, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)280);
			else SPRITEMANAGER->renderRectTexture(_NumberRawButton[2].tex, &_NumberRawButton[2].rc1, &_NumberRawButton[2].rc2, 0, 136, 258, 170, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)280);

			if (_NumberRawButton[3].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_NumberRawButton[3].tex, &_NumberRawButton[3].rc1, &_NumberRawButton[3].rc2, 0, 238, 258, 272, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)320);
			else SPRITEMANAGER->renderRectTexture(_NumberRawButton[3].tex, &_NumberRawButton[3].rc1, &_NumberRawButton[3].rc2, 0, 204, 258, 238, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)320);

			if (_NumberRawButton[4].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_NumberRawButton[4].tex, &_NumberRawButton[4].rc1, &_NumberRawButton[4].rc2, 0, 306, 258, 340, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)360);
			else SPRITEMANAGER->renderRectTexture(_NumberRawButton[4].tex, &_NumberRawButton[4].rc1, &_NumberRawButton[4].rc2, 0, 272, 258, 306, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)360);

			if (_NumberRawButton[5].uiNumber == UISTAGE::UION) SPRITEMANAGER->renderRectTexture(_NumberRawButton[5].tex, &_NumberRawButton[5].rc1, &_NumberRawButton[5].rc2, 0, 374, 258, 408, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)400);
			else SPRITEMANAGER->renderRectTexture(_NumberRawButton[5].tex, &_NumberRawButton[5].rc1, &_NumberRawButton[5].rc2, 0, 340, 258, 374, rightViewPort.X + (DWORD)70, rightViewPort.Y + (DWORD)400);
		}

		//높이조절창
		if (_TERRIANbutton.uiNumber == TERSTAGE::TERHEIGHT)
		{
			_UIsizeHeight[0].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/높이조절.png");
			SPRITEMANAGER->renderRectTexture(_UIsizeHeight[0].tex, &_UIsizeHeight[0].rc1, &_UIsizeHeight[0].rc2, 0, 0, 90, 34, rightViewPort.X + (DWORD)100, rightViewPort.Y + (DWORD)250);

			//충돌체크
			_heightContorol[0].rc2 = { (LONG)(rightViewPort.X + 220),(LONG)(rightViewPort.Y + 250),(LONG)(rightViewPort.X + 268),(LONG)(rightViewPort.Y + 283) };
			if (_heightContorol[0].uiNumber == UISTAGE::UIOFF)
			{
				_heightContorol[0].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/높이값.png");
				SPRITEMANAGER->renderRectTexture(_heightContorol[0].tex, &_heightContorol[0].rc1, &_heightContorol[0].rc2, 0, 0, 48, 33, rightViewPort.X + (DWORD)220, rightViewPort.Y + (DWORD)250);
			}
			else
			{
				_heightContorol[0].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/높이값.png");
				SPRITEMANAGER->renderRectTexture(_heightContorol[0].tex, &_heightContorol[0].rc1, &_heightContorol[0].rc2, 0, 33, 48, 66, rightViewPort.X + (DWORD)220, rightViewPort.Y + (DWORD)250);
			}

			_UIsizeHeight[1].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/높이조절.png");
			SPRITEMANAGER->renderRectTexture(_UIsizeHeight[1].tex, &_UIsizeHeight[1].rc1, &_UIsizeHeight[1].rc2, 0, 34, 90, 68, rightViewPort.X + (DWORD)100, rightViewPort.Y + (DWORD)350);

			//충돌체크
			_heightContorol[1].rc2 = { (LONG)(rightViewPort.X + 220),(LONG)(rightViewPort.Y + 350),(LONG)(rightViewPort.X + 268),(LONG)(rightViewPort.Y + 383) };
			if (_heightContorol[1].uiNumber == UISTAGE::UIOFF)
			{
				_heightContorol[1].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/높이값.png");
				SPRITEMANAGER->renderRectTexture(_heightContorol[1].tex, &_heightContorol[1].rc1, &_heightContorol[1].rc2, 0, 0, 48, 33, rightViewPort.X + (DWORD)220, rightViewPort.Y + (DWORD)350);
			}
			else
			{
				_heightContorol[1].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/높이값.png");
				SPRITEMANAGER->renderRectTexture(_heightContorol[1].tex, &_heightContorol[1].rc1, &_heightContorol[1].rc2, 0, 33, 48, 66, rightViewPort.X + (DWORD)220, rightViewPort.Y + (DWORD)350);
			}

		}
	}
}

void rightView::buttonTerUdate()
{
	//지형 상단이 트루일때
	if (_TOPbutton[1].uiNumber == UISTAGE::UION)
	{
		//왼쪽키
		if (PtInRect(&_TERRIANbutton.rc2, GetMousePos()))
		{
			for (int i = 0; i < 2; i++)
			{
				numberHeight = 0; //높이조절 초기화
				_heightContorol[i].uiNumber = UISTAGE::UIOFF;
				//false시켜버리기
				numberNodeInstal = 0;
				numberNodelink = 0;
				_nodeInstalContorol[i].uiNumber = UISTAGE::UIOFF;
				_nodeLinkContorol[i].uiNumber = UISTAGE::UIOFF;
			}

			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				if (_TERRIANbutton.uiNumber <= 1)
				{
					_TERRIANbutton.uiNumber = TERSTAGE::TILEMAP1;
				}
				else
				{
					_TERRIANbutton.uiNumber -= 1;
				}
			}
		}
		//오른쪽키
		if (PtInRect(&_TERRIANbutton.rc3, GetMousePos()))
		{
			for (int i = 0; i < 2; i++)
			{
				numberHeight = 0; //높이조절 초기화
				_heightContorol[i].uiNumber = UISTAGE::UIOFF;
				//false시켜버리기
				numberNodeInstal = 0;
				numberNodelink = 0;
				_nodeInstalContorol[i].uiNumber = UISTAGE::UIOFF;
				_nodeLinkContorol[i].uiNumber = UISTAGE::UIOFF;
			}

			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				if (_TERRIANbutton.uiNumber >= 6)
				{
					_TERRIANbutton.uiNumber = TERSTAGE::TERHEIGHT;
				}
				else
				{
					_TERRIANbutton.uiNumber += 1;
				}
			}
		}
	}

	if (_TOPbutton[1].uiNumber == UISTAGE::UION)
	{
		//지형하단타일1 클릭 충돌
		if (_TERRIANbutton.uiNumber == TERSTAGE::TILEMAP1)
		{
			for (int i = 0; i < DEFTER; i++)
			{
				if (PtInRect(&_NumberTile1Button[i].rc2, GetMousePos()))
				{
					_NumberTile1Button[i].uiNumber = UISTAGE::UION;
					//누르면 번호 넘겨주는거 해야됨

					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						boolTile1 = true;
						numberTile1 = i + 1;
					}
				}
				else
				{
					_NumberTile1Button[i].uiNumber = UISTAGE::UIOFF;
				}
			}
		}

		//지형하단타일2 클릭 충돌
		if (_TERRIANbutton.uiNumber == TERSTAGE::TILEMAP2)
		{
			for (int i = 0; i < DEFTER; i++)
			{
				if (PtInRect(&_NumberTile2Button[i].rc2, GetMousePos()))
				{
					_NumberTile2Button[i].uiNumber = UISTAGE::UION;
					//누르면 번호 넘겨주는거 해야됨

					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						boolTile2 = true;
						numberTile2 = i + 1;
					}
				}
				else
				{
					_NumberTile2Button[i].uiNumber = UISTAGE::UIOFF;
				}
			}
		}

		//지형하단타일3 클릭 충돌
		if (_TERRIANbutton.uiNumber == TERSTAGE::TILEMAP3)
		{
			for (int i = 0; i < DEFTER; i++)
			{
				if (PtInRect(&_NumberTile3Button[i].rc2, GetMousePos()))
				{
					_NumberTile3Button[i].uiNumber = UISTAGE::UION;
					//누르면 번호 넘겨주는거 해야됨

					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						boolTile3 = true;
						numberTile3 = i + 1;
					}
				}
				else
				{
					_NumberTile3Button[i].uiNumber = UISTAGE::UIOFF;
				}
			}
		}

		//지형하단타일4 클릭 충돌
		if (_TERRIANbutton.uiNumber == TERSTAGE::TILEMAP4)
		{
			for (int i = 0; i < DEFTER; i++)
			{
				if (PtInRect(&_NumberTile4Button[i].rc2, GetMousePos()))
				{
					_NumberTile4Button[i].uiNumber = UISTAGE::UION;
					//누르면 번호 넘겨주는거 해야됨
					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						boolTile4 = true;
						numberTile4 = i + 1;
					}
				}
				else
				{
					_NumberTile4Button[i].uiNumber = UISTAGE::UIOFF;
				}
			}
		}

		//splate 클릭 충돌
		if (_TERRIANbutton.uiNumber == TERSTAGE::SPLAT)
		{
			for (int i = 0; i < DEFTER; i++)
			{
				if (PtInRect(&_NumberSplatButton[i].rc2, GetMousePos()))
				{
					_NumberSplatButton[i].uiNumber = UISTAGE::UION;
					//누르면 번호 넘겨주는거 해야됨
					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						//boolSplate = true;
						numberSplate = i + 1;
					}
				}
				else
				{
					_NumberSplatButton[i].uiNumber = UISTAGE::UIOFF;
				}
			}
		}

		//RAW맵 클릭 충돌
		if (_TERRIANbutton.uiNumber == TERSTAGE::TERRAWMAP)
		{
			for (int i = 0; i < DEFTER; i++)
			{
				if (PtInRect(&_NumberRawButton[i].rc2, GetMousePos()))
				{
					_NumberRawButton[i].uiNumber = UISTAGE::UION;

					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						boolHeight = true;
						boolRaw = true;
						numberRaw = i + 1;
					}
				}
				else
				{
					_NumberRawButton[i].uiNumber = UISTAGE::UIOFF;
				}
			}
		}

		//사이즈 높이 조절
		if (_TERRIANbutton.uiNumber == TERSTAGE::TERHEIGHT)
		{
			if (PtInRect(&_heightContorol[0].rc2, GetMousePos()))
			{
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					_heightContorol[0].uiNumber = UISTAGE::UION;
					_heightContorol[1].uiNumber = UISTAGE::UIOFF;

					numberHeight = 1;
				}
			}

			if (PtInRect(&_heightContorol[1].rc2, GetMousePos()))
			{
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					_heightContorol[1].uiNumber = UISTAGE::UION;
					_heightContorol[0].uiNumber = UISTAGE::UIOFF;

					numberHeight = 2;
				}
			}
		}
	}
}

void rightView::Render(void)
{
	_mainCamera.updateCamToDevice();

	//자리 잘잡혔는지 확인하는 그리드 렌더
	//_rightSmallGrid->render();

	_objectClass->render(&_mainCamera);
}
