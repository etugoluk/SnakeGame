#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <stdexcept>

class InvalidSize : public std::exception
{
	public:
		virtual const char *what() const throw();
};

#endif