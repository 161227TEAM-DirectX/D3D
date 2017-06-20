#include "stdafx.h"
#include "objectClass.h"


objectClass::objectClass()
{
}


objectClass::~objectClass()
{
}

HRESULT objectClass::init(void)
{
	//기본 광원 생성
	_sceneBaseDirectionLight = new lightDirection;
	//기본 값
	_sceneBaseDirectionLight->_color = D3DXCOLOR(1, 1, 1, 1);
	_sceneBaseDirectionLight->_intensity = 1.0f;

	//넘버 초기화
	numberObject = 0;

	D3DXMATRIX scale;
	D3DXMatrixScaling(&scale, 0.5f, 0.5f, 0.5f);

	//오브젝트 초기화들
	for (int i = 0; i < NUMBER; i++)
	{
		_build[i].uiNumber = objectUi::OBJOFF;
		_object.push_back(new baseObject);
		_object[i]->_transform->SetLocalPosition(0.0f, -0.2f, 0.0f);
		_object[i]->setActive(true);
	}

	_object[0]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob000"));
	_object[1]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob001"));
	_object[2]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob002"));
	_object[3]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob003"));
	_object[4]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob004"));
	_object[5]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob005"));
	_object[6]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob006"));
	_object[7]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob007"));
	_object[8]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob008"));
	_object[9]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob009"));
	_object[10]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob010"));
	_object[11]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob011"));
	_object[12]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob012"));
	_object[13]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob013"));
	_object[14]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob014"));
	_object[15]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob015"));

	_object[17]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob017"));
	_object[18]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob018"));
	_object[19]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob019"));
	_object[20]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob020"));
	_object[21]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob021"));
	_object[22]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob022"));
	_object[23]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob023"));
	_object[24]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob024"));
	_object[25]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob025"));

	_object[26]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob026"));
	_object[27]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob027"));
	_object[28]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob028"));
	_object[29]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob029"));
	_object[30]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob030"));
	_object[31]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob031"));
	_object[32]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob032"));

	_object[34]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob034"));
	_object[35]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob035"));
	_object[36]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob036"));
	_object[37]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob037"));
	_object[38]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob038"));
	_object[39]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob039"));
	_object[40]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob040"));
	_object[41]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob041"));
	_object[42]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob042"));
	_object[43]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob043"));
	_object[44]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob044"));
	_object[45]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob045"));
	_object[46]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob046"));
	_object[47]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob047"));
	_object[48]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob048"));

	_object[50]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob050"));
	_object[51]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob051"));
	_object[52]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob052"));
	_object[53]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob053"));
	_object[54]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob054"));
	_object[55]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob055"));

	_object[56]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob056"));
	_object[57]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob057"));
	_object[58]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob058"));
	_object[59]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob059"));
	_object[60]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob060"));
	_object[61]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob061"));

	_object[62]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob062"));
	_object[63]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob063"));
	_object[64]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob064"));
	_object[65]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob065"));
	_object[66]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob066"));
	_object[67]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob067"));

	_object[68]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob068"));
	_object[69]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob069"));
	_object[70]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob070"));
	_object[71]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob071"));
	_object[72]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob072"));
	_object[73]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob073"));

	_object[74]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob074"));
	_object[75]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob075"));
	_object[76]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob076"));
	_object[77]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob077"));
	_object[78]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob078"));

	_object[79]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob079"));
	_object[80]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob080"));
	_object[81]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob081"));
	_object[82]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob082"));
	_object[83]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob083"));

	_object[84]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob084"));
	_object[85]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob085"));
	_object[86]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob086"));
	_object[87]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob087"));
	_object[88]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob088"));
	_object[89]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob089"));
	_object[90]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob090"));
	_object[91]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob091"));
	_object[92]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob092"));
	_object[93]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob093"));
	_object[94]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob094"));
	_object[95]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob095"));
	_object[96]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob096"));
	_object[97]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob097"));

	_object[98]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob098"));
	_object[99]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob099"));
	_object[100]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob100"));
	_object[101]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob101"));
	_object[102]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob102"));
	_object[103]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob103"));
	_object[104]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob104"));
	_object[105]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob105"));
	_object[106]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob106"));
	_object[107]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob107"));
	_object[108]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob108"));
	_object[109]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob109"));
	_object[110]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob110"));
	_object[111]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob111"));

	_object[112]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob112"));
	_object[113]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob113"));
	_object[114]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob114"));
	_object[115]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob115"));
	_object[116]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob116"));
	_object[117]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob117"));
	_object[118]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob118"));
	_object[119]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob119"));
	_object[120]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob120"));
	_object[121]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob121"));

	_object[122]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob122"));
	_object[123]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob123"));
	_object[124]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob124"));
	_object[125]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob125"));
	_object[126]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob126"));
	_object[127]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob127"));

	_object[128]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob128"));
	_object[129]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob129"));
	_object[130]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob130"));
	_object[131]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob131"));
	_object[132]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob132"));
	_object[133]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob133"));
	_object[134]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob134"));
	_object[135]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob135"));
	_object[136]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob136"));

	_object[137]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob137"));
	_object[138]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob138"));
	_object[139]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob139"));
	_object[140]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob140"));

	_object[141]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob141"));
	_object[142]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob142"));
	_object[143]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob143"));
	_object[144]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob144"));
	_object[145]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob145"));
	_object[146]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob146"));
	_object[147]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob147"));
	_object[148]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob148"));
	_object[149]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob149"));
	_object[150]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob150"));
	_object[151]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob151"));

	_object[152]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob152"));
	_object[153]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob153"));
	_object[154]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob154"));
	_object[155]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob155"));
	_object[156]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob156"));
	_object[157]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob157"));
	_object[158]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob158"));
	_object[159]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob159"));
	_object[160]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob160"));
	_object[161]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob161"));
	_object[162]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob162"));
	_object[163]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob163"));
	_object[164]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob164"));

	_object[165]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob165"));
	_object[166]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob166"));
	_object[167]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob167"));
	_object[168]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob168"));
	_object[169]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob169"));
	_object[170]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob170"));
	_object[171]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob171"));
	_object[172]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob172"));
	_object[173]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob173"));
	_object[174]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob174"));
	_object[175]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob175"));
	_object[176]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob176"));
	_object[177]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob177"));

	_object[178]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob178"));
	_object[179]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob179"));
	_object[180]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob180"));
	_object[181]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob181"));
	_object[182]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob182"));

	_object[183]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob183"));
	_object[184]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob184"));
	_object[185]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob185"));
	_object[186]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob186"));
	_object[187]->setMesh(XMESH_MANAGER->GetXmeshStatic("ob187"));

	return S_OK;
}

void objectClass::release(void)
{
}

void objectClass::update(void)
{
	for (int i = 0; i < NUMBER; i++)
	{
		_object[i]->update();
	}

	for (int i = 0; i < NUMBER; i++)
	{
		if (_build[i].uiNumber == objectUi::OBJON)
		{
			_object[i]->_transform->RotateSelf(0.0f, 0.05f, 0.0f);
		}
	}
}


void objectClass::render(camera * camera)
{
	//렌더시킬 조명행렬 초기화 (각각의 라이트 클래스안에 만들어져있음)
	xMeshStatic::_staticMeshEffect->SetMatrixArray("matLights", &_sceneBaseDirectionLight->getLightMatrix(), 1);
	xMeshStatic::_staticMeshEffect->SetInt("LightNum", 1);
	xMeshStatic::setCamera(camera);
}

void objectClass::objectUp(POINT mouse, int arrayS, int arrayE)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = arrayS; i < arrayE; i++)
		{
			if (PtInRect(&_build[i].rc2, mouse))
			{
				numberObject = i + 1;
				_build[i].uiNumber = objectUi::OBJON;
			}
			else
			{
				_build[i].uiNumber = objectUi::OBJOFF;
			}
		}
	}
}

