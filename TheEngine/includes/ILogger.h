#pragma once

#define LOG_INFO 0
#define LOG_WARNING 0
#define LOG_ERROR 2
class ILogger 
{

public:

	~ILogger(){};

	/// <summary>
	/// Log a message, if is in mode DEBUG it will be in console, otherwise it will be in file
	/// </summary>
	/// <param name="message">string of characters for logging</param>
	void virtual Print(int codeLog, const char* message,...) = 0;
};
