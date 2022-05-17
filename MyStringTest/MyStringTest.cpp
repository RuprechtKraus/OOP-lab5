﻿#include "pch.h"
#include "CppUnitTest.h"
#include "MyString.h"
#include <sstream>

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

		TEST_METHOD(MoveAssignStringToAnother)
		{
			MyString first("First string");
			first = std::move(MyString("Second string"));
			VerifyMyString(first, "Second string", 13);
		}

		TEST_METHOD(MoveAssignStringToItself)
		{
			#pragma warning (push)
			#pragma warning (disable: 26800)

			MyString first("First string");
			first = std::move(first);
			VerifyMyString(first, "First string", 12);

			#pragma warning (pop)
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

		TEST_METHOD(CompareEqual)
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

		TEST_METHOD(CompareLess)
		{
			Assert::IsTrue(MyString("abc") < MyString("abcd"), L"Left string must be less");
			Assert::IsTrue(MyString("abc") <= MyString("abcd"), L"Left string must be less");
			Assert::IsTrue(MyString("abc") <= MyString("abc"), L"Strings must be equal");
			Assert::IsFalse(MyString("abcd") < MyString("abc"), L"Right string must be less");
			Assert::IsFalse(MyString("abcd") <= MyString("abc"), L"Right string must be less");
		}

		TEST_METHOD(CompareGreater)
		{
			Assert::IsFalse(MyString("abc") > MyString("abcd"), L"Right string must be greater");
			Assert::IsFalse(MyString("abc") >= MyString("abcd"), L"Right string must be greater");
			Assert::IsTrue(MyString("abcd") > MyString("abc"), L"Left string must be greater");
			Assert::IsTrue(MyString("abcd") >= MyString("abc"), L"Left string must be greater");
			Assert::IsTrue(MyString("abcd") >= MyString("abcd"), L"String must be equal");
		}

		TEST_METHOD(SubscriptOperatorWithIndexWithinBounds)
		{
			MyString myString("Moss");
			myString[0] = 'B';

			Assert::AreEqual("Boss", myString.GetStringData(), L"Words don't match");
		}

		TEST_METHOD(SubscriptOperatorWithIndexOutOfBounds)
		{
			MyString myString("Moss");
			auto callSubscript = [&myString]() { myString[10]; };
			Assert::ExpectException<std::out_of_range>(callSubscript, L"Exception had to be thrown");
		}

		TEST_METHOD(PrintMyStringToStream)
		{
			MyString myString("Hello world!");
			std::ostringstream ss;

			ss << myString;
			Assert::IsTrue("Hello world!" == ss.str(), L"Output was incorrect");	
		}

		TEST_METHOD(PrintMyStringWithNullCharsInMiddleToStream)
		{
			MyString myString("abc\0\0abc", 8);
			std::ostringstream ss;

			ss << myString;
			Assert::IsTrue(memcmp(ss.str().c_str(), "abcabc", myString.GetLength()), L"Output was incorrect");
		}

		TEST_METHOD(ReadMyStringFromStreamUntilSpace)
		{
			MyString myString("");
			std::istringstream ss("Hello world!");

			ss >> myString;
			VerifyMyString(myString, "Hello", 5);
		}

		TEST_METHOD(ReadMyStringFromStreamUntilEnd)
		{
			MyString myString("");
			std::istringstream ss("Hello_world!");

			ss >> myString;
			VerifyMyString(myString, "Hello_world!", 12);
		}
	};

	TEST_CLASS(MyStringIteratorClassTest)
	{
	public:

		TEST_METHOD(DereferenceIterator)
		{
			MyString myString("Hello world!");
			MyString::Iterator it = myString.begin();
			Assert::AreEqual('H', *it, L"");
		}

		TEST_METHOD(IterateThroughNonConstantMyString)
		{
				MyString myString("Hello world!");
				int i{};

				for (char c : myString)
				{
					Assert::AreEqual(myString[i++], c, L"Letters don't match");
				}
		}

		TEST_METHOD(AddIntegerToIterator)
		{
			MyString myString("Hello world!");
			auto it{ myString.begin() };

			it = it + 6;
			Assert::AreEqual('w', *it, L"Letters don't match");
		}

		TEST_METHOD(AddIteratorToInteger)
		{
			MyString myString("Hello world!");
			auto it{ myString.begin() };

			it = 6 + it;
			Assert::AreEqual('w', *it, L"Letters don't match");
		}

		TEST_METHOD(AddAndAssignIntegerToIterator)
		{
			MyString myString("Hello world!");
			auto it{ myString.begin() };

			it += 6;
			Assert::AreEqual('w', *it, L"Letters don't match");
		}

		TEST_METHOD(DifferenceBetweenIterators)
		{
			MyString myString("Hello");
			auto begin{ myString.begin() };
			auto end{ myString.end() };

			Assert::IsTrue(5 == end - begin, L"Difference between iterators is wrong");
		}
	};
}