#include "PathManager.h"

DEFINITION_SINGLE(CPathManager)

bool CPathManager::Init()
{
	// ��Ʈ ���(���ҽ��� ������ Bin���� ����)�� ������ �����ڵ� ���ڿ��� �����.
	TCHAR root[MAX_PATH] = {};

	/*
		GetModuleFileName : 
		"���������� �����ϴ� ���� ������ ��ü���/�������� �̸�.exe" ��
		���ڿ��� ���� root�� ����ȴ�.

		ex ) "~~~Bin/aa.exe"
	*/
	GetModuleFileName(0, root, MAX_PATH);

	/*
		�ʿ��� ��Ʈ ��δ� �������� �κ��� ������ "~~~Bin/"���� �̹Ƿ�, 
		���ڿ��� �������� ������ �ش� �κб��� 0���� �о������.
	*/
	int length = lstrlen(root);

	for (int i = length - 1; i >= 0; --i)
	{
		/*
			�Ųٷ� �����ϴٰ� �����ó� �������ø� ������, 
			���� ���ڿ��� 0���� �о������.
		*/
		if (root[i] == '/' || root[i] == '\\')
		{
			memset(&root[i + 1], 0, sizeof(TCHAR) * (length - i - 1));
			break;
		}
	}

	// PathInfo����ü�� �ϳ� �����, ������ ���� ��Ʈ��θ� ����Ѵ�.
	PathInfo* info = new PathInfo;

	lstrcpy(info->path, root);

	/*
		#ifdef : ������ ������ �����ϴ� ���Ǻ� ��ó����ν�,
		�ڿ� �ִ� ������ #define���� ���ǵǾ� �ִ��� �Ǵ��Ͽ� 
		�����Ų��.
		������Ʈ�� �����ڵ� �����̶�� UNICODE�� ���ǵǾ� �ִ�.
	*/
#ifdef UNICODE	// ������Ʈ �Ӽ��� �����ڵ��� ���

	/*
		WideCharToMultiByte : �����ڵ�� �Ǿ��ִ� ���ڿ��� ��Ƽ����Ʈ�� �ٲ��ش�.
		1, 2 ���ڴ� �����Ѵ�.
		3. ��Ƽ����Ʈ�� �ٲ��� ���ڿ�
		4. �ٲ� ���� ����(-1 : ��ü)
		5. 3������ �ٲ� ��Ƽ����Ʈ ���ڿ��� ���Ե� ��
		   0, 0, 0, 0���� �ϸ� �����ڵ�� �Ǿ��ִ� 3�������� ���ڿ��� 
		   ��Ƽ����Ʈ�� �ٲٱ� ���� ���̸� ���´�.
	*/

	// �����ڵ�� �Ǿ��ִ� ���ڿ��� ��Ƽ����Ʈ�� �ٲٱ� ���� ���̸� ���´�.
	int pathLength = WideCharToMultiByte(CP_ACP, 0, info->path, -1,
		0, 0, 0, 0);
	
	// path�� ��Ƽ����Ʈ�� ��ȯ�Ͽ� pathMultibyte�� �־��ش�.
	WideCharToMultiByte(CP_ACP, 0, info->path, -1,
		info->pathMultibyte, pathLength, 0, 0);

#else	// ������Ʈ �Ӽ��� ��Ƽ����Ʈ�� ���

	// �׳� ��Ƽ����Ʈ�� �Լ��� ����ϸ� �ڵ� ��ȯ �ȴ�.
	strcpy_s(Info->PathMultibyte, Info->path);

#endif // UNICODE

	/*
		mapPath�� RootPath�� �̸����� �Ʊ� ���� info�� �߰��Ѵ�.
		�� path�� Bin������ �����̴�.
	*/
	m_mapPath.insert(std::make_pair(ROOT_PATH, info));

	/*
		�ؽ��� ������ path�� �߰��Ѵ�.
		TEXTURE_PATH�� �̸�����, ��Ʈ ��ο� "Texture/"�� ���� ���̴�.
	*/
	AddPath(TEXTURE_PATH, TEXT("Texture/"));
	AddPath(SOUND_PATH, TEXT("Sound/"));
	AddPath(FONT_PATH, TEXT("Font/"));

	return true;
}

