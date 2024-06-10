#pragma once
class ILogger 
{
public:

	/// <summary>
	/// Log a message, if is in mode DEBUG it will be in console, otherwise it will be in file
	/// </summary>
	/// <param name="message">string of characters for logging</param>
	void virtual Info(const char* message,...) = 0;
};
