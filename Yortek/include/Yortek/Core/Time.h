#pragma once

#include <chrono>

namespace Yortek
{
	class Time
	{
	private:
		typedef std::chrono::steady_clock::time_point TimePoint;

	public:
		static const float get_fps() { return s_average_fps; }
		static const float get_ms_per_frame() { return 1.0f / s_average_fps * 1000.0f; }
		static const float get_delta_time() { return s_delta_time; }
		static const float get_fixed_delta_time() { return s_fixed_delta_time; }

	private:
		friend class Application;
		static void _tick();

	private:
		static const float FIXED_DELTA_TIME;

		static TimePoint s_last_frame;
		static TimePoint s_last_fixed_frame;
		static std::vector<float> s_frame_times;

		static float s_average_fps;
		static float s_delta_time;
		static float s_fixed_delta_time;
	};
}