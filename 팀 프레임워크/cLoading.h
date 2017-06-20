#pragma once

#define g_pLoading cLoading::GetInstance()

class cLoading
{
	SINGLETONE(cLoading);

public:
	void Init();
	void Destroy();

private:
	void FxRegist();			//Fx 경로 등록
	void HeightRegist();		//높이맵 경로 등록
	void TileRegist();			//타일맵 경로 등록
	void SplatRegist();			//스플랫 경로 등록
	void BrushRegist();			//브러쉬 경로 등록
	void SoundRegist(); 		//사운드 경로 등록
	void ImageRegist();			//이미지 경로 등록
	void AniRegist();			//애니메이션 경로 등록
	void XMeshStaticRegist();	//X메쉬스태틱 경로 등록
	void XMeshSkinnedRegist();	//X메쉬스킨드 경로 등록

	void XMeshStaticLoading();	//X메쉬스태틱 로딩
	void XMeshSkinnedLoading(); //X메쉬스킨드 로딩
};

