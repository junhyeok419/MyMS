#pragma once

#include "../../Ref.h"
#include "../Texture/Texture.h"

/*
	애니메이션 시퀀스 : 숨쉬는 모션, 달리는 모션, 공격 모션과 같은
	모션들을 '애니메이션 시퀀스'라고 한다.

	'애니메이션 시퀀스'는 단순히 이러한 모션들을 동작시키기 위한 
	데이터를 들고있게 할 것이고, 레퍼런스 클래스를 상속할 것이다.
*/

class CAnimationSequence :
	public CRef
{
private:
	// 하나의 모션(이동, 공격 등)을 표현하기 위한 텍스쳐이다.
	CSharedPtr<CTexture> m_texture;
	/*
		위 sprite 이미지의 어디부터 어디까지 가져올지에 대한 좌표이다.
		가져온 이미지를 하나의 'frame'이미지로 보게 된다.
	*/
	std::vector<AnimationFrameData> m_vecFrame;
	std::vector <Vector2> m_vecFramePivot;	// 모션의 낱장마다 다른 피봇값을 잡아주기 위한 변수이다.
public:
	Vector2 GetFramePivot(int _index) const;
	bool IsFramePivot() const;
	CTexture* GetTexture() const;
	ETextureType GetTextureType() const;
	const AnimationFrameData& GetFrame(int _index) const;
	int GetFrameCount() const;

	// 프레임 이미지의 좌표 정보를 추가한다.
	void AddFrame(const Vector2& _start, const Vector2& _end);
	void AddFrame(float _posX, float _posY, float _sizeX, float _sizeY);
	// 프레임 이미지의 피봇 정보를 추가한다.
	void AddFramePivot(const Vector2& _pivot);
	void AddFramePivot(float _pivotX, float _pivotY);
private:
	CAnimationSequence();
	~CAnimationSequence();

	friend class CAnimationManager;
	friend class CAnimationInfo;
};

