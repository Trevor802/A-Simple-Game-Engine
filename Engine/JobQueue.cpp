#include "JobQueue.h"
#include <assert.h>

Engine::JobSystem::JobQueue::JobQueue() : m_bShutdownRequested(false)
{
	InitializeConditionVariable(&m_WakeAndCheck);
	InitializeCriticalSection(&m_QueueAccess);
}

bool Engine::JobSystem::JobQueue::Add(JobData* i_pJob)
{
	assert(i_pJob);
	bool bAdded = false;
	EnterCriticalSection(&m_QueueAccess);
	if (!m_bShutdownRequested) {
		m_Jobs.push(i_pJob);
		bAdded = true;
	}
	LeaveCriticalSection(&m_QueueAccess);
	if (bAdded)
		WakeConditionVariable(&m_WakeAndCheck);
	return bAdded;
}

Engine::JobSystem::JobData* Engine::JobSystem::JobQueue::GetFrontJob()
{
	EnterCriticalSection(&m_QueueAccess);
	if (m_Jobs.empty() && !m_bShutdownRequested) {
		BOOL result = SleepConditionVariableCS(&m_WakeAndCheck, &m_QueueAccess, INFINITE);
		assert(result != 0);
		if (m_bShutdownRequested) {
			LeaveCriticalSection(&m_QueueAccess);
			return nullptr;
		}
	}
	JobData* pJob = nullptr;
	if (!m_Jobs.empty()) {
		pJob = m_Jobs.front();
		m_Jobs.pop();
	}
	m_bJobRunning = true;
	LeaveCriticalSection(&m_QueueAccess);
	return pJob;
}

bool Engine::JobSystem::JobQueue::HasJob() const
{
	EnterCriticalSection(&m_QueueAccess);
	bool bFinished = m_Jobs.empty() && !m_bJobRunning;
	LeaveCriticalSection(&m_QueueAccess);
	return !bFinished;
}

bool Engine::JobSystem::JobQueue::JobFinished()
{
	EnterCriticalSection(&m_QueueAccess);
	m_bJobRunning = false;
	LeaveCriticalSection(&m_QueueAccess);
	return false;
}

//void Engine::JobSystem::JobQueue::Shutdown()
//{
//	EnterCriticalSection(&m_QueueAccess);
//	m_bShutdownRequested = true;
//	LeaveCriticalSection(&m_QueueAccess);
//	WakeAllConditionVariable(&m_WakeAndCheck);
//}
