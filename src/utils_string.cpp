#include "utils_string.hpp"
#include <algorithm>

namespace utils
{
	namespace string
	{
		String FormatPadding(const String &str, const Padding &padding, std::size_t s)
		{
			String res = str;
			
			if (res.size() < s)
			{
				switch (padding)
				{
				case padding_left:
					res = String(s - res.size(), ' ') + res;
					break;
				case padding_right:
					res = res + String(s - res.size(), ' ');
					break;
				}
			}

			return res;
		}
		String RemoveEndSpaces(const String &s)
		{
			String res{ s };
			Index npos{ 0 };

			npos = 0;
			for (auto i = 0; i < res.size(); ++i)
			{
				if (std::isspace(res[i]))
				{
					++npos;
				}
				else
				{
					res.erase(0, npos);
					break;
				}
			}

			npos = 0;
			for (auto i = res.size(); i > 0; --i)
			{
				if (std::isspace(res[i - 1]))
				{
					++npos;
				}
				else
				{
					res.erase(i, npos);
					break;
				}
			}

			return res;
		}
		String GetKey(const String &s, const char &separator)
		{
			std::size_t pos = s.find(separator);
			return RemoveEndSpaces(s.substr(0, pos - 1));
		}
		String GetValue(const String &s, const char &separator)
		{
			std::size_t pos = s.find(separator);

			return RemoveEndSpaces(s.substr(pos + 1));
		}
		String ToUpper(const String& s)
		{
			String res{ s };
			
			std::transform(res.begin(), res.end(), res.begin(), std::toupper);

			return res;
		}
		String ToLower(const String& s)
		{
			String res{ s };

			std::transform(res.begin(), res.end(), res.begin(), std::tolower);

			return res;
		}

		bool IsEmpty(const String& s)
		{
			bool res{ true };

			for (auto i = 0; i < s.size(); ++i)
			{
				if (std::isgraph(s[i]))
				{
					res = false;
					break;
				}
			}

			return res;
		}

		Strings Split(const String &s)
		{
			String item;
			Strings elems;
			bool flag{ false };

			for (auto i = 0; i < s.size(); ++i)
			{
				if (std::isgraph(s[i]))
				{
					if (!flag)
					{
						flag = true;
						item.clear();
					}

					item.push_back(s[i]);
				}
				else
				{
					if (flag)
					{
						elems.push_back(item);
						item.clear();
						flag = false;
					}
				}
			}

			if (flag)
			{
				elems.push_back(item);
				item.clear();
				flag = false;
			}

			return elems;
		}
		Strings Split(const String& s, std::initializer_list<char> separator)
		{
			String item;
			Strings elems;
			bool flag{ false };

			auto IsSeparator = [&separator](char c) 
				{
					return std::find(separator.begin(), separator.end(), c) != separator.end();
				};

			for (auto i = 0; i < s.size(); ++i)
			{
				if (!IsSeparator(s[i]))
				{
					if (!flag)
					{
						flag = true;
						item.clear();
					}

					item.push_back(s[i]);
				}
				else
				{
					if (flag)
					{
						elems.push_back(item);
						item.clear();
						flag = false;
					}
				}
			}

			if (flag)
			{
				elems.push_back(item);
				item.clear();
				flag = false;
			}

			return elems;
		}

		NumberWords GetNumberWords(const String& s)
		{
			NumberWords res{ 0 };
			bool entry{ false };

			for (auto i = 0; i < s.length(); ++i)
			{
				if (std::isgraph(s[i]))
				{
					if (!entry)
					{
						entry = true;
						++res;
					}
				}
				else
				{
					entry = false;
				}
			}

			return res;
		}
	} // namespace string

} // namespace utils