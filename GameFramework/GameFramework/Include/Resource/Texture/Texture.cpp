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
	// pathName�� �ش��ϴ� path(������ �� path)�� ���´�.
	const PathInfo* path = CPathManager::GetInst()->FindPath(_pathName);
	
	// ������ ���� path�� �� �� ���ڿ��̴�.
	TCHAR fullPath[MAX_PATH] = {};

	if (path)
		// ������ �� path�� �������ְ� (~~bin/)
		lstrcpy(fullPath, path->path);
	
	// �����̸��� �ٿ��ָ� "~~bin/aa.bmp" ���� Full Path�� ����� �� ���̴�.
	lstrcat(fullPath, _fileName);

	// ���� Full Path�� �̿��� �̹��� �ε带 ���� �����Ѵ�.
	return LoadTextureFullPath(fullPath);
}

bool CTexture::LoadTextureFullPath(const TCHAR* _fullPath)
{
	/*
		CreateCompatibleDC : ȭ�� DC�� �ְ� �޸� DC�� ��´�.
		���ӸŴ����� ȭ�� DC�� ���� ����Ѵ�.
	*/
	HDC hDC = CreateCompatibleDC(CGameManager::GetInst()->GetWindowDC());

	// ��Ʈ���� �ε��Ѵ�.
	HBITMAP hBmp = (HBITMAP)LoadImage(CGameManager::GetInst()->GetWindowInstance(),
		_fullPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	if (!hBmp)
		return false;

	/*
		�о�� ��Ʈ���� �޸� DC�� �����Ѵ�.

		SelectObject�� ������ DC�� ������ �ִ� ������ ��ȯ�ϴµ�,
		�װ��� m_hPrevBmp�� ������ �״ٰ� �Ҹ��ڿ��� �ٽ� DC�� �־��� ��
		(������� ������ ��) �����Ѵ�.
		�̰��� ������ �Ϸ��� �����̴�.
	*/
	HBITMAP hPrevBmp = (HBITMAP)SelectObject(hDC, hBmp);

	BITMAP bmpInfo;

	// ��Ʈ��(m_hBmp)�� ������ bmpInfo�� �����Ѵ�.
	GetObject(hBmp, sizeof(BITMAP), &bmpInfo);

	// ���� �̹��� ������ ImageInfo ����ü�� ����� �� ��´�
	ImageInfo* info = new ImageInfo;
	info->hMemDC = hDC;
	info->hBmp = hBmp;
	info->hPrevBmp = hPrevBmp;
	info->bmpInfo = bmpInfo;

	// �ϼ��� ImageInfo ����ü�� ���Ϳ� �߰��Ѵ�
	m_vecImageInfo.push_back(info);

	return true;
}

#ifdef UNICODE

bool CTexture::LoadTexture(const std::vector<std::wstring>& _vecFileName, const std::string& _pathName)
{
	// ���� �̹��� ���Ϸ� �ؽ��ĸ� �����Ѵٴ� ���� ���Ͼȿ� �Ѱ��� �̹����� �����Ǿ��ִٴ� �� (Frame)
	m_type = ETextureType::Frame;

	// pathName�� �ش��ϴ�(������ ��) path�� ���´�.
	const PathInfo* path = CPathManager::GetInst()->FindPath(_pathName);

	// ������ ���� path�� �� �� ���ڿ� �����̴�.
	std::vector<std::wstring> vecFullPath;

	size_t size = _vecFileName.size();
	
	/*
		resize : �������� + �� ä��
		1. �̸� ������ŭ push�Ͽ� 0(or nullptr)���� �ʱ�ȭ�Ѵ�. (�����Ⱚ�� ����)
		2. �뷮 �̻����� �� ������ ��������.
		3. �迭�� ���� �� int array[10] = {0,}; �ϴ°Ͱ� ����.

		reserve : ��������
		1. �̸� ������ �����Ͽ� �� á�� �� ���Ҵ��� �Ͼ�°��� ���´�.
		2. �뷮 �̻����� �� ������ �þ��.
		3. �迭�� ���� �� int array[10]; �ϴ°Ͱ� ����.
	*/
	vecFullPath.resize(size);

	for (size_t i = 0; i < size; ++i)
	{
		// �⺻ path�� �־��ְ�
		if (path)
			vecFullPath[i] = path->path;

		// �߰��� �� ���� �̸��� �ٿ��ش�. string �̹Ƿ� �̷��� ������� �����ϴ�.
		vecFullPath[i] += _vecFileName[i];
	}

	// ���� Full Path�� �̿��� �̹��� �ε带 ���� �����Ѵ�.
	return LoadTextureFullPath(vecFullPath);
}

bool CTexture::LoadTextureFullPath(const std::vector<std::wstring>& _vecFullPath)
{
	// ���� �̹��� ���Ϸ� �ؽ��ĸ� �����Ѵٴ� ���� ���Ͼȿ� �Ѱ��� �̹����� �����Ǿ��ִٴ� �� (Frame)
	m_type = ETextureType::Frame;

	// Full Path�� �ִ� ������ ����� �����´�.
	size_t size = _vecFullPath.size();

	// size��ŭ �ݺ����� ��� ��� �� ���̴�.
	for (size_t i = 0; i < size; ++i)
	{
		/*
			CreateCompatibleDC : ȭ�� DC�� �ְ� �޸� DC�� ��´�.
			���ӸŴ����� ȭ�� DC�� ���� ����Ѵ�.
		*/
		HDC hDC = CreateCompatibleDC(CGameManager::GetInst()->GetWindowDC());

		// ��Ʈ���� �ε��Ѵ�.
		// c_str : string�� ù ��° ������ �ּҸ� ��ȯ�Ѵ�. 
		HBITMAP hBmp = (HBITMAP)LoadImage(CGameManager::GetInst()->GetWindowInstance(),
			_vecFullPath[i].c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

		if (!hBmp)
			return false;

		/*
			�о�� ��Ʈ���� �޸� DC�� �����Ѵ�.

			SelectObject�� ������ DC�� ������ �ִ� ������ ��ȯ�ϴµ�,
			�װ��� m_hPrevBmp�� ������ �״ٰ� �Ҹ��ڿ��� �ٽ� DC�� �־��� ��
			(������� ������ ��) �����Ѵ�.
			�̰��� ������ �Ϸ��� �����̴�.
		*/
		HBITMAP hPrevBmp = (HBITMAP)SelectObject(hDC, hBmp);

		BITMAP bmpInfo;

		// ��Ʈ��(m_hBmp)�� ������ bmpInfo�� �����Ѵ�.
		GetObject(hBmp, sizeof(BITMAP), &bmpInfo);

		// ���� �̹��� ������ ImageInfo ����ü�� ����� �� ��´�
		ImageInfo* info = new ImageInfo;
		info->hMemDC = hDC;
		info->hBmp = hBmp;
		info->hPrevBmp = hPrevBmp;
		info->bmpInfo = bmpInfo;

		// �ϼ��� ImageInfo ����ü�� ���Ϳ� �߰��Ѵ�
		m_vecImageInfo.push_back(info);
	}
	return true;
}

#else
bool CTexture::LoadTexture(const std::vector<std::string>& _vecFileName, const std::string& _pathName)
{
	// ���� �̹��� ���Ϸ� �ؽ��ĸ� �����Ѵٴ� ���� ���Ͼȿ� �Ѱ��� �̹����� �����Ǿ��ִٴ� �� (Frame)
	m_type = ETextureType::Frame;

	// pathName�� �ش��ϴ�(������ ��) path�� ���´�.
	const PathInfo* path = CPathManager::GetInst()->FindPath(_pathName);

	// ������ ���� path�� �� �� ���ڿ� �����̴�.
	std::vector<std::string> vecFullPath;

	size_t size = _vecFileName.size();

	/*
		resize : �������� + �� ä��
		1. �̸� ������ŭ push�Ͽ� 0(or nullptr)���� �ʱ�ȭ�Ѵ�. (�����Ⱚ�� ����)
		2. �뷮 �̻����� �� ������ ��������.
		3. �迭�� ���� �� int array[10] = {0,}; �ϴ°Ͱ� ����.

		reserve : ��������
		1. �̸� ������ �����Ͽ� �� á�� �� ���Ҵ��� �Ͼ�°��� ���´�.
		2. �뷮 �̻����� �� ������ �þ��.
		3. �迭�� ���� �� int array[10]; �ϴ°Ͱ� ����.
	*/
	vecFullPath.resize(size);

	for (size_t i = 0; i < size; ++i)
	{
		// �⺻ path�� �־��ְ�
		if (path)
			vecFullPath[i] = path->path;

		// �߰��� �� ���� �̸��� �ٿ��ش�. string �̹Ƿ� �̷��� ������� �����ϴ�.
		vecFullPath[i] += _vecFileName[i];
	}

	// ���� Full Path�� �̿��� �̹��� �ε带 ���� �����Ѵ�.
	return LoadTextureFullPath(vecFullPath);
}

bool CTexture::LoadTextureFullPath(const std::vector<std::string>& _vecFullPath)
{
	// ���� �̹��� ���Ϸ� �ؽ��ĸ� �����Ѵٴ� ���� ���Ͼȿ� �Ѱ��� �̹����� �����Ǿ��ִٴ� �� (Frame)
	m_type = ETextureType::Frame;

	// Full Path�� �ִ� ������ ����� �����´�.
	size_t size = _vecFullPath.size();

	// size��ŭ �ݺ����� ��� ��� �� ���̴�.
	for (size_t i = 0; i < size; ++i)
	{
		/*
			CreateCompatibleDC : ȭ�� DC�� �ְ� �޸� DC�� ��´�.
			���ӸŴ����� ȭ�� DC�� ���� ����Ѵ�.
		*/
		HDC hDC = CreateCompatibleDC(CGameManager::GetInst()->GetWindowDC());

		// ��Ʈ���� �ε��Ѵ�.
		// c_str : string�� ù ��° ������ �ּҸ� ��ȯ�Ѵ�. 
		HBITMAP hBmp = (HBITMAP)LoadImage(CGameManager::GetInst()->GetWindowInstance(),
			_vecFullPath[i].c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

		if (!hBmp)
			return false;

		/*
			�о�� ��Ʈ���� �޸� DC�� �����Ѵ�.

			SelectObject�� ������ DC�� ������ �ִ� ������ ��ȯ�ϴµ�,
			�װ��� m_hPrevBmp�� ������ �״ٰ� �Ҹ��ڿ��� �ٽ� DC�� �־��� ��
			(������� ������ ��) �����Ѵ�.
			�̰��� ������ �Ϸ��� �����̴�.
		*/
		HBITMAP hPrevBmp = (HBITMAP)SelectObject(hDC, hBmp);

		BITMAP bmpInfo;

		// ��Ʈ��(m_hBmp)�� ������ bmpInfo�� �����Ѵ�.
		GetObject(hBmp, sizeof(BITMAP), &bmpInfo);

		// ���� �̹��� ������ ImageInfo ����ü�� ����� �� ��´�
		ImageInfo* info = new ImageInfo;
		info->hMemDC = hDC;
		info->hBmp = hBmp;
		info->hPrevBmp = hPrevBmp;
		info->bmpInfo = bmpInfo;

		// �ϼ��� ImageInfo ����ü�� ���Ϳ� �߰��Ѵ�
		m_vecImageInfo.push_back(info);
	}
	return true;
}
#endif // UNICODE

void CTexture::SetColorKey(unsigned char _r, unsigned char _g, unsigned char _b, int _index)
{
	// ������ �̹����� �÷�Ű�� �����ϰ� Ȱ��ȭ�Ѵ�.
	m_vecImageInfo[_index]->colorKey = RGB(_r, _g, _b);
	m_vecImageInfo[_index]->enableColorKey = true;
}

void CTexture::SetColorKeyAll(unsigned char _r, unsigned char _g, unsigned char _b)
{
	size_t  Size = m_vecImageInfo.size();

	// ��� �̹����� �÷�Ű�� �����ϰ� Ȱ��ȭ�Ѵ�.
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
