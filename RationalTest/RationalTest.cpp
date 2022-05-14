#include "pch.h"
#include "CppUnitTest.h"
#include "Rational.h"
#include <sstream>

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

		TEST_METHOD(MultiplicationOfRationalAndRational)
		{
			Rational num1(1, 2);
			Rational num2(2, 3);
			Rational result = num1 * num2;
			Assert::AreEqual(1, result.GetNumerator(), L"Numerators dont't match");
			Assert::AreEqual(3, result.GetDenominator(), L"Denominators dont't match");
		}

		TEST_METHOD(MultiplicationOfRationalAndInteger)
		{
			Rational num(1, 2);
			Rational result = num * -3;
			Assert::AreEqual(-3, result.GetNumerator(), L"Numerators dont't match");
			Assert::AreEqual(2, result.GetDenominator(), L"Denominators dont't match");
		}

		TEST_METHOD(MultiplicationOfIntegerAndRational)
		{
			Rational num(2, 3);
			Rational result = 7 * num;
			Assert::AreEqual(14, result.GetNumerator(), L"Numerators dont't match");
			Assert::AreEqual(3, result.GetDenominator(), L"Denominators dont't match");
		}

		TEST_METHOD(DivisionOfRationalAndRational)
		{
			Rational num1(1, 2);
			Rational num2(2, 3);
			Rational result = num1 / num2;
			Assert::AreEqual(3, result.GetNumerator(), L"Numerators dont't match");
			Assert::AreEqual(4, result.GetDenominator(), L"Denominators dont't match");
		}

		TEST_METHOD(DivisionOfRationalAndInteger)
		{
			Rational num(1, 2);
			Rational result = num / 5;
			Assert::AreEqual(1, result.GetNumerator(), L"Numerators dont't match");
			Assert::AreEqual(10, result.GetDenominator(), L"Denominators dont't match");
		}

		TEST_METHOD(DivisionOfIntegerAndRational)
		{
			Rational num(2, 3);
			Rational result = 7 / num;
			Assert::AreEqual(21, result.GetNumerator(), L"Numerators dont't match");
			Assert::AreEqual(2, result.GetDenominator(), L"Denominators dont't match");
		}

		TEST_METHOD(MultiplicationByRationalWithAssignment)
		{
			Rational num1(1, 2);
			Rational num2(2, 3);
			num1 *= num2;
			Assert::AreEqual(1, num1.GetNumerator(), L"Numerators dont't match");
			Assert::AreEqual(3, num1.GetDenominator(), L"Denominators dont't match");
		}

		TEST_METHOD(MultiplicationByIntegerWithAssignment)
		{
			Rational num(1, 2);
			num *= 3;
			Assert::AreEqual(3, num.GetNumerator(), L"Numerators dont't match");
			Assert::AreEqual(2, num.GetDenominator(), L"Denominators dont't match");
		}

		TEST_METHOD(DivisionByRationalWithAssignment)
		{
			Rational num1(1, 2);
			Rational num2(2, 3);
			num1 /= num2;
			Assert::AreEqual(3, num1.GetNumerator(), L"Numerators dont't match");
			Assert::AreEqual(4, num1.GetDenominator(), L"Denominators dont't match");

			Rational num3(3, 4);
			Rational num4(3, 8);
			num3 /= num4;
			Assert::AreEqual(2, num3.GetNumerator(), L"Numerators dont't match");
			Assert::AreEqual(1, num3.GetDenominator(), L"Denominators dont't match");
		}

		TEST_METHOD(DivisionByIntegerWithAssignment)
		{
			Rational num(1, 2);
			num /= 3;
			Assert::AreEqual(1, num.GetNumerator(), L"Numerators dont't match");
			Assert::AreEqual(6, num.GetDenominator(), L"Denominators dont't match");
		}

		TEST_METHOD(RationalNumbersAreEqual)
		{
			Assert::IsTrue(Rational{ 1, 2 } == Rational{ 1, 2 }, L"Numbers aren't equal");
			Assert::IsFalse(Rational{ 1, 2 } == Rational{ 2, 3 }, L"Numbers aren't equal");
			Assert::IsTrue(Rational{ 4, 1 } == Rational{ 4 }, L"Numbers aren't equal");
			Assert::IsFalse(Rational{ 1, 2 } == Rational{ 7 }, L"Numbers aren't equal");
			Assert::IsTrue(Rational{ 3 } == Rational{ 3, 1 }, L"Numbers aren't equal");
			Assert::IsFalse(Rational{ 3 } == Rational{ 2, 3 }, L"Numbers aren't equal");
		}

		TEST_METHOD(RationalNumbersAreNotEqual)
		{
			Assert::IsFalse(Rational{ 1, 2 } != Rational{ 1, 2 }, L"Numbers aren't equal");
			Assert::IsTrue(Rational{ 1, 2 } != Rational{ 2, 3 }, L"Numbers aren't equal");
			Assert::IsFalse(Rational{ 4, 1 } != Rational{ 4 }, L"Numbers aren't equal");
			Assert::IsTrue(Rational{ 1, 2 } != Rational{ 7 }, L"Numbers aren't equal");
			Assert::IsFalse(Rational{ 3 } != Rational{ 3, 1 }, L"Numbers aren't equal");
			Assert::IsTrue(Rational{ 3 } != Rational{ 2, 3 }, L"Numbers aren't equal");
		}

		TEST_METHOD(RationalNumbersComparison)
		{
			Assert::IsTrue(Rational{ 1, 2 } >= Rational{ 1, 3 }, L"Numbers aren't equal");
			Assert::IsFalse(Rational{ 1, 2 } <= Rational{ 1, 3 }, L"Numbers aren't equal");
			Assert::IsTrue(Rational{ 3, 1 } > Rational{ 2 }, L"Numbers aren't equal");
			Assert::IsTrue(Rational{ 1, 2 } < Rational{ 7 }, L"Numbers aren't equal");
			Assert::IsTrue(Rational{ 3 } <= Rational{ 7, 2 }, L"Numbers aren't equal");
			Assert::IsFalse(Rational{ 3 } >= Rational{ 8, 2 }, L"Numbers aren't equal");
			Assert::IsTrue(Rational{ 4, 7 } >= Rational{ 4, 7 }, L"Numbers aren't equal");
			Assert::IsTrue(Rational{ 4, 7 } <= Rational{ 4, 7 }, L"Numbers aren't equal");
			Assert::IsFalse(Rational{ 4, 7 } < Rational{ 4, 7 }, L"Numbers aren't equal");
			Assert::IsFalse(Rational{ 4, 7 } > Rational{ 4, 7 }, L"Numbers aren't equal");
		}

		TEST_METHOD(PrintRationalNumberToStream)
		{
			Rational num(7, 15);
			std::ostringstream ss;

			ss << num;
			Assert::IsTrue("7/15" == ss.str(), L"Output was incorrect");
		}

		TEST_METHOD(ReadRationalNumberFromStream)
		{
			Rational num;
			std::istringstream ss("7/15");

			ss >> num;
			Assert::AreEqual(7, num.GetNumerator(), L"Numerators dont't match");
			Assert::AreEqual(15, num.GetDenominator(), L"Denominators dont't match");
		}

		TEST_METHOD(RationalNumberToCompoundFraction)
		{
			auto compound1{ Rational(9, 4).ToCompoundFraction() };
			auto compound2{ Rational(-9, 4).ToCompoundFraction() };

			Assert::AreEqual(2, compound1.first, L"Whole numbers dont't match");
			Assert::AreEqual(1, compound1.second.GetNumerator(), L"Numerators dont't match");
			Assert::AreEqual(4, compound1.second.GetDenominator(), L"Denominators dont't match");

			Assert::AreEqual(-2, compound2.first, L"Whole numbers dont't match");
			Assert::AreEqual(1, compound2.second.GetNumerator(), L"Numerators dont't match");
			Assert::AreEqual(4, compound2.second.GetDenominator(), L"Denominators dont't match");
		}
	};
}