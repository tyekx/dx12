#pragma once

#include <math.h>

class Float2;
class Float3;
class Float4;

class Float2
{
public:

	union{
		struct {
			float x;
			float y;
		};

		float v[2];

		Float2swizzle<2, Float2, 0, 0> xx;
		Float2swizzle<2, Float2, 0, 1> xy;
		Float2swizzle<2, Float2, 1, 0> yx;
		Float2swizzle<2, Float2, 1, 1> yy;

		Float3swizzle<2, Float3, 0, 0, 0> xxx;
		Float3swizzle<2, Float3, 0, 0, 1> xxy;
		Float3swizzle<2, Float3, 0, 1, 0> xyx;
		Float3swizzle<2, Float3, 0, 1, 1> xyy;
		Float3swizzle<2, Float3, 1, 0, 0> yxx;
		Float3swizzle<2, Float3, 1, 0, 1> yxy;
		Float3swizzle<2, Float3, 1, 1, 0> yyx;
		Float3swizzle<2, Float3, 1, 1, 1> yyy;

		Float4swizzle<2, Float4, 0, 0, 0, 0> xxxx;
		Float4swizzle<2, Float4, 0, 0, 0, 1> xxxy;
		Float4swizzle<2, Float4, 0, 0, 1, 0> xxyx;
		Float4swizzle<2, Float4, 0, 0, 1, 1> xxyy;
		Float4swizzle<2, Float4, 0, 1, 0, 0> xyxx;
		Float4swizzle<2, Float4, 0, 1, 0, 1> xyxy;
		Float4swizzle<2, Float4, 0, 1, 1, 0> xyyx;
		Float4swizzle<2, Float4, 0, 1, 1, 1> xyyy;
		Float4swizzle<2, Float4, 1, 0, 0, 0> yxxx;
		Float4swizzle<2, Float4, 1, 0, 0, 1> yxxy;
		Float4swizzle<2, Float4, 1, 0, 1, 0> yxyx;
		Float4swizzle<2, Float4, 1, 0, 1, 1> yxyy;
		Float4swizzle<2, Float4, 1, 1, 0, 0> yyxx;
		Float4swizzle<2, Float4, 1, 1, 0, 1> yyxy;
		Float4swizzle<2, Float4, 1, 1, 1, 0> yyyx;
		Float4swizzle<2, Float4, 1, 1, 1, 1> yyyy;

	};

	Float2():x(0.0f),y(0.0f){}

	Float2(float f):x(f),y(f){}

	Float2(float x, float y):x(x),y(y){}

	Float2(float x, float y, float z, float w):x(x),y(y){z; w;}

	Float2(Int2 i):x((float)i.x),y((float)i.y){}

	Float2& operator+=(const Float2& o)
	{
		x += o.x;
		y += o.y;
	}

	Float2& operator-=(const Float2& o)
	{
		x -= o.x;
		y -= o.y;
	}

	Float2& operator*=(const Float2& o)
	{
		x *= o.x;
		y *= o.y;
	}

	Float2& operator/=(const Float2& o)
	{
		x /= o.x;
		y /= o.y;
	}

	Float2& operator%=(const Float2& o)
	{
		x = fmodf(x, o.x);
		y = fmodf(y, o.y);
	}

	Bool2 operator==(const Float2& o) const
	{
		return Bool2(x == o.x, y == o.y);
	}

	Bool2 operator!=(const Float2& o) const
	{
		return Bool2(x != o.x, y != o.y);
	}

	Bool2 operator<(const Float2& o) const
	{
		return Bool2(x < o.x, y < o.y);
	}

	Bool2 operator<=(const Float2& o) const
	{
		return Bool2(x <= o.x, y <= o.y);
	}

	Bool2 operator>(const Float2& o) const
	{
		return Bool2(x > o.x, y > o.y);
	}

	Bool2 operator>=(const Float2& o) const
	{
		return Bool2(x >= o.x, y >= o.y);
	}

	Float2 operator+(const Float2& o) const
	{
		return Float2(x + o.x, y + o.y);
	}

	Float2 operator-(const Float2& o) const
	{
		return Float2(x - o.x, y - o.y);
	}

	Float2 operator*(const Float2& o) const
	{
		return Float2(x * o.x, y * o.y);
	}

	Float2 operator/(const Float2& o) const
	{
		return Float2(x / o.x, y / o.y);
	}

	Float2 operator%(const Float2& o) const
	{
		return Float2(fmodf(x, o.x), fmodf(y, o.y));
	}


	Float2 operator+() const
	{
		return Float2(+x, +y);
	}

	Float2 operator-() const
	{
		return Float2(-x, -y);
	}

	Float2 operator!() const
	{
		return Float2(+x, -y);
	}

	float operator[](unsigned int i) const
	{
		if(i < 0 || i > 1)
			throw std::range_error("Float2 index out of range.");
		return v[i];
	}

	float& operator[](unsigned int i)
	{
		if(i < 0 || i > 1)
			throw std::range_error("Float2 index out of range.");
		return v[i];
	}

	Float2 abs() const
	{
		return Float2 (::abs(x), ::abs(y));
	}

