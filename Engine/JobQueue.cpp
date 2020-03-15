#include "JobQueue.h"
#include <assert.h>

Engine::JobSystem::JobQueue::JobQueue(DWORD i_Index) :
	Index(i_Index)
{
	InitializeConditionVariable(&m_WakeAndCheck);
	InitializeCriticalSection(&m_QueueAccess);
}

bool Engine::JobSystem::JobQueue::Add(JobData* i_pJob)
{
	assert(i_pJob);
	bool bAdded = false;
	EnterCriticalSection(&m_QueueAccess);
	m_Jobs.push(i_pJob);
	bAdded = true;
	LeaveCriticalSection(&m_QueueAccess);
	if (bAdded)
		WakeConditionVariable(&m_WakeAndCheck);
	return bAdded;
}

Engine::JobSystem::JobData* Engine::JobSystem::JobQueue::GetFrontJob()
{
	EnterCriticalSection(&m_QueueAccess);
	if (m_Jobs.empty()) {
		BOOL result = SleepConditionVariableCS(&m_WakeAndCheck, &m_QueueAccess, INFINITE);
		assert(result != 0);
	}
	JobData* pJob = nullptr;
	if (!m_Jobs.empty()) {
		pJob = m_Jobs.front();
		m_Jobs.pop();
	}
	LeaveCriticalSection(&m_QueueAccess);
	return pJob;
}

bool Engine::JobSystem::JobQueue::HasJob()
{
	EnterCriticalSection(&m_QueueAccess);
	bool bFinished = m_Jobs.empty();
	LeaveCriticalSection(&m_QueueAccess);
	return !bFinished;
}
