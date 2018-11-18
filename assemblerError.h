#include <stdexcept>
#include <string>

class AssemblerException : public std::exception
{
protected: 
	std::string msg;

public:
	explicit AssemblerException(std::string message) : msg(message) {}
	const char* what() const noexcept {return msg.c_str();}
};