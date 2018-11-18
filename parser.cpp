#include <iostream>
#include <string>

using namespace std;

string parse(string* line)
{
	string parsed = "";
	// is there a comment, if there is remove it
	if(line->find(";") != string::npos)
	{
		size_t semiColonIndex = line->find(";");

		if (semiColonIndex == 0)
		{
			return ""; //theres nothing useful on the line
		}
		else
		{
			(*line) = line->substr(0, semiColonIndex);
		}

	}

	// find first non whitespace character
	if(line->find_first_not_of(" ") != string::npos)
	{
		size_t firstIndex = line->find_first_not_of(" ");
		(*line) = line->substr(firstIndex, line->length() - firstIndex);

		// 2 cases being there is a space, word is end of line
		if(line->find(" ") != string::npos)
		{
			size_t whiteSpaceIndex = line->find(" ");

			parsed = line->substr(0,whiteSpaceIndex);

			(*line) = line->substr(whiteSpaceIndex, line->length() - whiteSpaceIndex);

			return parsed;
		}
		else
		{
			parsed = (*line);

			(*line) = "";

			return parsed;

		}

	}

	return "";
}

int main()
{
	string line = "    This is a string ; this should not be one    ";
	string line2 = line;
	string* line2ptr = &line2;

	string parsed;
	do
	{
		parsed = parse(line2ptr);
		cout << parsed << endl;
	}
	while (parsed!= "");
}

