#include "SceneCollision.h"
#include "../Collision/Collider.h"
#include "../Input.h"
#include "../UI/WidgetWindow.h"
#include "../UI/Widget.h"

void CSceneCollision::AddCollider(CCollider* _collider)
{
	m_vecCollider.push_back(_collider);
}

void CSceneCollision::AddWidgetWindow(CWidgetWindow* _window)
{
	m_vecWidgetWindow.push_back(_window);
}

void CSceneCollision::Collision(float _deltaTime)
{
	/*
		�ǽð����� ���� ����ִ� ��� �浹ü�� m_vecCollider�� �ְ�,
		��ü �����ϵ��� �Ź� �浹 üũ(�浹 ����)�� �� ���̴�.

		�浹ü ���ʹ� �� �����Ӹ��� ���ŵǾ� ���� ä������.
		�� �����Ӹ��� �������ų� �߰��Ǵ� �浹ü�� �߻��� �� �ֱ� �����̴�.
	*/
	size_t	size = m_vecCollider.size();

	// ���� �浹ü�� �� �̻� �����Ѵٸ� �浹 üũ�Ѵ�.
	if (size > 1)
	{
		for (size_t i = 0; i < size - 1; ++i)
		{
			CCollider* src = m_vecCollider[i];

			for (size_t j = i + 1; j < size; ++j)
			{
				CCollider* dest = m_vecCollider[j];

				// ���� ������Ʈ�� ���� �浹ü ������ ���� �ʿ� ����.
				if (src->GetOwner() == dest->GetOwner())
					continue;

				// �浹 ���������� �����ͼ� �浹���Ѿ� �ϴ� ��ü���� �Ǵ��Ѵ�.
				const CollisionProfile* srcProfile = src->GetProfile();
				const CollisionProfile* destProfile = dest->GetProfile();

				// �������Ͽ��� �ٸ� ä�ΰ� ��ȣ�ۿ��� ��� �ؾߵǴ����� �������ִ�.
				// �׷��Ƿ� ���� ä�ι�°�� ��ȣ�ۿ��� ���ͼ� �������� �浹������ �˾Ƴ��� �Ѵ�.
				ECollisionInteraction	srcInteraction = srcProfile->VecCollisionInteraction[(int)destProfile->Channel];
				ECollisionInteraction	destInteraction = destProfile->VecCollisionInteraction[(int)srcProfile->Channel];

				// ���� �ϳ��� �����ϱ�� �Ǿ� �ִٸ� �浹�� �����.
				if (srcInteraction == ECollisionInteraction::Ignore ||
					destInteraction == ECollisionInteraction::Ignore)
					continue;

				/*
					������ �浹�� �ƴ� ��츦 �� �ɷ������Ƿ�,
					���� Collision�� ȣ���Ͽ� ��ǥ�� �浹�� üũ�Ѵ�.
				*/
				if (src->Collision(dest))
				{
					/*
					    �浹 üũ ��,
						'�浹�� �浹ü ��� ����Ʈ'�� ������� ���,
						'���� �� �浹�� �����ߴ�'�� �ǹ��̴�.
					*/
					if (!src->CheckCollisionList(dest))
					{
						// ���ο��� ���� �浹ü�� �浹��Ͽ� ����Ѵ�.
						src->AddCollisionList(dest);
						dest->AddCollisionList(src);

						// �浹 ���� �Լ��� ȣ���Ѵ�.
						src->CallCollisionBegin(dest);
						dest->CallCollisionBegin(src);
					}
				}

				/*
				    ��ǥ������ �浹 ���°� �ƴѵ�
					'�浹�� ��� ����Ʈ'�� ���� �浹ü�� �ִٸ�,
					'�浹�� ����� ����'(�浹�� ��ü�� ���� ������)��� �ǹ��̴�.
				*/
				else if (src->CheckCollisionList(dest))
				{
					// ���� ��Ͽ��� ���� �浹ü�� �����ش�.
					src->DeleteCollisionList(dest);
					dest->DeleteCollisionList(src);

					// �浹 ���� �Լ��� ȣ���Ѵ�.
					src->CallCollisionEnd(dest);
					dest->CallCollisionEnd(src);
				}
			}
		}
	}
	// �� �����Ӹ��� ������Ʈ ���͸� ���� ä�� ���̹Ƿ� ��� �����ش�.
	m_vecCollider.clear();	
	// �� �����Ӹ��� ���� ������ ���͸� ���� ä�� ���̹Ƿ� ��� �����ش�.
	m_vecWidgetWindow.clear();

	/*
		���� ��ų�� ���� �浹�� ���������� Ȯ���ؾ� �ϴ� ���,
		begin �Լ����� Ʈ���Ÿ� true, end �Լ����� Ʈ���Ÿ� false��
		�ϴ� ��� ������ ��� �浹�� Ȯ���� �� �ִ�.
	*/
}

