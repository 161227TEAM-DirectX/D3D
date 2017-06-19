#pragma once

#define g_pLoading cLoading::GetInstance()

class cLoading
{
	SINGLETONE(cLoading);

public:
	void Init();
	void Destroy();

private:
	void FxRegist();		//Fx 경로 등록
	void HeightRegist();	//높이맵 경로 등록
	void TileRegist();		//타일맵 경로 등록
	void SplatRegist();		//스플랫 경로 등록
	void BrushRegist();		//브러쉬 경로 등록
	void SoundRegist(); 	//사운드 경로 등록
	void ImageRegist();		//이미지 경로 등록
};

