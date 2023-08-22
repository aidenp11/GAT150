#include "Logger.h"
#include "FileIO.h"
#include <iostream>

namespace lady
{
	bool Logger::Log(LogLevel logLevel, std::string filename, int line)
	{
		if (logLevel < m_logLevel) return false;

		switch (logLevel)
		{
		case lady::LogLevel::Info:
			*this << "INFO: ";
			break;
		case lady::LogLevel::Warning:
			*this << "WARNING: ";
			break;
		case lady::LogLevel::Error:
			*this << "ERROR: ";
			break;
		case lady::LogLevel::Assert:
			*this << "ASSERT: ";
			break;
		default:
			break;
		}

		*this << getFileName(filename) << "(" << line << ") ";

		return true;
	}
}