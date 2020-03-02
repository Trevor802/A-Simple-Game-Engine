#include "JobQueue.h"
#include <assert.h>

bool Engine::JobSystem::JobQueue::Add(JobData* i_pJob)
{
	assert(i_pJob);
	m_Jobs.push(i_pJob);
	return true;
}

Engine::JobSystem::JobData* Engine::JobSystem::JobQueue::GetFrontJob()
{
	JobData* pJob = nullptr;
	if (!m_Jobs.empty()) {
		pJob = m_Jobs.front();
		m_Jobs.pop();
	}
	return pJob;
}

bool Engine::JobSystem::JobQueue::HasJob()
{
	return !m_Jobs.empty();
}
