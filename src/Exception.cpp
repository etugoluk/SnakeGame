#include "../inc/Exception.hpp"

const char*    InvalidSize::what() const throw() {
	return ("Size of map should be in range [20;50]");
}