#include "../inc/Exception.hpp"

const char*    InvalidSize::what() const throw() {
	return ("Size of map should be in range [20;50].");
}

const char*    InvalidLibrary::what() const throw() {
	return ("Invalid library name.");
}

const char*    InvalidLibraryFunction::what() const throw() {
	return ("Invalid library function.");
}