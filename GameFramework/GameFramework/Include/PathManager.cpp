#include "PathManager.h"

DEFINITION_SINGLE(CPathManager)

bool CPathManager::Init()
{
	// 루트 경로(리소스가 존재할 Bin폴더 내부)를 저장할 유니코드 문자열을 만든다.
	TCHAR root[MAX_PATH] = {};

	/*
		GetModuleFileName : 
		"실행파일이 존재하는 폴더 까지의 전체경로/실행파일 이름.exe" 로
		문자열이 나와 root에 저장된다.

		ex ) "~~~Bin/aa.exe"
	*/
	GetModuleFileName(0, root, MAX_PATH);

	/*
		필요한 루트 경로는 실행파일 부분을 제외한 "~~~Bin/"까지 이므로, 
		문자열의 역순으로 접근해 해당 부분까지 0으로 밀어버린다.
	*/
	int length = lstrlen(root);

	for (int i = length - 1; i >= 0; --i)
	{
		/*
			거꾸로 접근하다가 슬래시나 역슬래시를 만나면, 
			이후 문자열을 0으로 밀어버린다.
		*/
		if (root[i] == '/' || root[i] == '\\')
		{
			memset(&root[i + 1], 0, sizeof(TCHAR) * (length - i - 1));
			break;
		}
	}

	// PathInfo구조체를 하나 만들어, 위에서 만든 루트경로를 등록한다.
	PathInfo* info = new PathInfo;

	lstrcpy(info->path, root);

	/*
		#ifdef : 컴파일 이전에 동작하는 조건부 전처리기로써,
		뒤에 있는 내용이 #define으로 정의되어 있는지 판단하여 
		실행시킨다.
		프로젝트가 유니코드 설정이라면 UNICODE는 정의되어 있다.
	*/
#ifdef UNICODE	// 프로젝트 속성이 유니코드일 경우

	/*
		WideCharToMultiByte : 유니코드로 되어있는 문자열을 멀티바이트로 바꿔준다.
		1, 2 인자는 무시한다.
		3. 멀티바이트로 바꿔줄 문자열
		4. 바꿀 문자 개수(-1 : 전체)
		5. 3번에서 바꾼 멀티바이트 문자열이 대입될 곳
		   0, 0, 0, 0으로 하면 유니코드로 되어있는 3번인자의 문자열을 
		   멀티바이트로 바꾸기 위한 길이를 얻어온다.
	*/

	// 유니코드로 되어있는 문자열을 멀티바이트로 바꾸기 위한 길이를 얻어온다.
	int pathLength = WideCharToMultiByte(CP_ACP, 0, info->path, -1,
		0, 0, 0, 0);
	
	// path를 멀티바이트로 변환하여 pathMultibyte에 넣어준다.
	WideCharToMultiByte(CP_ACP, 0, info->path, -1,
		info->pathMultibyte, pathLength, 0, 0);

#else	// 프로젝트 속성이 멀티바이트일 경우

	// 그냥 멀티바이트용 함수를 사용하면 자동 변환 된다.
	strcpy_s(Info->PathMultibyte, Info->path);

#endif // UNICODE

	/*
		mapPath에 RootPath란 이름으로 아까 만든 info를 추가한다.
		이 path가 Bin폴더의 내부이다.
	*/
	m_mapPath.insert(std::make_pair(ROOT_PATH, info));

	/*
		텍스쳐 파일의 path를 추가한다.
		TEXTURE_PATH란 이름으로, 루트 경로에 "Texture/"를 붙일 것이다.
	*/
	AddPath(TEXTURE_PATH, TEXT("Texture/"));
	AddPath(SOUND_PATH, TEXT("Sound/"));
	AddPath(FONT_PATH, TEXT("Font/"));

	return true;
}

/*
	1. 해당 이름으로 path를 추가한다.
	2. 3번 인자(기본이 될 path)에 추가로 이어붙일 경로이다.
	3. 기본이 될 path이다. (디폴트 : 루트path)
*/
bool CPathManager::AddPath(const std::string& _name, const TCHAR* _path, const std::string& _basePathName)
{
	// 해당 이름을 가진 path를 찾고, 이미 있다면 중복 이름이므로 리턴한다.
	if (FindPath(_name))
		return false;

	// 추가할 빈 pathInfo를 만든다.
	PathInfo* info = new PathInfo;

	// 기본이 될 path이다.
	const PathInfo* basePath = FindPath(_basePathName);

	// 빈 pathInfo에 기본이 될 path를 복사한다.
	if (basePath)
		lstrcpy(info->path, basePath->path);

	// pathInfo에 추가로 이어붙일 경로를 붙인다.
	lstrcat(info->path, _path);

	// 여기서부턴 Init과 동일하다.
#ifdef UNICODE	// 프로젝트 속성이 유니코드일 경우

	/*
		WideCharToMultiByte : 유니코드로 되어있는 문자열을 멀티바이트로 바꿔준다.
		1, 2 인자는 무시한다.
		3. 멀티바이트로 바꿔줄 문자열
		4. 바꿀 문자 개수(-1 : 전체)
		5. 3번에서 바꾼 멀티바이트 문자열이 대입될 곳
		   0, 0, 0, 0으로 하면 유니코드로 되어있는 3번인자의 문자열을
		   멀티바이트로 바꾸기 위한 길이를 얻어온다.
	*/

	// 유니코드로 되어있는 문자열을 멀티바이트로 바꾸기 위한 길이를 얻어온다.
	int pathLength = WideCharToMultiByte(CP_ACP, 0, info->path, -1,
		0, 0, 0, 0);

	// path를 멀티바이트로 변환하여 pathMultibyte에 넣어준다.
	WideCharToMultiByte(CP_ACP, 0, info->path, -1,
		info->pathMultibyte, pathLength, 0, 0);

#else	// 프로젝트 속성이 멀티바이트일 경우

	// 그냥 멀티바이트용 함수를 사용하면 자동 변환 된다.
	strcpy_s(Info->PathMultibyte, Info->path);

#endif // UNICODE

	// mapPath에 _name이란 이름으로 아까 만든 info를 추가한다.
	m_mapPath.insert(std::make_pair(_name, info));

	return true;
}

const PathInfo* CPathManager::FindPath(const std::string& _name)
{
	// 키(_name)에 해당하는 노드를 찾는다. 
	std::unordered_map<std::string, PathInfo*>::iterator iter = m_mapPath.find(_name);
	
	// 노드가 없다면 리턴한다.
	if (iter == m_mapPath.end())
		return nullptr;

	// 있다면 밸류를 반환한다.
	return iter->second;
}

CPathManager::CPathManager()
{}

CPathManager::~CPathManager()
{
	// 모든 동적할당한 map노드를 지워준다
	std::unordered_map<std::string, PathInfo*>::iterator iter = m_mapPath.begin();
	std::unordered_map<std::string, PathInfo*>::iterator iterEnd = m_mapPath.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}
}