	Float2 acos() const
	{
		return Float2(::acos(x), ::acos(y));
	}

	Float2 asin() const
	{
		return Float2(::asin(x), ::asin(y));
	}

	Float2 atan() const
	{
		return Float2(::atan(x), ::atan(y));
	}

	Float2 cos() const
	{
		return Float2(::cos(x), ::cos(y));
	}

	Float2 cosh() const
	{
		return Float2(::cosh(x), ::cosh(y));
	}

	Float2 exp() const
	{
		return Float2(::exp(x), ::exp(y));
	}

	Float2 sin() const
	{
		return Float2(::sin(x), ::sin(y));
	}

	Float2 sinh() const
	{
		return Float2(::sinh(x), ::sinh(y));
	}

	Float2 tan() const
	{
		return Float2(::tan(x), ::tan(y));
	}

	Float2 log() const
	{
		return Float2(::log(x), ::log(y));
	}

	Float2 log10() const
	{
		return Float2(::log10(x), ::log10(y));
	}

	Int2 ceil() const
	{
		return Int2((int)::ceil(x), (int)::ceil(y));
	}

	Int2 floor() const
	{
		return Int2((int)::floor(x), (int)::floor(y));
	}

	Float2 exp2() const
	{
		return Float2( ::pow(2.0f, x), ::pow(2.0f, y));
	}

	Float2 atan2(const Float2& o) const
	{
		return Float2(::atan2(x, o.x), ::atan2(y, o.y));
	}

	Float2 fmod (const Float2& o) const
	{
		return Float2(::fmod(x, o.x), ::fmod(y, o.y));
	}

	Float2 pow(const Float2& o) const
	{
		return Float2(::pow(x, o.x), ::pow(y, o.y));
	}

	float distance(const Float2& o) const
	{
		return (*this - o).length();
	}

	float dot(const Float2& o) const
	{
		return x * o.x + y * o.y;
	}

	Float2 frac() const
	{
		return *this - trunc();
	}

	Bool2 isfinite() const
	{
		return Bool2( ::_finite(x), ::_finite(y));
	}

	Bool2 isinf() const
	{
		return Bool2( !::_finite(x), !::_finite(y));
	}

	Bool2 isnan() const
	{
		return Bool2( ::_isnan(x), ::_isnan(y));
	}

	float length() const
	{
		return sqrtf( this->dot(*this));
	}

	float lengthSquared() const
	{
		return this->dot(*this);
	}

	Float2 lerp(const Float2& a, const Float2& b) const
	{
		return a * (Float2(1, 1) - *this) + b * *this;
	}

	Float2 log2() const
	{
		return Float2( ::log(x) / ::log(2.0f), ::log(y) / ::log(2.0f));
	}

	Float2 max(const Float2& o) const
	{
		return Float2( (x>o.x)?x:o.x, (y>o.y)?y:o.y);
	}

	Float2 min(const Float2& o) const
	{
		return Float2( (x<o.x)?x:o.x, (y<o.y)?y:o.y);
	}

	Float2 normalize() const
	{
		return *this / length();
	}

	Int2 round() const
	{
		return Int2( (int)(x+0.5f), (int)(y+0.5f));
	}

	Float2 rsqrt() const
	{
		return Float2( 1.0f / ::sqrtf(x), 1.0f / ::sqrtf(y));
	}

	Float2 saturate() const
	{
		return clamp( Float2(0, 0), Float2(1, 1));
	}

	Float2 sign() const
	{
		return Float2( (x>0.0f)?1.0f:((x<0.0f)?-1.0f:0.0f), (y>0.0f)?1.0f:((y<0.0f)?-1.0f:0.0f));
	}

	Float2 smoothstep(const Float2& a, const Float2& b) const
	{
		Float2 r = ((*this - a)/(b - a)).saturate(); 
		return r*r*(Float2(3,3) - r*2);
	}

	Float2 sqrt() const
	{
		return Float2( ::sqrtf(x), ::sqrtf(y));
	}

	Float2 step(const Float2& o) const
	{
		return Float2( (x>=o.x)?1.0f:0.0f, (y>=o.y)?1.0f:0.0f);
	}


	Int2 trunc() const
	{
		return Int2( (int)(x), (int)(y));
	}

	float arg() const
	{
		return ::atan2(y, x);
	}

	Float2 clamp(const Float2& low, const Float2& high) const
	{
		return Float2( (x<low.x)?low.x:((x>high.x)?high.x:x), (y<low.y)?low.y:((y>high.y)?high.y:y));
	}

	Float2 complexmul(const Float2& o) const
	{
		return Float2( x * o.x - y * o.y, x * o.y + y * o.x );
	}

	Float2 polar() const
	{
		return Float2( length(), arg() );
	}

	Float2 cartesian() const
	{
		return Float2( cosf(y), sinf(y) ) * x;
	}

	static Float2 random(float lower=0.0f, float upper=1.0f)
	{
		float range = upper - lower;
		return Float2(
			rand() * range / RAND_MAX + lower,
			rand() * range / RAND_MAX + lower);
	}

	static const Float2 zero;
	static const Float2 xUnit;
	static const Float2 yUnit;
	static const Float2 one;

};
