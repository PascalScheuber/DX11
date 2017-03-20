#pragma once
#include <chrono>

namespace Engine
{
	class Timer
	{
	#pragma region Variables
	public:

	private:   
		std::chrono::time_point<std::chrono::steady_clock> m_CurrentUpdate;
		std::chrono::time_point<std::chrono::steady_clock> m_LastUpdate;
		double m_DeltaTime;

	#pragma endregion

	#pragma region Methods
	public:
		Timer();
		~Timer();

		void Update();
		double GetDeltaTime();

	private:

	#pragma endregion
	};
}
