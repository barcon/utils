#ifndef UTILS_PAIR_HPP_
#define UTILS_PAIR_HPP_

namespace utils
{

	template <typename S, typename T>
	class Pair
	{
	public:
		S var1;
		T var2;

		Pair() = default;
		Pair(const S& arg1, const T& arg2) : var1(arg1), var2(arg2) {}
		Pair(const Pair<S, T>& arg1)
		{
			var1 = arg1.var1;
			var2 = arg1.var2;
		}
		Pair(Pair<S, T>&& arg1)
		{
			var1 = std::move(arg1.var1);
			var2 = std::move(arg1.var2);
		}
		virtual ~Pair() = default;

		inline Pair<S, T>& operator=(const Pair<S, T>& rhs)
		{
			if (this != &rhs)
			{
				var1 = rhs.var1;
				var2 = rhs.var2;
			}
			return *this;
		}
		inline Pair<S, T>& operator=(Pair<S, T>&& rhs)
		{
			if (this != &rhs)
			{
				var1 = std::move(rhs.var1);
				var2 = std::move(rhs.var2);
			}
			return *this;
		}
		inline bool operator==(const Pair<S, T>& rhs) const
		{
			if (var1 == rhs.var1 && var2 == rhs.var2)
			{
				return true;
			}
			return false;
		}
		inline bool operator!=(const Pair<S, T>& rhs) const
		{
			return !operator==(rhs);
		}
		inline bool operator<(const Pair<S, T>& rhs) const
		{
			bool res = true;
			if (var1 == rhs.var1)
			{
				return var2 < rhs.var2;
			}
			else
			{
				res = var1 < rhs.var1;
			}

			return res;
		}
	};

} // namespace utils

#endif /*UTILS_PAIR_HPP_*/
