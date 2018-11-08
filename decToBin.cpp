#include <iostream>
#include <vector>

using namespace std;

/*
	Converts a decimal number to a vector<bool>(32) in little-endian and returns the pointer
*/
vector<bool>* decToBinary(int dec) 
{
	vector<bool>* bin = new vector<bool>(32, 0); // vector to hold binary value (in this case size 8 for rule.)

	for (int i=31; dec>0; i--)
	{
		// take the remainder of the dec / 2 and save it to the vector
		// this value will always be 1 or 0
		(*bin).at(31-i) = dec%2;
		// update dec
		dec /= 2;
	}
		return bin;

}

/* prints vector */
void printVector(vector<bool> * v) {
	vector<bool>::iterator it;
	for (it=v->begin(); it != v->end(); ++it) {
		cout << *it << " " <<flush;
	}
	cout <<endl;
	
}

int main()
{
	int dec = 100;
	vector<bool>* vec = decToBinary(dec);
	printVector(vec);
}