void objectClass::storm1()
{
	_build[0].rc2 ={ (LONG)(rightViewPort.X + 80),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 120),(LONG)(rightViewPort.Y + 270) };
	_build[0].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/1.png");
	SPRITEMANAGER->renderRectTexture(_build[0].tex, &_build[0].rc1, &_build[0].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)80, rightViewPort.Y + (DWORD)230);

	_build[1].rc2 ={ (LONG)(rightViewPort.X + 130),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 170),(LONG)(rightViewPort.Y + 270) };
	_build[1].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/2.png");
	SPRITEMANAGER->renderRectTexture(_build[1].tex, &_build[1].rc1, &_build[1].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)130, rightViewPort.Y + (DWORD)230);

	_build[2].rc2 ={ (LONG)(rightViewPort.X + 180),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 220),(LONG)(rightViewPort.Y + 270) };
	_build[2].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/3.png");
	SPRITEMANAGER->renderRectTexture(_build[2].tex, &_build[2].rc1, &_build[2].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)180, rightViewPort.Y + (DWORD)230);

	_build[3].rc2 ={ (LONG)(rightViewPort.X + 230),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 270),(LONG)(rightViewPort.Y + 270) };
	_build[3].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/4.png");
	SPRITEMANAGER->renderRectTexture(_build[3].tex, &_build[3].rc1, &_build[3].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)230, rightViewPort.Y + (DWORD)230);

	_build[4].rc2 ={ (LONG)(rightViewPort.X + 280),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 320),(LONG)(rightViewPort.Y + 270) };
	_build[4].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/5.png");
	SPRITEMANAGER->renderRectTexture(_build[4].tex, &_build[4].rc1, &_build[4].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)280, rightViewPort.Y + (DWORD)230);

	_build[5].rc2 ={ (LONG)(rightViewPort.X + 80),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 120),(LONG)(rightViewPort.Y + 340) };
	_build[5].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/6.png");
	SPRITEMANAGER->renderRectTexture(_build[5].tex, &_build[5].rc1, &_build[5].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)80, rightViewPort.Y + (DWORD)300);

	_build[6].rc2 ={ (LONG)(rightViewPort.X + 130),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 170),(LONG)(rightViewPort.Y + 340) };
	_build[6].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/7.png");
	SPRITEMANAGER->renderRectTexture(_build[6].tex, &_build[6].rc1, &_build[6].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)130, rightViewPort.Y + (DWORD)300);

	_build[7].rc2 ={ (LONG)(rightViewPort.X + 180),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 220),(LONG)(rightViewPort.Y + 340) };
	_build[7].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/8.png");
	SPRITEMANAGER->renderRectTexture(_build[7].tex, &_build[7].rc1, &_build[7].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)180, rightViewPort.Y + (DWORD)300);

	_build[8].rc2 ={ (LONG)(rightViewPort.X + 230),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 270),(LONG)(rightViewPort.Y + 340) };
	_build[8].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/9.png");
	SPRITEMANAGER->renderRectTexture(_build[8].tex, &_build[8].rc1, &_build[8].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)230, rightViewPort.Y + (DWORD)300);

	_build[9].rc2 ={ (LONG)(rightViewPort.X + 280),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 320),(LONG)(rightViewPort.Y + 340) };
	_build[9].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/10.png");
	SPRITEMANAGER->renderRectTexture(_build[9].tex, &_build[9].rc1, &_build[9].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)280, rightViewPort.Y + (DWORD)300);

	_build[10].rc2 ={ (LONG)(rightViewPort.X + 80),(LONG)(rightViewPort.Y + 370),(LONG)(rightViewPort.X + 120),(LONG)(rightViewPort.Y + 410) };
	_build[10].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/11.png");
	SPRITEMANAGER->renderRectTexture(_build[10].tex, &_build[10].rc1, &_build[10].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)80, rightViewPort.Y + (DWORD)370);

	_build[11].rc2 ={ (LONG)(rightViewPort.X + 130),(LONG)(rightViewPort.Y + 370),(LONG)(rightViewPort.X + 170),(LONG)(rightViewPort.Y + 410) };
	_build[11].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/12.png");
	SPRITEMANAGER->renderRectTexture(_build[11].tex, &_build[11].rc1, &_build[11].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)130, rightViewPort.Y + (DWORD)370);

	_build[12].rc2 ={ (LONG)(rightViewPort.X + 180),(LONG)(rightViewPort.Y + 370),(LONG)(rightViewPort.X + 220),(LONG)(rightViewPort.Y + 410) };
	_build[12].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/13.png");
	SPRITEMANAGER->renderRectTexture(_build[12].tex, &_build[12].rc1, &_build[12].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)180, rightViewPort.Y + (DWORD)370);

	_build[13].rc2 ={ (LONG)(rightViewPort.X + 230),(LONG)(rightViewPort.Y + 370),(LONG)(rightViewPort.X + 270),(LONG)(rightViewPort.Y + 410) };
	_build[13].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/14.png");
	SPRITEMANAGER->renderRectTexture(_build[13].tex, &_build[13].rc1, &_build[13].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)230, rightViewPort.Y + (DWORD)370);

	_build[14].rc2 ={ (LONG)(rightViewPort.X + 280),(LONG)(rightViewPort.Y + 370),(LONG)(rightViewPort.X + 320),(LONG)(rightViewPort.Y + 410) };
	_build[14].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/15.png");
	SPRITEMANAGER->renderRectTexture(_build[14].tex, &_build[14].rc1, &_build[4].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)280, rightViewPort.Y + (DWORD)370);

	_build[15].rc2 ={ (LONG)(rightViewPort.X + 130),(LONG)(rightViewPort.Y + 440),(LONG)(rightViewPort.X + 170),(LONG)(rightViewPort.Y + 480) };
	_build[15].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/16.png");
	SPRITEMANAGER->renderRectTexture(_build[15].tex, &_build[15].rc1, &_build[15].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)130, rightViewPort.Y + (DWORD)440);

	for (int i = 0; i < 16; i++)
	{
		if (_build[i].uiNumber == objectUi::OBJON)
		{
			_object[i]->render();
		}
	}
}

void objectClass::storm2()
{
	//9,8,16,6
	_build[17].rc2 ={ (LONG)(rightViewPort.X + 80),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 120),(LONG)(rightViewPort.Y + 270) };
	_build[17].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/1.png");
	SPRITEMANAGER->renderRectTexture(_build[17].tex, &_build[17].rc1, &_build[17].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)80, rightViewPort.Y + (DWORD)230);

	_build[18].rc2 ={ (LONG)(rightViewPort.X + 130),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 170),(LONG)(rightViewPort.Y + 270) };
	_build[18].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/2.png");
	SPRITEMANAGER->renderRectTexture(_build[18].tex, &_build[18].rc1, &_build[18].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)130, rightViewPort.Y + (DWORD)230);

	_build[19].rc2 ={ (LONG)(rightViewPort.X + 180),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 220),(LONG)(rightViewPort.Y + 270) };
	_build[19].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/3.png");
	SPRITEMANAGER->renderRectTexture(_build[19].tex, &_build[19].rc1, &_build[19].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)180, rightViewPort.Y + (DWORD)230);

	_build[20].rc2 ={ (LONG)(rightViewPort.X + 230),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 270),(LONG)(rightViewPort.Y + 270) };
	_build[20].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/4.png");
	SPRITEMANAGER->renderRectTexture(_build[20].tex, &_build[20].rc1, &_build[20].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)230, rightViewPort.Y + (DWORD)230);

	_build[21].rc2 ={ (LONG)(rightViewPort.X + 280),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 320),(LONG)(rightViewPort.Y + 270) };
	_build[21].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/5.png");
	SPRITEMANAGER->renderRectTexture(_build[21].tex, &_build[21].rc1, &_build[21].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)280, rightViewPort.Y + (DWORD)230);

	_build[22].rc2 ={ (LONG)(rightViewPort.X + 80),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 120),(LONG)(rightViewPort.Y + 340) };
	_build[22].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/6.png");
	SPRITEMANAGER->renderRectTexture(_build[22].tex, &_build[22].rc1, &_build[22].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)80, rightViewPort.Y + (DWORD)300);

	_build[23].rc2 ={ (LONG)(rightViewPort.X + 130),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 170),(LONG)(rightViewPort.Y + 340) };
	_build[23].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/7.png");
	SPRITEMANAGER->renderRectTexture(_build[23].tex, &_build[23].rc1, &_build[23].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)130, rightViewPort.Y + (DWORD)300);

	_build[24].rc2 ={ (LONG)(rightViewPort.X + 180),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 220),(LONG)(rightViewPort.Y + 340) };
	_build[24].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/8.png");
	SPRITEMANAGER->renderRectTexture(_build[24].tex, &_build[24].rc1, &_build[24].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)180, rightViewPort.Y + (DWORD)300);

	_build[25].rc2 ={ (LONG)(rightViewPort.X + 230),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 270),(LONG)(rightViewPort.Y + 340) };
	_build[25].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/9.png");
	SPRITEMANAGER->renderRectTexture(_build[25].tex, &_build[25].rc1, &_build[25].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)230, rightViewPort.Y + (DWORD)300);

	for (int i = 17; i < 26; i++)
	{
		if (_build[i].uiNumber == objectUi::OBJON)
		{
			_object[i]->render();
		}
	}
}

void objectClass::storm3()
{
	//9,8,16,6
	_build[26].rc2 ={ (LONG)(rightViewPort.X + 80),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 120),(LONG)(rightViewPort.Y + 270) };
	_build[26].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/1.png");
	SPRITEMANAGER->renderRectTexture(_build[26].tex, &_build[26].rc1, &_build[26].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)80, rightViewPort.Y + (DWORD)230);

	_build[27].rc2 ={ (LONG)(rightViewPort.X + 130),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 170),(LONG)(rightViewPort.Y + 270) };
	_build[27].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/2.png");
	SPRITEMANAGER->renderRectTexture(_build[27].tex, &_build[27].rc1, &_build[27].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)130, rightViewPort.Y + (DWORD)230);

	_build[28].rc2 ={ (LONG)(rightViewPort.X + 180),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 220),(LONG)(rightViewPort.Y + 270) };
	_build[28].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/3.png");
	SPRITEMANAGER->renderRectTexture(_build[28].tex, &_build[28].rc1, &_build[28].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)180, rightViewPort.Y + (DWORD)230);

	_build[29].rc2 ={ (LONG)(rightViewPort.X + 230),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 270),(LONG)(rightViewPort.Y + 270) };
	_build[29].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/4.png");
	SPRITEMANAGER->renderRectTexture(_build[29].tex, &_build[29].rc1, &_build[29].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)230, rightViewPort.Y + (DWORD)230);

	_build[30].rc2 ={ (LONG)(rightViewPort.X + 280),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 320),(LONG)(rightViewPort.Y + 270) };
	_build[30].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/5.png");
	SPRITEMANAGER->renderRectTexture(_build[30].tex, &_build[30].rc1, &_build[30].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)280, rightViewPort.Y + (DWORD)230);

	_build[31].rc2 ={ (LONG)(rightViewPort.X + 80),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 120),(LONG)(rightViewPort.Y + 340) };
	_build[31].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/6.png");
	SPRITEMANAGER->renderRectTexture(_build[31].tex, &_build[31].rc1, &_build[31].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)80, rightViewPort.Y + (DWORD)300);

	_build[32].rc2 ={ (LONG)(rightViewPort.X + 130),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 170),(LONG)(rightViewPort.Y + 340) };
	_build[32].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/7.png");
	SPRITEMANAGER->renderRectTexture(_build[32].tex, &_build[32].rc1, &_build[32].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)130, rightViewPort.Y + (DWORD)300);

	for (int i = 26; i < 33; i++)
	{
		if (_build[i].uiNumber == objectUi::OBJON)
		{
			_object[i]->render();
		}
	}
}

