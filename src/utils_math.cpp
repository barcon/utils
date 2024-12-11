#include "utils_math.hpp"

namespace utils
{
	namespace math
	{
		unsigned char BitsLookUpTable[] = {
			0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
			1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
			1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
			2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
			1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
			2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
			2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
			3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
			1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
			2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
			2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
			3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
			2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
			3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
			3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
			4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8 };
		unsigned int CyclicLookUpTable1[] = { 1, 2, 0 };
		unsigned int CyclicLookUpTable2[] = { 2, 0, 1 };
		unsigned int CyclicLookUpTable3[] = { 2, 3, 1 };
		unsigned int CyclicLookUpTable4[] = { 3, 1, 2 };

		unsigned int CyclicPermutation0(unsigned int arg1)
		{
			return CyclicLookUpTable1[arg1];
		}
		unsigned int CyclicPermutationReverve0(unsigned int arg1)
		{
			return CyclicLookUpTable2[arg1];
		}
		unsigned int CyclicPermutation(unsigned int arg1)
		{
			return CyclicLookUpTable3[arg1];
		}
		unsigned int CyclicPermutationReverse(unsigned int arg1)
		{
			return CyclicLookUpTable4[arg1];
		}

		unsigned int Power(unsigned int base, unsigned int exp)
		{
			unsigned int res = 1;

			while (exp != 0)
			{
				if ((exp & 1) != 0)
					res *= base;
				exp >>= 1;
				base *= base;
			}

			return res;
		}
		unsigned int Power2Floor(unsigned int x)
		{
			unsigned int power = 1;
			while (x >>= 1) power <<= 1;
			return power;
		}
		unsigned int Power2Ceil(unsigned int x)
		{
			if (x <= 1) return 1;
			unsigned int power = 2;
			x--;
			while (x >>= 1) power <<= 1;
			return power;
		}

		unsigned char BitsCount(unsigned char arg1)
		{
			return BitsLookUpTable[arg1];
		}

	} // namespace math

} // namespace utils