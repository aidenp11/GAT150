#pragma once
#include <C:\Users\apatrick\source\repos\GAT150\Source\Engine\Framework\Singleton.h>
#include <string>
#include <cassert>
#include <fstream>
#include <iostream>

#ifdef _DEBUG
#define INFO_LOG(message) { if (lady::Logger::Instance().Log(lady::LogLevel::Info, __FILE__, __LINE__)) { lady::Logger::Instance() << message << "\n";} }
#define WARNING_LOG(message) { if (lady::Logger::Instance().Log(lady::LogLevel::Warning, __FILE__, __LINE__)) { lady::Logger::Instance() << message << "\n";} }
#define ERROR_LOG(message) { if (lady::Logger::Instance().Log(lady::LogLevel::Error, __FILE__, __LINE__)) { lady::Logger::Instance() << message << "\n";} }
#define ASSERT_LOG(condition, message) { if (!condition && Logger::Instance().Log(lady::LogLevel::Assert, __FILE__, __LINE__)) { lady::Logger::Instance() << message << "\n";} assert(condition); }
#else
#define INFO_LOG(message) {}
#define WARNING_LOG(message) {}
#define ERROR_LOG(message) {}
#define ASSERT_LOG(condition, message) {}
#endif // _DEBUG

namespace lady
{
	enum class LogLevel
	{
		Info,
		Warning,
		Error,
		Assert
	};

	class Logger : public Singleton<Logger>
	{
	public:
		Logger(LogLevel logLevel = LogLevel::Info, std::ostream* ostream = &std::cout, const std::string& filename = "log.txt") :
			m_logLevel{ logLevel },
			m_ostream{ ostream }
		{
			if (!filename.empty()) m_ofstream.open(filename);
		}

		bool Log(LogLevel logLevel, std::string filename, int line);

		template<typename T>
		Logger& operator << (T value);

	private:
		LogLevel m_logLevel; 
		std::ostream* m_ostream = nullptr;
		std::ofstream m_ofstream;

	};


	template<typename T>
	inline Logger& Logger::operator<<(T value)
	{
		if (m_ostream) *m_ostream << value;
		if (m_ofstream.is_open())
		{
			m_ofstream << value;
			m_ofstream.flush();
		}

		return *this;
	}
}