#pragma once
#include <glm/glm.hpp>
#include "../PhysicsEngine/Aabb.h"
#include "../PhysicsEngine/Plane.h"

namespace Clumsy {
	class FrustumController {

	private:

		enum {
			TOP = 0, BOTTOM, LEFT,
			RIGHT, NEARP, FARP
		};

	public:

		static enum { OUTSIDE, INTERSECT, INSIDE };

		Plane pl[6];

		glm::vec3 ntl, ntr, nbl, nbr, ftl, ftr, fbl, fbr;
		float nearD, farD, ratio, angle, tang;
		float nw, nh, fw, fh;

		FrustumController();
		~FrustumController();


		void setCamInternals(float angle, float ratio, float nearD, float farD);
		void setCamDef(glm::vec3& p, glm::vec3& l, glm::vec3& u);
		bool pointInPlane(Plane p, glm::vec3 point);
		int sphereInFrustum(glm::vec3& p, float raio);
		int boxInFrustum(Aabb& b);

	};

}