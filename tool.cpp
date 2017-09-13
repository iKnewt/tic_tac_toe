#include "tool.h"
#include "game.h"
#include <algorithm>

namespace tool
{
	// Converts the characters of a string to only lower case letters
	// Useful for ignoring capitalization in user input when looking for specific strings
	string toLower(string line)
	{
		transform(line.begin(), line.end(), line.begin(),(int (*)(int))tolower);
		return line;
	}

	// tests if a string/user input is an int
	// if string input is an int, it stores that data as an int
	// in the RAM adress specified by the int-poiner which we can later retreve
	// this function returns a bool because it's meant to be used as the parameter of an if-statement
	// so that if the input is not an int we can print an error message and exit that function
	bool tryParseInt(string input, int* out)
	{
		try
		{
			*out = stoi(input);
			return true;
		}
		catch (const exception&)
		{
			return false;
		}
	}

	// reads user input and determens if it's an int
	bool tryReadInt(int* out)
	{
		return tryParseInt(readLine(), out);
	}

	// eliminates the need to make a new variable every time we need a user input
	// I like doing this instead of cin to make sure we use ALL the data
	// in a cin there might be extra data that would be stored and used for the next instance of cin
	// which might lead to a lot of errors down the line

	string readLine()
	{
		string line = "";
		getline(cin, line);
		return line;
	}
}

