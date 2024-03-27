#pragma once

#include "SingletonMacro.h"
#include "GameInfo.h"

/*
	���ҽ��� ����ϱ� ���� ��Ʈ�� ���� ���� �о�� �� �־�� �Ѵ�.
	��Ʈ�ʰ� ���� ���ҽ������� ���������� �����ϴ� 'Bin'������ 
	��θ� �����ؾ� �Ѵ�.

	�׷��� �� ����� �����δ� ȯ�渶�� �ٸ��Ƿ�, ����θ� �̿��ؾ� �ϴµ�,
	PathManager��� ��� �ý����� ����� ����Ѵ�. 
*/

/*
	PathInfo ����ü�� ���� ��� ������ ��Ƽ����Ʈ�� �����ڵ� ��� 
	�� �߿� ��� ����� �� �ֵ��� �Ѵ�. 
*/
struct PathInfo
{
	TCHAR path[MAX_PATH];	// �����ڵ� ��� path
	char pathMultibyte[MAX_PATH];	// ��Ƽ����Ʈ ��� path

	PathInfo()
		: path{}
		, pathMultibyte{}
	{}
};

class CPathManager
{
	DECLARE_SINGLE(CPathManager)
private:
	std::unordered_map<std::string, PathInfo*> m_mapPath;	// path ���� map
public:
	bool Init();
	// mapPath�� path�� �߰��Ѵ�.
	bool AddPath(const std::string& _name, const TCHAR* _path,
		const std::string& _basePathName = ROOT_PATH);
	// Ű(_name)�� �ش��ϴ� ���(path)�� ã�´�
	const PathInfo* FindPath(const std::string& _name);
};