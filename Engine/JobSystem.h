#pragma once
#include <string>
#include <functional>
#include <Windows.h>
#include "JobQueue.h"
#include "IJob.h"

namespace Engine {
	namespace JobSystem {
		struct JobData
		{
			IJob* pJob	= nullptr;
			void* pArgs = nullptr;
			DWORD Index = 0;
			~JobData() {
				delete pJob;
				delete pArgs;
			}
		};
		void CreateQueue();
		void AddRunner(JobQueueData& i_QueueData);
		void RunJob(DWORD i_QueueIndex, std::function<void()> i_Func);
		bool HasJob(DWORD i_QueueIndex);
		/*void AddMemberJob(DWORD i_QueueIndex, T* i_Parent, std::function<void> i_Func, 
			void* i_Argc, DWORD i_Index);*/
	}
}


