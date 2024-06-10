#include "SDLLogger.h"


void SDLLogger::AllocConsole()
{
	m_HConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

void SDLLogger::FreeConsole()
{
	// TODO close console
}

void SDLLogger::Log(const char* message)
{
	//printf(message);
}
