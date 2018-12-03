#include <sstream>
#include <string>
#include "fraction.h"

#if VERSION == 0

long long gcd(long long a, long long b) {
	if(b == 0) return a;
	return gcd(b, a % b);
}

Fraction::Fraction(long long num, long long den, bool simp) {
	if(den == 0) throw "Denominator equals 0";
	if(num == 0) den = 1;
	else if(den < 0) {
		den = -den;
		num = -num;
	}
	_numerator = num;
	_denominator = den;
	if(simp) simplify();
}

Fraction::Fraction(Fraction const& other) {
	copy(other);
}

void Fraction::copy(Fraction const& other) {
	_numerator = other.numerator();
	_denominator = other.denominator();
}

Fraction::Fraction() {}

Fraction Fraction::inverse() const {
	return _numerator > 0 ? Fraction(_denominator, _numerator, false) : Fraction(-_denominator, -_numerator, false);
}
Fraction Fraction::operator-() const { return Fraction(-_numerator, _denominator, false); }

Fraction Fraction::operator+=(Fraction const& other) {
	long long d = gcd(_denominator, other._denominator);
	long long dd = other._denominator / d;
	_numerator = _numerator * dd + other._numerator * (_denominator / d);
	if(_numerator == 0) _denominator = 1;
	else _denominator *= dd;
	simplify();
	return *this;
}
Fraction Fraction::operator-=(Fraction const& other) { return (*this += -other); }

Fraction Fraction::operator*=(Fraction const& other) {
	long long d1 = gcd(std::abs(_numerator), other._denominator);
	long long d2 = gcd(_denominator, std::abs(other._numerator));
	_numerator = (_numerator / d1) * (other._numerator / d2);
	_denominator = (_denominator / d2) * (other._denominator / d1);
	return *this;
}
Fraction Fraction::operator/=(Fraction const& other) { return (*this *= other.inverse()); }

std::string Fraction::str() const {
    std::string res = std::to_string(_numerator);
	if(_denominator != 1)
		res += "/" + std::to_string(_denominator);
	return res;
}

std::istream& operator>>(std::istream& stream, Fraction &fraction) {
	std::string s;
	stream >> s;
	std::istringstream iss(s);
	long long a, b = 1;
	iss >> a;
	char c;
	if(iss >> c) iss >> b;
	fraction = Fraction(a, b);
	std::cout << a << " " << b << " " << fraction << std::endl;
	return stream;
}

long long Fraction::numerator() const { return _numerator; }
long long Fraction::denominator() const { return _denominator; }

void Fraction::simplify() {
	long long d = gcd(std::abs(_numerator), _denominator);
	_numerator /= d;
	_denominator /= d;
}

bool operator==(Fraction const& a, Fraction const& b) {
	return a.numerator() == b.numerator() && a.denominator() == b.denominator();
}

bool operator<=(Fraction const& a, Fraction const& b) { return (a - b).numerator() <= 0; }
bool operator<(Fraction const& a, Fraction const& b) { return (a - b).numerator() < 0; }
bool operator>=(Fraction const& a, Fraction const& b) { return (a - b).numerator() >= 0; }
bool operator>(Fraction const& a, Fraction const& b) { return (a - b).numerator() > 0; }

#else

Fraction::Fraction(long long num, long long den, bool simp) {
	if(den == 0) throw "Denominator equals 0";
	if(den < 0) {
		den = -den;
		num = -num;
	}
	mpq_init(_frac);
	mpq_set_si(_frac, num, den);
	if(simp) mpq_canonicalize(_frac);
}

Fraction::Fraction(Fraction const& other) {
	mpq_init(_frac);
	copy(other);
}

void Fraction::copy(Fraction const& other) {
	mpq_set(_frac, other._frac);
}

Fraction::Fraction() { mpq_init(_frac); }

Fraction::~Fraction() {
	mpq_clear(_frac);
}

Fraction Fraction::inverse() const {
	Fraction res;
	mpq_inv(res._frac, _frac);
	return res;
}

Fraction Fraction::operator-() const {
	Fraction res;
	mpq_neg(res._frac, _frac);
	return res;
}

Fraction Fraction::operator+=(Fraction const& other) {
	mpq_add(_frac, _frac, other._frac);
	return *this;
}

Fraction Fraction::operator-=(Fraction const& other) {
	mpq_sub(_frac, _frac, other._frac);
	return *this;
}

Fraction Fraction::operator*=(Fraction const& other) {
	mpq_mul(_frac, _frac, other._frac);
	return *this;
}

Fraction Fraction::operator/=(Fraction const& other)  {
	mpq_div(_frac, _frac, other._frac);
	return *this;
}

std::string Fraction::str() const { return mpq_get_str(NULL, 10, _frac); }

std::istream& operator>>(std::istream& stream, Fraction &fraction) {
	std::string s;
	stream >> s;
	mpq_set_str(fraction._frac, s.data(), 10);
	return stream;
}

bool operator==(Fraction const& a, Fraction const& b) { return mpq_equal(a._frac, b._frac); }

bool operator<=(Fraction const& a, Fraction const& b) { return mpq_cmp(a._frac, b._frac) <= 0; }
bool operator<(Fraction const& a, Fraction const& b) { return mpq_cmp(a._frac, b._frac) < 0; }
bool operator>=(Fraction const& a, Fraction const& b) { return mpq_cmp(a._frac, b._frac) >= 0; }
bool operator>(Fraction const& a, Fraction const& b) { return mpq_cmp(a._frac, b._frac) > 0; }

#endif

int Fraction::str_len() const { return str().size(); }

std::ostream& operator<<(std::ostream& stream, Fraction const& fraction) {
    return stream << fraction.str();
}

Fraction operator+(Fraction const& a, Fraction const&b) { Fraction res = a; return res += b; }
Fraction operator-(Fraction const& a, Fraction const&b) { Fraction res = a; return res -= b; }
Fraction operator*(Fraction const& a, Fraction const&b) { Fraction res = a; return res *= b; }
Fraction operator/(Fraction const& a, Fraction const&b) { Fraction res = a; return res /= b; }

bool operator!=(Fraction const& a, Fraction const& b) { return !(a == b); }