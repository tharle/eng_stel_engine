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

	std::ofstream newFileLog (strStream.str());
	m_OutFile = &newFileLog;
	//*(m_OutFile) << "NEW LOG tro" << std::endl;
	Info("====== Logging ==========");
}

FileLogger::~FileLogger()
{
	if(m_OutFile != nullptr)
	{
		Info("EOF");
		m_OutFile->close();
		delete m_OutFile;
		m_OutFile = nullptr;
	}


}

void FileLogger::Info(const char* message, ...)
{
	char buffer[512] = { 0 };
	va_list args;
	va_start(args, message);
	SetConsoleTextAttribute(m_OutFile, 12);
	vsnprintf(buffer, 512, message, args);
	*(m_OutFile) << buffer << std::endl;
	va_end(args);
}
