#pragma once
/*
	텍스쳐의 타입에 관한 enum class이다.
	Sprite : 1개의 이미지 파일에 연속된 이미지가 존재하는 형태 (기본 타입)
	Frame  : 1개의 이미지 파일에 낱장의 이미지만 존재하는 형태 

	이미지는 크게 이 2종류 중에서 사용한다.
*/
enum class ETextureType
{
	Sprite,
	Frame
};

/*
	오브젝트를 레이어 단위로 나누기 위한 enum class이다.

	Back : 배경 레이어
	Default : 일반 오브젝트 레이어
	Effect : 이펙트 레이어

	레이어는 '출력의 그룹'이다.
	레이어 단위로 정렬을 하여, 무조건 Back - Default - Effect 순으로
	출력되게 할 것이다.

	씬의 오브젝트 리스트의 길이를 Max로 한다.
*/
enum class ERenderLayer
{
	Back1,
	Back2,
	Default,
	Monster,
	Player,
	Effect,
	Effect2,
	Ground,
	Max
};

/*
	충돌을 채널별로 판단하기 위한 enum class이다.

	예를 들어, 플레이어가 투사체를 날릴 때 이것은 플레이어가 아닌
	'몬스터'라는 대상에 한정해서 충돌할 것이다.
	즉, 내가 원하는 물체와의 충돌만을 감지해서 처리할 수 있어야 효율적이므로,
	먼저 채널을 만들어 오브젝트를 분류할 것이다.

	충돌 프로파일이 이것을 멤버로 가지고 있다.
*/
enum class ECollisionChannel
{
	// 원하는 채널을 추가한다.
	Default,		
	Player,
	Monster,
	Cognition,
	Ground,
	PlayerAttack,
	MonsterAttack,
	Mouse,
	Npc,
	Item,
	Max
};

/*
	충돌 채널간의 상호작용에 관한 enum class이다.

	예를 들어, A채널을 사용하는 프로파일과 B채널을 사용하는 프로파일이
	서로에 대한 상호작용이 Collision이라면, 두 충돌체는 서로 충돌 체크를 한다.

	충돌 프로파일이 이것을 멤버로 가지고 있다.
*/
enum class ECollisionInteraction
{
	Ignore,
	Collision
};

/*
	충돌체의 타입에 관한 enum class이다.
	
	충돌체에 모양에 따라 충돌 처리 방식이 달라지기 때문에
	모양이 다르면 서로 다른 타입을 가져야 한다.

	일반적으로 리소스 소모 등의 이유로, 
	충돌체는 오브젝트 모양 그대로가 아닌 박스나 원의 형태로 만든다.
*/
enum class EColliderType
{
	Box,
	Circle,
	Line
};

/*
	브러쉬 종류를 나타내는 enum class이다.
	게임 매니저에서 브러쉬 배열을 Max만큼 크기로 선언할 것이다.
*/
enum class EBrushType
{
	Red,
	Green,
	Black,
	Blue,
	Yellow,
	Max
};

/*
	이펙트의 종류를 나타내는 enum class이다.

	Once은'타격 이펙트'와 같이 1회성 이펙트에 쓰이고,
	Duration은 일정 조건 또는 시간동안 발동하는 '버프 이펙트'에 쓰이며,
	Loop은 왠만한 이유가 아니면 계속 나타나는 (ex 태불망 등) 이펙트에 
	쓰인다.
*/
enum class EEffectType
{
	Once,		// 1회
	Duration,	// 1회 이상
	Loop		// 반복재생
};

/*
	버튼의 상태를 나타내는 enum class이다.

	Normal		 : 기본 상태
	MouseHovered : 커서가 올라간 상태
	Click		 : 클릭한 상태
	Disable		 : 버튼 비활성화 상태
*/
enum class EButtonState
{
	Normal,
	MouseHovered,
	Click,
	Disable,
	Max
};

/*
	사운드가 재생되는 버튼의 상태를 나타내는 enum class이다.

	MouseHovered : 커서가 올라간 상태
	Click		 : 클릭한 상태
*/
enum class EButtonSoundState
{
	MouseHovered,
	Click,
	Max
};

enum class ESkill
{
	Attack,
	PowerStrike,
	SlashBlast,
	Judgement,
	Justice,
	None
};