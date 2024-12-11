#ifndef UTILS_MATH_HPP_
#define UTILS_MATH_HPP_

#include <random>
#include <chrono>
#include <type_traits>

namespace utils
{	
	
namespace math
{
	extern unsigned char BitsLookUpTable[];
	extern unsigned int CyclicLookUpTable1[];
	extern unsigned int CyclicLookUpTable2[];
	extern unsigned int CyclicLookUpTable3[];
	extern unsigned int CyclicLookUpTable4[];

	unsigned int CyclicPermutation0(unsigned int arg1);
	unsigned int CyclicPermutationReverve0(unsigned int arg1);
	unsigned int CyclicPermutation(unsigned int arg1);
	unsigned int CyclicPermutationReverse(unsigned int arg1);
	unsigned int Power(unsigned int base, unsigned int exp);
	unsigned int Power2Floor(unsigned int x);
	unsigned int Power2Ceil(unsigned int x);
	unsigned char BitsCount(unsigned char arg1);
	
	template <typename T> constexpr T Pi()
	{
		return static_cast<T>(3.141592653589793238462643383279502884197169399375);
	}
	template<typename T> typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type IsAlmostEqual(T x, T y, int ulp)
	{
		return (std::fabs(x-y) <= std::numeric_limits<T>::epsilon() * std::fabs(x+y) * ulp) || (std::fabs(x-y) < std::numeric_limits<T>::min());
	}	

	namespace random
	{
		template <typename T>
		class Base
		{
		public:
			virtual ~Base() = default;

			virtual void SetParam(T a, T b) = 0;
			virtual void Reset() = 0;
			virtual T Generate() = 0;
			virtual T operator()() = 0;

		protected:
			Base() = default;
		};

		class UniformInt : public Base<int>
		{
		public:
			UniformInt()
			{
				SetParam(0, 1);
				Initialize();
			}
			UniformInt(int min, int max) {
				SetParam(min, max);
				Initialize();
			}
			virtual ~UniformInt() = default;

			void SetParam(int a, int b) override
			{				
				distribution = std::uniform_int_distribution<int>(a, b);
			}
			void Reset() override
			{
				distribution.reset();
			}		
			int Generate() override
			{
				return distribution(generator);
			}
			int operator()() override
			{
				return distribution(generator);
			}

		protected:
			virtual void Initialize()
			{
				generator = std::default_random_engine();
				generator.seed((unsigned int)std::chrono::system_clock::now().time_since_epoch().count());
			}

			std::default_random_engine generator;
			std::uniform_int_distribution<int> distribution;
		};
		
		class UniformDouble : public Base<double>
		{
		public:
			UniformDouble()
			{
				SetParam(0, 1);
				Initialize();
			}
			UniformDouble(double min, double max) {
				SetParam(min, max);
				Initialize();
			}
			virtual ~UniformDouble() = default;

			void SetParam(double a, double b) override
			{				
				distribution = std::uniform_real_distribution<double>(a, b);
			}
			void Reset() override
			{
				distribution.reset();
			}		
			double Generate() override
			{
				return distribution(generator);
			}
			double operator()() override
			{
				return distribution(generator);
			}

		protected:
			virtual void Initialize()
			{
				generator = std::default_random_engine();
				generator.seed((unsigned int)std::chrono::system_clock::now().time_since_epoch().count());
			}

			std::default_random_engine generator;
			std::uniform_real_distribution<double> distribution;
		};			
	} // namespace random
} // namespace math
} // namespace utils

#endif /*UTILS_MATH_HPP_*/