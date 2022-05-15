#include "pch.h"
#include "CppUnitTest.h"
#include "MyString.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

void VerifyMyString(const MyString& myString, const char* expectedData, size_t expectedLength)
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
			VerifyMyString(myString, "", 0);
		}

		TEST_METHOD(CreateStringFromPointerToChar)
		{
			char cstr[] = "Some data";
			MyString myString(cstr);
			VerifyMyString(myString, cstr, 9);
		}

		TEST_METHOD(CreateStringFromPointerToCharWithLength)
		{
			char cstr[] = "Some data";
			MyString myString(cstr, 4);
			VerifyMyString(myString, "Some", 4);
		}

		TEST_METHOD(CreateStringUsingCopyConstructor)
		{
			MyString myString("Some data");
			MyString myStringCopy(myString);
			VerifyMyString(myString, myString.GetStringData(), myString.GetLength());
		}

		TEST_METHOD(CreateStringUsingMoveConstructor)
		{
			MyString myString(std::move(MyString("Some data")));
			VerifyMyString(myString, "Some data", 9);
		}

		TEST_METHOD(CreateStringFromSTLString)
		{
			std::string str("Some data");
			MyString myString(str);
			VerifyMyString(myString, str.c_str(), str.size());
		}

		TEST_METHOD(CreateStringFromEmptyCString)
		{
			char cstr[] = "";
			MyString myString(cstr);
			VerifyMyString(myString, cstr, 0);
		}

		TEST_METHOD(CantCreateStringFromNullPointer)
		{
			auto createMyString = []() { MyString myString(nullptr); };
			Assert::ExpectException<std::invalid_argument>(createMyString, L"Created string from null pointer");
		}

		TEST_METHOD(AssignOneStringToAnother)
		{
			MyString first("First string");
			MyString second("Second string");
			first = second;
			VerifyMyString(first, second.GetStringData(), second.GetLength());
		}

		TEST_METHOD(AssignStringToItself)
		{
			MyString myString("My string");
			myString = myString;
			VerifyMyString(myString, "My string", 9);
		}

		TEST_METHOD(ConcatenateMyStringWithMyString)
		{
			MyString hello("Hello ");
			MyString world("world!");
			hello = hello + world;
			VerifyMyString(hello, "Hello world!", 12);
		}

		TEST_METHOD(ConcatenateMyStringWithSTLString)
		{
			MyString hello("Hello ");
			std::string world("world!");
			hello = hello + world;
			VerifyMyString(hello, "Hello world!", 12);
		}

		TEST_METHOD(ConcatenateMyStringWithCharArray)
		{
			MyString hello("Hello ");
			char world[] = "world!";
			hello = hello + world;
			VerifyMyString(hello, "Hello world!", 12);
		}

		TEST_METHOD(ConcatenateAndAssignMyStringWithMyString)
		{
			MyString hello("Hello ");
			MyString world("world!");
			hello += world;
			VerifyMyString(hello, "Hello world!", 12);
		}

		TEST_METHOD(ConcatenateAndAssignMyStringWithSTLString)
		{
			MyString hello("Hello ");
			std::string world("world!");
			hello += world;
			VerifyMyString(hello, "Hello world!", 12);
		}

		TEST_METHOD(ConcatenateAndAssignMyStringWithCharArray)
		{
			MyString hello("Hello ");
			char world[] = "world!";
			hello += world;
			VerifyMyString(hello, "Hello world!", 12);
		}

		TEST_METHOD(CompareMyStrings)
		{
			Assert::IsTrue(MyString("string") == MyString("string"), L"Equal string compare failed");
			Assert::IsTrue(MyString("MiXeD CaSe") == MyString("MiXeD CaSe"), L"Mixed case compare failed");
			Assert::IsTrue(MyString("one") != MyString("two"), L"Different string compare failed");
			Assert::IsFalse(MyString("string") != MyString("string"), L"Equal string compare failed");
			Assert::IsFalse(MyString("other") == MyString("another"), L"Different string compare failed");
			Assert::IsTrue(MyString("short") != MyString("looooong"), L"Different string compare failed");
			Assert::IsFalse(MyString("short") == MyString("looooong"), L"Different string compare failed");
			Assert::IsTrue(MyString("atoms\0\0\0\0", 9) == MyString("atoms\0\0\0\0", 9), 
				L"Strings with null-characters compare failed");
			Assert::IsTrue(MyString("atoms\0\0abs", 10) == MyString("atoms\0\0abs", 10), 
				L"Strings with null-characters compare failed");
			Assert::IsTrue(MyString("atoms\0\0absu", 13) != MyString("atoms\0\0abs", 10), 
				L"Strings with null-characters compare failed");
		}
	};
}