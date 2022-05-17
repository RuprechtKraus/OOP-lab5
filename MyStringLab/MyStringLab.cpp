#include <iostream>
#include <string>
#include "MyString.h"

int main()
{
	/*std::string str("Hello");
	auto a{ str.begin() + 1 };
	auto b { a + 2 };

	b - a;*/

	MyString myString("Hello");
	auto a{ myString.begin() };
	std::cout << *(++(++a));

	return 0;
}