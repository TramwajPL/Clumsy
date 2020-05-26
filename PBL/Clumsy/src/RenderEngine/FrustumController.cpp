#include "../pch.h"
#include "FrustumController.h"

namespace Clumsy {
#define ANG2RAD 3.14159265358979323846/180.0

	void FrustumController::setCamInternals(float angle, float ratio, float nearD, float farD) {

		this->ratio = ratio;
		this->angle = angle;
		this->nearD = nearD;
		this->farD = farD;

		tang = (float)tan(ANG2RAD * angle * 0.5);
		nh = nearD * tang;
		nw = nh * ratio;
		fh = farD * tang;
		fw = fh * ratio;
	}

	void FrustumController::setCamDef(glm::vec3& p, glm::vec3& l, glm::vec3& u) {

		pl[TOP].set3Points(ntr, ntl, ftl);
		pl[BOTTOM].set3Points(nbl, nbr, fbr);
		pl[LEFT].set3Points(ntl, nbl, fbl);
		pl[RIGHT].set3Points(nbr, ntr, fbr);
		pl[NEARP].set3Points(ntl, ntr, nbr);
		pl[FARP].set3Points(ftr, ftl, fbl);
	}

	bool FrustumController::pointInPlane(Plane p, glm::vec3 point) {

		bool result;
		float distance = glm::dot(p.GetNormal(), point) - p.GetDistance();
		if (distance < 0)
			result = true;
		else
			result = false;
		return result;
	}
}