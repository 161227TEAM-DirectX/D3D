#include "stdafx.h"
#include "cLoading.h"

cLoading::cLoading()
{	
}


cLoading::~cLoading()
{	
}

void cLoading::Init()
{
	//========================================================================
	//±âº» ¼³Á¤ ÃÊ±âÈ­
	//========================================================================
	SetRandomSeed();					//·£´ý½Ãµå ÃÊ±âÈ­
	CreateDevice();						//µð¹ÙÀÌ½º ÃÊ±âÈ­
	

	//========================================================================
	//°ÔÀÓ¿¡ »ç¿ëÇÒ ÆÄÀÏ°æ·Î µî·Ï
	//========================================================================
	FxRegist();
	HeightRegist();
	TileRegist();
	SplatRegist();
	BrushRegist();
	SoundRegist();
	ImageRegist();
	AniRegist();
	XMeshRegist();

	//========================================================================
	//¸Å´ÏÁ® ÃÊ±âÈ­
	//========================================================================
	KEYMANAGER->init();					//Å°¸Å´ÏÁ® ÃÊ±âÈ­
	TIMEMANAGER->init();				//Å¸ÀÓ¸Å´ÏÁ® ÃÊ±âÈ­
	SCENEMANAGER->init();				//¾À¸Å´ÏÁ® ÃÊ±âÈ­
	FONTMANAGER->init();				//ÆùÆ®¸Å´ÏÁ® ÃÊ±âÈ­
	GIZMOMANAGER->init();				//±âÁî¸ð¸Å´ÏÁ® ÃÊ±âÈ­
	RM_TEXTURE->init();					//RMÅØ½ºÃÄ ÃÊ±âÈ­
	RM_SHADERFX->init();				//RM¼ÎÀÌ´õFX ÃÊ±âÈ­
	RM_XMESH->init();					//RM½ºÅÂÆ½X¸Þ½¬ ÃÊ±âÈ­
	RM_SKINNED->init();					//RM½ºÅ²µåX¸Þ½¬ ÃÊ±âÈ­
	PHYSICSMANAGER->init();				//ÇÇÁ÷½º¸Å´ÏÁ® ÃÊ±âÈ­
	SPRITEMANAGER->init();				//½ºÇÁ¶óÀÌÆ®¸Å´ÏÁ® ÃÊ±âÈ­
	PSM->ParticleSystemSetInit();		//ÆÄÆ¼Å¬½Ã½ºÅÛ¸Å´ÏÁ® ÃÊ±âÈ­
	SOUNDMANAGER->init();				//»ç¿îµå¸Å´ÏÀúÃÊ±âÈ­

	

}

void cLoading::Destroy()
{
	//Å°¸Å´ÏÁ® ½Ì±ÛÅæ ÇØÁ¦
	KEYMANAGER->release();
	KEYMANAGER->releaseSingleton();
	//Å¸ÀÓ¸Å´ÏÁ® ½Ì±ÛÅæ ÇØÁ¦
	TIMEMANAGER->release();
	TIMEMANAGER->releaseSingleton();
	//¾À¸Å´ÏÁ® ½Ì±ÛÅæ ÇØÁ¦
	SCENEMANAGER->release();
	SCENEMANAGER->releaseSingleton();
	//ÆùÆ®¸Å´ÏÁ® ½Ì±ÛÅæ ÇØÁ¦
	FONTMANAGER->release();
	FONTMANAGER->releaseSingleton();
	//±âÁî¸ð¸Å´ÏÁ® ½Ì±ÛÅæ ÇØÁ¦
	GIZMOMANAGER->release();
	GIZMOMANAGER->releaseSingleton();
	//¸®¼Ò½º¸Å´ÏÁ® ½Ì±ÛÅæ ÇØÁ¦
	RM_TEXTURE->clearResource();
	RM_TEXTURE->releaseSingleton();
	RM_SHADERFX->clearResource();
	RM_SHADERFX->releaseSingleton();
	RM_XMESH->clearResource();
	RM_XMESH->releaseSingleton();
	RM_SKINNED->clearResource();
	RM_SKINNED->releaseSingleton();
	//ÇÇÁ÷½º¸Å´ÏÁ® ½Ì±ÛÅæ ÇØÁ¦
	PHYSICSMANAGER->release();
	PHYSICSMANAGER->releaseSingleton();
	//½ºÇÁ¶óÀÌÆ®¸Å´ÏÁ® ½Ì±ÛÅæ ÇØÁ¦
	SPRITEMANAGER->release();
	SPRITEMANAGER->releaseSingleton();
	//ÆÄÆ¼Å¬½Ã½ºÅÛ¸Å´ÏÁ® ½Ì±ÛÅæ ÇØÁ¦
	PSM->ParticleSystemSetRelease();
	PSM->releaseSingleton();

	SOUNDMANAGER->release();
	SOUNDMANAGER->releaseSingleton();

	//µð¹ÙÀÌ½º ÇØÁ¦
	ReleaseDevice();
}




void cLoading::FxRegist()
{
	FILEPATH_MANAGER->AddFilepath("FX_ÁöÇü±âº»", "Resource/Maptool/Shaders/TerrainBase.fx");
}

