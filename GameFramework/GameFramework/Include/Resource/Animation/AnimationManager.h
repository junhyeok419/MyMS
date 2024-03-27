#pragma once

#include "../../GameInfo.h"

/*
	애니메이션을 위한 이미지가 sprite일 수도 있고 frame일 수도 있다.
	그래서 애니메이션 관련 클래스를 따로 만들어서, 애니메이션을 돌리게 되면
	그러한 상황을 지원해주는 기능을 만들 것이다.
*/

class CAnimationManager
{
private:
	/*
		텍스쳐 매니저가 텍스쳐를 맵으로 관리하듯,
		애니메이션 매니저도 '모션'인 애니메이션 시퀀스를 맵으로 관리한다.
	*/
	std::unordered_map<std::string, CSharedPtr<class CAnimationSequence>> m_mapSequence;
public:
	bool Init();
	// 애니메이션 시퀀스를 생성한다.
	bool CreateAnimationSequence(const std::string& _name, class CTexture* _texture);
	// 애니메이션 시퀀스에 프레임 좌표를 등록한다.
	bool AddAnimationFrame(const std::string& _name, const Vector2& _start,
		const Vector2& _end);
	bool AddAnimationFrame(const std::string& _name, float _posX, float _posY, float _sizeX, float _sizeY);
	// 애니메이션 시퀀스에 피봇 좌표를 등록한다.
	bool AddAnimationFramePivot(const std::string& _name, const Vector2& _pivot);
	bool AddAnimationFramePivot(const std::string& _name, float _pivotX, float _pivotY);
	// 키에 해당하는 애니메이션 시퀀스를 찾는다.
	class CAnimationSequence* FindAnimation(const std::string& _name);
	// 키에 해당하는 애니메이션 시퀀스를 삭제한다.
	void ReleaseAnimation(const std::string& _name);

private:
	CAnimationManager();
	~CAnimationManager();

	friend class CResourceManager;
};

