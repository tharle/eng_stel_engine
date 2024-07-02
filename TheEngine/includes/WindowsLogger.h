#pragma once
#define COLOR_INFO 11
#define COLOR_WARNING 6
#define COLOR_ERROR 12

#include "ILogger.h"
#include <iostream>

// Library effective with Windows
#include <windows.h>
// Library effective with Linux
//#include <unistd.h>

class WindowsLogger : public ILogger
{
private:
	HANDLE m_HConsole;
public:
	WindowsLogger();
	~WindowsLogger();
	void Print(int codeLog, const char* message, ...) override;
};

