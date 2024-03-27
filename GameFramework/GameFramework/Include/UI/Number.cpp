#include "Number.h"
#include "../Resource/Texture/Texture.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "WidgetWindow.h"

bool CNumber::Init()
{
	return true;
}

void CNumber::Update(float _deltaTime)
{
	if (m_number == 0)
	{
		m_vecNumber.clear();
		m_vecNumber.push_back(0);
	}
	// ���ڸ� �� �ڸ����� �����Ѵ�.
	else
	{
		int	Number = m_number;

		std::stack<int>	NumberStack;

		/*
			123 % 10 = 3    
			123 / 10 = 12  

			12 % 10 = 2  
			12 / 10 = 1   

			1 % 10 = 1   
			1 / 10 = 0
		*/
		while (Number > 0)
		{
			/*
				���� �� 3, 2, 1 ������ ���ϰ�, 
				���� �� 1, 2, 3 ������ ������ �ϹǷ�
				������ ����Ѵ�.
			*/
			NumberStack.push(Number % 10);
			Number /= 10;
		}

		m_vecNumber.clear();

		while (!NumberStack.empty())
		{
			m_vecNumber.push_back(NumberStack.top());
			NumberStack.pop();
		}
	}

	
}

void CNumber::PostUpdate(float _deltaTime)
{
}

void CNumber::Render(HDC _hDC, float _deltaTime)
{
	

	if (!m_vecNumber.empty())
	{
		Vector2	renderPos = m_pos + m_owner->GetPos();

		if (m_texture)
		{
			size_t	size = m_vecNumber.size();

			// ���Ϳ� ���� ������ŭ �ݺ��Ͽ� ����ؾ� �Ѵ�.
			for (size_t i = 0; i < size; ++i)
			{
				// sprite �ؽ���
				if (m_texture->GetTextureType() == ETextureType::Sprite)
				{
					if (m_texture->GetEnableColorKey())
					{
						TransparentBlt(_hDC, (int)renderPos.x + i * m_size.x, (int)renderPos.y,
							(int)m_size.x, (int)m_size.y,
							m_texture->GetDC(),
							(int)(m_vecNumber[i] * m_size.x), 0,
							(int)m_size.x, (int)m_size.y,
							m_texture->GetColorKey());
					}
					else
					{
						BitBlt(_hDC, (int)renderPos.x + i * m_size.x, (int)renderPos.y,
							(int)m_size.x, (int)m_size.y,
							m_texture->GetDC(),
							(int)(m_vecNumber[i] * m_size.x), 0, SRCCOPY);
					}
				}
				// frame �ؽ���
				else
				{
					if (m_texture->GetEnableColorKey())
					{
						TransparentBlt(_hDC, (int)renderPos.x + i * m_size.x, (int)renderPos.y,
							(int)m_size.x, (int)m_size.y,
							m_texture->GetDC(m_vecNumber[i]),
							0, 0, (int)m_size.x, (int)m_size.y,
							m_texture->GetColorKey());
					}
					else
					{
						BitBlt(_hDC, (int)renderPos.x + i * m_size.x, (int)renderPos.y,
							(int)m_size.x, (int)m_size.y,
							m_texture->GetDC(m_vecNumber[i]),
							0, 0, SRCCOPY);
					}
				}
			}
		}
	}
}

void CNumber::Render(HDC _hDC, const Vector2& _pos, float _deltaTime)
{
	if (!m_vecNumber.empty())
	{
		Vector2	renderPos = _pos;

		if (m_texture)
		{
			size_t	size = m_vecNumber.size();

			// ���Ϳ� ���� ������ŭ �ݺ��Ͽ� ����ؾ� �Ѵ�.
			for (size_t i = 0; i < size; ++i)
			{
				// sprite �ؽ���
				if (m_texture->GetTextureType() == ETextureType::Sprite)
				{
					if (m_texture->GetEnableColorKey())
					{
						TransparentBlt(_hDC, (int)renderPos.x + i * m_size.x, (int)renderPos.y,
							(int)m_size.x, (int)m_size.y,
							m_texture->GetDC(),
							(int)(m_vecNumber[i] * m_size.x), 0,
							(int)m_size.x, (int)m_size.y,
							m_texture->GetColorKey());
					}
					else
					{
						BitBlt(_hDC, (int)renderPos.x + i * m_size.x, (int)renderPos.y,
							(int)m_size.x, (int)m_size.y,
							m_texture->GetDC(),
							(int)(m_vecNumber[i] * m_size.x), 0, SRCCOPY);
					}
				}
				// frame �ؽ���
				else
				{
					if (m_texture->GetEnableColorKey())
					{
						TransparentBlt(_hDC, (int)renderPos.x + i * m_size.x, (int)renderPos.y,
							(int)m_size.x, (int)m_size.y,
							m_texture->GetDC(m_vecNumber[i]),
							0, 0, (int)m_size.x, (int)m_size.y,
							m_texture->GetColorKey());
					}
					else
					{
						BitBlt(_hDC, (int)renderPos.x + i * m_size.x, (int)renderPos.y,
							(int)m_size.x, (int)m_size.y,
							m_texture->GetDC(m_vecNumber[i]),
							0, 0, SRCCOPY);
					}
				}
			}
		}
	}
}

void CNumber::SetNumber(int _number)
{
	m_number = _number;
}

void CNumber::AddNumber(int _number)
{
	m_number += _number;
}

void CNumber::SetTexture(const std::string& _name, const TCHAR* _fileName, const std::string& _pathName)
{
	m_scene->GetSceneResource()->LoadTexture(_name, _fileName, _pathName);
	m_texture = m_scene->GetSceneResource()->FindTexture(_name);
}

void CNumber::SetTextureFullPath(const std::string& _name, const TCHAR* _fullPath)
{
	m_scene->GetSceneResource()->LoadTextureFullPath(_name, _fullPath);
	m_texture = m_scene->GetSceneResource()->FindTexture(_name);
}

#ifdef UNICODE

void CNumber::SetTexture(const std::string& _name, const std::vector<std::wstring>& _vecFileName, const std::string& _pathName)
{
	m_scene->GetSceneResource()->LoadTexture(_name, _vecFileName, _pathName);
	m_texture = m_scene->GetSceneResource()->FindTexture(_name);
}

void CNumber::SetTextureFullPath(const std::string& _name, const std::vector<std::wstring>& _vecFullPath)
{
	m_scene->GetSceneResource()->LoadTextureFullPath(_name, _vecFullPath);
	m_texture = m_scene->GetSceneResource()->FindTexture(_name);
}

#else 

void CNumber::SetTexture(const std::string& _name, const std::vector<std::string>& _vecFileName, const std::string& _pathName)
{
	m_scene->GetSceneResource()->LoadTexture(_name, _vecFileName, _pathName);
	m_texture = m_scene->GetSceneResource()->FindTexture(_name);
}

void CNumber::SetTextureFullPath(const std::string& _name, const std::vector<std::string>& _vecFullPath)
{
	m_scene->GetSceneResource()->LoadTextureFullPath(_name, _vecFullPath);
	m_texture = m_scene->GetSceneResource()->FindTexture(_name);
}

#endif // UNICODE

void CNumber::SetColorKey(unsigned char _r, unsigned char _g, unsigned char _b)
{
	if (m_texture)
		m_texture->SetColorKey(_r, _g, _b);
}

CNumber::CNumber()
	: m_number(0)
{
}

CNumber::CNumber(const CNumber& _widget)
{
}

CNumber::~CNumber()
{
}
