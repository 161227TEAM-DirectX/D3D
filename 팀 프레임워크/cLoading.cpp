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
	FxRegist();							//Fx °æ·Î µî·Ï
	HeightRegist();						//³ôÀÌ¸Ê °æ·Î µî·Ï
	TileRegist();						//Å¸ÀÏ¸Ê °æ·Î µî·Ï
	SplatRegist();						//½ºÇÃ·§ °æ·Î µî·Ï
	BrushRegist();						//ºê·¯½¬ °æ·Î µî·Ï
	SoundRegist();						//»ç¿îµå °æ·Î µî·Ï
	ImageRegist();						//ÀÌ¹ÌÁö °æ·Î µî·Ï
	AniRegist();						//¾Ö´Ï¸ÞÀÌ¼Ç(ÀÌ¹ÌÁö) °æ·Î µî·Ï
	XMeshStaticRegist();				//X¸Þ½¬½ºÅÂÆ½ °æ·Î µî·Ï
	XMeshSkinnedRegist();				//X¸Þ½¬½ºÅ²µå °æ·Î µî·Ï

	XMeshStaticLoading();				//X¸Þ½¬½ºÅÂÆ½ ·Îµù
	XMeshSkinnedLoading();				//X¸Þ½¬½ºÅ²µå ·Îµù



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