void objectClass::storm4()
{
	_build[34].rc2 ={ (LONG)(rightViewPort.X + 80),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 120),(LONG)(rightViewPort.Y + 270) };
	_build[34].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/1.png");
	SPRITEMANAGER->renderRectTexture(_build[34].tex, &_build[34].rc1, &_build[34].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)80, rightViewPort.Y + (DWORD)230);

	_build[35].rc2 ={ (LONG)(rightViewPort.X + 130),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 170),(LONG)(rightViewPort.Y + 270) };
	_build[35].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/2.png");
	SPRITEMANAGER->renderRectTexture(_build[35].tex, &_build[35].rc1, &_build[35].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)130, rightViewPort.Y + (DWORD)230);

	_build[36].rc2 ={ (LONG)(rightViewPort.X + 180),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 220),(LONG)(rightViewPort.Y + 270) };
	_build[36].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/3.png");
	SPRITEMANAGER->renderRectTexture(_build[36].tex, &_build[36].rc1, &_build[36].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)180, rightViewPort.Y + (DWORD)230);

	_build[37].rc2 ={ (LONG)(rightViewPort.X + 230),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 270),(LONG)(rightViewPort.Y + 270) };
	_build[37].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/4.png");
	SPRITEMANAGER->renderRectTexture(_build[37].tex, &_build[37].rc1, &_build[37].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)230, rightViewPort.Y + (DWORD)230);

	_build[38].rc2 ={ (LONG)(rightViewPort.X + 280),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 320),(LONG)(rightViewPort.Y + 270) };
	_build[38].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/5.png");
	SPRITEMANAGER->renderRectTexture(_build[38].tex, &_build[38].rc1, &_build[38].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)280, rightViewPort.Y + (DWORD)230);

	_build[39].rc2 ={ (LONG)(rightViewPort.X + 80),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 120),(LONG)(rightViewPort.Y + 340) };
	_build[39].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/6.png");
	SPRITEMANAGER->renderRectTexture(_build[39].tex, &_build[39].rc1, &_build[39].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)80, rightViewPort.Y + (DWORD)300);

	_build[40].rc2 ={ (LONG)(rightViewPort.X + 130),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 170),(LONG)(rightViewPort.Y + 340) };
	_build[40].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/7.png");
	SPRITEMANAGER->renderRectTexture(_build[40].tex, &_build[40].rc1, &_build[40].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)130, rightViewPort.Y + (DWORD)300);

	_build[41].rc2 ={ (LONG)(rightViewPort.X + 180),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 220),(LONG)(rightViewPort.Y + 340) };
	_build[41].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/8.png");
	SPRITEMANAGER->renderRectTexture(_build[41].tex, &_build[41].rc1, &_build[41].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)180, rightViewPort.Y + (DWORD)300);

	_build[42].rc2 ={ (LONG)(rightViewPort.X + 230),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 270),(LONG)(rightViewPort.Y + 340) };
	_build[42].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/9.png");
	SPRITEMANAGER->renderRectTexture(_build[42].tex, &_build[42].rc1, &_build[42].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)230, rightViewPort.Y + (DWORD)300);

	_build[43].rc2 ={ (LONG)(rightViewPort.X + 280),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 320),(LONG)(rightViewPort.Y + 340) };
	_build[43].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/10.png");
	SPRITEMANAGER->renderRectTexture(_build[43].tex, &_build[43].rc1, &_build[43].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)280, rightViewPort.Y + (DWORD)300);

	_build[44].rc2 ={ (LONG)(rightViewPort.X + 80),(LONG)(rightViewPort.Y + 370),(LONG)(rightViewPort.X + 120),(LONG)(rightViewPort.Y + 410) };
	_build[44].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/11.png");
	SPRITEMANAGER->renderRectTexture(_build[44].tex, &_build[44].rc1, &_build[44].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)80, rightViewPort.Y + (DWORD)370);

	_build[45].rc2 ={ (LONG)(rightViewPort.X + 130),(LONG)(rightViewPort.Y + 370),(LONG)(rightViewPort.X + 170),(LONG)(rightViewPort.Y + 410) };
	_build[45].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/12.png");
	SPRITEMANAGER->renderRectTexture(_build[45].tex, &_build[45].rc1, &_build[45].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)130, rightViewPort.Y + (DWORD)370);

	_build[46].rc2 ={ (LONG)(rightViewPort.X + 180),(LONG)(rightViewPort.Y + 370),(LONG)(rightViewPort.X + 220),(LONG)(rightViewPort.Y + 410) };
	_build[46].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/13.png");
	SPRITEMANAGER->renderRectTexture(_build[46].tex, &_build[46].rc1, &_build[46].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)180, rightViewPort.Y + (DWORD)370);

	_build[47].rc2 ={ (LONG)(rightViewPort.X + 230),(LONG)(rightViewPort.Y + 370),(LONG)(rightViewPort.X + 270),(LONG)(rightViewPort.Y + 410) };
	_build[47].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/14.png");
	SPRITEMANAGER->renderRectTexture(_build[47].tex, &_build[47].rc1, &_build[47].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)230, rightViewPort.Y + (DWORD)370);

	_build[48].rc2 ={ (LONG)(rightViewPort.X + 280),(LONG)(rightViewPort.Y + 370),(LONG)(rightViewPort.X + 320),(LONG)(rightViewPort.Y + 410) };
	_build[48].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/15.png");
	SPRITEMANAGER->renderRectTexture(_build[48].tex, &_build[48].rc1, &_build[48].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)280, rightViewPort.Y + (DWORD)370);

	for (int i = 34; i < 49; i++)
	{
		if (_build[i].uiNumber == objectUi::OBJON)
		{
			_object[i]->render();
		}
	}
}

void objectClass::storm5()
{
	_build[50].rc2 ={ (LONG)(rightViewPort.X + 80),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 120),(LONG)(rightViewPort.Y + 270) };
	_build[50].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/1.png");
	SPRITEMANAGER->renderRectTexture(_build[50].tex, &_build[50].rc1, &_build[50].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)80, rightViewPort.Y + (DWORD)230);

	_build[51].rc2 ={ (LONG)(rightViewPort.X + 130),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 170),(LONG)(rightViewPort.Y + 270) };
	_build[51].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/2.png");
	SPRITEMANAGER->renderRectTexture(_build[51].tex, &_build[51].rc1, &_build[51].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)130, rightViewPort.Y + (DWORD)230);

	_build[52].rc2 ={ (LONG)(rightViewPort.X + 180),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 220),(LONG)(rightViewPort.Y + 270) };
	_build[52].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/3.png");
	SPRITEMANAGER->renderRectTexture(_build[52].tex, &_build[52].rc1, &_build[52].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)180, rightViewPort.Y + (DWORD)230);

	_build[53].rc2 ={ (LONG)(rightViewPort.X + 230),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 270),(LONG)(rightViewPort.Y + 270) };
	_build[53].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/4.png");
	SPRITEMANAGER->renderRectTexture(_build[53].tex, &_build[53].rc1, &_build[53].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)230, rightViewPort.Y + (DWORD)230);

	_build[54].rc2 ={ (LONG)(rightViewPort.X + 280),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 320),(LONG)(rightViewPort.Y + 270) };
	_build[54].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/5.png");
	SPRITEMANAGER->renderRectTexture(_build[54].tex, &_build[54].rc1, &_build[54].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)280, rightViewPort.Y + (DWORD)230);

	_build[55].rc2 ={ (LONG)(rightViewPort.X + 80),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 120),(LONG)(rightViewPort.Y + 340) };
	_build[55].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/6.png");
	SPRITEMANAGER->renderRectTexture(_build[55].tex, &_build[55].rc1, &_build[55].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)80, rightViewPort.Y + (DWORD)300);

	for (int i = 50; i < 56; i++)
	{
		if (_build[i].uiNumber == objectUi::OBJON)
		{
			_object[i]->render();
		}
	}
}

