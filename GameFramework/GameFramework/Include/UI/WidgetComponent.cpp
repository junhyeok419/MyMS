#include "WidgetComponent.h"
#include "Widget.h"
#include "../Resource/Texture/Texture.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Scene/Camera.h"
#include "WidgetWindow.h"
#include "../GameObject/GameObject.h"

bool CWidgetComponent::Init()
{
	// ���� �̿��� ����������Ʈ�� �߰��Ѵ�.
	m_scene->AddWidgetComponent(this);
	return true;
}

void CWidgetComponent::Update(float _deltaTime)
{
	if (m_widget)
		m_widget->Update(_deltaTime);
}

void CWidgetComponent::PostUpdate(float _deltaTime)
{
	if (m_widget)
		m_widget->PostUpdate(_deltaTime);
}

void CWidgetComponent::Render(HDC _hDC, float _deltaTime)
{
	if (m_widget)
	{
		/*
			���� ������Ʈ�κ��� ���� ������Ʈ�� �󸶳� ������ �ִ���, 
			���ʿ� ī�޶� �̿��� ������� ��ġ������ ���Ѵ�.
		*/
		Vector2	Pos = m_pos + m_owner->GetPos() - m_scene->GetCamera()->GetPos();


		// ������ ������ ������������ !!!
		if (GetName() == "DamageNo")
		{
			if (m_lifeTime <= 0.8f)
			{

				Pos.y -= (80.f * m_lifeTime);

				m_lifeTime += _deltaTime;
			}
			else
			{
				SetActive(false);
				m_lifeTime = 0.f;
			}
		}
		else // ������ ������ ������������ !!!
			if (GetName() == "DamageNo1")
			{
				if (m_lifeTime <= 0.8f)
				{

					Pos.y -= (80.f * m_lifeTime);

					m_lifeTime += _deltaTime;
				}
				else
				{
					SetActive(false);
					m_lifeTime = 0.f;
				}
			}
			else // ������ ������ ������������ !!!
				if (GetName() == "DamageNo2")
				{
					if (m_lifeTime <= 0.8f)
					{

						Pos.y -= (80.f * m_lifeTime);

						m_lifeTime += _deltaTime;
					}
					else
					{
						SetActive(false);
						m_lifeTime = 0.f;
					}
				}
				else // ������ ������ ������������ !!!
					if (GetName() == "DamageNo3")
					{
						if (m_lifeTime <= 0.8f)
						{

							Pos.y -= (80.f * m_lifeTime);

							m_lifeTime += _deltaTime;
						}
						else
						{
							SetActive(false);
							m_lifeTime = 0.f;
						}
					}


		// ��ġ�� ���� ���ؼ� �����ϱ� ������ 2��° Render�� ȣ���Ѵ�.
		// �� ������ 2��° ������ �����Ѵ�.
		m_widget->Render(_hDC, Pos, _deltaTime);
	}
}

Vector2 CWidgetComponent::GetPos() const
{
	/*
		�ܼ��� ��ġ�� �ƴ϶�, ���ʿ� ī�޶���� ����
		������� ��ġ�� ��ȯ�ϵ��� �Ѵ�.
	*/
	return m_pos + m_owner->GetPos() - m_scene->GetCamera()->GetPos();
}

float CWidgetComponent::GetBottom() const
{
	// ���� ������Ʈ�� ������� ��ġ�� �޾ƿ´�.
	Vector2	pos = GetPos();

	float bottom = pos.y;
	
	/*
		������ ���� ���� ���� ������Ʈ�� �»�� ��ǥ�̹Ƿ�,
		���⿡ ���� �������� y��ŭ ���ϸ� �ٴ���(bottom)��
		y��ǥ�� ���� ���̴�. 
	*/
	if (m_widget)
		bottom += m_widget->GetSize().y;

	return bottom;
}

void CWidgetComponent::SetPos(float _x, float _y)
{
	m_pos = Vector2(_x, _y);
}

void CWidgetComponent::SetPos(const Vector2& _pos)
{
	m_pos = _pos;
}

void CWidgetComponent::SetWidget(CWidget* _widget)
{
	m_widget = _widget;
}

CWidgetComponent::CWidgetComponent()
{
}

CWidgetComponent::CWidgetComponent(const CWidgetComponent& _widget)
{
}

CWidgetComponent::~CWidgetComponent()
{
}

CWidget* CWidgetComponent::GetWidget() const
{
	return m_widget;
}
