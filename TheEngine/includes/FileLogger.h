#pragma once
#include "ILogger.h"
#include <fstream>


class FileLogger : public ILogger 
{
private:
	std::ofstream m_OutFile;
public:
	FileLogger();
	~FileLogger();
	void Print(int codeLog, const char* message, ...) override;
};