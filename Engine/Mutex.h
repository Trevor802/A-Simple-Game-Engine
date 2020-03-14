#pragma once
#include "WaitableObject.h"
namespace Engine {
	namespace JobSystem {
		class Mutex : WaitableObject
		{
		public:
			Mutex(bool i_bTakeOwnership = false, const char* i_pName = nullptr);
			~Mutex();
			bool TryAcquire();
			void Acquire();
			bool Acquire(wait_t TimeToWait);
			void Release();
		private:
			Mutex(const Mutex&) = delete;
			Mutex& operator=(const Mutex&) = delete;
			HANDLE m_Handle;
		};
	}
}


