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

	return S_OK;
}

void mapObject::objectSet(int objectNumber, baseObject * tempObect, D3DXMATRIX matRotate, float m_fPickposX, float m_fPickposY, float m_fPickposZ, float mapScale, float mapRotation)
{
	D3DXMatrixRotationY(&matRotate, D3DXToRadian(180));

	if (objectNumber == 1) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob000"), &matRotate));
	if (objectNumber == 2) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob001"), &matRotate));
	if (objectNumber == 3) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob002"), &matRotate));
	if (objectNumber == 4) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob003"), &matRotate));
	if (objectNumber == 5) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob004"), &matRotate));
	if (objectNumber == 6) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob005"), &matRotate));
	if (objectNumber == 7) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob006"), &matRotate));
	if (objectNumber == 8) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob007"), &matRotate));
	if (objectNumber == 9) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob008"), &matRotate));
	if (objectNumber == 10) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob009"), &matRotate));
	if (objectNumber == 11) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob010"), &matRotate));
	if (objectNumber == 12) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob011"), &matRotate));
	if (objectNumber == 13) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob012"), &matRotate));
	if (objectNumber == 14) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob013"), &matRotate));
	if (objectNumber == 15) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob014"), &matRotate));
	if (objectNumber == 16) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob015"), &matRotate));

	if (objectNumber == 18) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob017"), &matRotate));
	if (objectNumber == 19) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob018"), &matRotate));
	if (objectNumber == 20) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob019"), &matRotate));
	if (objectNumber == 21) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob020"), &matRotate));
	if (objectNumber == 22) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob021"), &matRotate));
	if (objectNumber == 23) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob022"), &matRotate));
	if (objectNumber == 24) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob023"), &matRotate));
	if (objectNumber == 25) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob024"), &matRotate));
	if (objectNumber == 26) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob025"), &matRotate));

	if (objectNumber == 27) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob026"), &matRotate));
	if (objectNumber == 28) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob027"), &matRotate));
	if (objectNumber == 29) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob028"), &matRotate));
	if (objectNumber == 30) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob029"), &matRotate));
	if (objectNumber == 31) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob030"), &matRotate));
	if (objectNumber == 32) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob031"), &matRotate));
	if (objectNumber == 33) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob032"), &matRotate));

	if (objectNumber == 35) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob034"), &matRotate));
	if (objectNumber == 36) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob035"), &matRotate));
	if (objectNumber == 37) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob036"), &matRotate));
	if (objectNumber == 38) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob037"), &matRotate));
	if (objectNumber == 39) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob038"), &matRotate));
	if (objectNumber == 40) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob039"), &matRotate));
	if (objectNumber == 41) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob040"), &matRotate));
	if (objectNumber == 42) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob041"), &matRotate));
	if (objectNumber == 43) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob042"), &matRotate));
	if (objectNumber == 44) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob043"), &matRotate));
	if (objectNumber == 45) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob044"), &matRotate));
	if (objectNumber == 46) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob045"), &matRotate));
	if (objectNumber == 47) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob046"), &matRotate));
	if (objectNumber == 48) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob047"), &matRotate));
	if (objectNumber == 49) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob048"), &matRotate));

	if (objectNumber == 51) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob050"), &matRotate));
	if (objectNumber == 52) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob051"), &matRotate));
	if (objectNumber == 53) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob052"), &matRotate));
	if (objectNumber == 54) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob053"), &matRotate));
	if (objectNumber == 55) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob054"), &matRotate));
	if (objectNumber == 56) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob055"), &matRotate));

	if (objectNumber == 57) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob056"), &matRotate));
	if (objectNumber == 58) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob057"), &matRotate));
	if (objectNumber == 59) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob058"), &matRotate));
	if (objectNumber == 60) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob059"), &matRotate));
	if (objectNumber == 61) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob060"), &matRotate));
	if (objectNumber == 62) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob061"), &matRotate));

	if (objectNumber == 63) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob062"), &matRotate));
	if (objectNumber == 64) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob063"), &matRotate));
	if (objectNumber == 65) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob064"), &matRotate));
	if (objectNumber == 66) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob065"), &matRotate));
	if (objectNumber == 67) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob066"), &matRotate));
	if (objectNumber == 68) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob067"), &matRotate));

	if (objectNumber == 69) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob068"), &matRotate));
	if (objectNumber == 70) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob069"), &matRotate));
	if (objectNumber == 71) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob070"), &matRotate));
	if (objectNumber == 72) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob071"), &matRotate));
	if (objectNumber == 73) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob072"), &matRotate));
	if (objectNumber == 74) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob073"), &matRotate));

	if (objectNumber == 75) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob074"), &matRotate));
	if (objectNumber == 76) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob075"), &matRotate));
	if (objectNumber == 77) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob076"), &matRotate));
	if (objectNumber == 78) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob077"), &matRotate));
	if (objectNumber == 79) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob078"), &matRotate));

	if (objectNumber == 80) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob079"), &matRotate));
	if (objectNumber == 81) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob080"), &matRotate));
	if (objectNumber == 82) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob081"), &matRotate));
	if (objectNumber == 83) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob082"), &matRotate));
	if (objectNumber == 84) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob083"), &matRotate));

	if (objectNumber == 85) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob084"), &matRotate));
	if (objectNumber == 86) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob085"), &matRotate));
	if (objectNumber == 87) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob086"), &matRotate));
	if (objectNumber == 88) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob087"), &matRotate));
	if (objectNumber == 89) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob088"), &matRotate));
	if (objectNumber == 90) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob089"), &matRotate));
	if (objectNumber == 91) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob090"), &matRotate));
	if (objectNumber == 92) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob091"), &matRotate));
	if (objectNumber == 93) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob092"), &matRotate));
	if (objectNumber == 94) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob093"), &matRotate));
	if (objectNumber == 95) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob094"), &matRotate));
	if (objectNumber == 96) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob095"), &matRotate));
	if (objectNumber == 97) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob096"), &matRotate));
	if (objectNumber == 98) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob097"), &matRotate));

	if (objectNumber == 99)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob098"), &matRotate));
	if (objectNumber == 100) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob099"), &matRotate));
	if (objectNumber == 101) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob100"), &matRotate));
	if (objectNumber == 102) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob101"), &matRotate));
	if (objectNumber == 103) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob102"), &matRotate));
	if (objectNumber == 104) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob103"), &matRotate));
	if (objectNumber == 105) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob104"), &matRotate));
	if (objectNumber == 106) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob105"), &matRotate));
	if (objectNumber == 107) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob106"), &matRotate));
	if (objectNumber == 108) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob107"), &matRotate));
	if (objectNumber == 109) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob108"), &matRotate));
	if (objectNumber == 110) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob109"), &matRotate));
	if (objectNumber == 111) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob110"), &matRotate));
	if (objectNumber == 112) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob111"), &matRotate));

	if (objectNumber == 113) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob112"), &matRotate));
	if (objectNumber == 114) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob113"), &matRotate));
	if (objectNumber == 115) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob114"), &matRotate));
	if (objectNumber == 116) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob115"), &matRotate));
	if (objectNumber == 117) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob116"), &matRotate));
	if (objectNumber == 118) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob117"), &matRotate));
	if (objectNumber == 119) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob118"), &matRotate));
	if (objectNumber == 120) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob119"), &matRotate));
	if (objectNumber == 121) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob120"), &matRotate));
	if (objectNumber == 122) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob121"), &matRotate));

	if (objectNumber == 123) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob122"), &matRotate));
	if (objectNumber == 124) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob123"), &matRotate));
	if (objectNumber == 125) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob124"), &matRotate));
	if (objectNumber == 126) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob125"), &matRotate));
	if (objectNumber == 127) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob126"), &matRotate));
	if (objectNumber == 128) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob127"), &matRotate));

	if (objectNumber == 129) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob128"), &matRotate));
	if (objectNumber == 130) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob129"), &matRotate));
	if (objectNumber == 131) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob130"), &matRotate));
	if (objectNumber == 132) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob131"), &matRotate));
	if (objectNumber == 133) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob132"), &matRotate));
	if (objectNumber == 134) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob133"), &matRotate));
	if (objectNumber == 135) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob134"), &matRotate));
	if (objectNumber == 136) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob135"), &matRotate));
	if (objectNumber == 137) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob136"), &matRotate));

	if (objectNumber == 138) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob137"), &matRotate));
	if (objectNumber == 139) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob138"), &matRotate));
	if (objectNumber == 140) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob139"), &matRotate));
	if (objectNumber == 141) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob140"), &matRotate));

	if (objectNumber == 142) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob141"), &matRotate));
	if (objectNumber == 143) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob142"), &matRotate));
	if (objectNumber == 144) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob143"), &matRotate));
	if (objectNumber == 145) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob144"), &matRotate));
	if (objectNumber == 146) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob145"), &matRotate));
	if (objectNumber == 147) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob146"), &matRotate));
	if (objectNumber == 148) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob147"), &matRotate));
	if (objectNumber == 149) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob148"), &matRotate));
	if (objectNumber == 150) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob149"), &matRotate));
	if (objectNumber == 151) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob150"), &matRotate));
	if (objectNumber == 152) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob151"), &matRotate));

	if (objectNumber == 153) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob152"), &matRotate));
	if (objectNumber == 154) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob153"), &matRotate));
	if (objectNumber == 155) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob154"), &matRotate));
	if (objectNumber == 156) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob155"), &matRotate));
	if (objectNumber == 157) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob156"), &matRotate));
	if (objectNumber == 158) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob157"), &matRotate));
	if (objectNumber == 159) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob158"), &matRotate));
	if (objectNumber == 160) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob159"), &matRotate));
	if (objectNumber == 161) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob160"), &matRotate));
	if (objectNumber == 162) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob161"), &matRotate));
	if (objectNumber == 163) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob162"), &matRotate));
	if (objectNumber == 164) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob163"), &matRotate));
	if (objectNumber == 165) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob164"), &matRotate));

	if (objectNumber == 166) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob165"), &matRotate));
	if (objectNumber == 167) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob166"), &matRotate));
	if (objectNumber == 168) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob167"), &matRotate));
	if (objectNumber == 169) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob168"), &matRotate));
	if (objectNumber == 170) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob169"), &matRotate));
	if (objectNumber == 171) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob170"), &matRotate));
	if (objectNumber == 172) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob171"), &matRotate));
	if (objectNumber == 173) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob172"), &matRotate));
	if (objectNumber == 174) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob173"), &matRotate));
	if (objectNumber == 175) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob174"), &matRotate));
	if (objectNumber == 176) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob175"), &matRotate));
	if (objectNumber == 177) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob176"), &matRotate));
	if (objectNumber == 178) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob177"), &matRotate));

	if (objectNumber == 179) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob178"), &matRotate));
	if (objectNumber == 180) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob179"), &matRotate));
	if (objectNumber == 181) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob180"), &matRotate));
	if (objectNumber == 182) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob181"), &matRotate));
	if (objectNumber == 183) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob182"), &matRotate));

	if (objectNumber == 184) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob183"), &matRotate));
	if (objectNumber == 185) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob184"), &matRotate));
	if (objectNumber == 186) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob185"), &matRotate));
	if (objectNumber == 187) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob186"), &matRotate));
	if (objectNumber == 188) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob187"), &matRotate));

	if (objectNumber == 189) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_portal1"), &matRotate));
	if (objectNumber == 190) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_portal2"), &matRotate));
	if (objectNumber == 191) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_portal3"), &matRotate));
	if (objectNumber == 192) tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_portal4"), &matRotate));

	tempObect->setActive(true);
	tempObect->_transform->SetWorldPosition(m_fPickposX, m_fPickposY, m_fPickposZ);
	tempObect->_transform->SetScale(mapScale, mapScale, mapScale);
	tempObect->_transform->SetRotateWorld(0, mapRotation, 0);

	//삭제를 위해서 사이즈를 맞추기위한 수단
	switch (objectNumber)
	{
	case 189:
	case 190:
	case 191:
	case 192:
		Tportal* temp;
		temp = new Tportal;
		temp->portalSet(tempObect->_transform);
		_tportal.push_back(temp);
		tempObect->SetportalNumber(_tportal.size() - 1);
		break;
	}
}

