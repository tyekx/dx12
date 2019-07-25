#pragma once

#include <math.h>

class Float2;
class Float3;
class Float4;

class Float3
{
public:
	union
	{
		struct 
		{
			float x;
			float y;
			float z;
		};

		float v[3];

		Float2swizzle<3, Float2, 0, 0> xx;
		Float2swizzle<3, Float2, 0, 1> xy;
		Float2swizzle<3, Float2, 0, 2> xz;
		Float2swizzle<3, Float2, 1, 0> yx;
		Float2swizzle<3, Float2, 1, 1> yy;
		Float2swizzle<3, Float2, 1, 2> yz;
		Float2swizzle<3, Float2, 2, 0> zx;
		Float2swizzle<3, Float2, 2, 1> zy;
		Float2swizzle<3, Float2, 2, 2> zz;

		Float3swizzle<3, Float3, 0, 0, 0> xxx;
		Float3swizzle<3, Float3, 0, 0, 1> xxy;
		Float3swizzle<3, Float3, 0, 0, 2> xxz;
		Float3swizzle<3, Float3, 0, 1, 0> xyx;
		Float3swizzle<3, Float3, 0, 1, 1> xyy;
		Float3swizzle<3, Float3, 0, 1, 2> xyz;
		Float3swizzle<3, Float3, 0, 2, 0> xzx;
		Float3swizzle<3, Float3, 0, 2, 1> xzy;
		Float3swizzle<3, Float3, 0, 2, 2> xzz;
		Float3swizzle<3, Float3, 1, 0, 0> yxx;
		Float3swizzle<3, Float3, 1, 0, 1> yxy;
		Float3swizzle<3, Float3, 1, 0, 2> yxz;
		Float3swizzle<3, Float3, 1, 1, 0> yyx;
		Float3swizzle<3, Float3, 1, 1, 1> yyy;
		Float3swizzle<3, Float3, 1, 1, 2> yyz;
		Float3swizzle<3, Float3, 1, 2, 0> yzx;
		Float3swizzle<3, Float3, 1, 2, 1> yzy;
		Float3swizzle<3, Float3, 1, 2, 2> yzz;
		Float3swizzle<3, Float3, 2, 0, 0> zxx;
		Float3swizzle<3, Float3, 2, 0, 1> zxy;
		Float3swizzle<3, Float3, 2, 0, 2> zxz;
		Float3swizzle<3, Float3, 2, 1, 0> zyx;
		Float3swizzle<3, Float3, 2, 1, 1> zyy;
		Float3swizzle<3, Float3, 2, 1, 2> zyz;
		Float3swizzle<3, Float3, 2, 2, 0> zzx;
		Float3swizzle<3, Float3, 2, 2, 1> zzy;
		Float3swizzle<3, Float3, 2, 2, 2> zzz;

		Float4swizzle<3, Float4, 0, 0, 0, 0> xxxx;
		Float4swizzle<3, Float4, 0, 0, 0, 1> xxxy;
		Float4swizzle<3, Float4, 0, 0, 0, 2> xxxz;
		Float4swizzle<3, Float4, 0, 0, 1, 0> xxyx;
		Float4swizzle<3, Float4, 0, 0, 1, 1> xxyy;
		Float4swizzle<3, Float4, 0, 0, 1, 2> xxyz;
		Float4swizzle<3, Float4, 0, 0, 2, 0> xxzx;
		Float4swizzle<3, Float4, 0, 0, 2, 1> xxzy;
		Float4swizzle<3, Float4, 0, 0, 2, 2> xxzz;
		Float4swizzle<3, Float4, 0, 1, 0, 0> xyxx;
		Float4swizzle<3, Float4, 0, 1, 0, 1> xyxy;
		Float4swizzle<3, Float4, 0, 1, 0, 2> xyxz;
		Float4swizzle<3, Float4, 0, 1, 1, 0> xyyx;
		Float4swizzle<3, Float4, 0, 1, 1, 1> xyyy;
		Float4swizzle<3, Float4, 0, 1, 1, 2> xyyz;
		Float4swizzle<3, Float4, 0, 1, 2, 0> xyzx;
		Float4swizzle<3, Float4, 0, 1, 2, 1> xyzy;
		Float4swizzle<3, Float4, 0, 1, 2, 2> xyzz;
		Float4swizzle<3, Float4, 0, 2, 0, 0> xzxx;
		Float4swizzle<3, Float4, 0, 2, 0, 1> xzxy;
		Float4swizzle<3, Float4, 0, 2, 0, 2> xzxz;
		Float4swizzle<3, Float4, 0, 2, 1, 0> xzyx;
		Float4swizzle<3, Float4, 0, 2, 1, 1> xzyy;
		Float4swizzle<3, Float4, 0, 2, 1, 2> xzyz;
		Float4swizzle<3, Float4, 0, 2, 2, 0> xzzx;
		Float4swizzle<3, Float4, 0, 2, 2, 1> xzzy;
		Float4swizzle<3, Float4, 0, 2, 2, 2> xzzz;

