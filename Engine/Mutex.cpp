#include "Mutex.h"
#include <assert.h>
#include <Windows.h>

namespace Engine {
	namespace JobSystem {
		Mutex::Mutex(bool i_bTakeOwnership, const char* i_pName) {
			m_Handle = CreateMutex(NULL, (BOOL)i_bTakeOwnership, NULL);
			assert(m_Handle != NULL);
		}
		Mutex::~Mutex()
		{
			BOOL result = CloseHandle(m_Handle);
			assert(result == TRUE);
		}

		bool Mutex::TryAcquire()
		{
			DWORD result = WaitForSingleObject(m_Handle, 0);
			return result == WAIT_OBJECT_0;
		}

		void Mutex::Acquire()
		{
			DWORD result = WaitForSingleObject(m_Handle, WaitInfinite);
			assert(result == WAIT_OBJECT_0);
		}

		bool Mutex::Acquire(wait_t TimeToWait)
		{
			DWORD result = WaitForSingleObject(m_Handle, TimeToWait);
			assert((TimeToWait == WaitInfinite && result == WAIT_OBJECT_0) || (result == WAIT_TIMEOUT));
			return result == WAIT_OBJECT_0;
		}

		void Mutex::Release()
		{
			BOOL result = ReleaseMutex(m_Handle);
			assert(result == TRUE);
		}

	}
}



