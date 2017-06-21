#pragma once

#define REGIST_SGT cRegistBase::GetInstance()

class cRegistBase
{
	SINGLETONE(cRegistBase);

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
	void UIRegist();			//UI 경로 등록
	void AniRegist();			//애니메이션 경로 등록
	void XMeshStaticRegist();	//X메쉬스태틱 경로 등록
};