		Float4swizzle<3, Float4, 1, 0, 0, 0> yxxx;
		Float4swizzle<3, Float4, 1, 0, 0, 1> yxxy;
		Float4swizzle<3, Float4, 1, 0, 0, 2> yxxz;
		Float4swizzle<3, Float4, 1, 0, 1, 0> yxyx;
		Float4swizzle<3, Float4, 1, 0, 1, 1> yxyy;
		Float4swizzle<3, Float4, 1, 0, 1, 2> yxyz;
		Float4swizzle<3, Float4, 1, 0, 2, 0> yxzx;
		Float4swizzle<3, Float4, 1, 0, 2, 1> yxzy;
		Float4swizzle<3, Float4, 1, 0, 2, 2> yxzz;
		Float4swizzle<3, Float4, 1, 1, 0, 0> yyxx;
		Float4swizzle<3, Float4, 1, 1, 0, 1> yyxy;
		Float4swizzle<3, Float4, 1, 1, 0, 2> yyxz;
		Float4swizzle<3, Float4, 1, 1, 1, 0> yyyx;
		Float4swizzle<3, Float4, 1, 1, 1, 1> yyyy;
		Float4swizzle<3, Float4, 1, 1, 1, 2> yyyz;
		Float4swizzle<3, Float4, 1, 1, 2, 0> yyzx;
		Float4swizzle<3, Float4, 1, 1, 2, 1> yyzy;
		Float4swizzle<3, Float4, 1, 1, 2, 2> yyzz;
		Float4swizzle<3, Float4, 1, 2, 0, 0> yzxx;
		Float4swizzle<3, Float4, 1, 2, 0, 1> yzxy;
		Float4swizzle<3, Float4, 1, 2, 0, 2> yzxz;
		Float4swizzle<3, Float4, 1, 2, 1, 0> yzyx;
		Float4swizzle<3, Float4, 1, 2, 1, 1> yzyy;
		Float4swizzle<3, Float4, 1, 2, 1, 2> yzyz;
		Float4swizzle<3, Float4, 1, 2, 2, 0> yzzx;
		Float4swizzle<3, Float4, 1, 2, 2, 1> yzzy;
		Float4swizzle<3, Float4, 1, 2, 2, 2> yzzz;

