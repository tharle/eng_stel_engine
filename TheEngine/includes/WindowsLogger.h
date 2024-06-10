#pragma once
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
	void Info(const char* message, ...) override;
};

