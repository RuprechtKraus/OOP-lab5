#include "pch.h"
#include "CppUnitTest.h"
#include "MyString.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

void VerifyMyStringCreation(const MyString& myString, const char* expectedData, size_t expectedLength)
{
	Assert::AreEqual(expectedData, myString.GetStringData(), L"String contains wrong data");
	Assert::AreEqual(expectedLength, myString.GetLength(), L"String contains wrong length");
}

namespace MyStringClassTest
{
	TEST_CLASS(MyStringClassTest)
	{
	public:
		
		TEST_METHOD(CreateStringUsingDefaultConstructor)
		{
			MyString myString;
			VerifyMyStringCreation(myString, "", 0);
		}

		TEST_METHOD(CreateStringFromPointerToChar)
		{
			char cstr[] = "Some data";
			MyString myString(cstr);
			VerifyMyStringCreation(myString, cstr, 9);
		}

		TEST_METHOD(CreateStringFromPointerToCharWithLength)
		{
			char cstr[] = "Some data";
			MyString myString(cstr, 4);
			VerifyMyStringCreation(myString, "Some", 4);
		}

		TEST_METHOD(CreateStringUsingCopyConstructor)
		{
			MyString myString("Some data");
			MyString myStringCopy(myString);
			VerifyMyStringCreation(myString, myString.GetStringData(), myString.GetLength());
		}

		TEST_METHOD(CreateStringUsingMoveConstructor)
		{
			MyString myString(std::move(MyString("Some data")));
			VerifyMyStringCreation(myString, "Some data", 9);
		}

		TEST_METHOD(CreateStringFromSTLString)
		{
			std::string str("Some data");
			MyString myString(str);
			VerifyMyStringCreation(myString, str.c_str(), str.size());
		}

		TEST_METHOD(CreateStringFromEmptyCString)
		{
			char cstr[] = "";
			MyString myString(cstr);
			VerifyMyStringCreation(myString, cstr, 0);
		}

		TEST_METHOD(CantCreateStringFromNullPointer)
		{
			auto createMyString = []() { MyString myString(nullptr); };
			Assert::ExpectException<std::invalid_argument>(createMyString, L"Created string from null pointer");
		}
	};
}