		Float4swizzle<3, Float4, 2, 0, 0, 0> zxxx;
		Float4swizzle<3, Float4, 2, 0, 0, 1> zxxy;
		Float4swizzle<3, Float4, 2, 0, 0, 2> zxxz;
		Float4swizzle<3, Float4, 2, 0, 1, 0> zxyx;
		Float4swizzle<3, Float4, 2, 0, 1, 1> zxyy;
		Float4swizzle<3, Float4, 2, 0, 1, 2> zxyz;
		Float4swizzle<3, Float4, 2, 0, 2, 0> zxzx;
		Float4swizzle<3, Float4, 2, 0, 2, 1> zxzy;
		Float4swizzle<3, Float4, 2, 0, 2, 2> zxzz;
		Float4swizzle<3, Float4, 2, 1, 0, 0> zyxx;
		Float4swizzle<3, Float4, 2, 1, 0, 1> zyxy;
		Float4swizzle<3, Float4, 2, 1, 0, 2> zyxz;
		Float4swizzle<3, Float4, 2, 1, 1, 0> zyyx;
		Float4swizzle<3, Float4, 2, 1, 1, 1> zyyy;
		Float4swizzle<3, Float4, 2, 1, 1, 2> zyyz;
		Float4swizzle<3, Float4, 2, 1, 2, 0> zyzx;
		Float4swizzle<3, Float4, 2, 1, 2, 1> zyzy;
		Float4swizzle<3, Float4, 2, 1, 2, 2> zyzz;
		Float4swizzle<3, Float4, 2, 2, 0, 0> zzxx;
		Float4swizzle<3, Float4, 2, 2, 0, 1> zzxy;
		Float4swizzle<3, Float4, 2, 2, 0, 2> zzxz;
		Float4swizzle<3, Float4, 2, 2, 1, 0> zzyx;
		Float4swizzle<3, Float4, 2, 2, 1, 1> zzyy;
		Float4swizzle<3, Float4, 2, 2, 1, 2> zzyz;
		Float4swizzle<3, Float4, 2, 2, 2, 0> zzzx;
		Float4swizzle<3, Float4, 2, 2, 2, 1> zzzy;
		Float4swizzle<3, Float4, 2, 2, 2, 2> zzzz;

		Float4swizzle<3, Float4, 0, 1, 2, -1> xyz0;
		Float4swizzle<3, Float4, 0, 1, 2, -2> xyz1;
	};

	Float3():x(0.0f),y(0.0f),z(0.0f){}

	Float3(float f):x(f),y(f),z(f){}

	Float3(float x, float y, float z):x(x),y(y),z(z){}

	Float3(float x, float y, float z, float w):x(x),y(y),z(z){w;}

	Float3(float x, Float2 yz):x(x),y(yz.x),z(yz.y){}

	Float3(Float2 xy, float z):x(xy.x),y(xy.y),z(z){}

	Float3(Int3 i):x((float)i.x),y((float)i.y),z((float)i.z){}

	Float3& operator+=(const Float3& o)
	{
		x += o.x;
		y += o.y;
		z += o.z;
		return *this;
	}

	Float3& operator-=(const Float3& o)
	{
		x -= o.x;
		y -= o.y;
		z -= o.z;
		return *this;
	}

	Float3& operator*=(const Float3& o)
	{
		x *= o.x;
		y *= o.y;
		z *= o.z;
		return *this;
	}

	Float3& operator/=(const Float3& o)
	{
		x /= o.x;
		y /= o.y;
		z /= o.z;
		return *this;
	}

	Float3& operator%=(const Float3& o)
	{
		x = fmodf(x, o.x);
		y = fmodf(y, o.y);
		z = fmodf(z, o.z);
		return *this;
	}

	Bool3 operator==(const Float3& o) const
	{
		return Bool3(x == o.x, y == o.y, z == o.z);
	}

	Bool3 operator!=(const Float3& o) const
	{
		return Bool3(x != o.x, y != o.y, z != o.z);
	}

	Bool3 operator<(const Float3& o) const
	{
		return Bool3(x < o.x, y < o.y, z < o.z);
	}

	Bool3 operator<=(const Float3& o) const
	{
		return Bool3(x <= o.x, y <= o.y, z <= o.z);
	}

	Bool3 operator>(const Float3& o) const
	{
		return Bool3(x > o.x, y > o.y, z > o.z);
	}

	Bool3 operator>=(const Float3& o) const
	{
		return Bool3(x >= o.x, y >= o.y, z >= o.z);
	}

	Float3 operator+(const Float3& o) const
	{
		return Float3(x + o.x, y + o.y, z + o.z);
	}

