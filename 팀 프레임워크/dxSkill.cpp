#include "stdafx.h"
#include "dxSkill.h"
//
//HRESULT dxSkill::init()
//{
//	//PSM->initPS(_actionPS,"����");
//	//_actionSphereCollision->setBound(&_actionTrans->GetWorldPosition(),);
//	return S_OK;
//}
//
//void dxSkill::release()
//{
//
//}
//
//void dxSkill::update()
//{
//	
//	if (_SkillRenderType == SR_One)//����ų��
//	{
//		//��ų ����
//		if (_resetTime <= _currentResetTime)
//		{
//			_skillFinshOn = false;
//			this->Reset();
//			if (_preparePS != NULL) { _preparePS->reset(); }
//			if (_actionPS != NULL) { _actionPS->reset(); }
//			if (_finishPS != NULL) { _finishPS->reset(); }
//
//			//_skillReset = false;
//			_currentResetTime = 0.0f;
//		}
//		//�����غ�
//		if (_skillStartOn) { if ((_skillActionOn = !this->Prepare()) == TRUE) { _skillStartOn = false; } }
//		//�׼�
//		if (_skillActionOn) { if ((_skillFinshOn = !this->Action()) == TRUE) { _skillActionOn = false; } }
//		//�ǴϽ�
//		if (_skillFinshOn) { this->Finsh(); _currentResetTime += _timeDelta; }
//	}
//	else if (_SkillRenderType == SR_Array || _SkillRenderType == SR_Big)//�迭�� �Ǵ� ��
//	{
//		//��ų ����
//		if (_skillResetOn) { this->Reset(); _skillResetOn = false; }
//		//�����غ�
//		if (_skillStartOn) { this->Prepare(); }
//		//�׼�
//		if (_skillActionOn) { this->Action(); }
//		//�ǴϽ�
//		if (_skillFinshOn) { this->Finsh();  }
//	}
//	else if(_SkillRenderType == SR_Custom)
//	{
//		//��ų ����
//		if (_skillResetOn) { this->Reset(); _skillResetOn = false; }
//		//�׼�
//		if (_skillStartOn) { this->Action(); }
//	}
//
//}
//
//void dxSkill::render()
//{
//	if (_SkillRenderType == SR_One)//����ų��
//	{
//		if (_skillStartOn)  { if (_preparePS != NULL) _preparePS->render(); }
//		if (_skillActionOn) { if (_actionPS != NULL) _actionPS->render(); }
//		if (_skillFinshOn)  { if (_finishPS != NULL) _finishPS->render(); }
//	}
//	else if (_SkillRenderType == SR_Array)//�迭��
//	{
//		if (_skillStartOn) 
//		{
//			if (_vPrepaerPS.empty() == FALSE)	{ for (int i = 0; i < _vPrepaerPS.size(); i++) { _vPrepaerPS[i]->render(); }	}
//		}
//		if (_skillActionOn)
//		{
//			if (_vActionPS.empty() == FALSE)	{ for (int i = 0; i < _vActionPS.size(); i++) { _vActionPS[i]->render(); }	}
//		}
//		if (_skillFinshOn)
//		{
//			if (_vFinishPS.empty() == FALSE)	{ for (int i = 0; i < _vFinishPS.size(); i++) { _vFinishPS[i]->render(); } }
//		}
//	}
//	else if (_SkillRenderType == SR_Big)//���
//	{
//
// 		if (_skillStartOn)
//		{
//			for (int num = 0; num < _pvPrepaerMaxNum; num++)
//			{
//				if (_pvPrepaerPS[num].empty() == FALSE) { for (int i = 0; i < _pvPrepaerPS[num].size(); i++) { _pvPrepaerPS[num][i]->render(); } }
//			}
//			
//		}
//		if (_skillActionOn)
//		{
//			for (int num = 0; num < _pvActionMaxNum; num++)
//			{
//				if (_pvActionPS[num].empty() == FALSE) { for (int i = 0; i < _pvActionPS[num].size(); i++) { _pvActionPS[num][i]->render(); } }
//			}
//		}
//		if (_skillFinshOn)
//		{
//			for (int num = 0; num < _pvActionMaxNum; num++)
//			{
//				if (_pvFinishPS[num].empty() == FALSE) { for (int i = 0; i < _pvFinishPS[num].size(); i++) { _pvFinishPS[num][i]->render(); } }
//			}
//		}
//	}
//	else if (_SkillRenderType == SR_Custom)//Ŀ���ҿ�
//	{
//		//if (_skillStartOn) { this->RenderPrepare(); }
//		if (_skillActionOn) { this->RenderAction(); }
//		//if (_skillFinshOn) { this->RenderFinsh(); }
//	}
//}
