#pragma once

#include "../../GameInfo.h"

/*
	�ִϸ��̼��� ���� �̹����� sprite�� ���� �ְ� frame�� ���� �ִ�.
	�׷��� �ִϸ��̼� ���� Ŭ������ ���� ����, �ִϸ��̼��� ������ �Ǹ�
	�׷��� ��Ȳ�� �������ִ� ����� ���� ���̴�.
*/

class CAnimationManager
{
private:
	/*
		�ؽ��� �Ŵ����� �ؽ��ĸ� ������ �����ϵ�,
		�ִϸ��̼� �Ŵ����� '���'�� �ִϸ��̼� �������� ������ �����Ѵ�.
	*/
	std::unordered_map<std::string, CSharedPtr<class CAnimationSequence>> m_mapSequence;
public:
	bool Init();
	// �ִϸ��̼� �������� �����Ѵ�.
	bool CreateAnimationSequence(const std::string& _name, class CTexture* _texture);
	// �ִϸ��̼� �������� ������ ��ǥ�� ����Ѵ�.
	bool AddAnimationFrame(const std::string& _name, const Vector2& _start,
		const Vector2& _end);
	bool AddAnimationFrame(const std::string& _name, float _posX, float _posY, float _sizeX, float _sizeY);
	// �ִϸ��̼� �������� �Ǻ� ��ǥ�� ����Ѵ�.
	bool AddAnimationFramePivot(const std::string& _name, const Vector2& _pivot);
	bool AddAnimationFramePivot(const std::string& _name, float _pivotX, float _pivotY);
	// Ű�� �ش��ϴ� �ִϸ��̼� �������� ã�´�.
	class CAnimationSequence* FindAnimation(const std::string& _name);
	// Ű�� �ش��ϴ� �ִϸ��̼� �������� �����Ѵ�.
	void ReleaseAnimation(const std::string& _name);

private:
	CAnimationManager();
	~CAnimationManager();

	friend class CResourceManager;
};

