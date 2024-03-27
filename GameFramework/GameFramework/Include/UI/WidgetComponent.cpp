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
	// 씬을 이용해 위젯컴포넌트를 추가한다.
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
			게임 오브젝트로부터 위젯 컴포넌트가 얼마나 떨어져 있는지, 
			오너와 카메라를 이용해 상대적인 위치정보를 구한다.
		*/
		Vector2	Pos = m_pos + m_owner->GetPos() - m_scene->GetCamera()->GetPos();


		// 데미지 위젯을 위로위로위로 !!!
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
		else // 데미지 위젯을 위로위로위로 !!!
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
			else // 데미지 위젯을 위로위로위로 !!!
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
				else // 데미지 위젯을 위로위로위로 !!!
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


		// 위치를 직접 구해서 전달하기 때문에 2번째 Render를 호출한다.
		// 각 위젯의 2번째 렌더를 구현한다.
		m_widget->Render(_hDC, Pos, _deltaTime);
	}
}

Vector2 CWidgetComponent::GetPos() const
{
	/*
		단순한 위치가 아니라, 오너와 카메라까지 계산된
		상대적인 위치를 반환하도록 한다.
	*/
	return m_pos + m_owner->GetPos() - m_scene->GetCamera()->GetPos();
}

float CWidgetComponent::GetBottom() const
{
	// 위젯 컴포넌트의 상대적인 위치를 받아온다.
	Vector2	pos = GetPos();

	float bottom = pos.y;
	
	/*
		위에서 구한 것은 위젯 컴포넌트의 좌상단 좌표이므로,
		여기에 위젯 사이즈의 y만큼 더하면 바닥쪽(bottom)의
		y좌표가 나올 것이다. 
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
