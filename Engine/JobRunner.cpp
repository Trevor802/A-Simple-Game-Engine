#include "JobRunner.h"
#include <assert.h>
#include "JobSystem.h"
namespace Engine {
	namespace JobSystem {
		struct JobData;
		DWORD WINAPI JobRunner(LPVOID lpParam)
		{
			assert(lpParam);
			assert((JobRunnerData*)lpParam);
			JobRunnerData* pData = reinterpret_cast<JobRunnerData*> (lpParam);
			JobQueue* pQueue = reinterpret_cast<JobQueue*> (pData->pQueue);
			bool done = false;
			do {
				JobData* pJobData = pQueue->GetFrontJob();
				if (pJobData) {
					done = true;
					pJobData->pJob->RunJob();
					delete pJobData;
					pQueue->JobFinished();
				}
			} while (!done);
			return 0;
		}
	}
}

