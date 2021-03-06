#ifndef DEF_FRACTION
#define DEF_FRACTION

#define VERSION 1

#include <iostream>
#if VERSION == 1
#include <gmpxx.h>
#endif

class Fraction {
public:
	// Constructeurs
	Fraction(long long num, long long den = 1, bool simp = true);
	Fraction(Fraction const& other);
	Fraction();

	// Permet de copier le contenu de other
	void copy(Fraction const& other);

	#if VERSION == 1
	~Fraction(); // Important pour clear les mpq_t
	#endif

	// Retourne l'inverse de la fraction
	Fraction inverse() const;

	Fraction operator-() const;
	Fraction operator+=(Fraction const& other);
	Fraction operator-=(Fraction const& other);
	Fraction operator*=(Fraction const& other);
	Fraction operator/=(Fraction const& other);

	// Retourne la longueur de la représentation en chaîne de caractères de la fraction
	int str_len() const;

	#if VERSION == 0
	long long numerator() const;
	long long denominator() const;
	#endif
	// Retourne la représentation en chaîne de caractères de la fraction
	char* str() const;

private:
	#if VERSION == 0
	long long _numerator, _denominator;
	void simplify(); // Simplifie avec le PGCD du numérateur et du dénominateur
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