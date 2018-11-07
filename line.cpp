#include <iostream>
#include "line.h"

void Line::print(){
	for (bool &b : line) {
		cout << b << " " << flush;
	}
}

Line::Line() {
	line.fill(0);
}

/* for testing
int main () {
	Line l;
	l.print();
	return 0;
}
*/
