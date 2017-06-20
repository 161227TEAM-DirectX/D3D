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
	//라이트 설정
	lightDirection* directionLight = new lightDirection; 
	directionLight->_transform->LookDirection(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	directionLight->_color = D3DXCOLOR(1, 1, 1, 1);
	directionLight->_intensity = 2.0f;

	//빛벡터에 directionLight담기
	_light.push_back(directionLight);

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

	_object[0]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/1.build/1/1.X", scale));
	_object[1]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/1.build/2/2.X", scale));
	_object[2]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/1.build/3/3.X", scale));
	_object[3]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/1.build/4/4.X", scale));
	_object[4]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/1.build/5/5.X", scale));
	_object[5]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/1.build/6/6.X", scale));
	_object[6]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/1.build/7/7.X", scale));
	_object[7]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/1.build/8/8.X", scale));
	_object[8]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/1.build/9/9.X", scale));
	_object[9]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/1.build/10/10.X", scale));
	_object[10]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/1.build/11/11.X", scale));
	_object[11]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/1.build/12/12.X", scale));
	_object[12]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/1.build/13/13.X", scale));
	_object[13]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/1.build/14/14.X", scale));
	_object[14]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/1.build/15/15.X", scale));
	_object[15]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/1.build/16/16.X", scale));

	_object[17]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/2.townfence/1/1.X", scale));
	_object[18]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/2.townfence/2/2.X", scale));
	_object[19]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/2.townfence/3/3.X", scale));
	_object[20]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/2.townfence/4/4.X", scale));
	_object[21]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/2.townfence/5/5.X", scale));
	_object[22]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/2.townfence/6/6.X", scale));
	_object[23]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/2.townfence/7/7.X", scale));
	_object[24]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/2.townfence/8/8.X", scale));
	_object[25]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/2.townfence/9/9.X", scale));

	_object[26]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/3.tree/1/1.X", scale));
	_object[27]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/3.tree/2/2.X", scale));
	_object[28]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/3.tree/3/3.X", scale));
	_object[29]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/3.tree/4/4.X", scale));
	_object[30]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/3.tree/5/5.X", scale));
	_object[31]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/3.tree/6/6.X", scale));
	_object[32]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/3.tree/7/7.X", scale));

	_object[34]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/4.townObject/1/1.X", scale));
	_object[35]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/4.townObject/2/2.X", scale));
	_object[36]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/4.townObject/3/3.X", scale));
	_object[37]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/4.townObject/4/4.X", scale));
	_object[38]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/4.townObject/5/5.X", scale));
	_object[39]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/4.townObject/6/6.X", scale));
	_object[40]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/4.townObject/7/7.X", scale));
	_object[41]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/4.townObject/8/8.X", scale));
	_object[42]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/4.townObject/9/9.X", scale));
	_object[43]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/4.townObject/10/10.X", scale));
	_object[44]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/4.townObject/11/11.X", scale));
	_object[45]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/4.townObject/12/12.X", scale));
	_object[46]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/4.townObject/13/13.X", scale));
	_object[47]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/4.townObject/14/14.X", scale));
	_object[48]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/4.townObject/15/15.X", scale));

	_object[50]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/5.townSmallFence/1/1.X", scale));
	_object[51]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/5.townSmallFence/2/2.X", scale));
	_object[52]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/5.townSmallFence/3/3.X", scale));
	_object[53]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/5.townSmallFence/4/4.X", scale));
	_object[54]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/5.townSmallFence/5/5.X", scale));
	_object[55]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/5.townSmallFence/6/6.X", scale));

	_object[56]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/6.boxObject/1/1.X", scale));
	_object[57]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/6.boxObject/2/2.X", scale));
	_object[58]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/6.boxObject/3/3.X", scale));
	_object[59]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/6.boxObject/4/4.X", scale));
	_object[60]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/6.boxObject/5/5.X", scale));
	_object[61]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/6.boxObject/6/6.X", scale));

	_object[62]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/7.planterBox/1/1.X", scale));
	_object[63]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/7.planterBox/2/2.X", scale));
	_object[64]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/7.planterBox/3/3.X", scale));
	_object[65]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/7.planterBox/4/4.X", scale));
	_object[66]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/7.planterBox/5/5.X", scale));
	_object[67]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/7.planterBox/6/6.X", scale));

	_object[68]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/8.memorial stone/1/1.X", scale));
	_object[69]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/8.memorial stone/2/2.X", scale));
	_object[70]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/8.memorial stone/3/3.X", scale));
	_object[71]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/8.memorial stone/4/4.X", scale));
	_object[72]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/8.memorial stone/5/5.X", scale));
	_object[73]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/8.memorial stone/6/6.X", scale));

	_object[74]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/9.shopsign/1/1.X", scale));
	_object[75]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/9.shopsign/2/2.X", scale));
	_object[76]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/9.shopsign/3/3.X", scale));
	_object[77]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/9.shopsign/4/4.X", scale));
	_object[78]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/9.shopsign/5/5.X", scale));

	_object[79]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/10.lowWall/1/1.X", scale));
	_object[80]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/10.lowWall/2/2.X", scale));
	_object[81]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/10.lowWall/3/3.X", scale));
	_object[82]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/10.lowWall/4/4.X", scale));
	_object[83]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/10.lowWall/5/5.X", scale));

	_object[84]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/1/1.X", scale));
	_object[85]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/2/2.X", scale));
	_object[86]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/3/3.X", scale));
	_object[87]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/4/4.X", scale));
	_object[88]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/5/5.X", scale));
	_object[89]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/6/6.X", scale));
	_object[90]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/7/7.X", scale));
	_object[91]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/8/8.X", scale));
	_object[92]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/9/9.X", scale));
	_object[93]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/10/10.X", scale));
	_object[94]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/11/11.X", scale));
	_object[95]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/12/12.X", scale));
	_object[96]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/13/13.X", scale));
	_object[97]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/14/14.X", scale));

	_object[98]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/1/1.X", scale));
	_object[99]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/2/2.X", scale));
	_object[100]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/3/3.X", scale));
	_object[101]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/4/4.X", scale));
	_object[102]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/5/5.X", scale));
	_object[103]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/6/6.X", scale));
	_object[104]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/7/7.X", scale));
	_object[105]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/8/8.X", scale));
	_object[106]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/9/9.X", scale));
	_object[107]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/10/10.X", scale));
	_object[108]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/11/11.X", scale));
	_object[109]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/12/12.X", scale));
	_object[110]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/13/13.X", scale));
	_object[111]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/14/14.X", scale));

	_object[112]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/3.ruinStageRock/1/1.X", scale));
	_object[113]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/3.ruinStageRock/2/2.X", scale));
	_object[114]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/3.ruinStageRock/3/3.X", scale));
	_object[115]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/3.ruinStageRock/4/4.X", scale));
	_object[116]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/3.ruinStageRock/5/5.X", scale));
	_object[117]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/3.ruinStageRock/6/6.X", scale));
	_object[118]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/3.ruinStageRock/7/7.X", scale));
	_object[119]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/3.ruinStageRock/8/8.X", scale));
	_object[120]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/3.ruinStageRock/9/9.X", scale));
	_object[121]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/3.ruinStageRock/10/10.X", scale));

	_object[122]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/4.ruinStageSpider/1/1.X", scale));
	_object[123]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/4.ruinStageSpider/2/2.X", scale));
	_object[124]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/4.ruinStageSpider/3/3.X", scale));
	_object[125]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/4.ruinStageSpider/4/4.X", scale));
	_object[126]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/4.ruinStageSpider/5/5.X", scale));
	_object[127]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/4.ruinStageSpider/6/6.X", scale));

	_object[128]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/5.ruinStageTree/1/1.X", scale));
	_object[129]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/5.ruinStageTree/2/2.X", scale));
	_object[130]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/5.ruinStageTree/3/3.X", scale));
	_object[131]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/5.ruinStageTree/4/4.X", scale));
	_object[132]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/5.ruinStageTree/5/5.X", scale));
	_object[133]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/5.ruinStageTree/6/6.X", scale));
	_object[134]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/5.ruinStageTree/7/7.X", scale));
	_object[135]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/5.ruinStageTree/8/8.X", scale));
	_object[136]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/5.ruinStageTree/9/9.X", scale));

	_object[137]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/6.ruinStagePiramide/1/1.X", scale));
	_object[138]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/6.ruinStagePiramide/2/2.X", scale));
	_object[139]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/6.ruinStagePiramide/3/3.X", scale));
	_object[140]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/6.ruinStagePiramide/4/4.X", scale));

	_object[141]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/7.ruinYelloPyeheo/1/1.X", scale));
	_object[142]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/7.ruinYelloPyeheo/2/2.X", scale));
	_object[143]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/7.ruinYelloPyeheo/3/3.X", scale));
	_object[144]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/7.ruinYelloPyeheo/4/4.X", scale));
	_object[145]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/7.ruinYelloPyeheo/5/5.X", scale));
	_object[146]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/7.ruinYelloPyeheo/6/6.X", scale));
	_object[147]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/7.ruinYelloPyeheo/7/7.X", scale));
	_object[148]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/7.ruinYelloPyeheo/8/8.X", scale));
	_object[149]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/7.ruinYelloPyeheo/9/9.X", scale));
	_object[150]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/7.ruinYelloPyeheo/10/10.X", scale));
	_object[151]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/7.ruinYelloPyeheo/11/11.X", scale));

	_object[152]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/1.piramidBuild/1/1.X", scale));
	_object[153]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/1.piramidBuild/2/2.X", scale));
	_object[154]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/1.piramidBuild/3/3.X", scale));
	_object[155]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/1.piramidBuild/4/4.X", scale));
	_object[156]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/1.piramidBuild/5/5.X", scale));
	_object[157]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/1.piramidBuild/6/6.X", scale));
	_object[158]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/1.piramidBuild/7/7.X", scale));
	_object[159]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/1.piramidBuild/8/8.X", scale));
	_object[160]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/1.piramidBuild/9/9.X", scale));
	_object[161]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/1.piramidBuild/10/10.X", scale));
	_object[162]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/1.piramidBuild/11/11.X", scale));
	_object[163]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/1.piramidBuild/12/12.X", scale));
	_object[164]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/1.piramidBuild/13/13.X", scale));

	_object[165]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/2.piramidObject/15/15.X", scale));
	_object[166]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/2.piramidObject/14/14.X", scale));
	_object[167]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/2.piramidObject/3/3.X", scale));
	_object[168]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/2.piramidObject/4/4.X", scale));
	_object[169]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/2.piramidObject/5/5.X", scale));
	_object[170]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/2.piramidObject/6/6.X", scale));
	_object[171]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/2.piramidObject/7/7.X", scale));
	_object[172]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/2.piramidObject/8/8.X", scale));
	_object[173]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/2.piramidObject/9/9.X", scale));
	_object[174]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/2.piramidObject/10/10.X", scale));
	_object[175]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/2.piramidObject/11/11.X", scale));
	_object[176]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/2.piramidObject/12/12.X", scale));
	_object[177]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/2.piramidObject/13/13.X", scale));

	_object[178]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/3.piramidSmallObject/1/1.X", scale));
	_object[179]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/3.piramidSmallObject/2/2.X", scale));
	_object[180]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/3.piramidSmallObject/3/3.X", scale));
	_object[181]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/3.piramidSmallObject/4/4.X", scale));
	_object[182]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/3.piramidSmallObject/5/5.X", scale));

	_object[183]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/4.piramidRock/1/1.X", scale));
	_object[184]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/4.piramidRock/2/2.X", scale));
	_object[185]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/4.piramidRock/3/3.X", scale));
	_object[186]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/4.piramidRock/4/4.X", scale));
	_object[187]->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/4.piramidRock/5/5.X", scale));

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
	D3DXMATRIXA16 matLights[10];
	for (int i = 0; i < _light.size(); i++)
	{
		matLights[i] = _light[i]->getLightMatrix();
	}

	//셰이더에 라이트 세팅
	xMeshStatic::_staticMeshEffect->SetMatrixArray("matLights", matLights, 10);
	xMeshStatic::_staticMeshEffect->SetInt("LightNum", _light.size());

	//세이더에 카메라 세팅
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
