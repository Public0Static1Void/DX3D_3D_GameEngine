#include "Logger.h"
#include <iostream>

dx3d::Logger::Logger(LogLevel logLevel) : m_logLevel(logLevel)
{
	std::clog << "DGonzalez | C++ Game Engine practice" << "\n";
	std::clog << "------------------------------------" << "\n";
}

dx3d::Logger::~Logger()
{
}

void dx3d::Logger::Log(LogLevel logLevel, const char* message)
{
	auto logLevelToString = [](LogLevel level) {
		switch (level) {
		default: return "Unknown";
		case LogLevel::Info: return "Info";
		case LogLevel::Error: return "Error";
		case LogLevel::Warning: return "Warning";
		}
	};

	if (logLevel > m_logLevel) return;
	std::clog << "[DX3D " << logLevelToString(logLevel) << "]: " << message << "\n";
}
