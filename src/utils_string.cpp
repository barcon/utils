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
		String RemoveEndSpaces(const String &arg1)
		{
			String res = arg1;
			std::size_t length = res.length();
			std::size_t npos;

			if (res.size() != 0)
			{

				npos = 0;
				for (unsigned int i = 0; i < length; ++i)
				{
					if ((res[i] == 0x09) || (res[i] == 0x20))
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
				for (std::size_t i = res.length(); i > 0; --i)
				{
					if ((res[i - 1] == 0x09) || (res[i - 1] == 0x20))
					{
						++npos;
					}
					else
					{
						res.erase(i, npos);
						break;
					}
				}
			}

			return res;
		}
		String RemoveComments(const String &arg1, const char &arg2)
		{
			String res;
			std::istringstream input(arg1);

			std::getline(input, res, arg2);

			return res;
		}
		bool IsEmpty(const String& arg1)
		{
			auto size{ arg1.size() };
			bool res{ true };

			if (size != 0)
			{
				for (auto i = 0; i < size; ++i)
				{
					if (std::isgraph(arg1[i]))
					{
						res = false;
						break;
					}
				}
			}

			return res;
		}
		unsigned int GetWords(const String &arg1)
		{
			String::size_type length = arg1.length();
			bool entry(false);
			unsigned int res = 0;

			if (length != 0)
			{
				for (unsigned int i = 0; i < length; ++i)
				{
					switch (arg1[i])
					{
					case 0x09: //Tab
					case 0x20: //Space
					case 0x3B: //;
					case 0x3D: //=
						entry = false;
						break;
					default:
						if (!entry)
						{
							entry = true;
							++res;
						}
					}
				}
			}

			return res;
		}
		String GetWord(const String &arg1, const unsigned int &arg2)
		{
			String res;
			String::size_type length = arg1.length();
			bool entry(false);
			unsigned int aux = 0;

			if (length != 0)
			{
				for (unsigned int i = 0; i < length; ++i)
				{
					switch (arg1[i])
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
							res.push_back(arg1[i]);
						}
					}
				}
			}

			return res;
		}
		String GetKey(const String &arg1, const char &arg2)
		{
			std::size_t pos = arg1.find(arg2);
			return RemoveEndSpaces(arg1.substr(0, pos - 1));
		}
		String GetValue(const String &arg1, const char &arg2)
		{
			std::size_t pos = arg1.find(arg2);

			return RemoveEndSpaces(arg1.substr(pos + 1));
		}
	} // namespace string

} // namespace utils
