#include "Timer.h"

Engine::Timer::Timer()
{
	m_LastUpdate = std::chrono::high_resolution_clock::now();
	m_CurrentUpdate = m_LastUpdate;
}

Engine::Timer::~Timer()
{
}

void Engine::Timer::Update()
{
	m_LastUpdate = m_CurrentUpdate;
	m_CurrentUpdate = std::chrono::high_resolution_clock::now();

	// Calculate delta time in seconds
	m_DeltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(m_CurrentUpdate - m_LastUpdate).count() / 1000000000.f;
}

double Engine::Timer::GetDeltaTime()
{
	return (double)m_DeltaTime;
}
