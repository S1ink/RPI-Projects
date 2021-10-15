#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include <cstring>

#include "resources.h"

uint16_t toNum(char num);

char clearEnd(std::string& str);
void replace(std::string& str, const std::string find, const char* replace);

std::string withTime(const char* message);

const char* dateStamp();
const char* dateStamp(time_t* tme);

template<typename input>
void debug(input identifier) {
	std::cout << dateStamp() << " : DEBUG: " << identifier << newline;
}

void exitError(const char* message);