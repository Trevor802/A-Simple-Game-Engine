#pragma once
#include "IJob.h"
#include <queue>

namespace Engine {
	namespace JobSystem {
		struct JobData;
		class JobQueue {
		public:
			JobQueue(DWORD i_Index) : Index(i_Index) {};
			DWORD Index;
			bool Add(JobData* i_pJob);
			JobData* GetFrontJob();
			bool HasJob();
		private:
			std::queue<JobData*> m_Jobs;
		};
	}
}

