#pragma once

#define REGIST_SGT cRegistBase::GetInstance()

class cRegistBase
{
	SINGLETONE(cRegistBase);

public:
	void Init();
	void Destroy();

private:
	void FxRegist();			//Fx ��� ���
	void HeightRegist();		//���̸� ��� ���
	void TileRegist();			//Ÿ�ϸ� ��� ���
	void SplatRegist();			//���÷� ��� ���
	void BrushRegist();			//�귯�� ��� ���
	void SoundRegist(); 		//���� ��� ���
	void UIRegist();			//UI ��� ���
	void AniRegist();			//�ִϸ��̼� ��� ���
	void XMeshStaticRegist();	//X�޽�����ƽ ��� ���
};

