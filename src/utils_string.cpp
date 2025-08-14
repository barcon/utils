#include "utils_string.hpp"

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

/*
String RemoveComments(const String& s, const char& c)
{
	String res;
	std::istringstream input(s);

	std::getline(input, res, c);

	return res;
}

		String GetWord(const String &s, const unsigned int &arg2)
		{
			String res;
			bool entry(false);
			unsigned int aux = 0;

			for (auto i = 0; i < s.size(); ++i)
			{
				switch (s[i])
				{
				case 0x09: //Tab
				case 0x20: //Space
				case 0x3B: //;
				case 0x3D: //=
					if (entry && (aux == arg2))
					{
						return res;
					}
					entry = false;
					break;
				default:
					if (!entry)
					{
						entry = true;
						++aux;
					}

					if (aux == arg2)
					{
						res.push_back(s[i]);
					}
				}
			}

			return res;
		}

*/