#pragma once
#include <iostream>
#include <Windows.h>
#include "ILogger.h"

class SDLLogger : public ILogger
{
private:
	HANDLE m_HConsole;
public:
	void virtual AllocConsole() override;
	void virtual FreeConsole() override;
	void virtual Log(const char* message) override;
};