void mapObject::objectRenderTool2(vector<baseObject*>& object, camera * _mainCamera, lightDirection* _directionLight)
{

	for (int i = 0; i < object.size(); i++)
	{
		xMeshStatic::_staticMeshEffect->SetMatrixArray("matLights", &_directionLight->getLightMatrix(), 1);
		xMeshStatic::_staticMeshEffect->SetInt("LightNum", 1);
		xMeshStatic::setCamera(_mainCamera);
		object[i]->render();
	}
}

void mapObject::objectRenderTool(vector<baseObject*>& object, camera * _mainCamera, lightDirection* _directionLight)
{

	for (int i = 0; i < object.size(); i++)
	{
		xMeshStatic::_staticMeshEffect->SetMatrixArray("matLights", &_directionLight->getLightMatrix(), 1);
		xMeshStatic::_staticMeshEffect->SetInt("LightNum", 1);
		xMeshStatic::setCamera(_mainCamera);
		object[i]->render();
	}

	for (int j = 0; j < _tportal.size(); j++)
	{
		_tportal[j]->LinkCamera(*_mainCamera);
		_tportal[j]->update();
		_tportal[j]->renderPortal();
	}
}

void mapObject::potralErase(int objectNumber, int number)
{
	switch (objectNumber)
	{
	case 189:
	case 190:
	case 191:
	case 192:
		SAFE_DELETE(_tportal[number]);
		_tportal.erase(_tportal.begin() + number);
		temp = true;
		break;
	}
}

void mapObject::deletePortal()
{
	for (int i = 0; i < _tportal.size(); i++)
	{
		SAFE_DELETE(_tportal[i]);
	}
	_tportal.clear();
}

void mapObject::portalRender(camera * _mainCamera)
{
	for (int j = 0; j < _tportal.size(); j++)
	{
		_tportal[j]->LinkCamera(*_mainCamera);
		_tportal[j]->update();
		_tportal[j]->renderPortal();
	}
}

void mapObject::portal(vector<baseObject*>& tempObect)
{
	int j = 0;
	if (temp == true)
	{
		for (int i = 0; i < tempObect.size(); i++)
		{
			switch (tempObect[i]->getObjectNumber())
			{
			case 189:
			case 190:
			case 191:
			case 192:
				tempObect[i]->SetportalNumber(j++);

			}
		}
		temp = false;
	}

}

