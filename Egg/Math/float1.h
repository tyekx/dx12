#pragma once

#include <math.h>


class Float2;
class Float3;
class Float4;

class Float1
{
public:

	union{
		struct {
			float x;
		};

		float v[1];

		Float2swizzle<1, Float2, 0, 0> xx;
		Float3swizzle<1, Float3, 0, 0, 0> xxx;
		Float4swizzle<1, Float4, 0, 0, 0, 0> xxxx;

	};

	operator float() const
	{
		return x;
	}

	Float1():x(0.0f){}

	Float1(float f):x(f){}

	Float1(float x, float y, float z, float w):x(x){y; z; w;}

	Float1(Int1 i):x((float)i.x){}

	Float1& operator+=(const Float1& o)
	{
		x += o.x;
	}

	Float1& operator-=(const Float1& o)
	{
		x -= o.x;
	}

	Float1& operator*=(const Float1& o)
	{
		x *= o.x;
	}

	Float1& operator/=(const Float1& o)
	{
		x /= o.x;
	}

	Float1& operator%=(const Float1& o)
	{
		x = fmodf(x, o.x);
	}

	Bool1 operator==(const Float1& o) const
	{
		return Bool1(x == o.x);
	}

	Bool1 operator!=(const Float1& o) const
	{
		return Bool1(x != o.x);
	}

	Bool1 operator<(const Float1& o) const
	{
		return Bool1(x < o.x);
	}

	Bool1 operator<=(const Float1& o) const
	{
		return Bool1(x <= o.x);
	}

	Bool1 operator>(const Float1& o) const
	{
		return Bool1(x > o.x);
	}

	Bool1 operator>=(const Float1& o) const
	{
		return Bool1(x >= o.x);
	}

	Float1 operator+(const Float1& o) const
	{
		return Float1{ x + o.x };
	}

	Float1 operator-(const Float1& o) const
	{
		return Float1{x - o.x };
	}

	Float1 operator*(const Float1& o) const
	{
		return Float1{x * o.x };
	}

	Float1 operator/(const Float1& o) const
	{
		return Float1{x / o.x };
	}

	Float1 operator%(const Float1& o) const
	{
		return Float1{fmodf(x, o.x) };
	}

	Float1 operator+() const
	{
		return Float1{+x };
	}

	Float1 operator-() const
	{
		return Float1{-x };
	}

	float operator[](unsigned int i) const
	{
		if(i < 0 || i > 0)
			throw std::range_error("Float1 index out of range.");
		return v[i];
	}

	float& operator[](unsigned int i)
	{
		if(i < 0 || i > 0)
			throw std::range_error("Float1 index out of range.");
		return v[i];
	}

	Float1 abs () const
	{
		return Float1{::abs(x) };
	}

	Float1 acos() const
	{
		return Float1{::acos(x) };
	}

	Float1 asin() const
	{
		return Float1{::asin(x) };
	}

	Float1 atan() const
	{
		return Float1{::atan(x) };
	}

	Int1 ceil() const
	{
		return Int1((int)::ceil(x));
	}

	Float1 cos() const
	{
		return Float1{ ::cos(x) };
	}

	Float1 cosh() const
	{
		return Float1{ ::cosh(x) };
	}

	Float1 exp() const
	{
		return Float1{ ::exp(x) };
	}

	Int1 floor() const
	{
		return Int1((int)::floor(x));
	} 

	Float1 tan() const
	{
		return Float1{::tan(x) };
	}

	Float1 sin() const
	{
		return Float1{::sin(x) };
	}

	Float1 sinh() const
	{
		return Float1{::sinh(x) };
	}

	Float1 log() const
	{
		return Float1{::log(x) };
	}

	Float1 log10() const
	{
		return Float1{::log10(x) };
	}

	Float1 exp2() const
	{
		return Float1{ ::pow(2.0f, x) };
	}

	Float1 atan2(const Float1& o) const
	{
		return Float1{::atan2(x, o.x) };
	}
	Float1 fmod(const Float1& o) const
	{
		return Float1{::fmod(x, o.x) };
	}

	float distance(const Float1& o) const
	{
		return (*this - o).length();
	}

	float dot(const Float1& o) const
	{
		return x * o.x;
	}

	Float1 frac() const
	{
		return *this - trunc();
	}

	Bool1 isfinite() const
	{
		return Bool1( ::_finite(x));
	}

	Bool1 isinf() const
	{
		return Bool1( !::_finite(x));
	}

	Bool1 isnan() const
	{
		return Bool1( ::_isnan(x));
	}

	float length() const
	{
		return sqrtf( this->dot(*this));
	}

	float lengthSquared() const
	{
		return this->dot(*this);
	}

	Float1 lerp(const Float1& a, const Float1& b) const
	{
		return a * (Float1{1 } - *this) + b * *this;
	}

	Float1 log2() const
	{
		return Float1{ ::log(x) / ::log(2.0f) };
	}

	Float1 max(const Float1& o) const
	{
		return Float1{ (x>o.x)?x:o.x };
	}

	Float1 min(const Float1& o) const
	{
		return Float1{ (x<o.x)?x:o.x };
	}

	Float1 normalize() const
	{
		return *this / Float1{length() };
	}

	Float1 pow (const Float1& o) const	
	{	
		return Float1{::pow(x, o.x) };
	}


	Int1 round() const
	{
		return Int1( (int)(x+0.5f));
	}

	Float1 rsqrt() const
	{
		return Float1{ 1.0f / ::sqrtf(x) };
	}

	Float1 saturate() const
	{
		return clamp( Float1{0 }, Float1{1 });
	}

	Float1 sign() const
	{
		return Float1{ (x>0.0f)?1.0f:((x<0.0f)?-1.0f:0.0f) };
	}

	Float1 smoothstep(const Float1& a, const Float1& b) const
	{
		float r = ((*this - a)/(b - a)).saturate(); 
		return r*r*(3 - r*2);
	}

	Float1 sqrt() const
	{
		return Float1{ ::sqrtf(x) };
	}

	Float1 step(const Float1& o) const
	{
		return Float1{ (x>=o.x)?1.0f:0.0f };
	}

	Int1 trunc() const
	{
		return Int1( (int)(x));
	}

	Float1 clamp(const Float1& low, const Float1& high) const
	{
		return Float1{ (x<low.x)?low.x:((x>high.x)?high.x:x) };
	}

	static Float1 random(float lower=0.0f, float upper=1.0f)
	{
		float range = upper - lower;
		return Float1{
			rand() * range / RAND_MAX + lower };
	}

	static const Float1 zero;
	static const Float1 xUnit;
	static const Float1 one;

};
