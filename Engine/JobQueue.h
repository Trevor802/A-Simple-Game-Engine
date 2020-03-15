#pragma once
#include "IJob.h"
#include <Windows.h>
#include <queue>

namespace Engine {
	namespace JobSystem {
		struct JobData;
		class JobQueue {
		public:
			JobQueue(DWORD i_Index);
			DWORD Index;
			bool Add(JobData* i_pJob);
			JobData* GetFrontJob();
			bool HasJob();
		private:
			std::queue<JobData*> m_Jobs;
			CONDITION_VARIABLE m_WakeAndCheck;
			mutable CRITICAL_SECTION m_QueueAccess;
		};
	}
}