void objectClass::storm6()
{
	_build[56].rc2 ={ (LONG)(rightViewPort.X + 80),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 120),(LONG)(rightViewPort.Y + 270) };
	_build[56].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/1.png");
	SPRITEMANAGER->renderRectTexture(_build[56].tex, &_build[56].rc1, &_build[56].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)80, rightViewPort.Y + (DWORD)230);

	_build[57].rc2 ={ (LONG)(rightViewPort.X + 130),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 170),(LONG)(rightViewPort.Y + 270) };
	_build[57].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/2.png");
	SPRITEMANAGER->renderRectTexture(_build[57].tex, &_build[57].rc1, &_build[57].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)130, rightViewPort.Y + (DWORD)230);

	_build[58].rc2 ={ (LONG)(rightViewPort.X + 180),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 220),(LONG)(rightViewPort.Y + 270) };
	_build[58].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/3.png");
	SPRITEMANAGER->renderRectTexture(_build[58].tex, &_build[58].rc1, &_build[58].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)180, rightViewPort.Y + (DWORD)230);

	_build[59].rc2 ={ (LONG)(rightViewPort.X + 230),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 270),(LONG)(rightViewPort.Y + 270) };
	_build[59].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/4.png");
	SPRITEMANAGER->renderRectTexture(_build[59].tex, &_build[59].rc1, &_build[59].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)230, rightViewPort.Y + (DWORD)230);

	_build[60].rc2 ={ (LONG)(rightViewPort.X + 280),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 320),(LONG)(rightViewPort.Y + 270) };
	_build[60].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/5.png");
	SPRITEMANAGER->renderRectTexture(_build[60].tex, &_build[60].rc1, &_build[60].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)280, rightViewPort.Y + (DWORD)230);

	_build[61].rc2 ={ (LONG)(rightViewPort.X + 80),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 120),(LONG)(rightViewPort.Y + 340) };
	_build[61].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/6.png");
	SPRITEMANAGER->renderRectTexture(_build[61].tex, &_build[61].rc1, &_build[61].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)80, rightViewPort.Y + (DWORD)300);

	for (int i = 56; i < 62; i++)
	{
		if (_build[i].uiNumber == objectUi::OBJON)
		{
			_object[i]->render();
		}
	}
}

void objectClass::storm7()
{
	_build[62].rc2 ={ (LONG)(rightViewPort.X + 80),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 120),(LONG)(rightViewPort.Y + 270) };
	_build[62].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/1.png");
	SPRITEMANAGER->renderRectTexture(_build[62].tex, &_build[62].rc1, &_build[62].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)80, rightViewPort.Y + (DWORD)230);

	_build[63].rc2 ={ (LONG)(rightViewPort.X + 130),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 170),(LONG)(rightViewPort.Y + 270) };
	_build[63].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/2.png");
	SPRITEMANAGER->renderRectTexture(_build[63].tex, &_build[63].rc1, &_build[63].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)130, rightViewPort.Y + (DWORD)230);

	_build[64].rc2 ={ (LONG)(rightViewPort.X + 180),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 220),(LONG)(rightViewPort.Y + 270) };
	_build[64].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/3.png");
	SPRITEMANAGER->renderRectTexture(_build[64].tex, &_build[64].rc1, &_build[64].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)180, rightViewPort.Y + (DWORD)230);

	_build[65].rc2 ={ (LONG)(rightViewPort.X + 230),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 270),(LONG)(rightViewPort.Y + 270) };
	_build[65].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/4.png");
	SPRITEMANAGER->renderRectTexture(_build[65].tex, &_build[65].rc1, &_build[65].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)230, rightViewPort.Y + (DWORD)230);

	_build[66].rc2 ={ (LONG)(rightViewPort.X + 280),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 320),(LONG)(rightViewPort.Y + 270) };
	_build[66].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/5.png");
	SPRITEMANAGER->renderRectTexture(_build[66].tex, &_build[66].rc1, &_build[66].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)280, rightViewPort.Y + (DWORD)230);

	_build[67].rc2 ={ (LONG)(rightViewPort.X + 80),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 120),(LONG)(rightViewPort.Y + 340) };
	_build[67].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/6.png");
	SPRITEMANAGER->renderRectTexture(_build[67].tex, &_build[67].rc1, &_build[67].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)80, rightViewPort.Y + (DWORD)300);

	for (int i = 62; i < 68; i++)
	{
		if (_build[i].uiNumber == objectUi::OBJON)
		{
			_object[i]->render();
		}
	}
}

void objectClass::storm8()
{
	_build[68].rc2 ={ (LONG)(rightViewPort.X + 80),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 120),(LONG)(rightViewPort.Y + 270) };
	_build[68].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/1.png");
	SPRITEMANAGER->renderRectTexture(_build[68].tex, &_build[68].rc1, &_build[68].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)80, rightViewPort.Y + (DWORD)230);

	_build[69].rc2 ={ (LONG)(rightViewPort.X + 130),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 170),(LONG)(rightViewPort.Y + 270) };
	_build[69].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/2.png");
	SPRITEMANAGER->renderRectTexture(_build[69].tex, &_build[69].rc1, &_build[69].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)130, rightViewPort.Y + (DWORD)230);

	_build[70].rc2 ={ (LONG)(rightViewPort.X + 180),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 220),(LONG)(rightViewPort.Y + 270) };
	_build[70].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/3.png");
	SPRITEMANAGER->renderRectTexture(_build[70].tex, &_build[70].rc1, &_build[70].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)180, rightViewPort.Y + (DWORD)230);

	_build[71].rc2 ={ (LONG)(rightViewPort.X + 230),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 270),(LONG)(rightViewPort.Y + 270) };
	_build[71].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/4.png");
	SPRITEMANAGER->renderRectTexture(_build[71].tex, &_build[71].rc1, &_build[71].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)230, rightViewPort.Y + (DWORD)230);

	_build[72].rc2 ={ (LONG)(rightViewPort.X + 280),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 320),(LONG)(rightViewPort.Y + 270) };
	_build[72].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/5.png");
	SPRITEMANAGER->renderRectTexture(_build[72].tex, &_build[72].rc1, &_build[72].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)280, rightViewPort.Y + (DWORD)230);

	_build[73].rc2 ={ (LONG)(rightViewPort.X + 80),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 120),(LONG)(rightViewPort.Y + 340) };
	_build[73].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/6.png");
	SPRITEMANAGER->renderRectTexture(_build[73].tex, &_build[73].rc1, &_build[73].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)80, rightViewPort.Y + (DWORD)300);

	for (int i = 68; i < 74; i++)
	{
		if (_build[i].uiNumber == objectUi::OBJON)
		{
			_object[i]->render();
		}
	}
}

void objectClass::storm9()
{
	_build[74].rc2 ={ (LONG)(rightViewPort.X + 80),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 120),(LONG)(rightViewPort.Y + 270) };
	_build[74].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/1.png");
	SPRITEMANAGER->renderRectTexture(_build[74].tex, &_build[74].rc1, &_build[74].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)80, rightViewPort.Y + (DWORD)230);

	_build[75].rc2 ={ (LONG)(rightViewPort.X + 130),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 170),(LONG)(rightViewPort.Y + 270) };
	_build[75].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/2.png");
	SPRITEMANAGER->renderRectTexture(_build[75].tex, &_build[75].rc1, &_build[75].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)130, rightViewPort.Y + (DWORD)230);

	_build[76].rc2 ={ (LONG)(rightViewPort.X + 180),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 220),(LONG)(rightViewPort.Y + 270) };
	_build[76].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/3.png");
	SPRITEMANAGER->renderRectTexture(_build[76].tex, &_build[76].rc1, &_build[76].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)180, rightViewPort.Y + (DWORD)230);

	_build[77].rc2 ={ (LONG)(rightViewPort.X + 230),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 270),(LONG)(rightViewPort.Y + 270) };
	_build[77].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/4.png");
	SPRITEMANAGER->renderRectTexture(_build[77].tex, &_build[77].rc1, &_build[77].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)230, rightViewPort.Y + (DWORD)230);

	_build[78].rc2 ={ (LONG)(rightViewPort.X + 280),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 320),(LONG)(rightViewPort.Y + 270) };
	_build[78].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/5.png");
	SPRITEMANAGER->renderRectTexture(_build[78].tex, &_build[78].rc1, &_build[78].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)280, rightViewPort.Y + (DWORD)230);

	for (int i = 74; i < 79; i++)
	{
		if (_build[i].uiNumber == objectUi::OBJON)
		{
			_object[i]->render();
		}
	}
}

void objectClass::storm10()
{
	_build[79].rc2 ={ (LONG)(rightViewPort.X + 80),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 120),(LONG)(rightViewPort.Y + 270) };
	_build[79].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/1.png");
	SPRITEMANAGER->renderRectTexture(_build[79].tex, &_build[79].rc1, &_build[79].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)80, rightViewPort.Y + (DWORD)230);

	_build[80].rc2 ={ (LONG)(rightViewPort.X + 130),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 170),(LONG)(rightViewPort.Y + 270) };
	_build[80].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/2.png");
	SPRITEMANAGER->renderRectTexture(_build[80].tex, &_build[80].rc1, &_build[80].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)130, rightViewPort.Y + (DWORD)230);

	_build[81].rc2 ={ (LONG)(rightViewPort.X + 180),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 220),(LONG)(rightViewPort.Y + 270) };
	_build[81].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/3.png");
	SPRITEMANAGER->renderRectTexture(_build[81].tex, &_build[81].rc1, &_build[81].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)180, rightViewPort.Y + (DWORD)230);

	_build[82].rc2 ={ (LONG)(rightViewPort.X + 230),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 270),(LONG)(rightViewPort.Y + 270) };
	_build[82].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/4.png");
	SPRITEMANAGER->renderRectTexture(_build[82].tex, &_build[82].rc1, &_build[82].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)230, rightViewPort.Y + (DWORD)230);

	_build[83].rc2 ={ (LONG)(rightViewPort.X + 280),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 320),(LONG)(rightViewPort.Y + 270) };
	_build[83].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/5.png");
	SPRITEMANAGER->renderRectTexture(_build[83].tex, &_build[83].rc1, &_build[83].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)280, rightViewPort.Y + (DWORD)230);

	for (int i = 79; i < 84; i++)
	{
		if (_build[i].uiNumber == objectUi::OBJON)
		{
			_object[i]->render();
		}
	}
}

