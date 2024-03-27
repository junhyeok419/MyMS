#pragma once

#include "../../Ref.h"
#include "../Texture/Texture.h"

/*
	�ִϸ��̼� ������ : ������ ���, �޸��� ���, ���� ��ǰ� ����
	��ǵ��� '�ִϸ��̼� ������'��� �Ѵ�.

	'�ִϸ��̼� ������'�� �ܼ��� �̷��� ��ǵ��� ���۽�Ű�� ���� 
	�����͸� ����ְ� �� ���̰�, ���۷��� Ŭ������ ����� ���̴�.
*/

class CAnimationSequence :
	public CRef
{
private:
	// �ϳ��� ���(�̵�, ���� ��)�� ǥ���ϱ� ���� �ؽ����̴�.
	CSharedPtr<CTexture> m_texture;
	/*
		�� sprite �̹����� ������ ������ ���������� ���� ��ǥ�̴�.
		������ �̹����� �ϳ��� 'frame'�̹����� ���� �ȴ�.
	*/
	std::vector<AnimationFrameData> m_vecFrame;
	std::vector <Vector2> m_vecFramePivot;	// ����� ���帶�� �ٸ� �Ǻ����� ����ֱ� ���� �����̴�.
public:
	Vector2 GetFramePivot(int _index) const;
	bool IsFramePivot() const;
	CTexture* GetTexture() const;
	ETextureType GetTextureType() const;
	const AnimationFrameData& GetFrame(int _index) const;
	int GetFrameCount() const;

	// ������ �̹����� ��ǥ ������ �߰��Ѵ�.
	void AddFrame(const Vector2& _start, const Vector2& _end);
	void AddFrame(float _posX, float _posY, float _sizeX, float _sizeY);
	// ������ �̹����� �Ǻ� ������ �߰��Ѵ�.
	void AddFramePivot(const Vector2& _pivot);
	void AddFramePivot(float _pivotX, float _pivotY);
private:
	CAnimationSequence();
	~CAnimationSequence();

	friend class CAnimationManager;
	friend class CAnimationInfo;
};

