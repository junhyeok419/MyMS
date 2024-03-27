#include "ImageWidget.h"
#include "../Resource/Texture/Texture.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "WidgetWindow.h"

bool CImageWidget::Init()
{
	return true;
}

void CImageWidget::Update(float _deltaTime)
{
}

void CImageWidget::PostUpdate(float _deltaTime)
{
}

void CImageWidget::Render(HDC _hDC, float _deltaTime)
{
	/*
		ui용 위젯 윈도우(owner) 내에 이미지 위젯을 배치할 것인데,
		이미지 위젯의 위치는 위젯 윈도우를 기준으로
		상대적인 위치로 구할 것이다.

		따라서 owner의 위치에 이미지 위젯 위치를 더한 위치가
		실제 출력될 이미지 위젯 위치이다.
	*/
	Vector2	RenderPos = m_pos + m_owner->GetPos();

	// 텍스쳐가 있을 경우
	if (m_texture)
	{
		// 텍스쳐가 sprite 형식의 이미지일 경우
		if (m_texture->GetTextureType() == ETextureType::Sprite)
		{
			// 컬러키가 존재하면
			if (m_texture->GetEnableColorKey())
			{
			/*
				TransparentBlt : BitBlt와 1~6번인자는 같다.
				1. 이미지를 출력해줄 DC
				2. 출력해줄 DC에서의 x좌표
				3. 출력해줄 DC에서의 y좌표
				4. 그려낼 이미지의 가로크기
				5. 그려낼 이미지의 세로크기
				6. 이미지를 출력할 DC
				7.  출력할 이미지에서의 시작 x좌표
				8.  출력할 이미지에서의 시작 y좌표
				9.  출력할 이미지의 가로크기
				10. 출력할 이미지의 세로 크기
				11. 출력할 이미지에 대한 컬러키

				sprite이미지 기준으로 이미지에서 뽑아오는 시작점은 달라질 것이다.
				매번 시작점을 다르게 하여 이미지를 다르게 가져와야 한다.

				** 그러나 이미지 위젯은 1장이므로 좌표가 0,0으로 고정될수밖에 없다.
			*/
				TransparentBlt(_hDC, (int)RenderPos.x, (int)RenderPos.y,
					(int)m_size.x, (int)m_size.y,
					m_texture->GetDC(),
					0, 0, (int)m_size.x, (int)m_size.y,
					m_texture->GetColorKey());
			}

			else
			{
				// 마찬가지로 4,5번 인자는 0,0으로 고정이다.
				BitBlt(_hDC, (int)RenderPos.x, (int)RenderPos.y,
					(int)m_size.x, (int)m_size.y,
					m_texture->GetDC(),
					0, 0, SRCCOPY);
			}
		}
		// 이건 아마 frame 이미지일 경우?
		else
		{
		}
	}
	// 텍스쳐가 없을 경우 사각형 출력
	else
	{
		Rectangle(_hDC, (int)RenderPos.x, (int)RenderPos.y,
			(int)(RenderPos.x + m_size.x), (int)(RenderPos.y + m_size.y));
	}
}

void CImageWidget::Render(HDC _hDC, const Vector2& _pos, float _deltaTime)
{
	Vector2	RenderPos = _pos;

	// 텍스쳐가 있을 경우
	if (m_texture)
	{
		// 텍스쳐가 sprite 형식의 이미지일 경우
		if (m_texture->GetTextureType() == ETextureType::Sprite)
		{
			// 컬러키가 존재하면
			if (m_texture->GetEnableColorKey())
			{
				/*
					TransparentBlt : BitBlt와 1~6번인자는 같다.
					1. 이미지를 출력해줄 DC
					2. 출력해줄 DC에서의 x좌표
					3. 출력해줄 DC에서의 y좌표
					4. 그려낼 이미지의 가로크기
					5. 그려낼 이미지의 세로크기
					6. 이미지를 출력할 DC
					7.  출력할 이미지에서의 시작 x좌표
					8.  출력할 이미지에서의 시작 y좌표
					9.  출력할 이미지의 가로크기
					10. 출력할 이미지의 세로 크기
					11. 출력할 이미지에 대한 컬러키

					sprite이미지 기준으로 이미지에서 뽑아오는 시작점은 달라질 것이다.
					매번 시작점을 다르게 하여 이미지를 다르게 가져와야 한다.

					** 그러나 이미지 위젯은 1장이므로 좌표가 0,0으로 고정될수밖에 없다.
				*/
				TransparentBlt(_hDC, (int)RenderPos.x, (int)RenderPos.y,
					(int)m_size.x, (int)m_size.y,
					m_texture->GetDC(),
					0, 0, (int)m_size.x, (int)m_size.y,
					m_texture->GetColorKey());
			}

			else
			{
				// 마찬가지로 4,5번 인자는 0,0으로 고정이다.
				BitBlt(_hDC, (int)RenderPos.x, (int)RenderPos.y,
					(int)m_size.x, (int)m_size.y,
					m_texture->GetDC(),
					0, 0, SRCCOPY);
			}
		}
		// 이건 아마 frame 이미지일 경우?
		else
		{
		}
	}
	// 텍스쳐가 없을 경우 사각형 출력
	else
	{
		Rectangle(_hDC, (int)RenderPos.x, (int)RenderPos.y,
			(int)(RenderPos.x + m_size.x), (int)(RenderPos.y + m_size.y));
	}
}

void CImageWidget::SetTexture(const std::string& _name, const TCHAR* _fileName, const std::string& _pathName)
{
	m_scene->GetSceneResource()->LoadTexture(_name, _fileName, _pathName);
	m_texture = m_scene->GetSceneResource()->FindTexture(_name);
}

void CImageWidget::SetTextureFullPath(const std::string& _name, const TCHAR* _fullPath)
{
	m_scene->GetSceneResource()->LoadTextureFullPath(_name, _fullPath);
	m_texture = m_scene->GetSceneResource()->FindTexture(_name);
}

#ifdef UNICODE

void CImageWidget::SetTexture(const std::string& _name, const std::vector<std::wstring>& _vecFileName, const std::string& _pathName)
{
	m_scene->GetSceneResource()->LoadTexture(_name, _vecFileName, _pathName);
	m_texture = m_scene->GetSceneResource()->FindTexture(_name);
}

void CImageWidget::SetTextureFullPath(const std::string& _name, const std::vector<std::wstring>& _vecFullPath)
{
	m_scene->GetSceneResource()->LoadTextureFullPath(_name, _vecFullPath);
	m_texture = m_scene->GetSceneResource()->FindTexture(_name);
}

#else
	
void CImageWidget::SetTexture(const std::string& _name, const std::vector<std::string>& _vecFileName, const std::string& _pathName)
{
	m_scene->GetSceneResource()->LoadTexture(_name, _vecFileName, _pathName);
	m_texture = m_scene->GetSceneResource()->FindTexture(_name);
}

void CImageWidget::SetTextureFullPath(const std::string& _name, const std::vector<std::string>& _vecFullPath)
{
	m_scene->GetSceneResource()->LoadTextureFullPath(_name, _vecFullPath);
	m_texture = m_scene->GetSceneResource()->FindTexture(_name);
}

#endif // UNICODE

void CImageWidget::SetColorKey(unsigned char _r, unsigned char _g, unsigned char _b)
{
	if (m_texture)
		m_texture->SetColorKey(_r, _g, _b);
}

CImageWidget::CImageWidget()
{
}

CImageWidget::CImageWidget(const CImageWidget& _widget)
	: CWidget(_widget)
{
}

CImageWidget::~CImageWidget()
{
}
