#pragma once
#include <chrono>
using namespace std;

namespace Engine {
	namespace Time {
		static chrono::steady_clock::time_point firstFrameTime;
		static chrono::steady_clock::time_point lastFrameTime;
		static chrono::steady_clock::time_point lastFixedFrameTime;

		float GetLastFrameTime() {
			return chrono::duration_cast<chrono::duration<float>>(lastFrameTime - firstFrameTime).count();
		}
		float GetLastFixedFrameTime() {
			return chrono::duration_cast<chrono::duration<float>>(lastFixedFrameTime - firstFrameTime).count();
		}
		static float deltaTime = 0.0f;
		static float fixedDeltaTime = 1.0f;
	}
}

