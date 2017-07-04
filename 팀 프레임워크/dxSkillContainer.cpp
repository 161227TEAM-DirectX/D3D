#include "stdafx.h"
#include "dxSkill.h"

HRESULT dxSkillContainer::init()
{
	
	return S_OK;
}

void dxSkillContainer::release()
{

}

void dxSkillContainer::update()
{
	if (_skillStartOn == FALSE) return;

	if (_SkillRenderType == SR_One)//����ų��
	{
		//��ų ����
		if (_resetTime <= _currentResetTime)
		{
			
			this->Reset();
			if (_preparePS != NULL) { _preparePS->reset(); }
			if (_actionPS != NULL) { _actionPS->reset(); }
			if (_finishPS != NULL) { _finishPS->reset(); }

			//_skillReset = false;
			_currentResetTime = 0.0f;

			//���� �ʱ�ȭ
			_skillResetOn = false;
			_skillFinshOn = false;
			_skillActionOn = false;
			_skillFinshOn = false;
			_skillStartOn = false;

		}
		//�����غ�
		if (_skillPrepareOn) { if ((_skillActionOn = !this->Prepare()) == TRUE) { _skillStartOn = false; } }
		//�׼�
		if (_skillActionOn) { if ((_skillFinshOn = !this->Action()) == TRUE) { _skillActionOn = false; } }
		//�ǴϽ�
		if (_skillFinshOn) { this->Finsh(); _currentResetTime += _timeDelta; }
	}
	else if (_SkillRenderType == SR_Array)//��
	{
		//��ų ����
		if (_skillResetOn)
		{

			if (_skillPrepareOn)
			{
				if (_vPrepaerPS.empty() == FALSE) { for (int i = 0; i < _vPrepaerPS.size(); i++) { _vPrepaerPS[i]->reset(); } }
			}
			if (_skillActionOn)
			{
				if (_vActionPS.empty() == FALSE) { for (int i = 0; i < _vActionPS.size(); i++) { _vActionPS[i]->reset(); } }
			}
			if (_skillFinshOn)
			{
				if (_vFinishPS.empty() == FALSE) { for (int i = 0; i < _vFinishPS.size(); i++) { _vFinishPS[i]->reset(); } }
			}

			this->Reset();

			//���� �ʱ�ȭ
			_skillResetOn = false;
			_skillPrepareOn = false;
			_skillActionOn = false;
			_skillFinshOn = false;
			_skillStartOn = false;
		}
		//�����غ�
		if (_skillPrepareOn) { this->Prepare(); }
		//�׼�
		if (_skillActionOn) { this->Action(); }
		//�ǴϽ�
		if (_skillFinshOn) { this->Finsh(); }
	}
	else if (_SkillRenderType == SR_Big)//��
	{
		//��ų ����
		if (_skillResetOn)
		{
			//�⺻ ����
			for (int num = 0; num < _pvPrepaerMaxNum; num++)
			{
				if (_pvPrepaerPS[num].empty() == FALSE) { for (int i = 0; i < _pvPrepaerPS[num].size(); i++) { _pvPrepaerPS[num][i]->reset(); } }
			}
			for (int num = 0; num < _pvActionMaxNum; num++)
			{
				if (_pvActionPS[num].empty() == FALSE) { for (int i = 0; i < _pvActionPS[num].size(); i++) { _pvActionPS[num][i]->reset(); } }
			}
			for (int num = 0; num < _pvFinishMaxNum; num++)
			{
				if (_pvFinishPS[num].empty() == FALSE) { for (int i = 0; i < _pvFinishPS[num].size(); i++) { _pvFinishPS[num][i]->reset(); } }
			}

			this->Reset();

			//���� �ʱ�ȭ
			_skillResetOn = false;
			_skillPrepareOn = false;
			_skillActionOn = false;
			_skillFinshOn = false;
			_skillStartOn = false; 
		}
		//�����غ�
		if (_skillPrepareOn) { this->Prepare(); }
		//�׼�
		if (_skillActionOn) { this->Action(); }
		//�ǴϽ�
		if (_skillFinshOn) { this->Finsh();  }
	}
	else if(_SkillRenderType == SR_Custom)
	{
		//��ų ����
		if (_skillResetOn) { this->Reset(); _skillResetOn = false; }
		//�׼�
		if (_skillStartOn) { this->Action(); }
	}

}

void dxSkillContainer::render()
{
	if (_skillStartOn == FALSE) return;

	if (_SkillRenderType == SR_One)//����ų��
	{
		if (_skillPrepareOn)  { if (_preparePS != NULL) _preparePS->render(); }
		if (_skillActionOn) { if (_actionPS != NULL) _actionPS->render(); }
		if (_skillFinshOn)  { if (_finishPS != NULL) _finishPS->render(); }
	}
	else if (_SkillRenderType == SR_Array)//�迭��
	{
		if (_skillPrepareOn)
		{
			if (_vPrepaerPS.empty() == FALSE)	{ for (int i = 0; i < _vPrepaerPS.size(); i++) { _vPrepaerPS[i]->render(); }}
		}
		if (_skillActionOn)
		{
			if (_vActionPS.empty() == FALSE)	{ for (int i = 0; i < _vActionPS.size(); i++) { _vActionPS[i]->render(); }	}
		}
		if (_skillFinshOn)
		{
			if (_vFinishPS.empty() == FALSE)	{ for (int i = 0; i < _vFinishPS.size(); i++) { _vFinishPS[i]->render(); } }
		}
	}
	else if (_SkillRenderType == SR_Big)//���
	{

 		if (_skillPrepareOn)
		{
			for (int num = 0; num < _pvPrepaerMaxNum; num++)
			{
				if (_pvPrepaerPS[num].empty() == FALSE) { for (int i = 0; i < _pvPrepaerPS[num].size(); i++) { _pvPrepaerPS[num][i]->render(); } }
			}
			
		}
		if (_skillActionOn)
		{
			for (int num = 0; num < _pvActionMaxNum; num++)
			{
				if (_pvActionPS[num].empty() == FALSE) { for (int i = 0; i < _pvActionPS[num].size(); i++) { _pvActionPS[num][i]->render(); } }
			}
		}
		if (_skillFinshOn)
		{
			for (int num = 0; num < _pvFinishMaxNum; num++)
			{
				if (_pvFinishPS[num].empty() == FALSE) { for (int i = 0; i < _pvFinishPS[num].size(); i++) { _pvFinishPS[num][i]->render(); } }
			}
		}
	}
	else if (_SkillRenderType == SR_Custom)//Ŀ���ҿ�
	{
		//if (_skillStartOn) { this->RenderPrepare(); }
		if (_skillActionOn) { this->RenderAction(); }
		//if (_skillFinshOn) { this->RenderFinsh(); }
	}
}

bool dxSkillContainer::AutoResetTime(float inTime)
{
	{
		_resetTime = inTime;
		if (_resetTime <= _currentResetTime)
		{
			_currentResetTime = 0.0f;
			_skillResetOn = true;
			return TRUE;
		}
		_currentResetTime += _timeDelta;
		return FALSE;
	}
}
