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
	D3DXMATRIX scale;
	D3DXMatrixScaling(&scale, 0.5f, 0.5f, 0.5f);
	if (objectNumber == 1)			XMESH_MANAGER->AddXmeshStatic("ob000", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob000"), scale));
	if (objectNumber == 2)   		XMESH_MANAGER->AddXmeshStatic("ob001", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob001"), scale));
	if (objectNumber == 3)   		XMESH_MANAGER->AddXmeshStatic("ob002", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob002"), scale));
	if (objectNumber == 4)   		XMESH_MANAGER->AddXmeshStatic("ob003", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob003"), scale));
	if (objectNumber == 5)   		XMESH_MANAGER->AddXmeshStatic("ob004", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob004"), scale));
	if (objectNumber == 6)   		XMESH_MANAGER->AddXmeshStatic("ob005", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob005"), scale));
	if (objectNumber == 7)   		XMESH_MANAGER->AddXmeshStatic("ob006", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob006"), scale));
	if (objectNumber == 8)   		XMESH_MANAGER->AddXmeshStatic("ob007", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob007"), scale));
	if (objectNumber == 9)   		XMESH_MANAGER->AddXmeshStatic("ob008", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob008"), scale));
	if (objectNumber == 10)  		XMESH_MANAGER->AddXmeshStatic("ob009", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob009"), scale));
	if (objectNumber == 11)  		XMESH_MANAGER->AddXmeshStatic("ob010", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob010"), scale));
	if (objectNumber == 12)  		XMESH_MANAGER->AddXmeshStatic("ob011", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob011"), scale));
	if (objectNumber == 13)  		XMESH_MANAGER->AddXmeshStatic("ob012", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob012"), scale));
	if (objectNumber == 14)  		XMESH_MANAGER->AddXmeshStatic("ob013", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob013"), scale));
	if (objectNumber == 15)  		XMESH_MANAGER->AddXmeshStatic("ob014", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob014"), scale));
	if (objectNumber == 16)  		XMESH_MANAGER->AddXmeshStatic("ob015", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob015"), scale));
							 
	if (objectNumber == 18)  		XMESH_MANAGER->AddXmeshStatic("ob017", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob017"), scale));
	if (objectNumber == 19)  		XMESH_MANAGER->AddXmeshStatic("ob018", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob018"), scale));
	if (objectNumber == 20)  		XMESH_MANAGER->AddXmeshStatic("ob019", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob019"), scale));
	if (objectNumber == 21)  		XMESH_MANAGER->AddXmeshStatic("ob020", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob020"), scale));
	if (objectNumber == 22)  		XMESH_MANAGER->AddXmeshStatic("ob021", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob021"), scale));
	if (objectNumber == 23)  		XMESH_MANAGER->AddXmeshStatic("ob022", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob022"), scale));
	if (objectNumber == 24)  		XMESH_MANAGER->AddXmeshStatic("ob023", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob023"), scale));
	if (objectNumber == 25)  		XMESH_MANAGER->AddXmeshStatic("ob024", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob024"), scale));
	if (objectNumber == 26)  		XMESH_MANAGER->AddXmeshStatic("ob025", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob025"), scale));
							 
	if (objectNumber == 27)  		XMESH_MANAGER->AddXmeshStatic("ob026", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob026"), scale));
	if (objectNumber == 28)  		XMESH_MANAGER->AddXmeshStatic("ob027", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob027"), scale));
	if (objectNumber == 29)  		XMESH_MANAGER->AddXmeshStatic("ob028", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob028"), scale));
	if (objectNumber == 30)  		XMESH_MANAGER->AddXmeshStatic("ob029", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob029"), scale));
	if (objectNumber == 31)  		XMESH_MANAGER->AddXmeshStatic("ob030", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob030"), scale));
	if (objectNumber == 32)  		XMESH_MANAGER->AddXmeshStatic("ob031", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob031"), scale));
	if (objectNumber == 33)  		XMESH_MANAGER->AddXmeshStatic("ob032", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob032"), scale));
							 
	if (objectNumber == 35)  		XMESH_MANAGER->AddXmeshStatic("ob034", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob034"), scale));
	if (objectNumber == 36)  		XMESH_MANAGER->AddXmeshStatic("ob035", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob035"), scale));
	if (objectNumber == 37)  		XMESH_MANAGER->AddXmeshStatic("ob036", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob036"), scale));
	if (objectNumber == 38)  		XMESH_MANAGER->AddXmeshStatic("ob037", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob037"), scale));
	if (objectNumber == 39)  		XMESH_MANAGER->AddXmeshStatic("ob038", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob038"), scale));
	if (objectNumber == 40)  		XMESH_MANAGER->AddXmeshStatic("ob039", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob039"), scale));
	if (objectNumber == 41)  		XMESH_MANAGER->AddXmeshStatic("ob040", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob040"), scale));
	if (objectNumber == 42)  		XMESH_MANAGER->AddXmeshStatic("ob041", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob041"), scale));
	if (objectNumber == 43)  		XMESH_MANAGER->AddXmeshStatic("ob042", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob042"), scale));
	if (objectNumber == 44)  		XMESH_MANAGER->AddXmeshStatic("ob043", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob043"), scale));
	if (objectNumber == 45)  		XMESH_MANAGER->AddXmeshStatic("ob044", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob044"), scale));
	if (objectNumber == 46)  		XMESH_MANAGER->AddXmeshStatic("ob045", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob045"), scale));
	if (objectNumber == 47)  		XMESH_MANAGER->AddXmeshStatic("ob046", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob046"), scale));
	if (objectNumber == 48)  		XMESH_MANAGER->AddXmeshStatic("ob047", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob047"), scale));
	if (objectNumber == 49)  		XMESH_MANAGER->AddXmeshStatic("ob048", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob048"), scale));
							 
	if (objectNumber == 51)  		XMESH_MANAGER->AddXmeshStatic("ob050", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob050"), scale));
	if (objectNumber == 52)  		XMESH_MANAGER->AddXmeshStatic("ob051", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob051"), scale));
	if (objectNumber == 53)  		XMESH_MANAGER->AddXmeshStatic("ob052", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob052"), scale));
	if (objectNumber == 54)  		XMESH_MANAGER->AddXmeshStatic("ob053", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob053"), scale));
	if (objectNumber == 55)  		XMESH_MANAGER->AddXmeshStatic("ob054", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob054"), scale));
	if (objectNumber == 56)  		XMESH_MANAGER->AddXmeshStatic("ob055", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob055"), scale));
							 
	if (objectNumber == 57)  		XMESH_MANAGER->AddXmeshStatic("ob056", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob056"), scale));
	if (objectNumber == 58)  		XMESH_MANAGER->AddXmeshStatic("ob057", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob057"), scale));
	if (objectNumber == 59)  		XMESH_MANAGER->AddXmeshStatic("ob058", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob058"), scale));
	if (objectNumber == 60)  		XMESH_MANAGER->AddXmeshStatic("ob059", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob059"), scale));
	if (objectNumber == 61)  		XMESH_MANAGER->AddXmeshStatic("ob060", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob060"), scale));
	if (objectNumber == 62)  		XMESH_MANAGER->AddXmeshStatic("ob061", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob061"), scale));
							 
	if (objectNumber == 63)  		XMESH_MANAGER->AddXmeshStatic("ob062", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob062"), scale));
	if (objectNumber == 64)  		XMESH_MANAGER->AddXmeshStatic("ob063", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob063"), scale));
	if (objectNumber == 65)  		XMESH_MANAGER->AddXmeshStatic("ob064", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob064"), scale));
	if (objectNumber == 66)  		XMESH_MANAGER->AddXmeshStatic("ob065", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob065"), scale));
	if (objectNumber == 67)  		XMESH_MANAGER->AddXmeshStatic("ob066", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob066"), scale));
	if (objectNumber == 68)  		XMESH_MANAGER->AddXmeshStatic("ob067", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob067"), scale));
							 
	if (objectNumber == 69)  		XMESH_MANAGER->AddXmeshStatic("ob068", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob068"), scale));
	if (objectNumber == 70)  		XMESH_MANAGER->AddXmeshStatic("ob069", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob069"), scale));
	if (objectNumber == 71)  		XMESH_MANAGER->AddXmeshStatic("ob070", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob070"), scale));
	if (objectNumber == 72)  		XMESH_MANAGER->AddXmeshStatic("ob071", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob071"), scale));
	if (objectNumber == 73)  		XMESH_MANAGER->AddXmeshStatic("ob072", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob072"), scale));
	if (objectNumber == 74)  		XMESH_MANAGER->AddXmeshStatic("ob073", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob073"), scale));
							 
	if (objectNumber == 75)  		XMESH_MANAGER->AddXmeshStatic("ob074", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob074"), scale));
	if (objectNumber == 76)  		XMESH_MANAGER->AddXmeshStatic("ob075", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob075"), scale));
	if (objectNumber == 77)  		XMESH_MANAGER->AddXmeshStatic("ob076", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob076"), scale));
	if (objectNumber == 78)  		XMESH_MANAGER->AddXmeshStatic("ob077", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob077"), scale));
	if (objectNumber == 79)  		XMESH_MANAGER->AddXmeshStatic("ob078", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob078"), scale));
							 
	if (objectNumber == 80)  		XMESH_MANAGER->AddXmeshStatic("ob079", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob079"), scale));
	if (objectNumber == 81)  		XMESH_MANAGER->AddXmeshStatic("ob080", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob080"), scale));
	if (objectNumber == 82)  		XMESH_MANAGER->AddXmeshStatic("ob081", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob081"), scale));
	if (objectNumber == 83)  		XMESH_MANAGER->AddXmeshStatic("ob082", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob082"), scale));
	if (objectNumber == 84)  		XMESH_MANAGER->AddXmeshStatic("ob083", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob083"), scale));
							 
	if (objectNumber == 85)  		XMESH_MANAGER->AddXmeshStatic("ob084", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob084"), scale));
	if (objectNumber == 86)  		XMESH_MANAGER->AddXmeshStatic("ob085", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob085"), scale));
	if (objectNumber == 87)  		XMESH_MANAGER->AddXmeshStatic("ob086", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob086"), scale));
	if (objectNumber == 88)  		XMESH_MANAGER->AddXmeshStatic("ob087", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob087"), scale));
	if (objectNumber == 89)  		XMESH_MANAGER->AddXmeshStatic("ob088", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob088"), scale));
	if (objectNumber == 90)  		XMESH_MANAGER->AddXmeshStatic("ob089", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob089"), scale));
	if (objectNumber == 91)  		XMESH_MANAGER->AddXmeshStatic("ob090", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob090"), scale));
	if (objectNumber == 92)  		XMESH_MANAGER->AddXmeshStatic("ob091", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob091"), scale));
	if (objectNumber == 93)  		XMESH_MANAGER->AddXmeshStatic("ob092", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob092"), scale));
	if (objectNumber == 94)  		XMESH_MANAGER->AddXmeshStatic("ob093", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob093"), scale));
	if (objectNumber == 95)  		XMESH_MANAGER->AddXmeshStatic("ob094", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob094"), scale));
	if (objectNumber == 96)  		XMESH_MANAGER->AddXmeshStatic("ob095", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob095"), scale));
	if (objectNumber == 97)  		XMESH_MANAGER->AddXmeshStatic("ob096", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob096"), scale));
	if (objectNumber == 98)  		XMESH_MANAGER->AddXmeshStatic("ob097", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob097"), scale));
	
	if (objectNumber == 99)  		XMESH_MANAGER->AddXmeshStatic("ob098", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob098"), scale));
	if (objectNumber == 100) 		XMESH_MANAGER->AddXmeshStatic("ob099", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob099"), scale));
	if (objectNumber == 101) 		XMESH_MANAGER->AddXmeshStatic("ob100", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob100"), scale));
	if (objectNumber == 102) 		XMESH_MANAGER->AddXmeshStatic("ob101", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob101"), scale));
	if (objectNumber == 103) 		XMESH_MANAGER->AddXmeshStatic("ob102", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob102"), scale));
	if (objectNumber == 104) 		XMESH_MANAGER->AddXmeshStatic("ob103", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob103"), scale));
	if (objectNumber == 105) 		XMESH_MANAGER->AddXmeshStatic("ob104", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob104"), scale));
	if (objectNumber == 106) 		XMESH_MANAGER->AddXmeshStatic("ob105", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob105"), scale));
	if (objectNumber == 107) 		XMESH_MANAGER->AddXmeshStatic("ob106", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob106"), scale));
	if (objectNumber == 108) 		XMESH_MANAGER->AddXmeshStatic("ob107", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob107"), scale));
	if (objectNumber == 109) 		XMESH_MANAGER->AddXmeshStatic("ob108", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob108"), scale));
	if (objectNumber == 110) 		XMESH_MANAGER->AddXmeshStatic("ob109", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob109"), scale));
	if (objectNumber == 111) 		XMESH_MANAGER->AddXmeshStatic("ob110", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob110"), scale));
	if (objectNumber == 112) 		XMESH_MANAGER->AddXmeshStatic("ob111", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob111"), scale));
	
	if (objectNumber == 113) 		XMESH_MANAGER->AddXmeshStatic("ob112", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob112"), scale));
	if (objectNumber == 114) 		XMESH_MANAGER->AddXmeshStatic("ob113", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob113"), scale));
	if (objectNumber == 115) 		XMESH_MANAGER->AddXmeshStatic("ob114", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob114"), scale));
	if (objectNumber == 116) 		XMESH_MANAGER->AddXmeshStatic("ob115", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob115"), scale));
	if (objectNumber == 117) 		XMESH_MANAGER->AddXmeshStatic("ob116", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob116"), scale));
	if (objectNumber == 118) 		XMESH_MANAGER->AddXmeshStatic("ob117", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob117"), scale));
	if (objectNumber == 119) 		XMESH_MANAGER->AddXmeshStatic("ob118", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob118"), scale));
	if (objectNumber == 120) 		XMESH_MANAGER->AddXmeshStatic("ob119", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob119"), scale));
	if (objectNumber == 121) 		XMESH_MANAGER->AddXmeshStatic("ob120", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob120"), scale));
	if (objectNumber == 122) 		XMESH_MANAGER->AddXmeshStatic("ob121", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob121"), scale));
	
	if (objectNumber == 123) 		XMESH_MANAGER->AddXmeshStatic("ob122", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob122"), scale));
	if (objectNumber == 124) 		XMESH_MANAGER->AddXmeshStatic("ob123", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob123"), scale));
	if (objectNumber == 125) 		XMESH_MANAGER->AddXmeshStatic("ob124", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob124"), scale));
	if (objectNumber == 126) 		XMESH_MANAGER->AddXmeshStatic("ob125", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob125"), scale));
	if (objectNumber == 127) 		XMESH_MANAGER->AddXmeshStatic("ob126", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob126"), scale));
	if (objectNumber == 128) 		XMESH_MANAGER->AddXmeshStatic("ob127", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob127"), scale));
	
	if (objectNumber == 129) 		XMESH_MANAGER->AddXmeshStatic("ob128", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob128"), scale));
	if (objectNumber == 130) 		XMESH_MANAGER->AddXmeshStatic("ob129", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob129"), scale));
	if (objectNumber == 131) 		XMESH_MANAGER->AddXmeshStatic("ob130", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob130"), scale));
	if (objectNumber == 132) 		XMESH_MANAGER->AddXmeshStatic("ob131", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob131"), scale));
	if (objectNumber == 133) 		XMESH_MANAGER->AddXmeshStatic("ob132", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob132"), scale));
	if (objectNumber == 134) 		XMESH_MANAGER->AddXmeshStatic("ob133", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob133"), scale));
	if (objectNumber == 135) 		XMESH_MANAGER->AddXmeshStatic("ob134", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob134"), scale));
	if (objectNumber == 136) 		XMESH_MANAGER->AddXmeshStatic("ob135", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob135"), scale));
	if (objectNumber == 137) 		XMESH_MANAGER->AddXmeshStatic("ob136", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob136"), scale));
	
	if (objectNumber == 138) 		XMESH_MANAGER->AddXmeshStatic("ob137", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob137"), scale));
	if (objectNumber == 139) 		XMESH_MANAGER->AddXmeshStatic("ob138", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob138"), scale));
	if (objectNumber == 140) 		XMESH_MANAGER->AddXmeshStatic("ob139", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob139"), scale));
	if (objectNumber == 141) 		XMESH_MANAGER->AddXmeshStatic("ob140", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob140"), scale));
	
	if (objectNumber == 142) 		XMESH_MANAGER->AddXmeshStatic("ob141", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob141"), scale));
	if (objectNumber == 143) 		XMESH_MANAGER->AddXmeshStatic("ob142", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob142"), scale));
	if (objectNumber == 144) 		XMESH_MANAGER->AddXmeshStatic("ob143", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob143"), scale));
	if (objectNumber == 145) 		XMESH_MANAGER->AddXmeshStatic("ob144", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob144"), scale));
	if (objectNumber == 146) 		XMESH_MANAGER->AddXmeshStatic("ob145", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob145"), scale));
	if (objectNumber == 147) 		XMESH_MANAGER->AddXmeshStatic("ob146", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob146"), scale));
	if (objectNumber == 148) 		XMESH_MANAGER->AddXmeshStatic("ob147", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob147"), scale));
	if (objectNumber == 149) 		XMESH_MANAGER->AddXmeshStatic("ob148", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob148"), scale));
	if (objectNumber == 150) 		XMESH_MANAGER->AddXmeshStatic("ob149", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob149"), scale));
	if (objectNumber == 151) 		XMESH_MANAGER->AddXmeshStatic("ob150", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob150"), scale));
	if (objectNumber == 152) 		XMESH_MANAGER->AddXmeshStatic("ob151", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob151"), scale));
	
	if (objectNumber == 153) 		XMESH_MANAGER->AddXmeshStatic("ob152", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob152"), scale));
	if (objectNumber == 154) 		XMESH_MANAGER->AddXmeshStatic("ob153", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob153"), scale));
	if (objectNumber == 155) 		XMESH_MANAGER->AddXmeshStatic("ob154", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob154"), scale));
	if (objectNumber == 156) 		XMESH_MANAGER->AddXmeshStatic("ob155", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob155"), scale));
	if (objectNumber == 157) 		XMESH_MANAGER->AddXmeshStatic("ob156", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob156"), scale));
	if (objectNumber == 158) 		XMESH_MANAGER->AddXmeshStatic("ob157", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob157"), scale));
	if (objectNumber == 159) 		XMESH_MANAGER->AddXmeshStatic("ob158", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob158"), scale));
	if (objectNumber == 160) 		XMESH_MANAGER->AddXmeshStatic("ob159", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob159"), scale));
	if (objectNumber == 161) 		XMESH_MANAGER->AddXmeshStatic("ob160", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob160"), scale));
	if (objectNumber == 162) 		XMESH_MANAGER->AddXmeshStatic("ob161", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob161"), scale));
	if (objectNumber == 163) 		XMESH_MANAGER->AddXmeshStatic("ob162", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob162"), scale));
	if (objectNumber == 164) 		XMESH_MANAGER->AddXmeshStatic("ob163", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob163"), scale));
	if (objectNumber == 165) 		XMESH_MANAGER->AddXmeshStatic("ob164", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob164"), scale));
	
	if (objectNumber == 166) 		XMESH_MANAGER->AddXmeshStatic("ob165", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob165"), scale));
	if (objectNumber == 167) 		XMESH_MANAGER->AddXmeshStatic("ob166", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob166"), scale));
	if (objectNumber == 168) 		XMESH_MANAGER->AddXmeshStatic("ob167", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob167"), scale));
	if (objectNumber == 169) 		XMESH_MANAGER->AddXmeshStatic("ob168", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob168"), scale));
	if (objectNumber == 170) 		XMESH_MANAGER->AddXmeshStatic("ob169", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob169"), scale));
	if (objectNumber == 171) 		XMESH_MANAGER->AddXmeshStatic("ob170", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob170"), scale));
	if (objectNumber == 172) 		XMESH_MANAGER->AddXmeshStatic("ob171", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob171"), scale));
	if (objectNumber == 173) 		XMESH_MANAGER->AddXmeshStatic("ob172", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob172"), scale));
	if (objectNumber == 174) 		XMESH_MANAGER->AddXmeshStatic("ob173", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob173"), scale));
	if (objectNumber == 175) 		XMESH_MANAGER->AddXmeshStatic("ob174", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob174"), scale));
	if (objectNumber == 176) 		XMESH_MANAGER->AddXmeshStatic("ob175", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob175"), scale));
	if (objectNumber == 177) 		XMESH_MANAGER->AddXmeshStatic("ob176", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob176"), scale));
	if (objectNumber == 178) 		XMESH_MANAGER->AddXmeshStatic("ob177", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob177"), scale));
	
	if (objectNumber == 179) 		XMESH_MANAGER->AddXmeshStatic("ob178", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob178"), scale));
	if (objectNumber == 180) 		XMESH_MANAGER->AddXmeshStatic("ob179", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob179"), scale));
	if (objectNumber == 181) 		XMESH_MANAGER->AddXmeshStatic("ob180", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob180"), scale));
	if (objectNumber == 182) 		XMESH_MANAGER->AddXmeshStatic("ob181", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob181"), scale));
	if (objectNumber == 183) 		XMESH_MANAGER->AddXmeshStatic("ob182", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob182"), scale));
	
	if (objectNumber == 184) 		XMESH_MANAGER->AddXmeshStatic("ob183", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob183"), scale));
	if (objectNumber == 185) 		XMESH_MANAGER->AddXmeshStatic("ob184", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob184"), scale));
	if (objectNumber == 186) 		XMESH_MANAGER->AddXmeshStatic("ob185", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob185"), scale));
	if (objectNumber == 187) 		XMESH_MANAGER->AddXmeshStatic("ob186", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob186"), scale));
	if (objectNumber == 188) 		XMESH_MANAGER->AddXmeshStatic("ob187", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob187"), scale));
	
	if (objectNumber == 189) 		XMESH_MANAGER->AddXmeshStatic("portal1", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_portal1"), scale));
	if (objectNumber == 190) 		XMESH_MANAGER->AddXmeshStatic("portal2", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_portal2"), scale));
	if (objectNumber == 191) 		XMESH_MANAGER->AddXmeshStatic("portal3", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_portal3"), scale));
	if (objectNumber == 192) 		XMESH_MANAGER->AddXmeshStatic("portal4", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_portal4"), scale));
									



	
	D3DXMatrixRotationY(&matRotate, D3DXToRadian(180));

	if (objectNumber == 1)   tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob000"), &matRotate));
	if (objectNumber == 2)   tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob001"), &matRotate));
	if (objectNumber == 3)   tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob002"), &matRotate));
	if (objectNumber == 4)   tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob003"), &matRotate));
	if (objectNumber == 5)   tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob004"), &matRotate));
	if (objectNumber == 6)   tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob005"), &matRotate));
	if (objectNumber == 7)   tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob006"), &matRotate));
	if (objectNumber == 8)   tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob007"), &matRotate));
	if (objectNumber == 9)   tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob008"), &matRotate));
	if (objectNumber == 10)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob009"), &matRotate));
	if (objectNumber == 11)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob010"), &matRotate));
	if (objectNumber == 12)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob011"), &matRotate));
	if (objectNumber == 13)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob012"), &matRotate));
	if (objectNumber == 14)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob013"), &matRotate));
	if (objectNumber == 15)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob014"), &matRotate));
	if (objectNumber == 16)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob015"), &matRotate));
							 
	if (objectNumber == 18)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob017"), &matRotate));
	if (objectNumber == 19)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob018"), &matRotate));
	if (objectNumber == 20)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob019"), &matRotate));
	if (objectNumber == 21)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob020"), &matRotate));
	if (objectNumber == 22)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob021"), &matRotate));
	if (objectNumber == 23)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob022"), &matRotate));
	if (objectNumber == 24)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob023"), &matRotate));
	if (objectNumber == 25)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob024"), &matRotate));
	if (objectNumber == 26)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob025"), &matRotate));
							 
	if (objectNumber == 27)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob026"), &matRotate));
	if (objectNumber == 28)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob027"), &matRotate));
	if (objectNumber == 29)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob028"), &matRotate));
	if (objectNumber == 30)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob029"), &matRotate));
	if (objectNumber == 31)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob030"), &matRotate));
	if (objectNumber == 32)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob031"), &matRotate));
	if (objectNumber == 33)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob032"), &matRotate));
							 
	if (objectNumber == 35)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob034"), &matRotate));
	if (objectNumber == 36)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob035"), &matRotate));
	if (objectNumber == 37)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob036"), &matRotate));
	if (objectNumber == 38)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob037"), &matRotate));
	if (objectNumber == 39)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob038"), &matRotate));
	if (objectNumber == 40)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob039"), &matRotate));
	if (objectNumber == 41)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob040"), &matRotate));
	if (objectNumber == 42)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob041"), &matRotate));
	if (objectNumber == 43)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob042"), &matRotate));
	if (objectNumber == 44)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob043"), &matRotate));
	if (objectNumber == 45)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob044"), &matRotate));
	if (objectNumber == 46)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob045"), &matRotate));
	if (objectNumber == 47)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob046"), &matRotate));
	if (objectNumber == 48)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob047"), &matRotate));
	if (objectNumber == 49)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob048"), &matRotate));
							 
	if (objectNumber == 51)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob050"), &matRotate));
	if (objectNumber == 52)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob051"), &matRotate));
	if (objectNumber == 53)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob052"), &matRotate));
	if (objectNumber == 54)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob053"), &matRotate));
	if (objectNumber == 55)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob054"), &matRotate));
	if (objectNumber == 56)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob055"), &matRotate));
							 
	if (objectNumber == 57)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob056"), &matRotate));
	if (objectNumber == 58)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob057"), &matRotate));
	if (objectNumber == 59)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob058"), &matRotate));
	if (objectNumber == 60)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob059"), &matRotate));
	if (objectNumber == 61)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob060"), &matRotate));
	if (objectNumber == 62)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob061"), &matRotate));
							 
	if (objectNumber == 63)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob062"), &matRotate));
	if (objectNumber == 64)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob063"), &matRotate));
	if (objectNumber == 65)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob064"), &matRotate));
	if (objectNumber == 66)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob065"), &matRotate));
	if (objectNumber == 67)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob066"), &matRotate));
	if (objectNumber == 68)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob067"), &matRotate));
							 
	if (objectNumber == 69)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob068"), &matRotate));
	if (objectNumber == 70)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob069"), &matRotate));
	if (objectNumber == 71)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob070"), &matRotate));
	if (objectNumber == 72)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob071"), &matRotate));
	if (objectNumber == 73)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob072"), &matRotate));
	if (objectNumber == 74)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob073"), &matRotate));
							 
	if (objectNumber == 75)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob074"), &matRotate));
	if (objectNumber == 76)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob075"), &matRotate));
	if (objectNumber == 77)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob076"), &matRotate));
	if (objectNumber == 78)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob077"), &matRotate));
	if (objectNumber == 79)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob078"), &matRotate));
							 
	if (objectNumber == 80)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob079"), &matRotate));
	if (objectNumber == 81)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob080"), &matRotate));
	if (objectNumber == 82)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob081"), &matRotate));
	if (objectNumber == 83)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob082"), &matRotate));
	if (objectNumber == 84)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob083"), &matRotate));
							 
	if (objectNumber == 85)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob084"), &matRotate));
	if (objectNumber == 86)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob085"), &matRotate));
	if (objectNumber == 87)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob086"), &matRotate));
	if (objectNumber == 88)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob087"), &matRotate));
	if (objectNumber == 89)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob088"), &matRotate));
	if (objectNumber == 90)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob089"), &matRotate));
	if (objectNumber == 91)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob090"), &matRotate));
	if (objectNumber == 92)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob091"), &matRotate));
	if (objectNumber == 93)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob092"), &matRotate));
	if (objectNumber == 94)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob093"), &matRotate));
	if (objectNumber == 95)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob094"), &matRotate));
	if (objectNumber == 96)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob095"), &matRotate));
	if (objectNumber == 97)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob096"), &matRotate));
	if (objectNumber == 98)  tempObect->setMesh(RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob097"), &matRotate));

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
		tempObect->SetObjectNumber(objectNumber);
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

