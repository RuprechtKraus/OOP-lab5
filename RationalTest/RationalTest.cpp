#include "pch.h"
#include "CppUnitTest.h"
#include "Rational.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

double RoundNumber(double value, int decimalPlaces)
{
	const double multiplier = std::pow(10.0, decimalPlaces);
	return std::round(value * multiplier) / multiplier;
}

namespace RationalTest
{
	TEST_CLASS(RationalTest)
	{
	public:
		
		TEST_METHOD(DefaultConstructor)
		{
			Rational num;
			Assert::AreEqual(0, num.GetNumerator(), L"Numerators don't match");
			Assert::AreEqual(1, num.GetDenominator(), L"Denominators dont't match");
		}

		TEST_METHOD(OneParameterConstructor)
		{
			Rational num(10);
			Assert::AreEqual(10, num.GetNumerator(), L"Numerators don't match");
			Assert::AreEqual(1, num.GetDenominator(), L"Denominators dont't match");
		}

		TEST_METHOD(TwoParametersConstructor)
		{
			Rational num(10, 2);
			Assert::AreEqual(5, num.GetNumerator(), L"Numerators don't match");
			Assert::AreEqual(1, num.GetDenominator(), L"Denominators dont't match");
		}

		TEST_METHOD(CannotCreateNumberWithZeroDenominator)
		{
			auto numberCreation = []() { Rational num(10, 0); };
			Assert::ExpectException<std::invalid_argument>(numberCreation, L"Constructor didn't throw exception");
		}

		TEST_METHOD(ConversionToDouble)
		{
			Rational num(26, 8);
			Assert::AreEqual(3.25, num.ToDouble(), L"Numerators don't match");
		}

		TEST_METHOD(UnaryPlusReturnsSameObject)
		{
			Rational num(3, 5);
			num = +num;
			Assert::AreEqual(3, num.GetNumerator(), L"Numerators don't match");
			Assert::AreEqual(5, num.GetDenominator(), L"Denominators dont't match");
		}

		TEST_METHOD(UnaryMinusReturnsNumberWithOppositeSign)
		{
			Rational num(3, 5);
			num = -num;
			Assert::AreEqual(-3, num.GetNumerator(), L"Numerators don't match");
			Assert::AreEqual(5, num.GetDenominator(), L"Denominators dont't match");
		}

		TEST_METHOD(AdditionOfRationalAndRational)
		{
			Rational num1(1, 2);
			Rational num2(1, 6);
			Rational result = num1 + num2;
			Assert::AreEqual(2, result.GetNumerator(), L"Numerators dont't match");
			Assert::AreEqual(3, result.GetDenominator(), L"Denominators dont't match");
		}

		TEST_METHOD(AdditionOfRationalAndInterger)
		{
			Rational num(1, 2);
			Rational result = num + 1;
			Assert::AreEqual(3, result.GetNumerator(), L"Numerators dont't match");
			Assert::AreEqual(2, result.GetDenominator(), L"Denominators dont't match");
		}

		TEST_METHOD(AdditionOfIntegerAndRational)
		{
			Rational num(1, 2);
			Rational result = 1 + num;
			Assert::AreEqual(3, result.GetNumerator(), L"Numerators dont't match");
			Assert::AreEqual(2, result.GetDenominator(), L"Denominators dont't match");
		}

		TEST_METHOD(SubtractionOfRationalAndRational)
		{
			Rational num1(1, 2);
			Rational num2(1, 6);
			Rational result = num1 - num2;
			Assert::AreEqual(1, result.GetNumerator(), L"Numerators dont't match");
			Assert::AreEqual(3, result.GetDenominator(), L"Denominators dont't match");
		}

		TEST_METHOD(SubtractionOfRationalAndInteger)
		{
			Rational num(1, 2);
			Rational result = num - 1;
			Assert::AreEqual(-1, result.GetNumerator(), L"Numerators dont't match");
			Assert::AreEqual(2, result.GetDenominator(), L"Denominators dont't match");
		}

		TEST_METHOD(SubtractionOfIntegerAndRational)
		{
			Rational num(1, 2);
			Rational result = 1 - num;
			Assert::AreEqual(1, result.GetNumerator(), L"Numerators dont't match");
			Assert::AreEqual(2, result.GetDenominator(), L"Denominators dont't match");
		}

		TEST_METHOD(AdditionOfRationalWithAssignment)
		{
			Rational num1(1, 2);
			Rational num2(1, 6);
			num1 += num2;
			Assert::AreEqual(2, num1.GetNumerator(), L"Numerators dont't match");
			Assert::AreEqual(3, num1.GetDenominator(), L"Denominators dont't match");
		}

		TEST_METHOD(AdditionOfIntegerWithAssignment)
		{
			Rational num(1, 2);
			num += 1;
			Assert::AreEqual(3, num.GetNumerator(), L"Numerators dont't match");
			Assert::AreEqual(2, num.GetDenominator(), L"Denominators dont't match");
		}

		TEST_METHOD(SubtractionOfRationalWithAssignment)
		{
			Rational num1(1, 2);
			Rational num2(1, 6);
			num1 -= num2;
			Assert::AreEqual(1, num1.GetNumerator(), L"Numerators dont't match");
			Assert::AreEqual(3, num1.GetDenominator(), L"Denominators dont't match");
		}

		TEST_METHOD(SubtractionOfIntegerWithAssignment)
		{
			Rational num(1, 2);
			num -= 1;
			Assert::AreEqual(-1, num.GetNumerator(), L"Numerators dont't match");
			Assert::AreEqual(2, num.GetDenominator(), L"Denominators dont't match");
		}
	};
}
