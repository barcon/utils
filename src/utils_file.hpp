#ifndef UTILS_FILE_HPP_
#define UTILS_FILE_HPP_

#include "utils_string.hpp"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

namespace utils
{
	namespace file
	{		
		using Status = long long int;
		using Handler = std::fstream;
		using Length = std::size_t;
		
		using Key = String;
		using Value = String;
		using Item = std::pair<Key, Value>;
		using Items = std::vector<Item>;

		using Mode = std::ios_base::openmode;		
		static const Mode Binary = std::fstream::binary;
		static const Mode Read = std::fstream::in;
		static const Mode Write = std::fstream::out;
		static const Mode Append = std::fstream::app;
		static const Mode Truncate = std::fstream::trunc;
		static const Mode End = std::fstream::ate;		

		static const Status UTILS_SUCCESS = 0;
		static const Status UTILS_NOT_FOUND = -1;
		static const Status UTILS_INVALID_FILE_NAME = -2;
		static const Status UTILS_INVALID_HANDLER = -3;

		static const std::map<Status, String> messages =
		{
			{ 0, "UTILS_SUCCESS"},
			{-1, "UTILS_NOT_FOUND"},
			{-2, "UTILS_INVALID_FILE_NAME"},
			{-3, "UTILS_INVALID_HANDLER"}
		};

		class Base
		{
		public:
			Base() = default;
			Base(const String& fileName);
			Base(const char* fileName);
			virtual ~Base();

			Status Open();
			Status Open(const String& fileName);
			void Close();

			Length GetLength();
			String GetName() const;
			Mode GetMode() const;

			void SetName(const String& fileName);
			void SetMode(const Mode& openMode);

			bool EndOfFile();

		protected:
			String name_;
			Handler handler_;
			Mode mode_{ Read };
		};

		class Text : public Base
		{
		public:
			Text() = default;
			Text(const String& fileName);
			Text(const char* fileName);
			virtual ~Text() = default;

			String GetLine();
			String GetFull();

			void Write(const String& text);
		};

		class Keys : public Text
		{
		public:
			Keys() = default;
			Keys(const String& fileName);
			Keys(const char* fileName);
			virtual ~Keys() = default;

			void Initialize();

			const Items& GetItems() const;
			const Value& GetValue(const Key& key) const;
			void SetSeparator(char ch = '=');

		private:
			const Value valueNull_{ "" };
			char separator_{ '=' };
			Items items_;
		};

	} // namespace file
} // namespace utils

#endif /*UTILS_FILE_HPP_*/