void objectClass::ruinstage1()
{
	_build[84].rc2 ={ (LONG)(rightViewPort.X + 80),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 120),(LONG)(rightViewPort.Y + 270) };
	_build[84].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/1.png");
	SPRITEMANAGER->renderRectTexture(_build[84].tex, &_build[84].rc1, &_build[84].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)80, rightViewPort.Y + (DWORD)230);

	_build[85].rc2 ={ (LONG)(rightViewPort.X + 130),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 170),(LONG)(rightViewPort.Y + 270) };
	_build[85].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/2.png");
	SPRITEMANAGER->renderRectTexture(_build[85].tex, &_build[85].rc1, &_build[85].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)130, rightViewPort.Y + (DWORD)230);

	_build[86].rc2 ={ (LONG)(rightViewPort.X + 180),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 220),(LONG)(rightViewPort.Y + 270) };
	_build[86].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/3.png");
	SPRITEMANAGER->renderRectTexture(_build[86].tex, &_build[86].rc1, &_build[86].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)180, rightViewPort.Y + (DWORD)230);

	_build[87].rc2 ={ (LONG)(rightViewPort.X + 230),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 270),(LONG)(rightViewPort.Y + 270) };
	_build[87].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/4.png");
	SPRITEMANAGER->renderRectTexture(_build[87].tex, &_build[87].rc1, &_build[87].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)230, rightViewPort.Y + (DWORD)230);

	_build[88].rc2 ={ (LONG)(rightViewPort.X + 280),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 320),(LONG)(rightViewPort.Y + 270) };
	_build[88].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/5.png");
	SPRITEMANAGER->renderRectTexture(_build[88].tex, &_build[88].rc1, &_build[88].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)280, rightViewPort.Y + (DWORD)230);

	_build[89].rc2 ={ (LONG)(rightViewPort.X + 80),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 120),(LONG)(rightViewPort.Y + 340) };
	_build[89].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/6.png");
	SPRITEMANAGER->renderRectTexture(_build[89].tex, &_build[89].rc1, &_build[89].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)80, rightViewPort.Y + (DWORD)300);

	_build[90].rc2 ={ (LONG)(rightViewPort.X + 130),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 170),(LONG)(rightViewPort.Y + 340) };
	_build[90].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/7.png");
	SPRITEMANAGER->renderRectTexture(_build[90].tex, &_build[90].rc1, &_build[90].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)130, rightViewPort.Y + (DWORD)300);

	_build[91].rc2 ={ (LONG)(rightViewPort.X + 180),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 220),(LONG)(rightViewPort.Y + 340) };
	_build[91].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/8.png");
	SPRITEMANAGER->renderRectTexture(_build[91].tex, &_build[91].rc1, &_build[91].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)180, rightViewPort.Y + (DWORD)300);

	_build[92].rc2 ={ (LONG)(rightViewPort.X + 230),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 270),(LONG)(rightViewPort.Y + 340) };
	_build[92].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/9.png");
	SPRITEMANAGER->renderRectTexture(_build[92].tex, &_build[92].rc1, &_build[92].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)230, rightViewPort.Y + (DWORD)300);

	_build[93].rc2 ={ (LONG)(rightViewPort.X + 280),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 320),(LONG)(rightViewPort.Y + 340) };
	_build[93].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/10.png");
	SPRITEMANAGER->renderRectTexture(_build[93].tex, &_build[93].rc1, &_build[93].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)280, rightViewPort.Y + (DWORD)300);

	_build[94].rc2 ={ (LONG)(rightViewPort.X + 80),(LONG)(rightViewPort.Y + 370),(LONG)(rightViewPort.X + 120),(LONG)(rightViewPort.Y + 410) };
	_build[94].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/11.png");
	SPRITEMANAGER->renderRectTexture(_build[94].tex, &_build[94].rc1, &_build[94].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)80, rightViewPort.Y + (DWORD)370);

	_build[95].rc2 ={ (LONG)(rightViewPort.X + 130),(LONG)(rightViewPort.Y + 370),(LONG)(rightViewPort.X + 170),(LONG)(rightViewPort.Y + 410) };
	_build[95].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/12.png");
	SPRITEMANAGER->renderRectTexture(_build[95].tex, &_build[95].rc1, &_build[95].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)130, rightViewPort.Y + (DWORD)370);

	_build[96].rc2 ={ (LONG)(rightViewPort.X + 180),(LONG)(rightViewPort.Y + 370),(LONG)(rightViewPort.X + 220),(LONG)(rightViewPort.Y + 410) };
	_build[96].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/13.png");
	SPRITEMANAGER->renderRectTexture(_build[96].tex, &_build[96].rc1, &_build[96].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)180, rightViewPort.Y + (DWORD)370);

	_build[97].rc2 ={ (LONG)(rightViewPort.X + 230),(LONG)(rightViewPort.Y + 370),(LONG)(rightViewPort.X + 270),(LONG)(rightViewPort.Y + 410) };
	_build[97].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/14.png");
	SPRITEMANAGER->renderRectTexture(_build[97].tex, &_build[97].rc1, &_build[97].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)230, rightViewPort.Y + (DWORD)370);

	for (int i = 84; i < 98; i++)
	{
		if (_build[i].uiNumber == objectUi::OBJON)
		{
			_object[i]->render();
		}
	}
}

void objectClass::ruinstage2()
{
	_build[98].rc2 ={ (LONG)(rightViewPort.X + 80),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 120),(LONG)(rightViewPort.Y + 270) };
	_build[98].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/1.png");
	SPRITEMANAGER->renderRectTexture(_build[98].tex, &_build[98].rc1, &_build[98].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)80, rightViewPort.Y + (DWORD)230);

	_build[99].rc2 ={ (LONG)(rightViewPort.X + 130),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 170),(LONG)(rightViewPort.Y + 270) };
	_build[99].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/2.png");
	SPRITEMANAGER->renderRectTexture(_build[99].tex, &_build[99].rc1, &_build[99].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)130, rightViewPort.Y + (DWORD)230);

	_build[100].rc2 ={ (LONG)(rightViewPort.X + 180),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 220),(LONG)(rightViewPort.Y + 270) };
	_build[100].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/3.png");
	SPRITEMANAGER->renderRectTexture(_build[100].tex, &_build[100].rc1, &_build[100].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)180, rightViewPort.Y + (DWORD)230);

	_build[101].rc2 ={ (LONG)(rightViewPort.X + 230),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 270),(LONG)(rightViewPort.Y + 270) };
	_build[101].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/4.png");
	SPRITEMANAGER->renderRectTexture(_build[101].tex, &_build[101].rc1, &_build[101].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)230, rightViewPort.Y + (DWORD)230);

	_build[102].rc2 ={ (LONG)(rightViewPort.X + 280),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 320),(LONG)(rightViewPort.Y + 270) };
	_build[102].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/5.png");
	SPRITEMANAGER->renderRectTexture(_build[102].tex, &_build[102].rc1, &_build[102].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)280, rightViewPort.Y + (DWORD)230);

	_build[103].rc2 ={ (LONG)(rightViewPort.X + 80),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 120),(LONG)(rightViewPort.Y + 340) };
	_build[103].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/6.png");
	SPRITEMANAGER->renderRectTexture(_build[103].tex, &_build[103].rc1, &_build[103].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)80, rightViewPort.Y + (DWORD)300);

	_build[104].rc2 ={ (LONG)(rightViewPort.X + 130),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 170),(LONG)(rightViewPort.Y + 340) };
	_build[104].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/7.png");
	SPRITEMANAGER->renderRectTexture(_build[104].tex, &_build[104].rc1, &_build[104].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)130, rightViewPort.Y + (DWORD)300);

	_build[105].rc2 ={ (LONG)(rightViewPort.X + 180),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 220),(LONG)(rightViewPort.Y + 340) };
	_build[105].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/8.png");
	SPRITEMANAGER->renderRectTexture(_build[105].tex, &_build[105].rc1, &_build[105].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)180, rightViewPort.Y + (DWORD)300);

	_build[106].rc2 ={ (LONG)(rightViewPort.X + 230),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 270),(LONG)(rightViewPort.Y + 340) };
	_build[106].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/9.png");
	SPRITEMANAGER->renderRectTexture(_build[106].tex, &_build[106].rc1, &_build[106].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)230, rightViewPort.Y + (DWORD)300);

	_build[107].rc2 ={ (LONG)(rightViewPort.X + 280),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 320),(LONG)(rightViewPort.Y + 340) };
	_build[107].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/10.png");
	SPRITEMANAGER->renderRectTexture(_build[107].tex, &_build[107].rc1, &_build[107].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)280, rightViewPort.Y + (DWORD)300);

	_build[108].rc2 ={ (LONG)(rightViewPort.X + 80),(LONG)(rightViewPort.Y + 370),(LONG)(rightViewPort.X + 120),(LONG)(rightViewPort.Y + 410) };
	_build[108].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/11.png");
	SPRITEMANAGER->renderRectTexture(_build[108].tex, &_build[108].rc1, &_build[108].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)80, rightViewPort.Y + (DWORD)370);

	_build[109].rc2 ={ (LONG)(rightViewPort.X + 130),(LONG)(rightViewPort.Y + 370),(LONG)(rightViewPort.X + 170),(LONG)(rightViewPort.Y + 410) };
	_build[109].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/12.png");
	SPRITEMANAGER->renderRectTexture(_build[109].tex, &_build[109].rc1, &_build[109].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)130, rightViewPort.Y + (DWORD)370);

	_build[110].rc2 ={ (LONG)(rightViewPort.X + 180),(LONG)(rightViewPort.Y + 370),(LONG)(rightViewPort.X + 220),(LONG)(rightViewPort.Y + 410) };
	_build[110].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/13.png");
	SPRITEMANAGER->renderRectTexture(_build[110].tex, &_build[110].rc1, &_build[110].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)180, rightViewPort.Y + (DWORD)370);

	_build[111].rc2 ={ (LONG)(rightViewPort.X + 230),(LONG)(rightViewPort.Y + 370),(LONG)(rightViewPort.X + 270),(LONG)(rightViewPort.Y + 410) };
	_build[111].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/14.png");
	SPRITEMANAGER->renderRectTexture(_build[111].tex, &_build[111].rc1, &_build[111].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)230, rightViewPort.Y + (DWORD)370);

	for (int i = 98; i < 112; i++)
	{
		if (_build[i].uiNumber == objectUi::OBJON)
		{
			_object[i]->render();
		}
	}
}

