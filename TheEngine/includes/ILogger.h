#pragma once

class ILogger 
{
public:
	/// <summary>
	/// Show console.
	/// </summary>
	void virtual AllocConsole() = 0;

	/// <summary>
	/// Hide console.
	/// </summary>
	void virtual FreeConsole() = 0;

	/// <summary>
	/// Log a message, if is in mode DEBUG it will be in console, otherwise it will be in file
	/// </summary>
	/// <param name="message">string of characters for logging</param>
	void virtual Log(const char* message) = 0;
};
