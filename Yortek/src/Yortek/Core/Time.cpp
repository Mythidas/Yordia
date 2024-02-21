#include "Yortek/Core/Time.h"

namespace Yortek
{
	const float Time::FIXED_DELTA_TIME = 0.02f;

	Time::TimePoint Time::s_last_frame = std::chrono::high_resolution_clock::now();
	Time::TimePoint Time::s_last_fixed_frame;

	std::vector<float> Time::s_frame_times;

	float Time::s_average_fps;
	float Time::s_delta_time;
	float Time::s_fixed_delta_time;


	void Time::_tick()
	{
		static float s_one_second = 1.0f;
		TimePoint now = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> delta = now - s_last_frame;
		s_last_frame = now;
		s_delta_time = delta.count();

		s_one_second -= s_delta_time;
		if (s_one_second < 0.0f)
		{
			float total = 0.0f;
			for (auto& ds : s_frame_times)
				total += ds;

			s_average_fps = 1.0f / (total / s_frame_times.size());
			s_frame_times.clear();
			s_one_second = 1.0f;
		}
		else
		{
			s_frame_times.push_back(s_delta_time);
		}

		std::chrono::duration<float> fixedDelta = now - s_last_fixed_frame;
		if (fixedDelta.count() >= FIXED_DELTA_TIME)
		{
			s_last_fixed_frame = now;
			s_fixed_delta_time = fixedDelta.count();
		}
		else
		{
			s_fixed_delta_time = 0.0f;
		}
	}
}