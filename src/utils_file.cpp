#include "utils_file.hpp"

#include <algorithm>
#include <optional>
#include <functional>

namespace utils
{
	namespace file
	{
		Base::Base(const String& fileName)
		{
			SetName(fileName);
		}
		Base::Base(const char* fileName) : Base(static_cast<String>(fileName))
		{
		}
		Base::~Base()
		{
			Close();
		}
		Status Base::Open()
		{
			if (name_.size() == 0)
			{
				return UTILS_INVALID_FILE_NAME;
			}

			handler_.open(name_.c_str(), mode_);
			if(!handler_)
			{
				return UTILS_INVALID_HANDLER;
			}

			return UTILS_SUCCESS;
		}
		Status Base::Open(const String& fileName)
		{
			SetName(fileName);
			return Open();
		}
		void Base::Close()
		{
			if (handler_.is_open())
			{
				handler_.close();
			}
		}
		std::size_t Base::GetLength()
		{
			auto pos = handler_.tellg();

			handler_.clear();
			handler_.seekg(0, std::ios::end);
			auto res = handler_.tellg();

			handler_.clear();
			handler_.seekg(pos, std::ios::beg);

			return (unsigned int)res;
		}
		String Base::GetName() const
		{
			return name_;
		}
		Mode Base::GetMode() const
		{
			return mode_;
		}
		void Base::SetName(const String& fileName)
		{
			name_ = fileName;
		}
		void Base::SetMode(const Mode& openMode)
		{
			mode_ = openMode;
		}
		bool Base::EndOfFile()
		{
			return handler_.eof();
		}

		Text::Text(const String& fileName) : Base(fileName)
		{
		}
		Text::Text(const char* fileName) : Base(static_cast<String>(fileName))
		{
		}
		String Text::GetLine()
		{
			String res;
			std::getline(handler_, res);

			return res;
		}
		String Text::GetFull()
		{
			auto pos = handler_.tellg();

			handler_.clear();
			handler_.seekg(0, std::ios::beg);

			String res((std::istreambuf_iterator<char>(handler_)), (std::istreambuf_iterator<char>()));

			handler_.clear();
			handler_.seekg(pos, std::ios::beg);

			return res;
		}
		void Text::Write(const String& text)
		{
			handler_ << text;
		}

		Keys::Keys(const String& fileName) : Text(fileName)
		{
		}
		Keys::Keys(const char* fileName) : Text(static_cast<String>(fileName))
		{
		}
		void Keys::Initialize()
		{
			String line;
			Key key;
			Value value;

			items_.clear();
			do
			{
				line = GetLine();
				if (!utils::string::IsEmpty(line))
				{
					key = utils::string::GetKey(line, separator_);
					value = utils::string::GetValue(line, separator_);

					items_.push_back(std::pair<Key, Value>(key, value));
				}
			} while (!handler_.eof());
		}
		const Items& Keys::GetItems() const
		{
			return items_;
		}
		const Value& Keys::GetValue(const Key& key) const
		{
			String res{};
			auto it = std::find_if(items_.begin(), items_.end(), [&](const std::pair<Key, Value>& arg1) { return arg1.first == key; });

			if (it != items_.end())
			{
				return (*it).second;
			}

			return valueNull_;
		}
		void Keys::SetSeparator(char ch)
		{
			separator_ = ch;
		}
	} //namespace file
} // namespace utils