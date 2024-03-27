#pragma once
#include "../../GameInfo.h"

/*
    ���� ��Ʈ���� �����ϴ� �Ŵ��� Ŭ�����̴�.
	���ϴ� ��Ʈ�� �̿��� �ؽ�Ʈ�� ����� ����, ��Ʈ ���� Ŭ������ �����.
*/
class CFontManager
{
private:
	std::unordered_map<std::string, CSharedPtr<class CFont>> m_mapFont;  // ��Ʈ��
public:
	bool Init();
public:
	// ��Ʈ�� �ε��Ѵ�. / 2. ������ ��Ʈ���Ϸ� ��Ʈ ��ü�� �����Ͽ� �����Ѵ�.
	bool LoadFont(const std::string& _name, const TCHAR* _fontName,
		int _width, int _height);
	// ��Ʈ������ �ε��Ѵ�. / 1. ���� ��Ʈ ������ ������ ����� �� �ְ��Ѵ�.
	bool LoadFont(const TCHAR* _fontFileName,
		const std::string& _pathName = FONT_PATH);
	// ������ DC�� Ű(_name)�� �ش��ϴ� ��Ʈ ������ ��û�Ѵ�.
	void SetFont(const std::string& _name, HDC _hDC);
	// ������ DC�� ������ ��Ʈ�� �������� �ǵ�����.
	void ResetFont(const std::string& _name, HDC _hDC);
	// Ű(_name)�� �ش��ϴ� ��Ʈ�� ã�´�.
	class CFont* FindFont(const std::string& _name);
	// Ű(_name)�� �ش��ϴ� ��Ʈ�� map���� �����. (refCnt�� 1�� ��쿡�� �����)
	void ReleaseFont(const std::string& _name);
private:
	CFontManager();
	~CFontManager();

	friend class CResourceManager;
};

