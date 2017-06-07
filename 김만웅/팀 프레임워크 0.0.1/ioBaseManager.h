#pragma once
#include "singletonBase.h"

template<class T, class A>
class ioBaseManager : public singletonBase<A>
{
protected:
	typedef map<string, T> FILE_RESOURCE;
	FILE_RESOURCE _resourceTable;

	char ioString[128];

public:
	ioBaseManager() {}
	~ioBaseManager() {}

	virtual void loadFile(string filePath) = 0;
	virtual void saveFile(string filePath, vector<T>& vecT) = 0;

	T findTag(string resName);
};

template<class T, class A>
inline T ioBaseManager<T, A>::findTag(string resName)
{
	FILE_RESOURCE::iterator find;
	find = _resourceTable.find(resName);

	assert(find != _resourceTable.end() && "찾으려고 하는 이름의 정보가 없습니다.");

	return find->second;
}
