#include "JobSystem.h"
#include "JobQueue.h"
#include <vector>
#include <assert.h>
#include <functional>
#include <Windows.h>
#include "IJob.h"

namespace Engine {
	namespace JobSystem {
		std::vector<JobQueueData*> Queues;
		struct JobRunnerData;
		class JobQueue;
		void CreateQueue() {
			JobQueueData* newJobQueueData = new JobQueueData();
			newJobQueueData->m_Queue.SetID(Queues.size());
			Queues.push_back(newJobQueueData);
			AddRunner(*newJobQueueData);
		}

		void AddRunner(JobQueueData& i_QueueData) {
			JobRunnerData* pRunnerData = new JobRunnerData;
			pRunnerData->pQueue = &i_QueueData.m_Queue;
			pRunnerData->m_ThreadHandle = CreateThread(NULL, 0, JobRunner, &pRunnerData->pQueue, 
				CREATE_SUSPENDED, &pRunnerData->m_ThreadID);
			assert(pRunnerData->m_ThreadHandle != NULL);
			i_QueueData.m_Runners.push_back(pRunnerData);
			ResumeThread(pRunnerData->m_ThreadHandle);
		}

		void RunJob(DWORD i_QueueIndex, std::function<void()> i_Func) {
			assert(Queues.size() > i_QueueIndex);
			JobFunc* pJob = new JobFunc(i_Func);
			JobData* pJobData = new JobData();
			pJobData->pJob = pJob;
			Queues[i_QueueIndex]->m_Queue.Add(pJobData);
		}

		bool HasJob(DWORD i_QueueIndex)
		{
			assert(Queues.size() > i_QueueIndex);
			return Queues[i_QueueIndex]->m_Queue.HasJob();
		}

		/*template<typename T>
		void AddMemberJob(DWORD i_QueueIndex, T* i_Parent, std::function<void(void*, DWORD)> i_Func, void* i_Argc, DWORD i_Index) {
			JobMemberFunc* pJob = new JobMemberFunc<T>(i_Parent, i_Func);
			JobData* pJobData = new JobData();
			pJobData->pJob = pJob;
			pJobData->pArgs = i_Argc;
			pJobData->Index = i_Index;
			assert(Queues.size() > i_QueueIndex);
			Queues[i_QueueIndex].Add(pJobData);
		}*/
	}
}