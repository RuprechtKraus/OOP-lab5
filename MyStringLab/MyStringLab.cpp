#include "MyString.h"
#include <iostream>
#include <string>

int main()
{
	const std::string str("Hello");
	MyString myString("Hello");
	auto it = myString.cbegin();

	return 0;
}