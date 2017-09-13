#pragma once
#include <iostream>
#include <string>
#include <limits>

namespace tool
{
	using namespace std;

	string toLower(string stuff);

	bool tryParseInt(string input, int* out);
	string readLine();
	bool tryReadInt(int* out);

}