/*
	1. �ش� �̸����� path�� �߰��Ѵ�.
	2. 3�� ����(�⺻�� �� path)�� �߰��� �̾���� ����̴�.
	3. �⺻�� �� path�̴�. (����Ʈ : ��Ʈpath)
*/
bool CPathManager::AddPath(const std::string& _name, const TCHAR* _path, const std::string& _basePathName)
{
	// �ش� �̸��� ���� path�� ã��, �̹� �ִٸ� �ߺ� �̸��̹Ƿ� �����Ѵ�.
	if (FindPath(_name))
		return false;

	// �߰��� �� pathInfo�� �����.
	PathInfo* info = new PathInfo;

	// �⺻�� �� path�̴�.
	const PathInfo* basePath = FindPath(_basePathName);

	// �� pathInfo�� �⺻�� �� path�� �����Ѵ�.
	if (basePath)
		lstrcpy(info->path, basePath->path);

	// pathInfo�� �߰��� �̾���� ��θ� ���δ�.
	lstrcat(info->path, _path);

	// ���⼭���� Init�� �����ϴ�.
#ifdef UNICODE	// ������Ʈ �Ӽ��� �����ڵ��� ���

	/*
		WideCharToMultiByte : �����ڵ�� �Ǿ��ִ� ���ڿ��� ��Ƽ����Ʈ�� �ٲ��ش�.
		1, 2 ���ڴ� �����Ѵ�.
		3. ��Ƽ����Ʈ�� �ٲ��� ���ڿ�
		4. �ٲ� ���� ����(-1 : ��ü)
		5. 3������ �ٲ� ��Ƽ����Ʈ ���ڿ��� ���Ե� ��
		   0, 0, 0, 0���� �ϸ� �����ڵ�� �Ǿ��ִ� 3�������� ���ڿ���
		   ��Ƽ����Ʈ�� �ٲٱ� ���� ���̸� ���´�.
	*/

	// �����ڵ�� �Ǿ��ִ� ���ڿ��� ��Ƽ����Ʈ�� �ٲٱ� ���� ���̸� ���´�.
	int pathLength = WideCharToMultiByte(CP_ACP, 0, info->path, -1,
		0, 0, 0, 0);

	// path�� ��Ƽ����Ʈ�� ��ȯ�Ͽ� pathMultibyte�� �־��ش�.
	WideCharToMultiByte(CP_ACP, 0, info->path, -1,
		info->pathMultibyte, pathLength, 0, 0);

#else	// ������Ʈ �Ӽ��� ��Ƽ����Ʈ�� ���

	// �׳� ��Ƽ����Ʈ�� �Լ��� ����ϸ� �ڵ� ��ȯ �ȴ�.
	strcpy_s(Info->PathMultibyte, Info->path);

#endif // UNICODE

	// mapPath�� _name�̶� �̸����� �Ʊ� ���� info�� �߰��Ѵ�.
	m_mapPath.insert(std::make_pair(_name, info));

	return true;
}

const PathInfo* CPathManager::FindPath(const std::string& _name)
{
	// Ű(_name)�� �ش��ϴ� ��带 ã�´�. 
	std::unordered_map<std::string, PathInfo*>::iterator iter = m_mapPath.find(_name);
	
	// ��尡 ���ٸ� �����Ѵ�.
	if (iter == m_mapPath.end())
		return nullptr;

	// �ִٸ� ����� ��ȯ�Ѵ�.
	return iter->second;
}

CPathManager::CPathManager()
{}

CPathManager::~CPathManager()
{
	// ��� �����Ҵ��� map��带 �����ش�
	std::unordered_map<std::string, PathInfo*>::iterator iter = m_mapPath.begin();
	std::unordered_map<std::string, PathInfo*>::iterator iterEnd = m_mapPath.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}
}