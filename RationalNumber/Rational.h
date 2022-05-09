#pragma once

class Rational
{
public:
	Rational();
	Rational(int value);
	Rational(int numerator, int denominator);

	int GetNumerator() const;
	int GetDenominator() const;
	double ToDouble() const;

private:
	void Normalize();

	int m_numerator;
	int m_denominator;
};