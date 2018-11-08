
%: %.cpp
	g++ -std=c++14 -Wall -Wextra -pedantic $< -o $@
