#pragma once
/*
	�ؽ����� Ÿ�Կ� ���� enum class�̴�.
	Sprite : 1���� �̹��� ���Ͽ� ���ӵ� �̹����� �����ϴ� ���� (�⺻ Ÿ��)
	Frame  : 1���� �̹��� ���Ͽ� ������ �̹����� �����ϴ� ���� 

	�̹����� ũ�� �� 2���� �߿��� ����Ѵ�.
*/
enum class ETextureType
{
	Sprite,
	Frame
};

/*
	������Ʈ�� ���̾� ������ ������ ���� enum class�̴�.

	Back : ��� ���̾�
	Default : �Ϲ� ������Ʈ ���̾�
	Effect : ����Ʈ ���̾�

	���̾�� '����� �׷�'�̴�.
	���̾� ������ ������ �Ͽ�, ������ Back - Default - Effect ������
	��µǰ� �� ���̴�.

	���� ������Ʈ ����Ʈ�� ���̸� Max�� �Ѵ�.
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
	�浹�� ä�κ��� �Ǵ��ϱ� ���� enum class�̴�.

	���� ���, �÷��̾ ����ü�� ���� �� �̰��� �÷��̾ �ƴ�
	'����'��� ��� �����ؼ� �浹�� ���̴�.
	��, ���� ���ϴ� ��ü���� �浹���� �����ؼ� ó���� �� �־�� ȿ�����̹Ƿ�,
	���� ä���� ����� ������Ʈ�� �з��� ���̴�.

	�浹 ���������� �̰��� ����� ������ �ִ�.
*/
enum class ECollisionChannel
{
	// ���ϴ� ä���� �߰��Ѵ�.
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
	�浹 ä�ΰ��� ��ȣ�ۿ뿡 ���� enum class�̴�.

	���� ���, Aä���� ����ϴ� �������ϰ� Bä���� ����ϴ� ����������
	���ο� ���� ��ȣ�ۿ��� Collision�̶��, �� �浹ü�� ���� �浹 üũ�� �Ѵ�.

	�浹 ���������� �̰��� ����� ������ �ִ�.
*/
enum class ECollisionInteraction
{
	Ignore,
	Collision
};

/*
	�浹ü�� Ÿ�Կ� ���� enum class�̴�.
	
	�浹ü�� ��翡 ���� �浹 ó�� ����� �޶����� ������
	����� �ٸ��� ���� �ٸ� Ÿ���� ������ �Ѵ�.

	�Ϲ������� ���ҽ� �Ҹ� ���� ������, 
	�浹ü�� ������Ʈ ��� �״�ΰ� �ƴ� �ڽ��� ���� ���·� �����.
*/
enum class EColliderType
{
	Box,
	Circle,
	Line
};

/*
	�귯�� ������ ��Ÿ���� enum class�̴�.
	���� �Ŵ������� �귯�� �迭�� Max��ŭ ũ��� ������ ���̴�.
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
	����Ʈ�� ������ ��Ÿ���� enum class�̴�.

	Once��'Ÿ�� ����Ʈ'�� ���� 1ȸ�� ����Ʈ�� ���̰�,
	Duration�� ���� ���� �Ǵ� �ð����� �ߵ��ϴ� '���� ����Ʈ'�� ���̸�,
	Loop�� �ظ��� ������ �ƴϸ� ��� ��Ÿ���� (ex �ºҸ� ��) ����Ʈ�� 
	���δ�.
*/
enum class EEffectType
{
	Once,		// 1ȸ
	Duration,	// 1ȸ �̻�
	Loop		// �ݺ����
};

/*
	��ư�� ���¸� ��Ÿ���� enum class�̴�.

	Normal		 : �⺻ ����
	MouseHovered : Ŀ���� �ö� ����
	Click		 : Ŭ���� ����
	Disable		 : ��ư ��Ȱ��ȭ ����
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
	���尡 ����Ǵ� ��ư�� ���¸� ��Ÿ���� enum class�̴�.

	MouseHovered : Ŀ���� �ö� ����
	Click		 : Ŭ���� ����
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