#pragma once

#ifndef __UTILS_H_
#define __UTILS_H_ 1

#include <sstream>
#include <algorithm>
#include <string>
#include <iostream>


bool IsNonterminal(char c) {
    return (c >= 65 && c <= 90);
}

bool IsTerminal(char c) {
    return !IsNonterminal(c);
}

bool IsNonterminal(std::string s) {
    for(int i = 0; i < s.length(); i ++) {
        if (IsTerminal(s[i])) {
            return false;
        }
    }
    return true;
}

bool IsTerminal(std::string s) {
    for (int i = 0; i < s.length(); i ++) {
        if (IsNonterminal(s[i])) {
            return false;
        }
    }
    return true;
}

/* Adds a character to a string only if it is not already there */

bool AppendNoDuplicates(std::string &s, char c) {
    if (s.find(c) == std::string::npos) {
        s.append(1,c);
        return true;
    }
    return false;
}

/* Deletes all occurences of delim in the string s */

void squeeze(std::string &s, char delim) {
	s.erase(std::remove(s.begin(),s.end(),delim),s.end());
}

/* tokenize a string based on a delimitator, returns a vector of strings */

void split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
    	if (!item.empty()) {
	        elems.push_back(item);
    	}
    }
}

/* Wrapper for easier and cleaner writing of tokenization process */

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

#endif