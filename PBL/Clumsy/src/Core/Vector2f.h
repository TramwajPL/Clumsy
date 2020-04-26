#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <string>
#include <sstream>

namespace Clumsy {

	class Vector2f
	{
	public:
		Vector2f(float x, float y)
		{
			m_X = x;
			m_Y = y;
		}

		float Length()
		{
			return (float)sqrt(m_X * m_X + m_Y * m_Y);
		}

		float dot(Vector2f r)
		{
			return m_X * r.GetX() + m_Y * r.GetY();
		}

		std::stringstream ToString()
		{
			std::stringstream ss;
			ss << "(" << m_X << " " << m_Y << ")";
			return ss;
		}

		Vector2f Normalize()//? inaczej musisalam zapisaæ
		{
			float length = Length();

			return Vector2f(GetX() / length, GetY() / length);
		}

		Vector2f* Rotate(float angle)
		{
			double rad = (angle * M_PI) / 180;
			double m_cos = cos(rad);
			double m_sin = sin(rad);

			return new Vector2f((float)(m_X * m_cos - m_Y * m_sin),(float)( m_X * m_sin - m_Y * m_cos));
		}

		Vector2f* Add(Vector2f r) // * ?
		{
			return new Vector2f(m_X + r.GetX(), m_Y + r.GetY());
		}

		Vector2f* Add(float r) // * ?
		{
			return new Vector2f(m_X + r, m_Y + r);
		}

		Vector2f* Sub(Vector2f r) // * ?
		{
			return new Vector2f(m_X - r.GetX(), m_Y - r.GetY());
		}

		Vector2f* Sub(float r) // * ?
		{
			return new Vector2f(m_X - r, m_Y - r);
		}


		Vector2f* Div(Vector2f r) // * ?
		{
			return new Vector2f(m_X / r.GetX(), m_Y / r.GetY());
		}

		Vector2f* Div(float r) // * ?
		{
			return new Vector2f(m_X / r, m_Y / r);
		}

		Vector2f* Mul(Vector2f r) // * ?
		{
			return new Vector2f(m_X * r.GetX(), m_Y * r.GetY());
		}

		Vector2f* Mul(float r) // * ?
		{
			return new Vector2f(m_X * r, m_Y * r);
		}

		float GetX()
		{
			return m_X;
		}

		float GetY()
		{
			return m_Y;
		}

		void SetX(float x)
		{
			m_X = x;
		}

		void SetY(float y)
		{
			m_Y = y;
		}

	private:
		float m_X;
		float m_Y;
	};
}