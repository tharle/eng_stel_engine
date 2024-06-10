#pragma once
#include "ILogger.h"
#include <iostream>

// Library effective with Windows
#include <windows.h>
// Library effective with Linux
//#include <unistd.h>

class SdlLogger : public ILogger
{
private:
	HANDLE m_HConsole;
public:
	void virtual Init() override;
	void virtual FreeConsole() override;
	void virtual Log(const char* message,...) override;
	void virtual Warning(const char* message) override;
	void virtual Error(const char* message) override;
};

