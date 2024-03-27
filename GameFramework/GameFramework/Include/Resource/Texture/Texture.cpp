#include "Texture.h"
#include "../../PathManager.h"
#include "../../GameManager.h"

HDC CTexture::GetDC(int _index) const
{
	return m_vecImageInfo[_index]->hMemDC;
}

bool CTexture::GetEnableColorKey(int _index) const
{
	return m_vecImageInfo[_index]->enableColorKey;
}

COLORREF CTexture::GetColorKey(int _index) const
{
	return m_vecImageInfo[_index]->colorKey;
}

ETextureType CTexture::GetTextureType() const
{
	return m_type;
}



bool CTexture::LoadTexture(const TCHAR* _fileName, const std::string& _pathName)
{
	// pathName에 해당하는 path(파일이 들어갈 path)를 얻어온다.
	const PathInfo* path = CPathManager::GetInst()->FindPath(_pathName);
	
	// 파일의 최종 path가 들어갈 빈 문자열이다.
	TCHAR fullPath[MAX_PATH] = {};

	if (path)
		// 파일이 들어갈 path를 복사해주고 (~~bin/)
		lstrcpy(fullPath, path->path);
	
	// 파일이름을 붙여주면 "~~bin/aa.bmp" 같은 Full Path가 만들어 질 것이다.
	lstrcat(fullPath, _fileName);

	// 구한 Full Path를 이용해 이미지 로드를 마저 진행한다.
	return LoadTextureFullPath(fullPath);
}

