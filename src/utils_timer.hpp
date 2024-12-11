#ifndef UTILS_TIMER_HPP_
#define UTILS_TIMER_HPP_

#include <chrono>
#include <ctime>

namespace utils{
	
	using Clock = std::chrono::high_resolution_clock;
	
	struct Date{
		unsigned int years;
		unsigned int months;	
		unsigned int days;	
		unsigned int hours;			
		unsigned int minutes;				
		double seconds;
	};
	
	std::tm GetLocalTime(std::time_t timer);

	Date GetDate();
	
	class Timer
	{
	public:

		Timer();
		virtual ~Timer() = default;

		void Reset();
		double Elapsed() const;

	private:
		std::chrono::time_point<Clock> begin_;
	};

} // namespace utils

#endif /*UTILS_TIMER_HPP_*/