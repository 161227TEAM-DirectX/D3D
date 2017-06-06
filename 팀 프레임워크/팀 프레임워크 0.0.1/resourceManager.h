#pragma once
#include "singletonBase.h"

template <typename T, typename A>
class resourceManager : public singletonBase <A>
{
protected:
	typedef map<string, T> MAP_RESOURCE;
	MAP_RESOURCE _resourceTable; //리소스 테이블

public:
	//파일 경로로 리소스를 불러온다
	T getResource(string filePath, void* pParam = NULL);
	//특정 리소스 해제
	void removeResource(string filePath);
	//모든 리소스 해제
	void clearResource(void);

	//리소스 로딩 방식만 재정의한다(텍스쳐, 셰이더이펙트)
	virtual T loadResource(string filePath, void* pParam = NULL) = 0;
	//리소스 해제 방식만 재정의한다
	virtual void releaseResource(T data) = 0;

	resourceManager() {}
	~resourceManager() {}
};

template<typename T, typename A>
inline T resourceManager<T, A>::getResource(string filePath, void * pParam)
{
	MAP_RESOURCE::iterator find;
	//이미 로딩되었는지 확인
	find = _resourceTable.find(filePath);

	//해당 filePath가 맵에 추가 되어 있지 않다면 새로만들어서 추가시키기
	if (find == _resourceTable.end())
	{
		//loadResource 함수로 새로운 리소스 로딩
		T newResource = this->loadResource(filePath, pParam);
		//리소스 로딩이 실패되었다면 0 리턴
		if (newResource == 0) return 0;
		//리소스테이블에 추가하기
		_resourceTable.insert(make_pair(filePath, newResource));

		return newResource;
	}

	return find->second;
}

template<typename T, typename A>
inline void resourceManager<T, A>::removeResource(string filePath)
{
	MAP_RESOURCE::iterator find;
	//이미 로딩되었는지 확인
	find = _resourceTable.find(filePath);

	//존재한다면 리소스 지우기
	if (find != _resourceTable.end())
	{
		//찾은 리소스 해제
		releaseResource(find->second);
		//반복자 삭제
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

	//전체삭제
	_resourceTable.clear();
}

