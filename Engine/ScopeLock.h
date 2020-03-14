#pragma once
#include "Mutex.h"
namespace Engine {
	namespace JobSystem {
		class ScopeLock {
		public:
			ScopeLock(Mutex& mutex) : m_pMutex(&mutex) {
				m_pMutex->Acquire();
			}
			~ScopeLock() {
				m_pMutex->Release();
			}
		private:
			ScopeLock(const ScopeLock&) = delete;
			ScopeLock& operator=(const ScopeLock&) = delete;
			Mutex* m_pMutex;
		};
	}
}
