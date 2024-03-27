#pragma once

#include "SingletonMacro.h"
#include "GameInfo.h"

/*
	리소스를 사용하기 위해 비트맵 파일 등을 읽어올 수 있어야 한다.
	비트맵과 같은 리소스파일은 실행파일이 존재하는 'Bin'폴더로 
	경로를 지정해야 한다.

	그러나 이 경로의 절대경로는 환경마다 다르므로, 상대경로를 이용해야 하는데,
	PathManager라는 경로 시스템을 만들어 사용한다. 
*/

/*
	PathInfo 구조체를 통해 경로 정보를 멀티바이트와 유니코드 방식 
	둘 중에 골라서 사용할 수 있도록 한다. 
*/
struct PathInfo
{
	TCHAR path[MAX_PATH];	// 유니코드 방식 path
	char pathMultibyte[MAX_PATH];	// 멀티바이트 방식 path

	PathInfo()
		: path{}
		, pathMultibyte{}
	{}
};

class CPathManager
{
	DECLARE_SINGLE(CPathManager)
private:
	std::unordered_map<std::string, PathInfo*> m_mapPath;	// path 정보 map
public:
	bool Init();
	// mapPath에 path를 추가한다.
	bool AddPath(const std::string& _name, const TCHAR* _path,
		const std::string& _basePathName = ROOT_PATH);
	// 키(_name)에 해당하는 노드(path)를 찾는다
	const PathInfo* FindPath(const std::string& _name);
};