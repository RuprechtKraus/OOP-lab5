#include "Rational.h"
#include <stdexcept>
#include <numeric>

Rational::Rational()
	: m_numerator(0)
	, m_denominator(1)
{
}

Rational::Rational(int value)
	: m_numerator(value)
	, m_denominator(1)
{
}

Rational::Rational(int numerator, int denominator)
{
	if (denominator == 0)
	{
		throw std::invalid_argument("Zero denominator");
	}

	if (denominator < 0)
	{
		numerator = -numerator;
		denominator = -denominator;
	}

	m_numerator = numerator;
	m_denominator = denominator;

	Normalize();
}

void Rational::Normalize()
{
	int gcd = std::gcd(m_numerator, m_denominator);
	m_numerator /= gcd;
	m_denominator /= gcd;
}

int Rational::GetNumerator() const
{
	return m_numerator;
}

int Rational::GetDenominator() const
{
	return m_denominator;
}

double Rational::ToDouble() const
{
	return {};
}