#include "Rational.h"
#include <numeric>
#include <stdexcept>

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
	return static_cast<double>(m_numerator) / static_cast<double>(m_denominator);
}

std::pair<int, Rational> Rational::ToCompoundFraction() const
{
	int wholeNumber{ m_numerator / m_denominator };
	Rational rational(std::abs(m_numerator) - m_denominator * std::abs(wholeNumber), m_denominator);

	return { wholeNumber, rational };
}

const Rational Rational::operator+() const
{
	return *this;
}

const Rational Rational::operator-() const
{
	return { -m_numerator, m_denominator };
}

Rational& Rational::operator+=(const Rational& right)
{
	*this = *this + right;
	return *this;
}

Rational& Rational::operator-=(const Rational& right)
{
	*this = *this - right;
	return *this;
}

Rational& Rational::operator*=(const Rational& right)
{
	*this = *this * right;
	return *this;
}

Rational& Rational::operator/=(const Rational& right)
{
	*this = *this / right;
	return *this;
}

const Rational operator+(const Rational& left, const Rational& right)
{
	int lcm = std::lcm(left.m_denominator, right.m_denominator);

	return {
		left.m_numerator * (lcm / left.m_denominator) + right.m_numerator * (lcm / right.m_denominator),
		lcm
	};
}

const Rational operator-(const Rational& left, const Rational& right)
{
	return -right + left;
}

const Rational operator*(const Rational& left, const Rational& right)
{
	return {
		left.m_numerator * right.m_numerator, left.m_denominator * right.m_denominator
	};
}

const Rational operator/(const Rational& left, const Rational& right)
{
	if (right.m_numerator == 0)
	{
		throw std::invalid_argument("Division by zero");
	}

	return left * Rational{ right.m_denominator, right.m_numerator };
}

bool operator==(const Rational& left, const Rational& right)
{
	return left.m_numerator == right.m_numerator && left.m_denominator == right.m_denominator;
}

bool operator!=(const Rational& left, const Rational& right)
{
	return !(left == right);
}

bool operator<(const Rational& left, const Rational& right)
{
	return left.ToDouble() < right.ToDouble();
}

bool operator<=(const Rational& left, const Rational& right)
{
	return left < right || left == right;
}

bool operator>(const Rational& left, const Rational& right)
{
	return !(left <= right);
}

bool operator>=(const Rational& left, const Rational& right)
{
	return left > right || left == right;
}

std::ostream& operator<<(std::ostream& os, const Rational& rational)
{
	os << rational.m_numerator << '/' << rational.m_denominator;
	return os;
}

std::istream& operator>>(std::istream& is, Rational& rational)
{
	char divisionSign{};
	int numerator{};
	int denominator{};

	if (!(is >> numerator) || !(is >> divisionSign) || divisionSign != '/' || !(is >> denominator))
	{
		return is;
	}

	rational.m_numerator = numerator;
	rational.m_denominator = denominator;
	rational.Normalize();

	return is;
}