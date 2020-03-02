#include "JobSystem.h"
#include "JobQueue.h"
#include <vector>
#include <assert.h>
#include <functional>
#include "IJob.h"

namespace Engine {
	namespace JobSystem {
		std::vector<JobQueue> Queues;

		void CreateQueue() {
			JobQueue newJobQueue = JobQueue(Queues.size());
			Queues.push_back(newJobQueue);
		}

		void RunJob(DWORD i_QueueIndex) {
			assert(Queues.size() > i_QueueIndex);
			JobData* pData = Queues[i_QueueIndex].GetFrontJob();
			pData->pJob->RunJob();
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

		void Add(DWORD i_QueueIndex, std::function<void()> i_Func) {
			JobFunc* pJob = new JobFunc(i_Func);
			JobData* pJobData = new JobData();
			pJobData->pJob = pJob;
			assert(Queues.size() > i_QueueIndex);
			Queues[i_QueueIndex].Add(pJobData);
		}
	}
}