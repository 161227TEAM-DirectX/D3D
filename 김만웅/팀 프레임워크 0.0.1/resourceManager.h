#pragma once
#include "singletonBase.h"

template <typename T, typename A>
class resourceManager : public singletonBase <A>
{
protected:
	typedef map<string, T> MAP_RESOURCE;
	MAP_RESOURCE _resourceTable; //���ҽ� ���̺�

public:
	//���� ��η� ���ҽ��� �ҷ��´�
	T getResource(string filePath, void* pParam = NULL);
	//Ư�� ���ҽ� ����
	void removeResource(string filePath);
	//��� ���ҽ� ����
	void clearResource(void);

	//���ҽ� �ε� ��ĸ� �������Ѵ�(�ؽ���, ���̴�����Ʈ)
	virtual T loadResource(string filePath, void* pParam = NULL) = 0;
	//���ҽ� ���� ��ĸ� �������Ѵ�
	virtual void releaseResource(T data) = 0;

	resourceManager() {}
	~resourceManager() {}
};

template<typename T, typename A>
inline T resourceManager<T, A>::getResource(string filePath, void * pParam)
{
	MAP_RESOURCE::iterator find;
	//�̹� �ε��Ǿ����� Ȯ��
	find = _resourceTable.find(filePath);

	//�ش� filePath�� �ʿ� �߰� �Ǿ� ���� �ʴٸ� ���θ��� �߰���Ű��
	if (find == _resourceTable.end())
	{
		//loadResource �Լ��� ���ο� ���ҽ� �ε�
		T newResource = this->loadResource(filePath, pParam);
		//���ҽ� �ε��� ���еǾ��ٸ� 0 ����
		if (newResource == 0) return 0;
		//���ҽ����̺� �߰��ϱ�
		_resourceTable.insert(make_pair(filePath, newResource));

		return newResource;
	}

	return find->second;
}

template<typename T, typename A>
inline void resourceManager<T, A>::removeResource(string filePath)
{
	MAP_RESOURCE::iterator find;
	//�̹� �ε��Ǿ����� Ȯ��
	find = _resourceTable.find(filePath);

	//�����Ѵٸ� ���ҽ� �����
	if (find != _resourceTable.end())
	{
		//ã�� ���ҽ� ����
		releaseResource(find->second);
		//�ݺ��� ����
		_resourceTable.remove(find);
	}
}

template<typename T, typename A>
inline void resourceManager<T, A>::clearResource(void)
{
	MAP_RESOURCE::iterator iter;
	for (iter = _resourceTable.begin(); iter != _resourceTable.end(); ++iter)
	{
		releaseResource(iter->second);
	}

	//��ü����
	_resourceTable.clear();
}