	Float3 operator-(const Float3& o) const
	{
		return Float3(x - o.x, y - o.y, z - o.z);
	}

	Float3 operator*(const Float3& o) const
	{
		return Float3(x * o.x, y * o.y, z * o.z);
	}

	Float3 operator/(const Float3& o) const
	{
		return Float3(x / o.x, y / o.y, z / o.z);
	}

	Float3 operator%(const Float3& o) const
	{
		return Float3(fmodf(x, o.x), fmodf(y, o.y), fmodf(z, o.z));
	}


	Float3 operator+() const
	{
		return Float3(+x, +y, +z);
	}

	Float3 operator-() const
	{
		return Float3(-x, -y, -z);
	}

	Float3 operator!() const
	{
		return Float3(+x, -y, -z);
	}

	float operator[](unsigned int i) const
	{
		if(i < 0 || i > 2)
			throw std::range_error("Float3 index out of range.");
		return v[i];
	}

	float& operator[](unsigned int i)
	{
		if(i < 0 || i > 2)
			throw std::range_error("Float3 index out of range.");
		return v[i];
	}

	Float3 abs () const
	{
		return Float3(::abs(x), ::abs(y), ::abs(z));
	}

	Float3 acos() const
	{
		return Float3(::acos(x), ::acos(y), ::acos(z));
	}

	Float3 asin() const
	{
		return Float3(::asin(x), ::asin(y), ::asin(z));
	}

	Float3 atan() const
	{
		return Float3(::atan(x), ::atan(y), ::atan(z));
	}

	Float3 cos() const
	{
		return Float3(::cos(x), ::cos(y), ::cos(z));
	}

	Float3 cosh() const
	{
		return Float3(::cosh(x), ::cosh(y), ::cosh(z));
	}

	Float3 exp() const
	{
		return Float3(::exp(x), ::exp(y), ::exp(z));
	}

	Float3 log() const
	{
		return Float3(::log(x), ::log(y), ::log(z));
	}

	Float3 log10() const
	{
		return Float3(::log10(x), ::log10(y), ::log10(z));
	}

	Float3 sin() const
	{
		return Float3(::sin(x), ::sin(y), ::sin(z));
	}

	Float3 sinh() const
	{
		return Float3(::sinh(x), ::sinh(y), ::sinh(z));
	}

	Float3 tan() const
	{
		return Float3(::tan(x), ::tan(y), ::tan(z));
	}

	Int3 ceil() const
	{
		return Int3((int)::ceil(x), (int)::ceil(y), (int)::ceil(z));
	}

	Int3 floor() const
	{
		return Int3((int)::floor(x), (int)::floor(y), (int)::floor(z));
	}

	Float3 exp2() const
	{
		return Float3( ::pow(2.0f, x), ::pow(2.0f, y), ::pow(2.0f, z));
	}

	Float3 atan2 (const Float3& o) const
	{
		return Float3 (::atan2(x, o.x), ::atan2(y, o.y), ::atan2(z, o.z));
	}

	Float3 fmod(const Float3& o) const
	{
		return Float3(::fmod(x, o.x), ::fmod(y, o.y), ::fmod(z, o.z));
	}

	Float3 pow(const Float3& o) const
	{
		return Float3(::pow(x, o.x), ::pow(y, o.y), ::pow(z, o.z));
	}

	float distance(const Float3& o) const
	{
		return (*this - o).length();
	}

	float dot(const Float3& o) const
	{
		return x * o.x + y * o.y + z * o.z;
	}

	Float3 frac() const
	{
		return *this - trunc();
	}

	Bool3 isfinite() const
	{
		return Bool3( ::_finite(x), ::_finite(y), ::_finite(z));
	}

	Bool3 isinf() const
	{
		return Bool3( !::_finite(x), !::_finite(y), !::_finite(z));
	}

	Bool3 isnan() const
	{
		return Bool3( ::_isnan(x), ::_isnan(y), ::_isnan(z));
	}

	float length() const
	{
		return sqrtf( this->dot(*this));
	}