void objectClass::ruinstage3()
{
	_build[112].rc2 ={ (LONG)(rightViewPort.X + 80),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 120),(LONG)(rightViewPort.Y + 270) };
	_build[112].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/1.png");
	SPRITEMANAGER->renderRectTexture(_build[112].tex, &_build[112].rc1, &_build[112].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)80, rightViewPort.Y + (DWORD)230);

	_build[113].rc2 ={ (LONG)(rightViewPort.X + 130),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 170),(LONG)(rightViewPort.Y + 270) };
	_build[113].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/2.png");
	SPRITEMANAGER->renderRectTexture(_build[113].tex, &_build[113].rc1, &_build[113].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)130, rightViewPort.Y + (DWORD)230);

	_build[114].rc2 ={ (LONG)(rightViewPort.X + 180),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 220),(LONG)(rightViewPort.Y + 270) };
	_build[114].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/3.png");
	SPRITEMANAGER->renderRectTexture(_build[114].tex, &_build[114].rc1, &_build[114].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)180, rightViewPort.Y + (DWORD)230);

	_build[115].rc2 ={ (LONG)(rightViewPort.X + 230),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 270),(LONG)(rightViewPort.Y + 270) };
	_build[115].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/4.png");
	SPRITEMANAGER->renderRectTexture(_build[115].tex, &_build[115].rc1, &_build[115].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)230, rightViewPort.Y + (DWORD)230);

	_build[116].rc2 ={ (LONG)(rightViewPort.X + 280),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 320),(LONG)(rightViewPort.Y + 270) };
	_build[116].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/5.png");
	SPRITEMANAGER->renderRectTexture(_build[116].tex, &_build[116].rc1, &_build[116].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)280, rightViewPort.Y + (DWORD)230);

	_build[117].rc2 ={ (LONG)(rightViewPort.X + 80),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 120),(LONG)(rightViewPort.Y + 340) };
	_build[117].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/6.png");
	SPRITEMANAGER->renderRectTexture(_build[117].tex, &_build[117].rc1, &_build[117].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)80, rightViewPort.Y + (DWORD)300);

	_build[118].rc2 ={ (LONG)(rightViewPort.X + 130),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 170),(LONG)(rightViewPort.Y + 340) };
	_build[118].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/7.png");
	SPRITEMANAGER->renderRectTexture(_build[118].tex, &_build[118].rc1, &_build[118].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)130, rightViewPort.Y + (DWORD)300);

	_build[119].rc2 ={ (LONG)(rightViewPort.X + 180),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 220),(LONG)(rightViewPort.Y + 340) };
	_build[119].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/8.png");
	SPRITEMANAGER->renderRectTexture(_build[119].tex, &_build[119].rc1, &_build[119].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)180, rightViewPort.Y + (DWORD)300);

	_build[120].rc2 ={ (LONG)(rightViewPort.X + 230),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 270),(LONG)(rightViewPort.Y + 340) };
	_build[120].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/9.png");
	SPRITEMANAGER->renderRectTexture(_build[120].tex, &_build[120].rc1, &_build[120].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)230, rightViewPort.Y + (DWORD)300);

	_build[121].rc2 ={ (LONG)(rightViewPort.X + 280),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 320),(LONG)(rightViewPort.Y + 340) };
	_build[121].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/10.png");
	SPRITEMANAGER->renderRectTexture(_build[121].tex, &_build[121].rc1, &_build[121].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)280, rightViewPort.Y + (DWORD)300);

	for (int i = 112; i < 122; i++)
	{
		if (_build[i].uiNumber == objectUi::OBJON)
		{
			_object[i]->render();
		}
	}
}

void objectClass::ruinstage4()
{
	_build[122].rc2 ={ (LONG)(rightViewPort.X + 80),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 120),(LONG)(rightViewPort.Y + 270) };
	_build[122].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/1.png");
	SPRITEMANAGER->renderRectTexture(_build[122].tex, &_build[122].rc1, &_build[122].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)80, rightViewPort.Y + (DWORD)230);

	_build[123].rc2 ={ (LONG)(rightViewPort.X + 130),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 170),(LONG)(rightViewPort.Y + 270) };
	_build[123].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/2.png");
	SPRITEMANAGER->renderRectTexture(_build[123].tex, &_build[123].rc1, &_build[123].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)130, rightViewPort.Y + (DWORD)230);

	_build[124].rc2 ={ (LONG)(rightViewPort.X + 180),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 220),(LONG)(rightViewPort.Y + 270) };
	_build[124].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/3.png");
	SPRITEMANAGER->renderRectTexture(_build[124].tex, &_build[124].rc1, &_build[124].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)180, rightViewPort.Y + (DWORD)230);

	_build[125].rc2 ={ (LONG)(rightViewPort.X + 230),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 270),(LONG)(rightViewPort.Y + 270) };
	_build[125].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/4.png");
	SPRITEMANAGER->renderRectTexture(_build[125].tex, &_build[125].rc1, &_build[125].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)230, rightViewPort.Y + (DWORD)230);

	_build[126].rc2 ={ (LONG)(rightViewPort.X + 280),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 320),(LONG)(rightViewPort.Y + 270) };
	_build[126].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/5.png");
	SPRITEMANAGER->renderRectTexture(_build[126].tex, &_build[126].rc1, &_build[126].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)280, rightViewPort.Y + (DWORD)230);

	_build[127].rc2 ={ (LONG)(rightViewPort.X + 80),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 120),(LONG)(rightViewPort.Y + 340) };
	_build[127].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/6.png");
	SPRITEMANAGER->renderRectTexture(_build[127].tex, &_build[127].rc1, &_build[127].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)80, rightViewPort.Y + (DWORD)300);

	for (int i = 122; i < 128; i++)
	{
		if (_build[i].uiNumber == objectUi::OBJON)
		{
			_object[i]->render();
		}
	}
}

void objectClass::ruinstage5()
{
	_build[128].rc2 ={ (LONG)(rightViewPort.X + 80),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 120),(LONG)(rightViewPort.Y + 270) };
	_build[128].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/1.png");
	SPRITEMANAGER->renderRectTexture(_build[128].tex, &_build[128].rc1, &_build[128].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)80, rightViewPort.Y + (DWORD)230);

	_build[129].rc2 ={ (LONG)(rightViewPort.X + 130),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 170),(LONG)(rightViewPort.Y + 270) };
	_build[129].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/2.png");
	SPRITEMANAGER->renderRectTexture(_build[129].tex, &_build[129].rc1, &_build[129].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)130, rightViewPort.Y + (DWORD)230);

	_build[130].rc2 ={ (LONG)(rightViewPort.X + 180),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 220),(LONG)(rightViewPort.Y + 270) };
	_build[130].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/3.png");
	SPRITEMANAGER->renderRectTexture(_build[130].tex, &_build[130].rc1, &_build[130].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)180, rightViewPort.Y + (DWORD)230);

	_build[131].rc2 ={ (LONG)(rightViewPort.X + 230),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 270),(LONG)(rightViewPort.Y + 270) };
	_build[131].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/4.png");
	SPRITEMANAGER->renderRectTexture(_build[131].tex, &_build[131].rc1, &_build[131].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)230, rightViewPort.Y + (DWORD)230);

	_build[132].rc2 ={ (LONG)(rightViewPort.X + 280),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 320),(LONG)(rightViewPort.Y + 270) };
	_build[132].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/5.png");
	SPRITEMANAGER->renderRectTexture(_build[132].tex, &_build[132].rc1, &_build[132].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)280, rightViewPort.Y + (DWORD)230);

	_build[133].rc2 ={ (LONG)(rightViewPort.X + 80),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 120),(LONG)(rightViewPort.Y + 340) };
	_build[133].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/6.png");
	SPRITEMANAGER->renderRectTexture(_build[133].tex, &_build[133].rc1, &_build[133].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)80, rightViewPort.Y + (DWORD)300);

	_build[134].rc2 ={ (LONG)(rightViewPort.X + 130),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 170),(LONG)(rightViewPort.Y + 340) };
	_build[134].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/7.png");
	SPRITEMANAGER->renderRectTexture(_build[134].tex, &_build[134].rc1, &_build[134].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)130, rightViewPort.Y + (DWORD)300);

	_build[135].rc2 ={ (LONG)(rightViewPort.X + 180),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 220),(LONG)(rightViewPort.Y + 340) };
	_build[135].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/8.png");
	SPRITEMANAGER->renderRectTexture(_build[135].tex, &_build[135].rc1, &_build[135].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)180, rightViewPort.Y + (DWORD)300);

	_build[136].rc2 ={ (LONG)(rightViewPort.X + 230),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 270),(LONG)(rightViewPort.Y + 340) };
	_build[136].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/9.png");
	SPRITEMANAGER->renderRectTexture(_build[136].tex, &_build[136].rc1, &_build[136].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)230, rightViewPort.Y + (DWORD)300);

	for (int i = 128; i < 137; i++)
	{
		if (_build[i].uiNumber == objectUi::OBJON)
		{
			_object[i]->render();
		}
	}
}