void cLoading::XMeshStaticRegist()
{
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob000", "Resource/Maptool/Meshes/stormTown1/1.build/1/1.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob001", "Resource/Maptool/Meshes/stormTown1/1.build/2/2.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob002", "Resource/Maptool/Meshes/stormTown1/1.build/3/3.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob003", "Resource/Maptool/Meshes/stormTown1/1.build/4/4.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob004", "Resource/Maptool/Meshes/stormTown1/1.build/5/5.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob005", "Resource/Maptool/Meshes/stormTown1/1.build/6/6.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob006", "Resource/Maptool/Meshes/stormTown1/1.build/7/7.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob007", "Resource/Maptool/Meshes/stormTown1/1.build/8/8.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob008", "Resource/Maptool/Meshes/stormTown1/1.build/9/9.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob009", "Resource/Maptool/Meshes/stormTown1/1.build/10/10.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob010", "Resource/Maptool/Meshes/stormTown1/1.build/11/11.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob011", "Resource/Maptool/Meshes/stormTown1/1.build/12/12.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob012", "Resource/Maptool/Meshes/stormTown1/1.build/13/13.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob013", "Resource/Maptool/Meshes/stormTown1/1.build/14/14.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob014", "Resource/Maptool/Meshes/stormTown1/1.build/15/15.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob015", "Resource/Maptool/Meshes/stormTown1/1.build/16/16.X");

	FILEPATH_MANAGER->AddFilepath("Xmesh_ob017", "Resource/Maptool/Meshes/stormTown1/2.townfence/1/1.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob018", "Resource/Maptool/Meshes/stormTown1/2.townfence/2/2.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob019", "Resource/Maptool/Meshes/stormTown1/2.townfence/3/3.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob020", "Resource/Maptool/Meshes/stormTown1/2.townfence/4/4.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob021", "Resource/Maptool/Meshes/stormTown1/2.townfence/5/5.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob022", "Resource/Maptool/Meshes/stormTown1/2.townfence/6/6.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob023", "Resource/Maptool/Meshes/stormTown1/2.townfence/7/7.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob024", "Resource/Maptool/Meshes/stormTown1/2.townfence/8/8.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob025", "Resource/Maptool/Meshes/stormTown1/2.townfence/9/9.X");

	FILEPATH_MANAGER->AddFilepath("Xmesh_ob026", "Resource/Maptool/Meshes/stormTown1/3.tree/1/1.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob027", "Resource/Maptool/Meshes/stormTown1/3.tree/2/2.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob028", "Resource/Maptool/Meshes/stormTown1/3.tree/3/3.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob029", "Resource/Maptool/Meshes/stormTown1/3.tree/4/4.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob030", "Resource/Maptool/Meshes/stormTown1/3.tree/5/5.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob031", "Resource/Maptool/Meshes/stormTown1/3.tree/6/6.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob032", "Resource/Maptool/Meshes/stormTown1/3.tree/7/7.X");

	FILEPATH_MANAGER->AddFilepath("Xmesh_ob034", "Resource/Maptool/Meshes/stormTown1/4.townObject/1/1.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob035", "Resource/Maptool/Meshes/stormTown1/4.townObject/2/2.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob036", "Resource/Maptool/Meshes/stormTown1/4.townObject/3/3.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob037", "Resource/Maptool/Meshes/stormTown1/4.townObject/4/4.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob038", "Resource/Maptool/Meshes/stormTown1/4.townObject/5/5.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob039", "Resource/Maptool/Meshes/stormTown1/4.townObject/6/6.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob040", "Resource/Maptool/Meshes/stormTown1/4.townObject/7/7.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob041", "Resource/Maptool/Meshes/stormTown1/4.townObject/8/8.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob042", "Resource/Maptool/Meshes/stormTown1/4.townObject/9/9.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob043", "Resource/Maptool/Meshes/stormTown1/4.townObject/10/10.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob044", "Resource/Maptool/Meshes/stormTown1/4.townObject/11/11.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob045", "Resource/Maptool/Meshes/stormTown1/4.townObject/12/12.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob046", "Resource/Maptool/Meshes/stormTown1/4.townObject/13/13.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob047", "Resource/Maptool/Meshes/stormTown1/4.townObject/14/14.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob048", "Resource/Maptool/Meshes/stormTown1/4.townObject/15/15.X");

	FILEPATH_MANAGER->AddFilepath("Xmesh_ob050", "Resource/Maptool/Meshes/stormTown1/5.townSmallFence/1/1.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob051", "Resource/Maptool/Meshes/stormTown1/5.townSmallFence/2/2.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob052", "Resource/Maptool/Meshes/stormTown1/5.townSmallFence/3/3.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob053", "Resource/Maptool/Meshes/stormTown1/5.townSmallFence/4/4.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob054", "Resource/Maptool/Meshes/stormTown1/5.townSmallFence/5/5.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob055", "Resource/Maptool/Meshes/stormTown1/5.townSmallFence/6/6.X");

	FILEPATH_MANAGER->AddFilepath("Xmesh_ob056", "Resource/Maptool/Meshes/stormTown2/6.boxObject/1/1.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob057", "Resource/Maptool/Meshes/stormTown2/6.boxObject/2/2.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob058", "Resource/Maptool/Meshes/stormTown2/6.boxObject/3/3.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob059", "Resource/Maptool/Meshes/stormTown2/6.boxObject/4/4.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob060", "Resource/Maptool/Meshes/stormTown2/6.boxObject/5/5.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob061", "Resource/Maptool/Meshes/stormTown2/6.boxObject/6/6.X");

	FILEPATH_MANAGER->AddFilepath("Xmesh_ob062", "Resource/Maptool/Meshes/stormTown2/7.planterBox/1/1.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob063", "Resource/Maptool/Meshes/stormTown2/7.planterBox/2/2.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob064", "Resource/Maptool/Meshes/stormTown2/7.planterBox/3/3.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob065", "Resource/Maptool/Meshes/stormTown2/7.planterBox/4/4.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob066", "Resource/Maptool/Meshes/stormTown2/7.planterBox/5/5.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob067", "Resource/Maptool/Meshes/stormTown2/7.planterBox/6/6.X");

	FILEPATH_MANAGER->AddFilepath("Xmesh_ob068", "Resource/Maptool/Meshes/stormTown2/8.memorial stone/1/1.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob069", "Resource/Maptool/Meshes/stormTown2/8.memorial stone/2/2.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob070", "Resource/Maptool/Meshes/stormTown2/8.memorial stone/3/3.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob071", "Resource/Maptool/Meshes/stormTown2/8.memorial stone/4/4.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob072", "Resource/Maptool/Meshes/stormTown2/8.memorial stone/5/5.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob073", "Resource/Maptool/Meshes/stormTown2/8.memorial stone/6/6.X");

	FILEPATH_MANAGER->AddFilepath("Xmesh_ob074", "Resource/Maptool/Meshes/stormTown2/9.shopsign/1/1.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob075", "Resource/Maptool/Meshes/stormTown2/9.shopsign/2/2.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob076", "Resource/Maptool/Meshes/stormTown2/9.shopsign/3/3.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob077", "Resource/Maptool/Meshes/stormTown2/9.shopsign/4/4.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob078", "Resource/Maptool/Meshes/stormTown2/9.shopsign/5/5.X");

	FILEPATH_MANAGER->AddFilepath("Xmesh_ob079", "Resource/Maptool/Meshes/stormTown2/10.lowWall/1/1.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob080", "Resource/Maptool/Meshes/stormTown2/10.lowWall/2/2.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob081", "Resource/Maptool/Meshes/stormTown2/10.lowWall/3/3.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob082", "Resource/Maptool/Meshes/stormTown2/10.lowWall/4/4.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob083", "Resource/Maptool/Meshes/stormTown2/10.lowWall/5/5.X");

	FILEPATH_MANAGER->AddFilepath("Xmesh_ob084", "Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/1/1.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob085", "Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/2/2.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob086", "Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/3/3.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob087", "Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/4/4.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob088", "Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/5/5.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob089", "Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/6/6.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob090", "Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/7/7.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob091", "Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/8/8.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob092", "Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/9/9.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob093", "Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/10/10.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob094", "Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/11/11.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob095", "Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/12/12.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob096", "Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/13/13.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob097", "Resource/Maptool/Meshes/ruinStage/1.ruinStagePyeheo/14/14.X");

	FILEPATH_MANAGER->AddFilepath("Xmesh_ob098", "Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/1/1.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob099", "Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/2/2.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob100", "Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/3/3.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob101", "Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/4/4.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob102", "Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/5/5.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob103", "Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/6/6.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob104", "Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/7/7.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob105", "Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/8/8.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob106", "Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/9/9.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob107", "Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/10/10.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob108", "Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/11/11.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob109", "Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/12/12.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob110", "Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/13/13.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob111", "Resource/Maptool/Meshes/ruinStage/2.ruinStageObject/14/14.X");

	FILEPATH_MANAGER->AddFilepath("Xmesh_ob112", "Resource/Maptool/Meshes/ruinStage/3.ruinStageRock/1/1.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob113", "Resource/Maptool/Meshes/ruinStage/3.ruinStageRock/2/2.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob114", "Resource/Maptool/Meshes/ruinStage/3.ruinStageRock/3/3.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob115", "Resource/Maptool/Meshes/ruinStage/3.ruinStageRock/4/4.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob116", "Resource/Maptool/Meshes/ruinStage/3.ruinStageRock/5/5.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob117", "Resource/Maptool/Meshes/ruinStage/3.ruinStageRock/6/6.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob118", "Resource/Maptool/Meshes/ruinStage/3.ruinStageRock/7/7.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob119", "Resource/Maptool/Meshes/ruinStage/3.ruinStageRock/8/8.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob120", "Resource/Maptool/Meshes/ruinStage/3.ruinStageRock/9/9.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob121", "Resource/Maptool/Meshes/ruinStage/3.ruinStageRock/10/10.X");

	FILEPATH_MANAGER->AddFilepath("Xmesh_ob122", "Resource/Maptool/Meshes/ruinStage/4.ruinStageSpider/1/1.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob123", "Resource/Maptool/Meshes/ruinStage/4.ruinStageSpider/2/2.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob124", "Resource/Maptool/Meshes/ruinStage/4.ruinStageSpider/3/3.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob125", "Resource/Maptool/Meshes/ruinStage/4.ruinStageSpider/4/4.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob126", "Resource/Maptool/Meshes/ruinStage/4.ruinStageSpider/5/5.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob127", "Resource/Maptool/Meshes/ruinStage/4.ruinStageSpider/6/6.X");

	FILEPATH_MANAGER->AddFilepath("Xmesh_ob128", "Resource/Maptool/Meshes/ruinStage/5.ruinStageTree/1/1.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob129", "Resource/Maptool/Meshes/ruinStage/5.ruinStageTree/2/2.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob130", "Resource/Maptool/Meshes/ruinStage/5.ruinStageTree/3/3.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob131", "Resource/Maptool/Meshes/ruinStage/5.ruinStageTree/4/4.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob132", "Resource/Maptool/Meshes/ruinStage/5.ruinStageTree/5/5.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob133", "Resource/Maptool/Meshes/ruinStage/5.ruinStageTree/6/6.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob134", "Resource/Maptool/Meshes/ruinStage/5.ruinStageTree/7/7.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob135", "Resource/Maptool/Meshes/ruinStage/5.ruinStageTree/8/8.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob136", "Resource/Maptool/Meshes/ruinStage/5.ruinStageTree/9/9.X");

	FILEPATH_MANAGER->AddFilepath("Xmesh_ob137", "Resource/Maptool/Meshes/ruinStage/6.ruinStagePiramide/1/1.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob138", "Resource/Maptool/Meshes/ruinStage/6.ruinStagePiramide/2/2.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob139", "Resource/Maptool/Meshes/ruinStage/6.ruinStagePiramide/3/3.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob140", "Resource/Maptool/Meshes/ruinStage/6.ruinStagePiramide/4/4.X");

	FILEPATH_MANAGER->AddFilepath("Xmesh_ob141", "Resource/Maptool/Meshes/ruinStage/7.ruinYelloPyeheo/1/1.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob142", "Resource/Maptool/Meshes/ruinStage/7.ruinYelloPyeheo/2/2.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob143", "Resource/Maptool/Meshes/ruinStage/7.ruinYelloPyeheo/3/3.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob144", "Resource/Maptool/Meshes/ruinStage/7.ruinYelloPyeheo/4/4.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob145", "Resource/Maptool/Meshes/ruinStage/7.ruinYelloPyeheo/5/5.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob146", "Resource/Maptool/Meshes/ruinStage/7.ruinYelloPyeheo/6/6.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob147", "Resource/Maptool/Meshes/ruinStage/7.ruinYelloPyeheo/7/7.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob148", "Resource/Maptool/Meshes/ruinStage/7.ruinYelloPyeheo/8/8.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob149", "Resource/Maptool/Meshes/ruinStage/7.ruinYelloPyeheo/9/9.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob150", "Resource/Maptool/Meshes/ruinStage/7.ruinYelloPyeheo/10/10.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob151", "Resource/Maptool/Meshes/ruinStage/7.ruinYelloPyeheo/11/11.X");

	FILEPATH_MANAGER->AddFilepath("Xmesh_ob152", "Resource/Maptool/Meshes/piramid/1.piramidBuild/1/1.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob153", "Resource/Maptool/Meshes/piramid/1.piramidBuild/2/2.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob154", "Resource/Maptool/Meshes/piramid/1.piramidBuild/3/3.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob155", "Resource/Maptool/Meshes/piramid/1.piramidBuild/4/4.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob156", "Resource/Maptool/Meshes/piramid/1.piramidBuild/5/5.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob157", "Resource/Maptool/Meshes/piramid/1.piramidBuild/6/6.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob158", "Resource/Maptool/Meshes/piramid/1.piramidBuild/7/7.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob159", "Resource/Maptool/Meshes/piramid/1.piramidBuild/8/8.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob160", "Resource/Maptool/Meshes/piramid/1.piramidBuild/9/9.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob161", "Resource/Maptool/Meshes/piramid/1.piramidBuild/10/10.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob162", "Resource/Maptool/Meshes/piramid/1.piramidBuild/11/11.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob163", "Resource/Maptool/Meshes/piramid/1.piramidBuild/12/12.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob164", "Resource/Maptool/Meshes/piramid/1.piramidBuild/13/13.X");

	FILEPATH_MANAGER->AddFilepath("Xmesh_ob165", "Resource/Maptool/Meshes/piramid/2.piramidObject/15/15.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob166", "Resource/Maptool/Meshes/piramid/2.piramidObject/14/14.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob167", "Resource/Maptool/Meshes/piramid/2.piramidObject/3/3.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob168", "Resource/Maptool/Meshes/piramid/2.piramidObject/4/4.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob169", "Resource/Maptool/Meshes/piramid/2.piramidObject/5/5.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob170", "Resource/Maptool/Meshes/piramid/2.piramidObject/6/6.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob171", "Resource/Maptool/Meshes/piramid/2.piramidObject/7/7.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob172", "Resource/Maptool/Meshes/piramid/2.piramidObject/8/8.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob173", "Resource/Maptool/Meshes/piramid/2.piramidObject/9/9.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob174", "Resource/Maptool/Meshes/piramid/2.piramidObject/10/10.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob175", "Resource/Maptool/Meshes/piramid/2.piramidObject/11/11.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob176", "Resource/Maptool/Meshes/piramid/2.piramidObject/12/12.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob177", "Resource/Maptool/Meshes/piramid/2.piramidObject/13/13.X");

	FILEPATH_MANAGER->AddFilepath("Xmesh_ob178", "Resource/Maptool/Meshes/piramid/3.piramidSmallObject/1/1.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob179", "Resource/Maptool/Meshes/piramid/3.piramidSmallObject/2/2.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob180", "Resource/Maptool/Meshes/piramid/3.piramidSmallObject/3/3.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob181", "Resource/Maptool/Meshes/piramid/3.piramidSmallObject/4/4.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob182", "Resource/Maptool/Meshes/piramid/3.piramidSmallObject/5/5.X");

	FILEPATH_MANAGER->AddFilepath("Xmesh_ob183", "Resource/Maptool/Meshes/piramid/4.piramidRock/1/1.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob184", "Resource/Maptool/Meshes/piramid/4.piramidRock/2/2.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob185", "Resource/Maptool/Meshes/piramid/4.piramidRock/3/3.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob186", "Resource/Maptool/Meshes/piramid/4.piramidRock/4/4.X");
	FILEPATH_MANAGER->AddFilepath("Xmesh_ob187", "Resource/Maptool/Meshes/piramid/4.piramidRock/5/5.X");

}

