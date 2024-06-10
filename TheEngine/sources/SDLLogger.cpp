#include "SDLLogger.h"
#include "SDL.h"

void SdlLogger::Init()
{
	AllocConsole();
	m_HConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int _r = freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
}

void SdlLogger::FreeConsole()
{
	//FreeConsole();
	// TODO valider les choses à fermer
	fcloseall();
}

void SdlLogger::Log(const char* message,...)
{
	char temp[512] = { 0 };
	va_list args;
	va_start(args,message);
	SetConsoleTextAttribute(m_HConsole, 12);
	vsnprintf(temp, 512, message, args);
	std::cout << "LOG: " << temp << std::endl;
	va_end(args);
}

void SdlLogger::Warning(const char* message)
{
	SDL_Log(message);
}

void SdlLogger::Error(const char* message)
{
	SDL_Log(message);
}