void CSceneCollision::CollisionMouse(float _deltaTime)
{
	/*
		���콺 �� �浹ü üũ�� �ϱ� ����,
		�翬�� ���콺 �� ui üũ�� ���� �� ���̴�.
	*/

	// ���� ���� ���� �������� ������ �޾ƿ´�.
	size_t	windowCount = m_vecWidgetWindow.size();

	bool	mouseCollision = false;

	// ���� �����찡 �����ϸ�
	if (windowCount >= 1)
	{
		// ���� �����찡 2�� �̻� �����ϸ� ���� �������ش�.
		if (windowCount > 1)
			std::sort(m_vecWidgetWindow.begin(), m_vecWidgetWindow.end(), CSceneCollision::SortWidget);
		
		// ui�浹�� '����' ���콺 ��ġ�� ������ �����Ƿ�, Ŭ���̾�Ʈ ���� ���콺 ��ġ�� �����´�.
		Vector2	mousePos = CInput::GetInst()->GetMousePos();

		// �浹�� ������ �ִٸ� �̰��� ��� ���̴�.
		CWidget* result = nullptr;

		// �ݺ� ���鼭 ��� ������ ���� ���콺�� �浹 üũ�� �Ѵ�.
		for (size_t i = 0; i < windowCount; ++i)
		{
			// ���� ��� ���� �����츦 zOrder�� ū ������ �������� �����Ѵ�.
		    m_vecWidgetWindow[i]->SortCollision(); 

			/*
				���� �����캰�� ���콺�� �浹 üũ���Ѵ�.
			    ���� ������� ���콺�� �浹�̶��, 
			    ���ο��� �̾ �ش� ���� �������� ������ ���콺���� 
				�浹 üũ�� �� ���̴�.
				
				�浹�� ������ �ִٸ� result�� ��� ���̴�.
			*/

			// ���콺�� ������ �浹�̶��
			if (m_vecWidgetWindow[i]->CollisionMouse(&result, mousePos))
			{
				/*
					������ ���콺�� �浹�� '����'�� �����ϴµ� �װ��� ��� �浹�� 
					������ �ƴ϶�� ����, �ٷ� �� ���� �ٸ� ������ �浹 ���̾��ٴ� ���̹Ƿ�
				*/
				if (m_mouseCollisionWidget && m_mouseCollisionWidget!= result)
					// ���� ��ü���� hovered�� false�� �ٲ��ش�.
					m_mouseCollisionWidget->CollisionMouseReleaseCallback();

				// ������ ���콺�� �浹�� '�浹ü'�� ������ ���
				if (m_mouseCollision)
				{
					// ���� �浹ü�� ���콺���� �浹���¸� false�� �ٲ��ش�.
					m_mouseCollision->SetMouseCollision(false);
					// ���� �浹ü�� ���콺 �浹 ���� �Լ��� ȣ���Ѵ�.
					m_mouseCollision->CallMouseCollisionEnd(CInput::GetInst()->GetMouseWorldPos());
					// ���� ���콺�� �浹�� �浹ü�� '����'���� �����Ѵ�.
					m_mouseCollision = nullptr;
				}

				// ���콺�� �浹�� ������ ��´�.
				m_mouseCollisionWidget = result;

				mouseCollision = true;

				break;
			}
		}
	}


	/*
		���콺�� ���� �浹�� �Ͼ�� ���� ��쿡�� 
		���콺�� �浹ü�� �浹 üũ�� �Ѵ�!!
	*/
	if (!mouseCollision)
	{
		/*
			���콺 �� ���� �浹�� false�ε� ���콺�� �浹�� ������ �ִٴ� ����,
			�ٷ� ������ �浹�̾��� ���̹Ƿ�
		*/
		if (m_mouseCollisionWidget)
		{
			// �������� Ŀ���� �������� ���� �Լ��� ȣ��
			m_mouseCollisionWidget->CollisionMouseReleaseCallback();
			// �浹���� ���� ����� '����'����
			m_mouseCollisionWidget = nullptr;
		}

		/*
			�츮�� �����ִ� ��ü���� y������ ����� ������������
			�����Ͽ�, y���� Ŭ ���� ���߿� �׷������� �Ͽ���.

			�׷��� ���콺 �浹 üũ������ �ݴ��̴�.
			y���� Ŭ ����(���� �׷�������) ���� ���� �浹�� üũ�Ѵ�.
			(����â ui�� Ŭ���ߴµ� �ڿ��ִ� ���Ͱ� Ŭ���Ǵ°� ��ü�� ���� �ȵȴ�.)
			���� ���콺 �浹�� y������ ������������ �ؾ� �Ѵ�.
		*/

		// ���� �����ϴ� �浹ü ��ü ������ �޾ƿ´�.
		size_t	size = m_vecCollider.size();

		if (size >= 1)
		{
			// �浹ü�� 2�� �̻��� ���, ���콺�� �浹 üũ�� �� ���̴�.
			if (size > 1)
				// ������ ��� algorithm�� �����ϴ� std::sort�� �̿��� y��ǥ�� ū ������ �����Ͽ� �浹 üũ�� �Ѵ�. 
				std::sort(m_vecCollider.begin(), m_vecCollider.end(), CSceneCollision::SortY);

			// ���콺 Ŀ���� ����� ��ǥ�� �浹 ���������� �޾ƿ´�.
			Vector2	mouseWorldPos = CInput::GetInst()->GetMouseWorldPos();
			CollisionProfile* mouseProfile = CInput::GetInst()->GetMouseProfile();

			//// �⺻ ���·� ������ش�.
			//bool mouseCollision = false;

			// ��� �浹ü�� ��ȸ�ϸ鼭 ���콺 Ŀ���� �浹�� �Ͼ���� üũ �� ���̴�.
			for (size_t i = 0; i < size; ++i)
			{
				// �浹ü�� ������� �޾ƿ´�.
				CCollider* dest = m_vecCollider[i];

				// �浹 ���������� �����ͼ� �浹���Ѿ� �ϴ� ��ü���� �Ǵ��Ѵ�.
				const CollisionProfile* srcProfile = mouseProfile;
				const CollisionProfile* destProfile = dest->GetProfile();

				// �������Ͽ��� �ٸ� ä�ΰ� ��ȣ�ۿ��� ��� �ؾߵǴ����� �������ִ�.
				// �׷��Ƿ� ���� ä�ι�°�� ��ȣ�ۿ��� ���ͼ� �������� �浹������ �˾Ƴ��� �Ѵ�.
				ECollisionInteraction	srcInteraction = srcProfile->VecCollisionInteraction[(int)destProfile->Channel];
				ECollisionInteraction	destInteraction = destProfile->VecCollisionInteraction[(int)srcProfile->Channel];

				// ���� �ϳ��� �����ϱ�� �Ǿ� �ִٸ� �浹�� �����.
				if (srcInteraction == ECollisionInteraction::Ignore ||
					destInteraction == ECollisionInteraction::Ignore)
					continue;

				// ������� �Դٸ� ���� �浹�� �����ϹǷ�, �浹�� üũ�Ѵ�.
				if (dest->CollisionMouse(mouseWorldPos))
				{
					// �浹�̴ϱ�
					// ���콺�� �浹 �����̴�.
					mouseCollision = true;

					// ������ mouseCollision �� false ��� '���� �� �浹�� �����ߴ�'�� �ǹ��̹Ƿ�
					if (!dest->GetMouseCollision())
					{
						// ������ ���콺�� �浹�Ǵ� �浹ü�� ���� ��� �浹�� �����ϰ�,
						if (m_mouseCollision)
							m_mouseCollision->SetMouseCollision(false);

						// ���� �浹ü�� ���콺���� �浹 ���¸� true�� �����.
						dest->SetMouseCollision(true);

						// �浹 ���� �Լ��� ȣ���Ѵ�.
						dest->CallMouseCollisionBegin(mouseWorldPos);
					}

					// ���콺�� �浹�� �浹ü(m_mouseCollision)�� dest�� �־��ش�.
					m_mouseCollision = dest;

					break;
				}

				// �浹�� �ƴ����� ������ ���콺 �浹ü�� ����(true)�Ѵٴ� ����
				// '�浹�� �Ǵ� ��ü�� ���� ������ ��'��� �� �̹Ƿ�
				else if (dest->GetMouseCollision())
				{
					// ���콺�� �浹�� �浹ü��, ���콺 �浹 ���¸� false�� �ٲ��ְ�
					m_mouseCollision->SetMouseCollision(false);

					// '���콺�� �浹�� �浹ü'�� ���� ���⶧���� nullptr�� ����ش�.
					m_mouseCollision = nullptr;
				}
			}

			/*
				mouseCollision ������ false�� �����ϰ� �ִٸ�, ���콺�� � ��ü�͵�
				�浹�� �ƴ϶�� ���̴�.
				�׷��Ƿ� �� ��쿣 ������ �浹�ǰ� �ִ� ��ü�� ���� ��� ������ �浹��
				�ȵǰ� �ִ� ��Ȳ�̹Ƿ� ���� ����ó���� �Ѵ�.
			*/
			if (!mouseCollision)
			{
				// �׷����� '���콺�� �浹�� �浹ü'�� �����Ѵٸ� 
				if (m_mouseCollision)
				{
					// ���콺�� �浹�� �浹ü��, ���콺 �浹 ���¸� false�� �ٲ��ְ�
					m_mouseCollision->SetMouseCollision(false);

					// '���콺�� �浹�� �浹ü'�� ���⶧���� nullptr�� ����ش�.
					m_mouseCollision = nullptr;
				}
			}
		}
	}
}

bool CSceneCollision::SortY(CCollider* _src, CCollider* _dest)
{
	// bottom�� ū ����(y��ǥ�� ū ����)�� �����Ѵ�.
	return _src->GetBottom() > _dest->GetBottom();
}

bool CSceneCollision::SortWidget(CWidgetWindow* _src, CWidgetWindow* _dest)
{
	// zOrder�� ū ������ �����Ѵ�. Scene�� SortWidget�� �ݴ��̴�.
	return _src->GetZOrder() > _dest->GetZOrder();
}

CSceneCollision::CSceneCollision()
	: m_mouseCollision(nullptr)
	, m_mouseCollisionWidget(nullptr)
{
	// �浹ü ���Ϳ� ���������� 500��ŭ �̸� �Ҵ��Ѵ�.
	m_vecCollider.reserve(500);
}

CSceneCollision::~CSceneCollision()
{
}
