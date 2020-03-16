#pragma once
#include "IJob.h"
#include <Windows.h>
#include <queue>
#include <vector>
#include <JobRunner.h>

namespace Engine {
	namespace JobSystem {
		struct JobRunnerData;
		struct JobData;
		class JobQueue {
		public:
			JobQueue();
			DWORD Index;
			bool Add(JobData* i_pJob);
			JobData* GetFrontJob();
			bool HasJob() const;
			inline void SetID(DWORD i_Index) { Index = i_Index; }
			bool JobFinished();
			//void Shutdown();
			//inline bool ShutdownRequested() const { return m_bShutdownRequested; }
		private:
			JobQueue(const JobQueue&) = delete;
			JobQueue& operator= (const JobQueue&) = delete;
			std::queue<JobData*> m_Jobs;
			CONDITION_VARIABLE m_WakeAndCheck;
			mutable CRITICAL_SECTION m_QueueAccess;
			bool m_bJobRunning;
			bool m_bShutdownRequested;
		};
		struct JobQueueData {
			JobQueue					m_Queue;
			std::vector<JobRunnerData*> m_Runners;
		};
	}
}

