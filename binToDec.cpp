#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

/*
	converts an array of booleans (1's and 0's) to a decimal number (little-endian)
*/
int binToDec(vector<bool> bin)
{
	int length = bin.size();
	int decimal = 0;

	for (int i = 0; i < length; i++)
	{
		if (bin.at(i) == 1) //add value of 2^(length - i - 1)(value of its position in the binary number)
		{
			decimal += (static_cast<int>(pow(2, i)));
		}
	}

	return decimal;
}

int main()
{
	cout << binToDec(vector<bool>{1,0,1}) << endl;
}

