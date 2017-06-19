#pragma once

#define g_pLoading cLoading::GetInstance()

class cLoading
{
	SINGLETONE(cLoading);

public:
	void Init();
	void Destroy();

private:
	void FxRegist();		//Fx ��� ���
	void HeightRegist();	//���̸� ��� ���
	void TileRegist();		//Ÿ�ϸ� ��� ���
	void SplatRegist();		//���÷� ��� ���
	void BrushRegist();		//�귯�� ��� ���
	void SoundRegist(); 	//���� ��� ���
	void ImageRegist();		//�̹��� ��� ���
};

