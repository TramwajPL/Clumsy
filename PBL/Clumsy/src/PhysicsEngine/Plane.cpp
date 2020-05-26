#include "../pch.h"
#include "Plane.h"

namespace Clumsy
{
	void Plane::set3Points(glm::vec3 ntr, glm::vec3 ntl, glm::vec3 ftl)
	{
		this->ntr = ntr;
		this->ntl = ntl;
		this->ftl = ftl;
	}
	Plane Plane::Normalized() const
	{
		float magnitude = glm::length(m_Normal);

		return Plane(m_Normal / magnitude, m_Distance / magnitude);
	}

	IntersectData Plane::IntersectSphere(const BoundingSphere& other) const
	{
		float distanceFromSphereCenter = glm::abs(glm::dot(m_Normal, other.GetCenter()) + m_Distance);
		float distanceFromSphere = distanceFromSphereCenter - other.GetRadius();

		return IntersectData(distanceFromSphere < 0, m_Normal * distanceFromSphere);
	}

}