void objectClass::ruinstage6()
{
	_build[137].rc2 ={ (LONG)(rightViewPort.X + 80),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 120),(LONG)(rightViewPort.Y + 270) };
	_build[137].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/1.png");
	SPRITEMANAGER->renderRectTexture(_build[137].tex, &_build[137].rc1, &_build[137].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)80, rightViewPort.Y + (DWORD)230);

	_build[138].rc2 ={ (LONG)(rightViewPort.X + 130),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 170),(LONG)(rightViewPort.Y + 270) };
	_build[138].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/2.png");
	SPRITEMANAGER->renderRectTexture(_build[138].tex, &_build[138].rc1, &_build[138].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)130, rightViewPort.Y + (DWORD)230);

	_build[139].rc2 ={ (LONG)(rightViewPort.X + 180),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 220),(LONG)(rightViewPort.Y + 270) };
	_build[139].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/3.png");
	SPRITEMANAGER->renderRectTexture(_build[139].tex, &_build[139].rc1, &_build[139].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)180, rightViewPort.Y + (DWORD)230);

	_build[140].rc2 ={ (LONG)(rightViewPort.X + 230),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 270),(LONG)(rightViewPort.Y + 270) };
	_build[140].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/4.png");
	SPRITEMANAGER->renderRectTexture(_build[140].tex, &_build[140].rc1, &_build[140].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)230, rightViewPort.Y + (DWORD)230);

	for (int i = 137; i < 141; i++)
	{
		if (_build[i].uiNumber == objectUi::OBJON)
		{
			_object[i]->render();
		}
	}
}

void objectClass::ruinstage7()
{
	_build[141].rc2 ={ (LONG)(rightViewPort.X + 80),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 120),(LONG)(rightViewPort.Y + 270) };
	_build[141].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/1.png");
	SPRITEMANAGER->renderRectTexture(_build[141].tex, &_build[141].rc1, &_build[141].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)80, rightViewPort.Y + (DWORD)230);

	_build[142].rc2 ={ (LONG)(rightViewPort.X + 130),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 170),(LONG)(rightViewPort.Y + 270) };
	_build[142].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/2.png");
	SPRITEMANAGER->renderRectTexture(_build[142].tex, &_build[142].rc1, &_build[142].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)130, rightViewPort.Y + (DWORD)230);

	_build[143].rc2 ={ (LONG)(rightViewPort.X + 180),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 220),(LONG)(rightViewPort.Y + 270) };
	_build[143].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/3.png");
	SPRITEMANAGER->renderRectTexture(_build[143].tex, &_build[143].rc1, &_build[143].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)180, rightViewPort.Y + (DWORD)230);

	_build[144].rc2 ={ (LONG)(rightViewPort.X + 230),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 270),(LONG)(rightViewPort.Y + 270) };
	_build[144].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/4.png");
	SPRITEMANAGER->renderRectTexture(_build[144].tex, &_build[144].rc1, &_build[144].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)230, rightViewPort.Y + (DWORD)230);

	_build[145].rc2 ={ (LONG)(rightViewPort.X + 280),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 320),(LONG)(rightViewPort.Y + 270) };
	_build[145].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/5.png");
	SPRITEMANAGER->renderRectTexture(_build[145].tex, &_build[145].rc1, &_build[145].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)280, rightViewPort.Y + (DWORD)230);

	_build[146].rc2 ={ (LONG)(rightViewPort.X + 80),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 120),(LONG)(rightViewPort.Y + 340) };
	_build[146].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/6.png");
	SPRITEMANAGER->renderRectTexture(_build[146].tex, &_build[146].rc1, &_build[146].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)80, rightViewPort.Y + (DWORD)300);

	_build[147].rc2 ={ (LONG)(rightViewPort.X + 130),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 170),(LONG)(rightViewPort.Y + 340) };
	_build[147].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/7.png");
	SPRITEMANAGER->renderRectTexture(_build[147].tex, &_build[147].rc1, &_build[147].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)130, rightViewPort.Y + (DWORD)300);

	_build[148].rc2 ={ (LONG)(rightViewPort.X + 180),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 220),(LONG)(rightViewPort.Y + 340) };
	_build[148].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/8.png");
	SPRITEMANAGER->renderRectTexture(_build[148].tex, &_build[148].rc1, &_build[148].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)180, rightViewPort.Y + (DWORD)300);

	_build[149].rc2 ={ (LONG)(rightViewPort.X + 230),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 270),(LONG)(rightViewPort.Y + 340) };
	_build[149].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/9.png");
	SPRITEMANAGER->renderRectTexture(_build[149].tex, &_build[149].rc1, &_build[149].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)230, rightViewPort.Y + (DWORD)300);

	_build[150].rc2 ={ (LONG)(rightViewPort.X + 280),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 320),(LONG)(rightViewPort.Y + 340) };
	_build[150].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/10.png");
	SPRITEMANAGER->renderRectTexture(_build[150].tex, &_build[150].rc1, &_build[150].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)280, rightViewPort.Y + (DWORD)300);

	_build[151].rc2 ={ (LONG)(rightViewPort.X + 80),(LONG)(rightViewPort.Y + 370),(LONG)(rightViewPort.X + 120),(LONG)(rightViewPort.Y + 410) };
	_build[151].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/11.png");
	SPRITEMANAGER->renderRectTexture(_build[151].tex, &_build[151].rc1, &_build[151].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)80, rightViewPort.Y + (DWORD)370);

	for (int i = 141; i < 152; i++)
	{
		if (_build[i].uiNumber == objectUi::OBJON)
		{
			_object[i]->render();
		}
	}
}

void objectClass::piramid1()
{
	_build[152].rc2 ={ (LONG)(rightViewPort.X + 80),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 120),(LONG)(rightViewPort.Y + 270) };
	_build[152].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/1.png");
	SPRITEMANAGER->renderRectTexture(_build[152].tex, &_build[152].rc1, &_build[152].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)80, rightViewPort.Y + (DWORD)230);

	_build[153].rc2 ={ (LONG)(rightViewPort.X + 130),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 170),(LONG)(rightViewPort.Y + 270) };
	_build[153].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/2.png");
	SPRITEMANAGER->renderRectTexture(_build[153].tex, &_build[153].rc1, &_build[153].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)130, rightViewPort.Y + (DWORD)230);

	_build[154].rc2 ={ (LONG)(rightViewPort.X + 180),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 220),(LONG)(rightViewPort.Y + 270) };
	_build[154].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/3.png");
	SPRITEMANAGER->renderRectTexture(_build[154].tex, &_build[154].rc1, &_build[154].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)180, rightViewPort.Y + (DWORD)230);

	_build[155].rc2 ={ (LONG)(rightViewPort.X + 230),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 270),(LONG)(rightViewPort.Y + 270) };
	_build[155].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/4.png");
	SPRITEMANAGER->renderRectTexture(_build[155].tex, &_build[155].rc1, &_build[155].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)230, rightViewPort.Y + (DWORD)230);

	_build[156].rc2 ={ (LONG)(rightViewPort.X + 280),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 320),(LONG)(rightViewPort.Y + 270) };
	_build[156].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/5.png");
	SPRITEMANAGER->renderRectTexture(_build[156].tex, &_build[156].rc1, &_build[156].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)280, rightViewPort.Y + (DWORD)230);

	_build[157].rc2 ={ (LONG)(rightViewPort.X + 80),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 120),(LONG)(rightViewPort.Y + 340) };
	_build[157].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/6.png");
	SPRITEMANAGER->renderRectTexture(_build[157].tex, &_build[157].rc1, &_build[157].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)80, rightViewPort.Y + (DWORD)300);

	_build[158].rc2 ={ (LONG)(rightViewPort.X + 130),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 170),(LONG)(rightViewPort.Y + 340) };
	_build[158].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/7.png");
	SPRITEMANAGER->renderRectTexture(_build[158].tex, &_build[158].rc1, &_build[158].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)130, rightViewPort.Y + (DWORD)300);

	_build[159].rc2 ={ (LONG)(rightViewPort.X + 180),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 220),(LONG)(rightViewPort.Y + 340) };
	_build[159].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/8.png");
	SPRITEMANAGER->renderRectTexture(_build[159].tex, &_build[159].rc1, &_build[159].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)180, rightViewPort.Y + (DWORD)300);

	_build[160].rc2 ={ (LONG)(rightViewPort.X + 230),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 270),(LONG)(rightViewPort.Y + 340) };
	_build[160].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/9.png");
	SPRITEMANAGER->renderRectTexture(_build[160].tex, &_build[160].rc1, &_build[160].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)230, rightViewPort.Y + (DWORD)300);

	_build[161].rc2 ={ (LONG)(rightViewPort.X + 280),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 320),(LONG)(rightViewPort.Y + 340) };
	_build[161].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/10.png");
	SPRITEMANAGER->renderRectTexture(_build[161].tex, &_build[161].rc1, &_build[161].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)280, rightViewPort.Y + (DWORD)300);

	_build[162].rc2 ={ (LONG)(rightViewPort.X + 80),(LONG)(rightViewPort.Y + 370),(LONG)(rightViewPort.X + 120),(LONG)(rightViewPort.Y + 410) };
	_build[162].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/11.png");
	SPRITEMANAGER->renderRectTexture(_build[162].tex, &_build[162].rc1, &_build[162].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)80, rightViewPort.Y + (DWORD)370);

	_build[163].rc2 ={ (LONG)(rightViewPort.X + 130),(LONG)(rightViewPort.Y + 370),(LONG)(rightViewPort.X + 170),(LONG)(rightViewPort.Y + 410) };
	_build[163].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/12.png");
	SPRITEMANAGER->renderRectTexture(_build[163].tex, &_build[163].rc1, &_build[163].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)130, rightViewPort.Y + (DWORD)370);

	_build[164].rc2 ={ (LONG)(rightViewPort.X + 180),(LONG)(rightViewPort.Y + 370),(LONG)(rightViewPort.X + 220),(LONG)(rightViewPort.Y + 410) };
	_build[164].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/13.png");
	SPRITEMANAGER->renderRectTexture(_build[164].tex, &_build[164].rc1, &_build[164].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)180, rightViewPort.Y + (DWORD)370);

	for (int i = 152; i < 165; i++)
	{
		if (_build[i].uiNumber == objectUi::OBJON)
		{
			_object[i]->render();
		}
	}
}

