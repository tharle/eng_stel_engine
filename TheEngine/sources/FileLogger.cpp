#pragma once
#include "FileLogger.h"
#include <iostream>
#include <chrono>
#include <windows.h>
#include <sstream>

FileLogger::FileLogger()
{
	// TODO create a "Logs" directory in deployements for all files
	// TODO add to a function generateFileName
	std::stringstream strStream;
	char* fileName = "LOG_";
	std::time_t t = std::time(0);   // get time now
	std::tm* now = std::localtime(&t);
	strStream << "LOG_";
	strStream << now->tm_year + 1900;
	strStream << now->tm_mon + 1;
	strStream << now->tm_mday;
	strStream << now->tm_hour;
	strStream << now->tm_min;
	strStream << now->tm_sec;
	strStream << ".log";

	m_OutFile = std::ofstream(strStream.str());
	Info("======= Logging =======");
}

FileLogger::~FileLogger()
{
	Info("======= EOF =======");
	m_OutFile.close();
}

void FileLogger::Info(const char* message, ...)
{
	char buffer[512] = { 0 };
	va_list args;
	va_start(args, message);
	vsnprintf(buffer, 512, message, args);
	m_OutFile << buffer << std::endl;
	va_end(args);
}