void cLoading::XMeshSkinnedRegist()
{
	D3DXMATRIX scale;
	D3DXMatrixScaling(&scale, 0.5f, 0.5f, 0.5f);

	XMESH_MANAGER->AddXmeshStatic("ob000", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob000"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob001", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob001"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob002", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob002"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob003", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob003"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob004", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob004"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob005", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob005"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob006", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob006"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob007", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob007"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob008", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob008"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob009", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob009"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob010", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob010"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob011", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob011"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob012", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob012"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob013", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob013"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob014", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob014"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob015", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob015"), scale));

	XMESH_MANAGER->AddXmeshStatic("ob017", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob017"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob018", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob018"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob019", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob019"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob020", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob020"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob021", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob021"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob022", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob022"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob023", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob023"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob024", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob024"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob025", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob025"), scale));

	XMESH_MANAGER->AddXmeshStatic("ob026", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob026"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob027", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob027"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob028", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob028"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob029", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob029"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob030", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob030"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob031", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob031"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob032", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob032"), scale));

	XMESH_MANAGER->AddXmeshStatic("ob034", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob034"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob035", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob035"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob036", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob036"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob037", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob037"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob038", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob038"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob039", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob039"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob040", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob040"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob041", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob041"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob042", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob042"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob043", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob043"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob044", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob044"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob045", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob045"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob046", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob046"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob047", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob047"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob048", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob048"), scale));

	XMESH_MANAGER->AddXmeshStatic("ob050", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob050"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob051", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob051"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob052", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob052"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob053", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob053"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob054", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob054"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob055", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob055"), scale));

	XMESH_MANAGER->AddXmeshStatic("ob056", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob056"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob057", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob057"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob058", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob058"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob059", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob059"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob060", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob060"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob061", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob061"), scale));

	XMESH_MANAGER->AddXmeshStatic("ob062", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob062"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob063", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob063"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob064", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob064"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob065", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob065"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob066", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob066"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob067", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob067"), scale));

	XMESH_MANAGER->AddXmeshStatic("ob068", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob068"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob069", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob069"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob070", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob070"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob071", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob071"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob072", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob072"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob073", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob073"), scale));

	XMESH_MANAGER->AddXmeshStatic("ob074", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob074"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob075", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob075"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob076", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob076"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob077", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob077"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob078", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob078"), scale));

	XMESH_MANAGER->AddXmeshStatic("ob079", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob079"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob080", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob080"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob081", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob081"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob082", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob082"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob083", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob083"), scale));

	XMESH_MANAGER->AddXmeshStatic("ob084", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob084"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob085", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob085"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob086", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob086"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob087", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob087"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob088", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob088"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob089", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob089"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob090", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob090"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob091", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob091"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob092", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob092"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob093", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob093"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob094", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob094"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob095", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob095"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob096", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob096"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob097", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob097"), scale));

	XMESH_MANAGER->AddXmeshStatic("ob098", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob098"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob099", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob099"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob100", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob100"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob101", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob101"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob102", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob102"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob103", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob103"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob104", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob104"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob105", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob105"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob106", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob106"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob107", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob107"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob108", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob108"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob109", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob109"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob110", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob110"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob111", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob111"), scale));

	XMESH_MANAGER->AddXmeshStatic("ob112", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob112"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob113", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob113"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob114", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob114"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob115", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob115"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob116", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob116"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob117", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob117"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob118", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob118"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob119", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob119"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob120", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob120"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob121", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob121"), scale));

	XMESH_MANAGER->AddXmeshStatic("ob122", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob122"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob123", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob123"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob124", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob124"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob125", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob125"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob126", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob126"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob127", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob127"), scale));

	XMESH_MANAGER->AddXmeshStatic("ob128", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob128"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob129", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob129"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob130", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob130"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob131", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob131"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob132", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob132"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob133", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob133"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob134", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob134"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob135", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob135"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob136", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob136"), scale));

	XMESH_MANAGER->AddXmeshStatic("ob137", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob137"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob138", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob138"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob139", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob139"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob140", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob140"), scale));

	XMESH_MANAGER->AddXmeshStatic("ob141", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob141"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob142", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob142"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob143", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob143"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob144", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob144"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob145", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob145"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob146", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob146"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob147", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob147"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob148", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob148"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob149", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob149"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob150", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob150"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob151", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob151"), scale));

	XMESH_MANAGER->AddXmeshStatic("ob152", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob152"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob153", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob153"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob154", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob154"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob155", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob155"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob156", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob156"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob157", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob157"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob158", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob158"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob159", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob159"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob160", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob160"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob161", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob161"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob162", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob162"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob163", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob163"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob164", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob164"), scale));

	XMESH_MANAGER->AddXmeshStatic("ob165", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob165"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob166", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob166"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob167", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob167"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob168", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob168"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob169", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob169"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob170", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob170"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob171", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob171"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob172", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob172"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob173", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob173"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob174", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob174"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob175", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob175"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob176", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob176"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob177", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob177"), scale));

	XMESH_MANAGER->AddXmeshStatic("ob178", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob178"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob179", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob179"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob180", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob180"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob181", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob181"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob182", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob182"), scale));

	XMESH_MANAGER->AddXmeshStatic("ob183", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob183"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob184", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob184"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob185", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob185"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob186", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob186"), scale));
	XMESH_MANAGER->AddXmeshStatic("ob187", RM_XMESH->getResource(FILEPATH_MANAGER->GetFilepath("Xmesh_ob187"), scale));

}

void cLoading::XMeshStaticLoading()
{
}

void cLoading::XMeshSkinnedLoading()
{
}