	float lengthSquared() const
	{
		return this->dot(*this);
	}

	Float3 lerp(const Float3& a, const Float3& b) const
	{
		return a * (Float3(1, 1, 1) - *this) + b * *this;
	}

	Float3 log2() const
	{
		return Float3( ::log(x) / ::log(2.0f), ::log(y) / ::log(2.0f), ::log(z) / ::log(2.0f));
	}

	Float3 max(const Float3& o) const
	{
		return Float3( (x>o.x)?x:o.x, (y>o.y)?y:o.y, (z>o.z)?z:o.z);
	}

	Float3 min(const Float3& o) const
	{
		return Float3( (x<o.x)?x:o.x, (y<o.y)?y:o.y, (z<o.z)?z:o.z);
	}

	Float3 normalize() const
	{
		return *this / length();
	}


	Int3 round() const
	{
		return Int3( (int)(x+0.5f), (int)(y+0.5f), (int)(z+0.5f));
	}

	Float3 rsqrt() const
	{
		return Float3( 1.0f / ::sqrtf(x), 1.0f / ::sqrtf(y), 1.0f / ::sqrtf(z));
	}

	Float3 saturate() const
	{
		return clamp( Float3(0, 0, 0), Float3(1, 1, 1));
	}

	Float3 sign() const
	{
		return Float3( (x>0.0f)?1.0f:((x<0.0f)?-1.0f:0.0f), (y>0.0f)?1.0f:((y<0.0f)?-1.0f:0.0f), (z>0.0f)?1.0f:((z<0.0f)?-1.0f:0.0f));
	}

	Float3 smoothstep(const Float3& a, const Float3& b) const
	{
		Float3 r = ((*this - a)/(b - a)).saturate(); 
		return r*r*(Float3(3.0f,3.0f,3.0f) - r*2.0f);
	}

	Float3 sqrt() const
	{
		return Float3( ::sqrtf(x), ::sqrtf(y), ::sqrtf(z));
	}

	Float3 step(const Float3& o) const
	{
		return Float3( (x>=o.x)?1.0f:0.0f, (y>=o.y)?1.0f:0.0f, (z>=o.z)?1.0f:0.0f);
	}

	Int3 trunc() const
	{
		return Int3( (int)(x), (int)(y), (int)(z));
	}

	Float3 clamp(const Float3& low, const Float3& high) const
	{
		return Float3( (x<low.x)?low.x:((x>high.x)?high.x:x), (y<low.y)?low.y:((y>high.y)?high.y:y), (z<low.z)?low.z:((z>high.z)?high.z:z));
	}

	Float3 cross(const Float3& o) const
	{
		return Float3(y * o.z - z * o.y, z * o.x - x * o.z, x * o.y - y * o.x);
	}

	static Float3 random(float lower=0.0f, float upper=1.0f)
	{
		float range = upper - lower;
		return Float3(
			rand() * range / RAND_MAX + lower,
			rand() * range / RAND_MAX + lower,
			rand() * range / RAND_MAX + lower);
	}


	static const Float3 zero;
	static const Float3 xUnit;
	static const Float3 yUnit;
	static const Float3 zUnit;
	static const Float3 one;

	static const Float3 black				;
	static const Float3 navy				;
	static const Float3 blue				;
	static const Float3 darkGreen			;
	static const Float3 teal				;
	static const Float3 slateBlue			;
	static const Float3 green				;
	static const Float3 cyan				;
	static const Float3 maroon				;
	static const Float3 purple				;
	static const Float3 azure				;
	static const Float3 olive				;
	static const Float3 gray				;
	static const Float3 cornflower			;
	static const Float3 aquamarine			;
	static const Float3 red					;
	static const Float3 deepPink			;
	static const Float3 magenta				;
	static const Float3 orange				;
	static const Float3 coral				;
	static const Float3 mallow				;
	static const Float3 yellow				;
	static const Float3 gold				;
	static const Float3 white				;
	static const Float3 silver				;
};