void cLoading::HeightRegist()
{
	FILEPATH_MANAGER->AddFilepath("³ôÀÌ¸Ê_1", "Resource/Maptool/Textures/RAW/1.png");
	FILEPATH_MANAGER->AddFilepath("³ôÀÌ¸Ê_2", "Resource/Maptool/Textures/RAW/2.png");
	FILEPATH_MANAGER->AddFilepath("³ôÀÌ¸Ê_3", "Resource/Maptool/Textures/RAW/3.png");
	FILEPATH_MANAGER->AddFilepath("³ôÀÌ¸Ê_4", "Resource/Maptool/Textures/RAW/4.png");
	FILEPATH_MANAGER->AddFilepath("³ôÀÌ¸Ê_5", "Resource/Maptool/Textures/RAW/5.png");
	FILEPATH_MANAGER->AddFilepath("³ôÀÌ¸Ê_6", "Resource/Maptool/Textures/RAW/6.png");
}

void cLoading::TileRegist()
{
	FILEPATH_MANAGER->AddFilepath("Å¸ÀÏ¸Ê_1", "Resource/Maptool/Textures/Tile/1.png");
	FILEPATH_MANAGER->AddFilepath("Å¸ÀÏ¸Ê_2", "Resource/Maptool/Textures/Tile/2.png");
	FILEPATH_MANAGER->AddFilepath("Å¸ÀÏ¸Ê_3", "Resource/Maptool/Textures/Tile/3.png");
	FILEPATH_MANAGER->AddFilepath("Å¸ÀÏ¸Ê_4", "Resource/Maptool/Textures/Tile/4.png");
	FILEPATH_MANAGER->AddFilepath("Å¸ÀÏ¸Ê_5", "Resource/Maptool/Textures/Tile/5.png");
	FILEPATH_MANAGER->AddFilepath("Å¸ÀÏ¸Ê_6", "Resource/Maptool/Textures/Tile/6.png");
	FILEPATH_MANAGER->AddFilepath("Å¸ÀÏ¸Ê_7", "Resource/Maptool/Textures/Tile/13.png");
	FILEPATH_MANAGER->AddFilepath("Å¸ÀÏ¸Ê_8", "Resource/Maptool/Textures/Tile/12.png");
	FILEPATH_MANAGER->AddFilepath("Å¸ÀÏ¸Ê_9", "Resource/Maptool/Textures/Tile/21.png");
	FILEPATH_MANAGER->AddFilepath("Å¸ÀÏ¸Ê_10", "Resource/Maptool/Textures/Tile/10.png");
	FILEPATH_MANAGER->AddFilepath("Å¸ÀÏ¸Ê_11", "Resource/Maptool/Textures/Tile/11.png");
	FILEPATH_MANAGER->AddFilepath("Å¸ÀÏ¸Ê_12", "Resource/Maptool/Textures/Tile/12.png");
	FILEPATH_MANAGER->AddFilepath("Å¸ÀÏ¸Ê_13", "Resource/Maptool/Textures/Tile/13.png");
	FILEPATH_MANAGER->AddFilepath("Å¸ÀÏ¸Ê_14", "Resource/Maptool/Textures/Tile/14.png");
	FILEPATH_MANAGER->AddFilepath("Å¸ÀÏ¸Ê_15", "Resource/Maptool/Textures/Tile/15.png");
	FILEPATH_MANAGER->AddFilepath("Å¸ÀÏ¸Ê_16", "Resource/Maptool/Textures/Tile/8.png");
	FILEPATH_MANAGER->AddFilepath("Å¸ÀÏ¸Ê_17", "Resource/Maptool/Textures/Tile/3.png");
	FILEPATH_MANAGER->AddFilepath("Å¸ÀÏ¸Ê_18", "Resource/Maptool/Textures/Tile/18.png");
	FILEPATH_MANAGER->AddFilepath("Å¸ÀÏ¸Ê_19", "Resource/Maptool/Textures/Tile/19.png");
	FILEPATH_MANAGER->AddFilepath("Å¸ÀÏ¸Ê_20", "Resource/Maptool/Textures/Tile/20.png");
	FILEPATH_MANAGER->AddFilepath("Å¸ÀÏ¸Ê_21", "Resource/Maptool/Textures/Tile/21.png");
	FILEPATH_MANAGER->AddFilepath("Å¸ÀÏ¸Ê_22", "Resource/Maptool/Textures/Tile/22.png");
	FILEPATH_MANAGER->AddFilepath("Å¸ÀÏ¸Ê_23", "Resource/Maptool/Textures/Tile/14.png");
	FILEPATH_MANAGER->AddFilepath("Å¸ÀÏ¸Ê_24", "Resource/Maptool/Textures/Tile/16.png");
	FILEPATH_MANAGER->AddFilepath("Å¸ÀÏ¸Ê_25", "Resource/Maptool/Textures/Tile/4.png");
}

