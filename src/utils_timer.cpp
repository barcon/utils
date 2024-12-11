#include "utils_timer.hpp"
#include <mutex>

namespace utils
{
	std::tm GetLocalTime(std::time_t timer)
	{
		std::tm bt{};
#if defined(__unix__)
		localtime_r(&timer, &bt);
#elif defined(_MSC_VER)
		localtime_s(&bt, &timer);
#else
		static std::mutex mtx;
		std::lock_guard<std::mutex> lock(mtx);
		bt = *std::localtime(&timer);
#endif
		return bt;
	}
	Date GetDate()
	{
		Date res{};
				
		auto now = std::chrono::system_clock::now();		
		auto time = std::chrono::system_clock::to_time_t(now);
		struct tm parts = GetLocalTime(time);

		res.years = parts.tm_year + 1900;
		res.months = parts.tm_mon + 1;
		res.days = parts.tm_mday;
		res.hours = parts.tm_hour;
		res.minutes = parts.tm_min;
		
		std::chrono::duration<double> fraction = (now - std::chrono::system_clock::from_time_t(time)) + std::chrono::seconds(parts.tm_sec);
		res.seconds = fraction.count();
		
		return res;
	}
	Timer::Timer() : begin_(std::chrono::high_resolution_clock::now())
	{
	}
	void Timer::Reset()
	{
		begin_ = std::chrono::high_resolution_clock::now();
	}
	double Timer::Elapsed() const
	{
		return (double)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - begin_).count();
	}
} // namespace utils