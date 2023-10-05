#pragma once

#ifndef __ERROR_H_
#define __ERROR_H_ 1

#include <iostream>
#include <vector>

/* Error codes */

#define SYNTAX_ERROR 1
#define SEMANTIC_ERROR 2
#define INCORRECT_ARGUMENT_FORMAT 3


/* Error messages */

std::vector<std::string> error_messages = {"NULL", "Syntax error", "Semantic error", "Argument error"};


/* Prints a  message to stderr, according to the error code */

void printError(int error_code) {
	std::cerr << error_messages[error_code];
}

#endif