void cLoading::SplatRegist()
{
	FILEPATH_MANAGER->AddFilepath("½ºÇÃ·§_1", "Resource/Maptool/Textures/Splat/1.png");
	FILEPATH_MANAGER->AddFilepath("½ºÇÃ·§_2", "Resource/Maptool/Textures/Splat/2.png");
	FILEPATH_MANAGER->AddFilepath("½ºÇÃ·§_3", "Resource/Maptool/Textures/Splat/3.png");
	FILEPATH_MANAGER->AddFilepath("½ºÇÃ·§_4", "Resource/Maptool/Textures/Splat/4.png");
	FILEPATH_MANAGER->AddFilepath("½ºÇÃ·§_5", "Resource/Maptool/Textures/Splat/5.png");
	FILEPATH_MANAGER->AddFilepath("½ºÇÃ·§_6", "Resource/Maptool/Textures/Splat/6.png");
}

void cLoading::BrushRegist()
{
	FILEPATH_MANAGER->AddFilepath("ºê·¯½¬_brush00", "Resource/Maptool/Textures/Brush/brush00.png");
	FILEPATH_MANAGER->AddFilepath("ºê·¯½¬_brush01", "Resource/Maptool/Textures/Brush/brush01.png");
}

void cLoading::SoundRegist()
{
	FILEPATH_MANAGER->AddFilepath("ÇÊµå", "Sound/FieldBGM1.mp3");
	FILEPATH_MANAGER->AddFilepath("º¸½º", "Sound/BossBGM1.mp3");
	FILEPATH_MANAGER->AddFilepath("¸¶À»", "Sound/TownBGM1.mp3");
	FILEPATH_MANAGER->AddFilepath("°ø°Ý", "Sound/°ø°Ý1.mp3");
	FILEPATH_MANAGER->AddFilepath("º£±â", "Sound/º£±â1.mp3");
	FILEPATH_MANAGER->AddFilepath("°ÉÀ½¼Ò¸®", "Sound/°ÉÀ½¼Ò¸®1.mp3");
}

void cLoading::ImageRegist()
{
	FILEPATH_MANAGER->AddFilepath("ÀÌ¹ÌÁö_¸®ÀÚ¸ù", "Resource/ÀÌ¹ÌÁö/¸®ÀÚ¸ù.png");
	FILEPATH_MANAGER->AddFilepath("ÀÌ¹ÌÁö_°ÅºÏ¿Õ", "Resource/ÀÌ¹ÌÁö/°ÅºÏ¿Õ.png");
	FILEPATH_MANAGER->AddFilepath("ÀÌ¹ÌÁö_ÀÌ»óÇØ²É", "Resource/ÀÌ¹ÌÁö/ÀÌ»óÇØ²É.png");
}

void cLoading::AniRegist()
{
	FILEPATH_MANAGER->AddFilepath("cat", "Resource/ÀÌ¹ÌÁö/cat.png");

	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å00", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å/output-0.png");
	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å01", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å/output-1.png");
	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å02", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å/output-2.png");
	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å03", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å/output-3.png");
	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å04", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å/output-4.png");
	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å05", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å/output-5.png");
	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å06", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å/output-6.png");
	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å07", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å/output-7.png");
	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å08", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å/output-8.png");
	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å09", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å/output-9.png");
	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å10", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å/output-10.png");
	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å11", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å/output-11.png");
	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å12", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å/output-12.png");
	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å13", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å/output-13.png");
	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å14", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å/output-14.png");
	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å15", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å/output-15.png");

	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å00-2", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å2/output-0.png");
	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å01-2", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å2/output-1.png");
	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å02-2", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å2/output-2.png");
	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å03-2", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å2/output-3.png");
	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å04-2", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å2/output-4.png");
	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å05-2", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å2/output-5.png");
	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å06-2", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å2/output-6.png");
	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å07-2", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å2/output-7.png");
	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å08-2", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å2/output-8.png");
	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å09-2", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å2/output-9.png");
	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å10-2", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å2/output-10.png");
	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å11-2", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å2/output-11.png");
	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å12-2", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å2/output-12.png");
	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å13-2", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å2/output-13.png");
	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å14-2", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å2/output-14.png");
	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å15-2", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å2/output-15.png");

	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å00-3", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å3/output-0.png");
	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å01-3", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å3/output-1.png");
	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å02-3", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å3/output-2.png");
	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å03-3", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å3/output-3.png");
	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å04-3", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å3/output-4.png");
	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å05-3", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å3/output-5.png");
	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å06-3", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å3/output-6.png");
	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å07-3", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å3/output-7.png");
	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å08-3", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å3/output-8.png");
	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å09-3", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å3/output-9.png");
	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å10-3", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å3/output-10.png");
	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å11-3", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å3/output-11.png");
	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å12-3", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å3/output-12.png");
	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å13-3", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å3/output-13.png");
	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å14-3", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å3/output-14.png");
	FILEPATH_MANAGER->AddFilepath("ÄÆ½Å15-3", "Resource/ÀÌ¹ÌÁö/ÄÆ½Å3/output-15.png");
}

void cLoading::XMeshRegist()
{
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob000", "Resource/Maptool/Meshes/stormTown1/1.build/1/1.X");
}
