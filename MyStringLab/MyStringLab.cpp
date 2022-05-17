#include "MyString.h"
#include <iostream>
#include <string>

int main()
{
	MyString str("Hello");
	auto a{ str.begin() };
	auto b{ str.end() };

	std::cout << b - a;

	return 0;
}