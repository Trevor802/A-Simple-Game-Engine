#pragma once
#include "JobQueue.h"
#include <Windows.h>
namespace Engine {
	namespace JobSystem {
		class JobQueue;
		struct JobRunnerData
		{
			HANDLE		m_ThreadHandle;
			DWORD		m_ThreadID;
			JobQueue*	pQueue;
		};

		DWORD WINAPI JobRunner(LPVOID lpParam);
	}
}

