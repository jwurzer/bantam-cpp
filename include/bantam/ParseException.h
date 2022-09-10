#ifndef PARSE_EXCEPTION_H
#define PARSE_EXCEPTION_H

#include <exception>
#include <string>

namespace bantam
{

class ParseException: public std::exception {
public:
	ParseException(const std::string& message)
		:mMessage(message)
	{
	}
	
	virtual const char* what() const throw() override
	{
		return mMessage.c_str();
	}
private:
	const std::string mMessage;
};

}

#endif
