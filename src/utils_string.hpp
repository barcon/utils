#ifndef UTILS_STRING_HPP_
#define UTILS_STRING_HPP_

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iterator>
#include <memory>

namespace utils {

	using String = std::string;
	using Strings = std::vector<String>;

	namespace string {
		
		using Padding = std::size_t;
		static const Padding padding_left{ 0 };
		static const Padding padding_right{ 1 };

		template<typename ... Args> String Format( const String& format, Args ... args )
		{
			size_t size = snprintf( nullptr, 0, format.c_str(), args ... ) + static_cast<size_t>(1);

			if( size <= 0 )
			{
				throw std::runtime_error( "Error during formatting." );
			}
			std::unique_ptr<char[]> buf(new char[size]);
			snprintf( buf.get(), size, format.c_str(), args ... );

			return String( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
		}
		template <typename T>  T ConvertTo(const String &input)
		{
			T res;

			static_cast<std::istringstream>(input) >> res;
			return res;
		}	
		String FormatPadding(const String& str, const Padding& padding, std::size_t s);

		Strings Split(const String& s);
		String RemoveEndSpaces(const String &arg1);
		String RemoveComments(const String &arg1, const char &arg2);
		
		bool IsEmpty(const String& arg1);
		unsigned int GetWords(const String &arg1);
		
		String GetWord(const String &arg1, const unsigned int &arg2);
		String GetKey(const String &arg1, const char &arg2);
		String GetValue(const String &arg1, const char &arg2);
	} // namespace string

} // namespace utils

#endif /*UTILS_STRING_HPP_*/