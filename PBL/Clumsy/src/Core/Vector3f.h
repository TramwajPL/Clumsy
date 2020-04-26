#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <string>
#include <sstream>

namespace Clumsy {

	class Vector3f
	{
	public:

		Vector3f(float x, float y, float z)
		{
			m_X = x;
			m_Y = y;
			m_Z = z;
		}

		float Length()
		{
			return (float)sqrt(m_X * m_X + m_Y * m_Y + m_Z * m_Z);
		}

		float dot(Vector3f r)
		{
			return m_X * r.GetX() + m_Y * r.GetY() + m_Z * r.GetZ();
		}

		std::stringstream ToString()
		{
			std::stringstream ss;
			ss << "(" << m_X << " " << m_Y << " " << m_Z << ")";
			return ss;
		}

		Vector3f Cross(Vector3f r)
		{
			float x_ = m_Y * r.GetZ() - m_Z * r.GetY();
			float y_ = m_Z * r.GetX() - m_X * r.GetZ();
			float z_ = m_X * r.GetY() - m_Y * r.GetX();

			return Vector3f(x_, y_, z_); //? czy tutaj dodaæ new ? jako pointer?
		}

		Vector3f Normalize()//? inaczej musisalam zapisaæ
		{
			float length = Length();

			return Vector3f(GetX() / length, GetY() / length, GetZ() / length);
		}

		Vector3f* Rotate(float angle)
		{
			return nullptr; //for now
		}

		Vector3f* Add(Vector3f r) // * ?
		{
			return new Vector3f(m_X + r.GetX(), m_Y + r.GetY(), m_Z + r.GetZ()); // NWM CZY NIE ZMIENIÆ NA  PO PROSTU : RETURN VECTOR3....??
		}

		Vector3f* Add(float r) // * ?
		{
			return new Vector3f(m_X + r, m_Y + r, m_Z + r);
		}

		Vector3f* Sub(Vector3f r) // * ?
		{
			return new Vector3f(m_X - r.GetX(), m_Y - r.GetY(), m_Z - r.GetZ());
		}

		Vector3f* Sub(float r) // * ?
		{
			return new Vector3f(m_X - r, m_Y - r, m_Z - r);
		}


		Vector3f* Div(Vector3f r) // * ?
		{
			return new Vector3f(m_X / r.GetX(), m_Y / r.GetY(), m_Z / r.GetZ());
		}

		Vector3f* Div(float r) // * ?
		{
			return new Vector3f(m_X / r, m_Y / r, m_Z / r);
		}

		Vector3f* Mul(Vector3f r) // * ?
		{
			return new Vector3f(m_X * r.GetX(), m_Y * r.GetY(), m_Z * r.GetZ());
		}

		Vector3f* Mul(float r) // * ?
		{
			return new Vector3f(m_X * r, m_Y * r, m_Z * r);
		}

		float GetX()
		{
			return m_X;
		}

		float GetY()
		{
			return m_Y;
		}

		float GetZ()
		{
			return m_Z;
		}

		void SetX(float x)
		{
			m_X = x;
		}

		void SetY(float y)
		{
			m_Y = y;
		}
		
		void SetZ(float z)
		{
			m_Z = z;
		}
	private:
		float m_X;
		float m_Y;
		float m_Z;
	};
}