void objectClass::piramid2()
{
	_build[165].rc2 ={ (LONG)(rightViewPort.X + 80),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 120),(LONG)(rightViewPort.Y + 270) };
	_build[165].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/1.png");
	SPRITEMANAGER->renderRectTexture(_build[165].tex, &_build[165].rc1, &_build[165].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)80, rightViewPort.Y + (DWORD)230);

	_build[166].rc2 ={ (LONG)(rightViewPort.X + 130),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 170),(LONG)(rightViewPort.Y + 270) };
	_build[166].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/2.png");
	SPRITEMANAGER->renderRectTexture(_build[166].tex, &_build[166].rc1, &_build[166].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)130, rightViewPort.Y + (DWORD)230);

	_build[167].rc2 ={ (LONG)(rightViewPort.X + 180),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 220),(LONG)(rightViewPort.Y + 270) };
	_build[167].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/3.png");
	SPRITEMANAGER->renderRectTexture(_build[167].tex, &_build[167].rc1, &_build[167].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)180, rightViewPort.Y + (DWORD)230);

	_build[168].rc2 ={ (LONG)(rightViewPort.X + 230),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 270),(LONG)(rightViewPort.Y + 270) };
	_build[168].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/4.png");
	SPRITEMANAGER->renderRectTexture(_build[168].tex, &_build[168].rc1, &_build[168].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)230, rightViewPort.Y + (DWORD)230);

	_build[169].rc2 ={ (LONG)(rightViewPort.X + 280),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 320),(LONG)(rightViewPort.Y + 270) };
	_build[169].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/5.png");
	SPRITEMANAGER->renderRectTexture(_build[169].tex, &_build[169].rc1, &_build[169].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)280, rightViewPort.Y + (DWORD)230);

	_build[170].rc2 ={ (LONG)(rightViewPort.X + 80),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 120),(LONG)(rightViewPort.Y + 340) };
	_build[170].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/6.png");
	SPRITEMANAGER->renderRectTexture(_build[170].tex, &_build[170].rc1, &_build[170].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)80, rightViewPort.Y + (DWORD)300);

	_build[171].rc2 ={ (LONG)(rightViewPort.X + 130),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 170),(LONG)(rightViewPort.Y + 340) };
	_build[171].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/7.png");
	SPRITEMANAGER->renderRectTexture(_build[171].tex, &_build[171].rc1, &_build[171].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)130, rightViewPort.Y + (DWORD)300);

	_build[172].rc2 ={ (LONG)(rightViewPort.X + 180),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 220),(LONG)(rightViewPort.Y + 340) };
	_build[172].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/8.png");
	SPRITEMANAGER->renderRectTexture(_build[172].tex, &_build[172].rc1, &_build[172].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)180, rightViewPort.Y + (DWORD)300);

	_build[173].rc2 ={ (LONG)(rightViewPort.X + 230),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 270),(LONG)(rightViewPort.Y + 340) };
	_build[173].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/9.png");
	SPRITEMANAGER->renderRectTexture(_build[173].tex, &_build[173].rc1, &_build[173].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)230, rightViewPort.Y + (DWORD)300);

	_build[174].rc2 ={ (LONG)(rightViewPort.X + 280),(LONG)(rightViewPort.Y + 300),(LONG)(rightViewPort.X + 320),(LONG)(rightViewPort.Y + 340) };
	_build[174].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/10.png");
	SPRITEMANAGER->renderRectTexture(_build[174].tex, &_build[174].rc1, &_build[174].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)280, rightViewPort.Y + (DWORD)300);

	_build[175].rc2 ={ (LONG)(rightViewPort.X + 80),(LONG)(rightViewPort.Y + 370),(LONG)(rightViewPort.X + 120),(LONG)(rightViewPort.Y + 410) };
	_build[175].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/11.png");
	SPRITEMANAGER->renderRectTexture(_build[175].tex, &_build[175].rc1, &_build[175].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)80, rightViewPort.Y + (DWORD)370);

	_build[176].rc2 ={ (LONG)(rightViewPort.X + 130),(LONG)(rightViewPort.Y + 370),(LONG)(rightViewPort.X + 170),(LONG)(rightViewPort.Y + 410) };
	_build[176].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/12.png");
	SPRITEMANAGER->renderRectTexture(_build[176].tex, &_build[176].rc1, &_build[176].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)130, rightViewPort.Y + (DWORD)370);

	_build[177].rc2 ={ (LONG)(rightViewPort.X + 180),(LONG)(rightViewPort.Y + 370),(LONG)(rightViewPort.X + 220),(LONG)(rightViewPort.Y + 410) };
	_build[177].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/13.png");
	SPRITEMANAGER->renderRectTexture(_build[177].tex, &_build[177].rc1, &_build[177].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)180, rightViewPort.Y + (DWORD)370);

	for (int i = 165; i < 178; i++)
	{
		if (_build[i].uiNumber == objectUi::OBJON)
		{
			_object[i]->render();
		}
	}
}

void objectClass::piramid3()
{
	_build[178].rc2 ={ (LONG)(rightViewPort.X + 80),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 120),(LONG)(rightViewPort.Y + 270) };
	_build[178].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/1.png");
	SPRITEMANAGER->renderRectTexture(_build[178].tex, &_build[178].rc1, &_build[178].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)80, rightViewPort.Y + (DWORD)230);

	_build[179].rc2 ={ (LONG)(rightViewPort.X + 130),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 170),(LONG)(rightViewPort.Y + 270) };
	_build[179].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/2.png");
	SPRITEMANAGER->renderRectTexture(_build[179].tex, &_build[179].rc1, &_build[179].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)130, rightViewPort.Y + (DWORD)230);

	_build[180].rc2 ={ (LONG)(rightViewPort.X + 180),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 220),(LONG)(rightViewPort.Y + 270) };
	_build[180].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/3.png");
	SPRITEMANAGER->renderRectTexture(_build[180].tex, &_build[180].rc1, &_build[180].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)180, rightViewPort.Y + (DWORD)230);

	_build[181].rc2 ={ (LONG)(rightViewPort.X + 230),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 270),(LONG)(rightViewPort.Y + 270) };
	_build[181].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/4.png");
	SPRITEMANAGER->renderRectTexture(_build[181].tex, &_build[181].rc1, &_build[181].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)230, rightViewPort.Y + (DWORD)230);

	_build[182].rc2 ={ (LONG)(rightViewPort.X + 280),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 320),(LONG)(rightViewPort.Y + 270) };
	_build[182].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/5.png");
	SPRITEMANAGER->renderRectTexture(_build[182].tex, &_build[182].rc1, &_build[182].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)280, rightViewPort.Y + (DWORD)230);

	for (int i = 178; i < 183; i++)
	{
		if (_build[i].uiNumber == objectUi::OBJON)
		{
			_object[i]->render();
		}
	}
}

void objectClass::piramid4()
{
	_build[183].rc2 ={ (LONG)(rightViewPort.X + 80),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 120),(LONG)(rightViewPort.Y + 270) };
	_build[183].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/1.png");
	SPRITEMANAGER->renderRectTexture(_build[183].tex, &_build[183].rc1, &_build[183].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)80, rightViewPort.Y + (DWORD)230);

	_build[184].rc2 ={ (LONG)(rightViewPort.X + 130),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 170),(LONG)(rightViewPort.Y + 270) };
	_build[184].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/2.png");
	SPRITEMANAGER->renderRectTexture(_build[184].tex, &_build[184].rc1, &_build[184].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)130, rightViewPort.Y + (DWORD)230);

	_build[185].rc2 ={ (LONG)(rightViewPort.X + 180),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 220),(LONG)(rightViewPort.Y + 270) };
	_build[185].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/3.png");
	SPRITEMANAGER->renderRectTexture(_build[185].tex, &_build[185].rc1, &_build[185].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)180, rightViewPort.Y + (DWORD)230);

	_build[186].rc2 ={ (LONG)(rightViewPort.X + 230),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 270),(LONG)(rightViewPort.Y + 270) };
	_build[186].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/4.png");
	SPRITEMANAGER->renderRectTexture(_build[186].tex, &_build[186].rc1, &_build[186].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)230, rightViewPort.Y + (DWORD)230);

	_build[187].rc2 ={ (LONG)(rightViewPort.X + 280),(LONG)(rightViewPort.Y + 230),(LONG)(rightViewPort.X + 320),(LONG)(rightViewPort.Y + 270) };
	_build[187].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/5.png");
	SPRITEMANAGER->renderRectTexture(_build[187].tex, &_build[187].rc1, &_build[187].rc2, 0, 0, 64, 64, rightViewPort.X + (DWORD)280, rightViewPort.Y + (DWORD)230);

	for (int i = 183; i < 188; i++)
	{
		if (_build[i].uiNumber == objectUi::OBJON)
		{
			_object[i]->render();
		}
	}
}
