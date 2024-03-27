#include "ProgressBar.h"
#include "../Resource/Texture/Texture.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "WidgetWindow.h"

bool CProgressBar::Init()
{
	return true;
}

void CProgressBar::Update(float _deltaTime)
{
	// barSize는 조정될 바 사이즈이고, size는 꽉 채워진 바 사이즈이다
	m_barSize = m_size;
	// barSize는 조정될 바 출력 위치이고, size는 꽉 채워진 바의 출력 위치이다.
	m_barPos = m_pos;

	// 방향에 따라 바 크기를 다르게 갱신한다.
	switch (m_dir)
	{
	/*
		좌->우 증가 : size에 value를 곱한다.
	*/
	case EProgressBar_Dir::LeftToRight:
		m_barSize.x = m_value * m_size.x;
		break;
	/*
		우->좌 증가 : 크기는 좌->우와 동일하지만, 그려지는 위치를 반대로 해야함.
		1.f - value에 size를 곱하여, 
		좌->우 증가에서 채워진 바의 위치를 반대로 그릴 수 있도록 한다.
	*/
	case EProgressBar_Dir::RightToLeft:
		m_barSize.x = m_value * m_size.x;
		m_barPos.x = m_pos.x + (1.f - m_value) * m_size.x;
		break;
	case EProgressBar_Dir::BottomToTop:
		m_barSize.y = m_value * m_size.y;
		m_barPos.y = m_pos.y + (1.f - m_value) * m_size.y;
		break;
	case EProgressBar_Dir::TopToBottom:
		m_barSize.y = m_value * m_size.y;
		break;
	}
}

void CProgressBar::PostUpdate(float _deltaTime)
{
}

void CProgressBar::Render(HDC _hDC, float _deltaTime)
{
	/*
		바가 그려질 좌상단 위치. 
		바의 위치는 위젯 윈도우 내에서의 위치를 잡아야 하므로
		owner를 더해서 잡는다.
	*/
	Vector2	RenderPos = m_barPos + m_owner->GetPos();

	for (int i = 0; i < (int)EProgressBar_Texture_Type::End; ++i)
	{
		if (m_texture[i])
		{
			if (m_texture[i]->GetTextureType() == ETextureType::Sprite)
			{
				if (m_texture[i]->GetEnableColorKey())
				{
					TransparentBlt(_hDC, (int)RenderPos.x, (int)RenderPos.y,
						(int)m_barSize.x, (int)m_barSize.y,
						m_texture[i]->GetDC(),
						0, 0, (int)m_barSize.x, (int)m_barSize.y,
						m_texture[i]->GetColorKey());
				}

				else
				{
					BitBlt(_hDC, (int)RenderPos.x, (int)RenderPos.y,
						(int)m_barSize.x, (int)m_barSize.y,
						m_texture[i]->GetDC(),
						0, 0, SRCCOPY);
				}
			}

			else
			{
			}
		}
	}
}

void CProgressBar::Render(HDC _hDC, const Vector2& _pos, float _deltaTime)
{
	Vector2	RenderPos = _pos;

	for (int i = 0; i < (int)EProgressBar_Texture_Type::End; ++i)
	{
		if (m_texture[i])
		{
			if (m_texture[i]->GetTextureType() == ETextureType::Sprite)
			{
				if (m_texture[i]->GetEnableColorKey())
				{
					TransparentBlt(_hDC, (int)RenderPos.x, (int)RenderPos.y,
						(int)m_barSize.x, (int)m_barSize.y,
						m_texture[i]->GetDC(),
						0, 0, (int)m_barSize.x, (int)m_barSize.y,
						m_texture[i]->GetColorKey());
				}

				else
				{
					BitBlt(_hDC, (int)RenderPos.x, (int)RenderPos.y,
						(int)m_barSize.x, (int)m_barSize.y,
						m_texture[i]->GetDC(),
						0, 0, SRCCOPY);
				}
			}

			else
			{
			}
		}
	}
}

void CProgressBar::SetBarDir(EProgressBar_Dir _dir)
{
	m_dir = _dir;
}

void CProgressBar::SetValue(float _value)
{
	m_value = _value;

	if (m_value > 1.f)
		m_value = 1.f;

	else if (m_value < 0.f)
		m_value = 0.f;
}

void CProgressBar::AddValue(float _value)
{
	m_value += _value;

	if (m_value > 1.f)
		m_value = 1.f;

	else if (m_value < 0.f)
		m_value = 0.f;
}

void CProgressBar::SetTexture(EProgressBar_Texture_Type _type, const std::string& _name, const TCHAR* _fileName, const std::string& _pathName)
{
	m_scene->GetSceneResource()->LoadTexture(_name, _fileName, _pathName);
	m_texture[(int)_type] = m_scene->GetSceneResource()->FindTexture(_name);
}

void CProgressBar::SetTextureFullPath(EProgressBar_Texture_Type _type, const std::string& _name, const TCHAR* _fullPath)
{
	m_scene->GetSceneResource()->LoadTexture(_name, _fullPath);
	m_texture[(int)_type] = m_scene->GetSceneResource()->FindTexture(_name);
}

#ifdef UNICODE

void CProgressBar::SetTexture(EProgressBar_Texture_Type _type, const std::string& _name, const std::vector<std::wstring>& _vecFileName, const std::string& _pathName)
{
	m_scene->GetSceneResource()->LoadTexture(_name, _vecFileName, _pathName);
	m_texture[(int)_type] = m_scene->GetSceneResource()->FindTexture(_name);
}

void CProgressBar::SetTextureFullPath(EProgressBar_Texture_Type _type, const std::string& _name, const std::vector<std::wstring>& _vecFullPath)
{
	m_scene->GetSceneResource()->LoadTexture(_name, _vecFullPath);
	m_texture[(int)_type] = m_scene->GetSceneResource()->FindTexture(_name);
}

#else

void CProgressBar::SetTexture(EProgressBar_Texture_Type _type, const std::string& _name, const std::vector<std::string>& _vecFileName, const std::string& _pathName)
{
	m_scene->GetSceneResource()->LoadTexture(_name, _vecFileName, _pathName);
	m_texture[(int)_type] = m_scene->GetSceneResource()->FindTexture(_name);
}

void CProgressBar::SetTextureFullPath(EProgressBar_Texture_Type _type, const std::string& _name, const std::vector<std::string>& _vecFullPath)
{
	m_scene->GetSceneResource()->LoadTexture(_name, _vecFullPath);
	m_texture[(int)_type] = m_scene->GetSceneResource()->FindTexture(_name);
}

#endif // UNICODE

void CProgressBar::SetColorKey(EProgressBar_Texture_Type _type, unsigned char _r, unsigned char _g, unsigned char _b)
{
	if (m_texture[(int)_type])
		m_texture[(int)_type]->SetColorKey(_r, _g, _b);
}

CProgressBar::CProgressBar() :
	m_dir(EProgressBar_Dir::LeftToRight),
	m_value(1.f)
{
}

CProgressBar::CProgressBar(const CProgressBar& widget) :
	CWidget(widget)
{
}

CProgressBar::~CProgressBar()
{
}