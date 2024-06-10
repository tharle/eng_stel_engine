#include "WindowsLogger.h"

WindowsLogger::WindowsLogger()
{
	AllocConsole();
	m_HConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int _r = freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
}

WindowsLogger::~WindowsLogger()
{
	// TODO valider les choses à fermer
	fcloseall();
}
void WindowsLogger::Info(const char* message, ...)
{
	char buffer[512] = { 0 };
	va_list args;
	va_start(args, message);
	SetConsoleTextAttribute(m_HConsole, 12);
	vsnprintf(buffer, 512, message, args);
	std::cout << buffer << std::endl;
	va_end(args);
}
