#ifndef DEF_FRACTION
#define DEF_FRACTION

#define VERSION 1

#include <iostream>
#if VERSION == 1
#include <gmpxx.h>
#endif

class Fraction {
public:
	// Constructors
	Fraction(long long num, long long den = 1, bool simp = true);
	Fraction(Fraction const& other);
	Fraction();

	Fraction inverse() const;

	Fraction operator-() const;
	Fraction operator+=(Fraction const& other);
	Fraction operator-=(Fraction const& other);
	Fraction operator*=(Fraction const& other);
	Fraction operator/=(Fraction const& other);

	int str_len() const;

	#if VERSION == 0
	long long numerator() const;
	long long denominator() const;
	#endif
	std::string str() const;

private:
	#if VERSION == 0
	long long _numerator, _denominator;
	void simplify();
	#else
	mpq_t _frac;
	friend std::istream& operator>>(std::istream &stream, Fraction &fraction);
	friend bool operator==(Fraction const& a, Fraction const& b);
	friend bool operator<=(Fraction const& a, Fraction const& b);
	friend bool operator<(Fraction const& a, Fraction const& b);
	friend bool operator>=(Fraction const& a, Fraction const& b);
	friend bool operator>(Fraction const& a, Fraction const& b);
	#endif
};

std::ostream& operator<<(std::ostream &stream, Fraction const& fraction);
std::istream& operator>>(std::istream &stream, Fraction &fraction);

Fraction operator+(Fraction const& a, Fraction const&b);
Fraction operator-(Fraction const& a, Fraction const&b);
Fraction operator*(Fraction const& a, Fraction const&b);
Fraction operator/(Fraction const& a, Fraction const&b);

bool operator==(Fraction const& a, Fraction const& b);
bool operator!=(Fraction const& a, Fraction const& b);

bool operator<=(Fraction const& a, Fraction const& b);
bool operator<(Fraction const& a, Fraction const& b);
bool operator>=(Fraction const& a, Fraction const& b);
bool operator>(Fraction const& a, Fraction const& b);

#endif