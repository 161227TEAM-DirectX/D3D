#include "stdafx.h"
#include "mapObject.h"


mapObject::mapObject()
{
	
}


mapObject::~mapObject()
{
}

HRESULT mapObject::objectinit()
{
	//라이트 설정
	_directionLight = new lightDirection;
	_directionLight->_transform->RotateWorld(D3DXToRadian(90), 0, 0);
	_directionLight->_color = D3DXCOLOR(1, 1, 1, 1);
	_directionLight->_intensity = 2.0f;

	return S_OK;
}

void mapObject::objectUpdate()
{
//	_mainCamera.DefaultControl(_timeDelta, 1);
//	_mainCamera.updateCamToDevice();
}

void mapObject::objectSet(int objectNumber, baseObject * tempObect, D3DXMATRIX matRotate, float m_fPickposX, float m_fPickposY, float m_fPickposZ, float mapScale, float mapRotation)
{
	D3DXMatrixRotationY(&matRotate, D3DXToRadian(180));

	if (objectNumber == 1) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/1.build/1/1.x", &matRotate));
	if (objectNumber == 2) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/1.build/2/2.x", &matRotate));
	if (objectNumber == 3) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/1.build/3/3.x", &matRotate));
	if (objectNumber == 4) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/1.build/4/4.x", &matRotate));
	if (objectNumber == 5) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/1.build/5/5.x", &matRotate));
	if (objectNumber == 6) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/1.build/6/6.x", &matRotate));
	if (objectNumber == 7) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/1.build/7/7.x", &matRotate));
	if (objectNumber == 8) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/1.build/8/8.x", &matRotate));
	if (objectNumber == 9) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/1.build/9/9.x", &matRotate));
	if (objectNumber == 10) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/1.build/10/10.x", &matRotate));
	if (objectNumber == 11) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/1.build/11/11.x", &matRotate));
	if (objectNumber == 12) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/1.build/12/12.x", &matRotate));
	if (objectNumber == 13) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/1.build/13/13.x", &matRotate));
	if (objectNumber == 14) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/1.build/14/14.x", &matRotate));
	if (objectNumber == 15) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/1.build/15/15.x", &matRotate));
	if (objectNumber == 16) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/1.build/16/16.x", &matRotate));

	if (objectNumber == 18) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/2.townfence/1/1.x", &matRotate));
	if (objectNumber == 19) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/2.townfence/2/2.x", &matRotate));
	if (objectNumber == 20) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/2.townfence/3/3.x", &matRotate));
	if (objectNumber == 21) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/2.townfence/4/4.x", &matRotate));
	if (objectNumber == 22) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/2.townfence/5/5.x", &matRotate));
	if (objectNumber == 23) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/2.townfence/6/6.x", &matRotate));
	if (objectNumber == 24) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/2.townfence/7/7.x", &matRotate));
	if (objectNumber == 25) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/2.townfence/8/8.x", &matRotate));
	if (objectNumber == 26) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/2.townfence/9/9.x", &matRotate));

	if (objectNumber == 27) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/3.tree/1/1.X", &matRotate));
	if (objectNumber == 28) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/3.tree/2/2.X", &matRotate));
	if (objectNumber == 29) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/3.tree/3/3.X", &matRotate));
	if (objectNumber == 30) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/3.tree/4/4.X", &matRotate));
	if (objectNumber == 31) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/3.tree/5/5.X", &matRotate));
	if (objectNumber == 32) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/3.tree/6/6.X", &matRotate));
	if (objectNumber == 33) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/3.tree/7/7.X", &matRotate));

	if (objectNumber == 35) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/4.townObject/1/1.X", &matRotate));
	if (objectNumber == 36) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/4.townObject/2/2.X", &matRotate));
	if (objectNumber == 37) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/4.townObject/3/3.X", &matRotate));
	if (objectNumber == 38) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/4.townObject/4/4.X", &matRotate));
	if (objectNumber == 39) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/4.townObject/5/5.X", &matRotate));
	if (objectNumber == 40) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/4.townObject/6/6.X", &matRotate));
	if (objectNumber == 41) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/4.townObject/7/7.X", &matRotate));
	if (objectNumber == 42) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/4.townObject/8/8.X", &matRotate));
	if (objectNumber == 43) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/4.townObject/9/9.X", &matRotate));
	if (objectNumber == 44) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/4.townObject/10/10.X", &matRotate));
	if (objectNumber == 45) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/4.townObject/11/11.X", &matRotate));
	if (objectNumber == 46) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/4.townObject/12/12.X", &matRotate));
	if (objectNumber == 47) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/4.townObject/13/13.X", &matRotate));
	if (objectNumber == 48) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/4.townObject/14/14.X", &matRotate));
	if (objectNumber == 49) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/4.townObject/15/15.X", &matRotate));

	if (objectNumber == 51) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/5.townSmallFence/1/1.X", &matRotate));
	if (objectNumber == 52) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/5.townSmallFence/2/2.X", &matRotate));
	if (objectNumber == 53) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/5.townSmallFence/3/3.X", &matRotate));
	if (objectNumber == 54) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/5.townSmallFence/4/4.X", &matRotate));
	if (objectNumber == 55) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/5.townSmallFence/5/5.X", &matRotate));
	if (objectNumber == 56) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown1/5.townSmallFence/6/6.X", &matRotate));

	if (objectNumber == 57) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/6.boxObject/1/1.X", &matRotate));
	if (objectNumber == 58) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/6.boxObject/2/2.X", &matRotate));
	if (objectNumber == 59) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/6.boxObject/3/3.X", &matRotate));
	if (objectNumber == 60) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/6.boxObject/4/4.X", &matRotate));
	if (objectNumber == 61) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/6.boxObject/5/5.X", &matRotate));
	if (objectNumber == 62) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/6.boxObject/6/6.X", &matRotate));

	if (objectNumber == 63) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/7.planterBox/1/1.X", &matRotate));
	if (objectNumber == 64) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/7.planterBox/2/2.X", &matRotate));
	if (objectNumber == 65) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/7.planterBox/3/3.X", &matRotate));
	if (objectNumber == 66) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/7.planterBox/4/4.X", &matRotate));
	if (objectNumber == 67) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/7.planterBox/5/5.X", &matRotate));
	if (objectNumber == 68) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/7.planterBox/6/6.X", &matRotate));

	if (objectNumber == 69) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/8.memorial stone/1/1.X", &matRotate));
	if (objectNumber == 70) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/8.memorial stone/2/2.X", &matRotate));
	if (objectNumber == 71) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/8.memorial stone/3/3.X", &matRotate));
	if (objectNumber == 72) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/8.memorial stone/4/4.X", &matRotate));
	if (objectNumber == 73) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/8.memorial stone/5/5.X", &matRotate));
	if (objectNumber == 74) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/8.memorial stone/6/6.X", &matRotate));

	if (objectNumber == 75) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/9.shopsign/1/1.X", &matRotate));
	if (objectNumber == 76) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/9.shopsign/2/2.X", &matRotate));
	if (objectNumber == 77) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/9.shopsign/3/3.X", &matRotate));
	if (objectNumber == 78) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/9.shopsign/4/4.X", &matRotate));
	if (objectNumber == 79) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/9.shopsign/5/5.X", &matRotate));

	if (objectNumber == 80) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/10.lowWall/1/1.X", &matRotate));
	if (objectNumber == 81) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/10.lowWall/2/2.X", &matRotate));
	if (objectNumber == 82) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/10.lowWall/3/3.X", &matRotate));
	if (objectNumber == 83) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/10.lowWall/4/4.X", &matRotate));
	if (objectNumber == 84) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/stormTown2/10.lowWall/5/5.X", &matRotate));

	if (objectNumber == 85) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/1/1.X", &matRotate));
	if (objectNumber == 86) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/2/2.X", &matRotate));
	if (objectNumber == 87) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/3/3.X", &matRotate));
	if (objectNumber == 88) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/4/4.X", &matRotate));
	if (objectNumber == 89) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/5/5.X", &matRotate));
	if (objectNumber == 90) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/6/6.X", &matRotate));
	if (objectNumber == 91) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/7/7.X", &matRotate));
	if (objectNumber == 92) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/8/8.X", &matRotate));
	if (objectNumber == 93) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/9/9.X", &matRotate));
	if (objectNumber == 94) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/10/10.X", &matRotate));
	if (objectNumber == 95) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/11/11.X", &matRotate));
	if (objectNumber == 96) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/12/12.X", &matRotate));
	if (objectNumber == 97) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/13/13.X", &matRotate));
	if (objectNumber == 98) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/14/14.X", &matRotate));

	if (objectNumber == 99) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/1/1.X", &matRotate));
	if (objectNumber == 100) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/2/2.X", &matRotate));
	if (objectNumber == 101) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/3/3.X", &matRotate));
	if (objectNumber == 102) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/4/4.X", &matRotate));
	if (objectNumber == 103) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/5/5.X", &matRotate));
	if (objectNumber == 104) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/6/6.X", &matRotate));
	if (objectNumber == 105) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/7/7.X", &matRotate));
	if (objectNumber == 106) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/8/8.X", &matRotate));
	if (objectNumber == 107) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/9/9.X", &matRotate));
	if (objectNumber == 108) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/10/10.X", &matRotate));
	if (objectNumber == 109) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/11/11.X", &matRotate));
	if (objectNumber == 110) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/12/12.X", &matRotate));
	if (objectNumber == 111) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/13/13.X", &matRotate));
	if (objectNumber == 112) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/14/14.X", &matRotate));

	if (objectNumber == 113) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/3.ruinStageRock/1/1.X", &matRotate));
	if (objectNumber == 114) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/3.ruinStageRock/2/2.X", &matRotate));
	if (objectNumber == 115) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/3.ruinStageRock/3/3.X", &matRotate));
	if (objectNumber == 116) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/3.ruinStageRock/4/4.X", &matRotate));
	if (objectNumber == 117) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/3.ruinStageRock/5/5.X", &matRotate));
	if (objectNumber == 118) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/3.ruinStageRock/6/6.X", &matRotate));
	if (objectNumber == 119) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/3.ruinStageRock/7/7.X", &matRotate));
	if (objectNumber == 120) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/3.ruinStageRock/8/8.X", &matRotate));
	if (objectNumber == 121) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/3.ruinStageRock/9/9.X", &matRotate));
	if (objectNumber == 122) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/3.ruinStageRock/10/10.X", &matRotate));

	if (objectNumber == 123) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/4.ruinStageSpider/1/1.X", &matRotate));
	if (objectNumber == 124) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/4.ruinStageSpider/2/2.X", &matRotate));
	if (objectNumber == 125) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/4.ruinStageSpider/3/3.X", &matRotate));
	if (objectNumber == 126) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/4.ruinStageSpider/4/4.X", &matRotate));
	if (objectNumber == 127) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/4.ruinStageSpider/5/5.X", &matRotate));
	if (objectNumber == 128) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/4.ruinStageSpider/6/6.X", &matRotate));

	if (objectNumber == 129) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/5.ruinStageTree/1/1.X", &matRotate));
	if (objectNumber == 130) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/5.ruinStageTree/2/2.X", &matRotate));
	if (objectNumber == 131) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/5.ruinStageTree/3/3.X", &matRotate));
	if (objectNumber == 132) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/5.ruinStageTree/4/4.X", &matRotate));
	if (objectNumber == 133) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/5.ruinStageTree/5/5.X", &matRotate));
	if (objectNumber == 134) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/5.ruinStageTree/6/6.X", &matRotate));
	if (objectNumber == 135) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/5.ruinStageTree/7/7.X", &matRotate));
	if (objectNumber == 136) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/5.ruinStageTree/8/8.X", &matRotate));
	if (objectNumber == 137) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/5.ruinStageTree/9/9.X", &matRotate));

	if (objectNumber == 138) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/6.ruinStagePiramide/1/1.X", &matRotate));
	if (objectNumber == 139) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/6.ruinStagePiramide/2/2.X", &matRotate));
	if (objectNumber == 140) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/6.ruinStagePiramide/3/3.X", &matRotate));
	if (objectNumber == 141) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/6.ruinStagePiramide/4/4.X", &matRotate));

	if (objectNumber == 142) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/7.ruinYelloPyeheo/1/1.X", &matRotate));
	if (objectNumber == 143) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/7.ruinYelloPyeheo/2/2.X", &matRotate));
	if (objectNumber == 144) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/7.ruinYelloPyeheo/3/3.X", &matRotate));
	if (objectNumber == 145) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/7.ruinYelloPyeheo/4/4.X", &matRotate));
	if (objectNumber == 146) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/7.ruinYelloPyeheo/5/5.X", &matRotate));
	if (objectNumber == 147) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/7.ruinYelloPyeheo/6/6.X", &matRotate));
	if (objectNumber == 148) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/7.ruinYelloPyeheo/7/7.X", &matRotate));
	if (objectNumber == 149) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/7.ruinYelloPyeheo/8/8.X", &matRotate));
	if (objectNumber == 150) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/7.ruinYelloPyeheo/9/9.X", &matRotate));
	if (objectNumber == 151) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/7.ruinYelloPyeheo/10/10.X", &matRotate));
	if (objectNumber == 152) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/ruinStage/7.ruinYelloPyeheo/11/11.X", &matRotate));

	if (objectNumber == 153) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/1.piramidBuild/1/1.X", &matRotate));
	if (objectNumber == 154) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/1.piramidBuild/2/2.X", &matRotate));
	if (objectNumber == 155) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/1.piramidBuild/3/3.X", &matRotate));
	if (objectNumber == 156) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/1.piramidBuild/4/4.X", &matRotate));
	if (objectNumber == 157) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/1.piramidBuild/5/5.X", &matRotate));
	if (objectNumber == 158) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/1.piramidBuild/6/6.X", &matRotate));
	if (objectNumber == 159) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/1.piramidBuild/7/7.X", &matRotate));
	if (objectNumber == 160) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/1.piramidBuild/8/8.X", &matRotate));
	if (objectNumber == 161) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/1.piramidBuild/9/9.X", &matRotate));
	if (objectNumber == 162) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/1.piramidBuild/10/10.X", &matRotate));
	if (objectNumber == 163) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/1.piramidBuild/11/11.X", &matRotate));
	if (objectNumber == 164) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/1.piramidBuild/12/12.X", &matRotate));
	if (objectNumber == 165) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/1.piramidBuild/13/13.X", &matRotate));

	if (objectNumber == 166) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/2.piramidObject/15/15.X", &matRotate));
	if (objectNumber == 167) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/2.piramidObject/14/14.X", &matRotate));
	if (objectNumber == 168) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/2.piramidObject/3/3.X", &matRotate));
	if (objectNumber == 169) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/2.piramidObject/4/4.X", &matRotate));
	if (objectNumber == 170) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/2.piramidObject/5/5.X", &matRotate));
	if (objectNumber == 171) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/2.piramidObject/6/6.X", &matRotate));
	if (objectNumber == 172) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/2.piramidObject/7/7.X", &matRotate));
	if (objectNumber == 173) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/2.piramidObject/8/8.X", &matRotate));
	if (objectNumber == 174) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/2.piramidObject/9/9.X", &matRotate));
	if (objectNumber == 175) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/2.piramidObject/10/10.X", &matRotate));
	if (objectNumber == 176) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/2.piramidObject/11/11.X", &matRotate));
	if (objectNumber == 177) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/2.piramidObject/12/12.X", &matRotate));
	if (objectNumber == 178) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/2.piramidObject/13/13.X", &matRotate));

	if (objectNumber == 179) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/3.piramidSmallObject/1/1.X", &matRotate));
	if (objectNumber == 180) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/3.piramidSmallObject/2/2.X", &matRotate));
	if (objectNumber == 181) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/3.piramidSmallObject/3/3.X", &matRotate));
	if (objectNumber == 182) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/3.piramidSmallObject/4/4.X", &matRotate));
	if (objectNumber == 183) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/3.piramidSmallObject/5/5.X", &matRotate));

	if (objectNumber == 184) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/4.piramidRock/1/1.X", &matRotate));
	if (objectNumber == 185) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/4.piramidRock/2/2.X", &matRotate));
	if (objectNumber == 186) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/4.piramidRock/3/3.X", &matRotate));
	if (objectNumber == 187) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/4.piramidRock/4/4.X", &matRotate));
	if (objectNumber == 188) tempObect->setMesh(RM_XMESH->getResource("Resource/Maptool/Meshes/piramid/4.piramidRock/5/5.X", &matRotate));



	tempObect->setActive(true);
	tempObect->_transform->SetWorldPosition(m_fPickposX, m_fPickposY, m_fPickposZ);
	tempObect->_transform->SetScale(mapScale, mapScale, mapScale);
	tempObect->_transform->SetRotateWorld(0, mapRotation, 0);

}
//
//void mapObject::objectRender(vector<baseObject>& object)
//{
//	for (int i = 0; i < object.size(); i++)
//	{
//		xMeshStatic::_staticMeshEffect->SetMatrixArray("matLights", &_directionLight->getLightMatrix(), 1);
//		xMeshStatic::_staticMeshEffect->SetInt("LightNum", 1);
//		xMeshStatic::setCamera(_mainCamera);
//		object[i].render();
//	}
//}

void mapObject::objectRenderTool(vector<baseObject*>& object, camera * _mainCamera)
{
	for (int i = 0; i < object.size(); i++)
	{
		xMeshStatic::_staticMeshEffect->SetMatrixArray("matLights", &_directionLight->getLightMatrix(), 1);
		xMeshStatic::_staticMeshEffect->SetInt("LightNum", 1);
		xMeshStatic::setCamera(_mainCamera);
		object[i]->render();
	}
}
