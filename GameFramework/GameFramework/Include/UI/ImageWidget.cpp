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
		ui�� ���� ������(owner) ���� �̹��� ������ ��ġ�� ���ε�,
		�̹��� ������ ��ġ�� ���� �����츦 ��������
		������� ��ġ�� ���� ���̴�.

		���� owner�� ��ġ�� �̹��� ���� ��ġ�� ���� ��ġ��
		���� ��µ� �̹��� ���� ��ġ�̴�.
	*/
	Vector2	RenderPos = m_pos + m_owner->GetPos();

	// �ؽ��İ� ���� ���
	if (m_texture)
	{
		// �ؽ��İ� sprite ������ �̹����� ���
		if (m_texture->GetTextureType() == ETextureType::Sprite)
		{
			// �÷�Ű�� �����ϸ�
			if (m_texture->GetEnableColorKey())
			{
			/*
				TransparentBlt : BitBlt�� 1~6�����ڴ� ����.
				1. �̹����� ������� DC
				2. ������� DC������ x��ǥ
				3. ������� DC������ y��ǥ
				4. �׷��� �̹����� ����ũ��
				5. �׷��� �̹����� ����ũ��
				6. �̹����� ����� DC
				7.  ����� �̹��������� ���� x��ǥ
				8.  ����� �̹��������� ���� y��ǥ
				9.  ����� �̹����� ����ũ��
				10. ����� �̹����� ���� ũ��
				11. ����� �̹����� ���� �÷�Ű

				sprite�̹��� �������� �̹������� �̾ƿ��� �������� �޶��� ���̴�.
				�Ź� �������� �ٸ��� �Ͽ� �̹����� �ٸ��� �����;� �Ѵ�.

				** �׷��� �̹��� ������ 1���̹Ƿ� ��ǥ�� 0,0���� �����ɼ��ۿ� ����.
			*/
				TransparentBlt(_hDC, (int)RenderPos.x, (int)RenderPos.y,
					(int)m_size.x, (int)m_size.y,
					m_texture->GetDC(),
					0, 0, (int)m_size.x, (int)m_size.y,
					m_texture->GetColorKey());
			}

			else
			{
				// ���������� 4,5�� ���ڴ� 0,0���� �����̴�.
				BitBlt(_hDC, (int)RenderPos.x, (int)RenderPos.y,
					(int)m_size.x, (int)m_size.y,
					m_texture->GetDC(),
					0, 0, SRCCOPY);
			}
		}
		// �̰� �Ƹ� frame �̹����� ���?
		else
		{
		}
	}
	// �ؽ��İ� ���� ��� �簢�� ���
	else
	{
		Rectangle(_hDC, (int)RenderPos.x, (int)RenderPos.y,
			(int)(RenderPos.x + m_size.x), (int)(RenderPos.y + m_size.y));
	}
}

void CImageWidget::Render(HDC _hDC, const Vector2& _pos, float _deltaTime)
{
	Vector2	RenderPos = _pos;

	// �ؽ��İ� ���� ���
	if (m_texture)
	{
		// �ؽ��İ� sprite ������ �̹����� ���
		if (m_texture->GetTextureType() == ETextureType::Sprite)
		{
			// �÷�Ű�� �����ϸ�
			if (m_texture->GetEnableColorKey())
			{
				/*
					TransparentBlt : BitBlt�� 1~6�����ڴ� ����.
					1. �̹����� ������� DC
					2. ������� DC������ x��ǥ
					3. ������� DC������ y��ǥ
					4. �׷��� �̹����� ����ũ��
					5. �׷��� �̹����� ����ũ��
					6. �̹����� ����� DC
					7.  ����� �̹��������� ���� x��ǥ
					8.  ����� �̹��������� ���� y��ǥ
					9.  ����� �̹����� ����ũ��
					10. ����� �̹����� ���� ũ��
					11. ����� �̹����� ���� �÷�Ű

					sprite�̹��� �������� �̹������� �̾ƿ��� �������� �޶��� ���̴�.
					�Ź� �������� �ٸ��� �Ͽ� �̹����� �ٸ��� �����;� �Ѵ�.

					** �׷��� �̹��� ������ 1���̹Ƿ� ��ǥ�� 0,0���� �����ɼ��ۿ� ����.
				*/
				TransparentBlt(_hDC, (int)RenderPos.x, (int)RenderPos.y,
					(int)m_size.x, (int)m_size.y,
					m_texture->GetDC(),
					0, 0, (int)m_size.x, (int)m_size.y,
					m_texture->GetColorKey());
			}

			else
			{
				// ���������� 4,5�� ���ڴ� 0,0���� �����̴�.
				BitBlt(_hDC, (int)RenderPos.x, (int)RenderPos.y,
					(int)m_size.x, (int)m_size.y,
					m_texture->GetDC(),
					0, 0, SRCCOPY);
			}
		}
		// �̰� �Ƹ� frame �̹����� ���?
		else
		{
		}
	}
	// �ؽ��İ� ���� ��� �簢�� ���
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
