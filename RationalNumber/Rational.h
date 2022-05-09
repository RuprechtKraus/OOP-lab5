#pragma once
#include <iostream>

class Rational
{
public:
	Rational();
	Rational(int value);
	Rational(int numerator, int denominator);

	const Rational operator+() const;
	const Rational operator-() const;
	Rational& operator+=(const Rational& right);
	Rational& operator-=(const Rational& right);
	Rational& operator*=(const Rational& right);
	Rational& operator/=(const Rational& right);
	friend const Rational operator+(const Rational& left, const Rational& right);
	friend const Rational operator-(const Rational& left, const Rational& right);
	friend const Rational operator*(const Rational& left, const Rational& right);
	friend const Rational operator/(const Rational& left, const Rational& right);
	friend bool operator==(const Rational& left, const Rational& right);
	friend bool operator!=(const Rational& left, const Rational& right);
	friend bool operator<(const Rational& left, const Rational& right);
	friend bool operator<=(const Rational& left, const Rational& right);
	friend bool operator>(const Rational& left, const Rational& right);
	friend bool operator>=(const Rational& left, const Rational& right);
	friend std::ostream& operator<<(std::ostream& os, const Rational& rational);

	int GetNumerator() const;
	int GetDenominator() const;
	double ToDouble() const;

private:
	void Normalize();

	int m_numerator;
	int m_denominator;
};