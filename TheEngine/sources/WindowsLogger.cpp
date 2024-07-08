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
	_fcloseall();
}
void WindowsLogger::Print(int codeLog, const char* message, ...)
{
	int codeColor = COLOR_INFO;
	switch (codeLog)
	{
		case LOG_WARNING:
			codeColor = COLOR_WARNING;
			break;
		case LOG_ERROR:
			codeColor = COLOR_ERROR;
			break;
		default:
			codeColor = COLOR_INFO;
			break;
	}

	char buffer[512] = { 0 };
	va_list args;
	va_start(args, message);
	SetConsoleTextAttribute(m_HConsole, codeColor);
	vsnprintf(buffer, 512, message, args);
	std::cout << buffer << std::endl;
	SetConsoleTextAttribute(m_HConsole, 7);
	va_end(args);

}
