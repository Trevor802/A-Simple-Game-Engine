#pragma once
#include <math.h>
#include <cfloat>
#include <assert.h>
namespace Engine {
	namespace Numeric {
		static bool AreEqual(float i_lhs, float i_rhs, float i_maxDiff = FLT_EPSILON) {
			return fabs(i_lhs - i_rhs) < i_maxDiff;
		}

		template<typename T>
		static constexpr const T& clamp(const T& v, const T& lo, const T& hi) {
			assert(!(hi < lo));
			return (v < lo) ? lo : (v > hi) ? hi : v;
		}
	}
}