bool CTexture::LoadTextureFullPath(const TCHAR* _fullPath)
{
	/*
		CreateCompatibleDC : 화면 DC를 넣고 메모리 DC를 얻는다.
		게임매니저의 화면 DC를 얻어다 사용한다.
	*/
	HDC hDC = CreateCompatibleDC(CGameManager::GetInst()->GetWindowDC());

	// 비트맵을 로딩한다.
	HBITMAP hBmp = (HBITMAP)LoadImage(CGameManager::GetInst()->GetWindowInstance(),
		_fullPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	if (!hBmp)
		return false;

	/*
		읽어온 비트맵을 메모리 DC에 지정한다.

		SelectObject는 기존에 DC가 가지고 있던 도구를 반환하는데,
		그것을 m_hPrevBmp에 저장해 뒀다가 소멸자에서 다시 DC에 넣어준 뒤
		(원래대로 돌려준 뒤) 삭제한다.
		이것은 정해진 일련의 과정이다.
	*/
	HBITMAP hPrevBmp = (HBITMAP)SelectObject(hDC, hBmp);

	BITMAP bmpInfo;

	// 비트맵(m_hBmp)의 정보를 bmpInfo에 저장한다.
	GetObject(hBmp, sizeof(BITMAP), &bmpInfo);

	// 만든 이미지 정보를 ImageInfo 구조체를 만들어 다 담는다
	ImageInfo* info = new ImageInfo;
	info->hMemDC = hDC;
	info->hBmp = hBmp;
	info->hPrevBmp = hPrevBmp;
	info->bmpInfo = bmpInfo;

	// 완성한 ImageInfo 구조체를 벡터에 추가한다
	m_vecImageInfo.push_back(info);

	return true;
}

#ifdef UNICODE

bool CTexture::LoadTexture(const std::vector<std::wstring>& _vecFileName, const std::string& _pathName)
{
	// 여러 이미지 파일로 텍스쳐를 구성한다는 것은 파일안에 한개의 이미지로 구성되어있다는 뜻 (Frame)
	m_type = ETextureType::Frame;

	// pathName에 해당하는(파일이 들어갈) path를 얻어온다.
	const PathInfo* path = CPathManager::GetInst()->FindPath(_pathName);

	// 파일의 최종 path가 들어갈 빈 문자열 벡터이다.
	std::vector<std::wstring> vecFullPath;

	size_t size = _vecFileName.size();
	
	/*
		resize : 공간예약 + 값 채움
		1. 미리 개수만큼 push하여 0(or nullptr)으로 초기화한다. (쓰레기값이 없다)
		2. 용량 이상으로 더 들어오면 버려진다.
		3. 배열을 만들 때 int array[10] = {0,}; 하는것과 같다.

		reserve : 공간예약
		1. 미리 공간만 예약하여 꽉 찼을 때 재할당이 일어나는것을 막는다.
		2. 용량 이상으로 더 들어오면 늘어난다.
		3. 배열을 만들 때 int array[10]; 하는것과 같다.
	*/
	vecFullPath.resize(size);

	for (size_t i = 0; i < size; ++i)
	{
		// 기본 path를 넣어주고
		if (path)
			vecFullPath[i] = path->path;

		// 추가로 각 파일 이름을 붙여준다. string 이므로 이러한 연산들이 가능하다.
		vecFullPath[i] += _vecFileName[i];
	}

	// 구한 Full Path를 이용해 이미지 로드를 마저 진행한다.
	return LoadTextureFullPath(vecFullPath);
}

bool CTexture::LoadTextureFullPath(const std::vector<std::wstring>& _vecFullPath)
{
	// 여러 이미지 파일로 텍스쳐를 구성한다는 것은 파일안에 한개의 이미지로 구성되어있다는 뜻 (Frame)
	m_type = ETextureType::Frame;

	// Full Path가 있는 벡터의 사이즈를 가져온다.
	size_t size = _vecFullPath.size();

	// size만큼 반복시켜 모두 등록 할 것이다.
	for (size_t i = 0; i < size; ++i)
	{
		/*
			CreateCompatibleDC : 화면 DC를 넣고 메모리 DC를 얻는다.
			게임매니저의 화면 DC를 얻어다 사용한다.
		*/
		HDC hDC = CreateCompatibleDC(CGameManager::GetInst()->GetWindowDC());

		// 비트맵을 로딩한다.
		// c_str : string의 첫 번째 문자의 주소를 반환한다. 
		HBITMAP hBmp = (HBITMAP)LoadImage(CGameManager::GetInst()->GetWindowInstance(),
			_vecFullPath[i].c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

		if (!hBmp)
			return false;

		/*
			읽어온 비트맵을 메모리 DC에 지정한다.

			SelectObject는 기존에 DC가 가지고 있던 도구를 반환하는데,
			그것을 m_hPrevBmp에 저장해 뒀다가 소멸자에서 다시 DC에 넣어준 뒤
			(원래대로 돌려준 뒤) 삭제한다.
			이것은 정해진 일련의 과정이다.
		*/
		HBITMAP hPrevBmp = (HBITMAP)SelectObject(hDC, hBmp);

		BITMAP bmpInfo;

		// 비트맵(m_hBmp)의 정보를 bmpInfo에 저장한다.
		GetObject(hBmp, sizeof(BITMAP), &bmpInfo);

		// 만든 이미지 정보를 ImageInfo 구조체를 만들어 다 담는다
		ImageInfo* info = new ImageInfo;
		info->hMemDC = hDC;
		info->hBmp = hBmp;
		info->hPrevBmp = hPrevBmp;
		info->bmpInfo = bmpInfo;

		// 완성한 ImageInfo 구조체를 벡터에 추가한다
		m_vecImageInfo.push_back(info);
	}
	return true;
}

#else
bool CTexture::LoadTexture(const std::vector<std::string>& _vecFileName, const std::string& _pathName)
{
	// 여러 이미지 파일로 텍스쳐를 구성한다는 것은 파일안에 한개의 이미지로 구성되어있다는 뜻 (Frame)
	m_type = ETextureType::Frame;

	// pathName에 해당하는(파일이 들어갈) path를 얻어온다.
	const PathInfo* path = CPathManager::GetInst()->FindPath(_pathName);

	// 파일의 최종 path가 들어갈 빈 문자열 벡터이다.
	std::vector<std::string> vecFullPath;

	size_t size = _vecFileName.size();

	/*
		resize : 공간예약 + 값 채움
		1. 미리 개수만큼 push하여 0(or nullptr)으로 초기화한다. (쓰레기값이 없다)
		2. 용량 이상으로 더 들어오면 버려진다.
		3. 배열을 만들 때 int array[10] = {0,}; 하는것과 같다.

		reserve : 공간예약
		1. 미리 공간만 예약하여 꽉 찼을 때 재할당이 일어나는것을 막는다.
		2. 용량 이상으로 더 들어오면 늘어난다.
		3. 배열을 만들 때 int array[10]; 하는것과 같다.
	*/
	vecFullPath.resize(size);

	for (size_t i = 0; i < size; ++i)
	{
		// 기본 path를 넣어주고
		if (path)
			vecFullPath[i] = path->path;

		// 추가로 각 파일 이름을 붙여준다. string 이므로 이러한 연산들이 가능하다.
		vecFullPath[i] += _vecFileName[i];
	}

	// 구한 Full Path를 이용해 이미지 로드를 마저 진행한다.
	return LoadTextureFullPath(vecFullPath);
}

bool CTexture::LoadTextureFullPath(const std::vector<std::string>& _vecFullPath)
{
	// 여러 이미지 파일로 텍스쳐를 구성한다는 것은 파일안에 한개의 이미지로 구성되어있다는 뜻 (Frame)
	m_type = ETextureType::Frame;

	// Full Path가 있는 벡터의 사이즈를 가져온다.
	size_t size = _vecFullPath.size();

	// size만큼 반복시켜 모두 등록 할 것이다.
	for (size_t i = 0; i < size; ++i)
	{
		/*
			CreateCompatibleDC : 화면 DC를 넣고 메모리 DC를 얻는다.
			게임매니저의 화면 DC를 얻어다 사용한다.
		*/
		HDC hDC = CreateCompatibleDC(CGameManager::GetInst()->GetWindowDC());

		// 비트맵을 로딩한다.
		// c_str : string의 첫 번째 문자의 주소를 반환한다. 
		HBITMAP hBmp = (HBITMAP)LoadImage(CGameManager::GetInst()->GetWindowInstance(),
			_vecFullPath[i].c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

		if (!hBmp)
			return false;

		/*
			읽어온 비트맵을 메모리 DC에 지정한다.

			SelectObject는 기존에 DC가 가지고 있던 도구를 반환하는데,
			그것을 m_hPrevBmp에 저장해 뒀다가 소멸자에서 다시 DC에 넣어준 뒤
			(원래대로 돌려준 뒤) 삭제한다.
			이것은 정해진 일련의 과정이다.
		*/
		HBITMAP hPrevBmp = (HBITMAP)SelectObject(hDC, hBmp);

		BITMAP bmpInfo;

		// 비트맵(m_hBmp)의 정보를 bmpInfo에 저장한다.
		GetObject(hBmp, sizeof(BITMAP), &bmpInfo);

		// 만든 이미지 정보를 ImageInfo 구조체를 만들어 다 담는다
		ImageInfo* info = new ImageInfo;
		info->hMemDC = hDC;
		info->hBmp = hBmp;
		info->hPrevBmp = hPrevBmp;
		info->bmpInfo = bmpInfo;

		// 완성한 ImageInfo 구조체를 벡터에 추가한다
		m_vecImageInfo.push_back(info);
	}
	return true;
}
#endif // UNICODE

void CTexture::SetColorKey(unsigned char _r, unsigned char _g, unsigned char _b, int _index)
{
	// 지정한 이미지의 컬러키를 지정하고 활성화한다.
	m_vecImageInfo[_index]->colorKey = RGB(_r, _g, _b);
	m_vecImageInfo[_index]->enableColorKey = true;
}

void CTexture::SetColorKeyAll(unsigned char _r, unsigned char _g, unsigned char _b)
{
	size_t  Size = m_vecImageInfo.size();

	// 모든 이미지의 컬러키를 지정하고 활성화한다.
	for (size_t i = 0; i < Size; ++i)
	{
		m_vecImageInfo[i]->colorKey = RGB(_r, _g, _b);
		m_vecImageInfo[i]->enableColorKey = true;
	}
}

CTexture::CTexture()
	: m_type(ETextureType::Sprite)
{
}

CTexture::~CTexture()
{
	size_t	size = m_vecImageInfo.size();

	for (size_t i = 0; i < size; ++i)
	{
		SAFE_DELETE(m_vecImageInfo[i]);
	}
}
