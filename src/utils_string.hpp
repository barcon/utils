#ifndef UTILS_STRING_HPP_
#define UTILS_STRING_HPP_

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iterator>
#include <memory>
#include <initializer_list>

namespace utils {

	using String = std::string;
	using Strings = std::vector<String>;
	using NumberWords = std::size_t;
	using Index = std::size_t;

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
		Strings Split(const String& s, std::initializer_list<char> separator);
		String RemoveEndSpaces(const String &s);
		
		bool IsEmpty(const String& s);
		
		String GetKey(const String &s, const char &separator);
		String GetValue(const String &s, const char &separator);

		NumberWords GetNumberWords(const String &s);
	} // namespace string

} // namespace utils

#endif /*UTILS_STRING_HPP_*/

//String RemoveComments(const String &s, const char &c);
//String GetWord(const String &arg1, const unsigned int &arg2);