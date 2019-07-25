#pragma once

#include <math.h>

class Int2;
class Int4;

class Int3
{
public:
	union{
		struct {
			int x;
			int y;
			int z;
		};

		int v[3];

		intswizzle<3, Int2, Bool2, 0, 0> xx;
		intswizzle<3, Int2, Bool2, 0, 1> xy;
		intswizzle<3, Int2, Bool2, 0, 2> xz;
		intswizzle<3, Int2, Bool2, 1, 0> yx;
		intswizzle<3, Int2, Bool2, 1, 1> yy;
		intswizzle<3, Int2, Bool2, 1, 2> yz;
		intswizzle<3, Int2, Bool2, 2, 0> zx;
		intswizzle<3, Int2, Bool2, 2, 1> zy;
		intswizzle<3, Int2, Bool2, 2, 2> zz;

		intswizzle<3, Int3, Bool3, 0, 0, 0> xxx;
		intswizzle<3, Int3, Bool3, 0, 0, 1> xxy;
		intswizzle<3, Int3, Bool3, 0, 0, 2> xxz;
		intswizzle<3, Int3, Bool3, 0, 1, 0> xyx;
		intswizzle<3, Int3, Bool3, 0, 1, 1> xyy;
		intswizzle<3, Int3, Bool3, 0, 1, 2> xyz;
		intswizzle<3, Int3, Bool3, 0, 2, 0> xzx;
		intswizzle<3, Int3, Bool3, 0, 2, 1> xzy;
		intswizzle<3, Int3, Bool3, 0, 2, 2> xzz;
		intswizzle<3, Int3, Bool3, 1, 0, 0> yxx;
		intswizzle<3, Int3, Bool3, 1, 0, 1> yxy;
		intswizzle<3, Int3, Bool3, 1, 0, 2> yxz;
		intswizzle<3, Int3, Bool3, 1, 1, 0> yyx;
		intswizzle<3, Int3, Bool3, 1, 1, 1> yyy;
		intswizzle<3, Int3, Bool3, 1, 1, 2> yyz;
		intswizzle<3, Int3, Bool3, 1, 2, 0> yzx;
		intswizzle<3, Int3, Bool3, 1, 2, 1> yzy;
		intswizzle<3, Int3, Bool3, 1, 2, 2> yzz;
		intswizzle<3, Int3, Bool3, 2, 0, 0> zxx;
		intswizzle<3, Int3, Bool3, 2, 0, 1> zxy;
		intswizzle<3, Int3, Bool3, 2, 0, 2> zxz;
		intswizzle<3, Int3, Bool3, 2, 1, 0> zyx;
		intswizzle<3, Int3, Bool3, 2, 1, 1> zyy;
		intswizzle<3, Int3, Bool3, 2, 1, 2> zyz;
		intswizzle<3, Int3, Bool3, 2, 2, 0> zzx;
		intswizzle<3, Int3, Bool3, 2, 2, 1> zzy;
		intswizzle<3, Int3, Bool3, 2, 2, 2> zzz;

		intswizzle<3, Int4, Bool4, 0, 0, 0, 0> xxxx;
		intswizzle<3, Int4, Bool4, 0, 0, 0, 1> xxxy;
		intswizzle<3, Int4, Bool4, 0, 0, 0, 2> xxxz;
		intswizzle<3, Int4, Bool4, 0, 0, 1, 0> xxyx;
		intswizzle<3, Int4, Bool4, 0, 0, 1, 1> xxyy;
		intswizzle<3, Int4, Bool4, 0, 0, 1, 2> xxyz;
		intswizzle<3, Int4, Bool4, 0, 0, 2, 0> xxzx;
		intswizzle<3, Int4, Bool4, 0, 0, 2, 1> xxzy;
		intswizzle<3, Int4, Bool4, 0, 0, 2, 2> xxzz;
		intswizzle<3, Int4, Bool4, 0, 1, 0, 0> xyxx;
		intswizzle<3, Int4, Bool4, 0, 1, 0, 1> xyxy;
		intswizzle<3, Int4, Bool4, 0, 1, 0, 2> xyxz;
		intswizzle<3, Int4, Bool4, 0, 1, 1, 0> xyyx;
		intswizzle<3, Int4, Bool4, 0, 1, 1, 1> xyyy;
		intswizzle<3, Int4, Bool4, 0, 1, 1, 2> xyyz;
		intswizzle<3, Int4, Bool4, 0, 1, 2, 0> xyzx;
		intswizzle<3, Int4, Bool4, 0, 1, 2, 1> xyzy;
		intswizzle<3, Int4, Bool4, 0, 1, 2, 2> xyzz;
		intswizzle<3, Int4, Bool4, 0, 2, 0, 0> xzxx;
		intswizzle<3, Int4, Bool4, 0, 2, 0, 1> xzxy;
		intswizzle<3, Int4, Bool4, 0, 2, 0, 2> xzxz;
		intswizzle<3, Int4, Bool4, 0, 2, 1, 0> xzyx;
		intswizzle<3, Int4, Bool4, 0, 2, 1, 1> xzyy;
		intswizzle<3, Int4, Bool4, 0, 2, 1, 2> xzyz;
		intswizzle<3, Int4, Bool4, 0, 2, 2, 0> xzzx;
		intswizzle<3, Int4, Bool4, 0, 2, 2, 1> xzzy;
		intswizzle<3, Int4, Bool4, 0, 2, 2, 2> xzzz;

		intswizzle<3, Int4, Bool4, 1, 0, 0, 0> yxxx;
		intswizzle<3, Int4, Bool4, 1, 0, 0, 1> yxxy;
		intswizzle<3, Int4, Bool4, 1, 0, 0, 2> yxxz;
		intswizzle<3, Int4, Bool4, 1, 0, 1, 0> yxyx;
		intswizzle<3, Int4, Bool4, 1, 0, 1, 1> yxyy;
		intswizzle<3, Int4, Bool4, 1, 0, 1, 2> yxyz;
		intswizzle<3, Int4, Bool4, 1, 0, 2, 0> yxzx;
		intswizzle<3, Int4, Bool4, 1, 0, 2, 1> yxzy;
		intswizzle<3, Int4, Bool4, 1, 0, 2, 2> yxzz;
		intswizzle<3, Int4, Bool4, 1, 1, 0, 0> yyxx;
		intswizzle<3, Int4, Bool4, 1, 1, 0, 1> yyxy;
		intswizzle<3, Int4, Bool4, 1, 1, 0, 2> yyxz;
		intswizzle<3, Int4, Bool4, 1, 1, 1, 0> yyyx;
		intswizzle<3, Int4, Bool4, 1, 1, 1, 1> yyyy;
		intswizzle<3, Int4, Bool4, 1, 1, 1, 2> yyyz;
		intswizzle<3, Int4, Bool4, 1, 1, 2, 0> yyzx;
		intswizzle<3, Int4, Bool4, 1, 1, 2, 1> yyzy;
		intswizzle<3, Int4, Bool4, 1, 1, 2, 2> yyzz;
		intswizzle<3, Int4, Bool4, 1, 2, 0, 0> yzxx;
		intswizzle<3, Int4, Bool4, 1, 2, 0, 1> yzxy;
		intswizzle<3, Int4, Bool4, 1, 2, 0, 2> yzxz;
		intswizzle<3, Int4, Bool4, 1, 2, 1, 0> yzyx;
		intswizzle<3, Int4, Bool4, 1, 2, 1, 1> yzyy;
		intswizzle<3, Int4, Bool4, 1, 2, 1, 2> yzyz;
		intswizzle<3, Int4, Bool4, 1, 2, 2, 0> yzzx;
		intswizzle<3, Int4, Bool4, 1, 2, 2, 1> yzzy;
		intswizzle<3, Int4, Bool4, 1, 2, 2, 2> yzzz;

		intswizzle<3, Int4, Bool4, 2, 0, 0, 0> zxxx;
		intswizzle<3, Int4, Bool4, 2, 0, 0, 1> zxxy;
		intswizzle<3, Int4, Bool4, 2, 0, 0, 2> zxxz;
		intswizzle<3, Int4, Bool4, 2, 0, 1, 0> zxyx;
		intswizzle<3, Int4, Bool4, 2, 0, 1, 1> zxyy;
		intswizzle<3, Int4, Bool4, 2, 0, 1, 2> zxyz;
		intswizzle<3, Int4, Bool4, 2, 0, 2, 0> zxzx;
		intswizzle<3, Int4, Bool4, 2, 0, 2, 1> zxzy;
		intswizzle<3, Int4, Bool4, 2, 0, 2, 2> zxzz;
		intswizzle<3, Int4, Bool4, 2, 1, 0, 0> zyxx;
		intswizzle<3, Int4, Bool4, 2, 1, 0, 1> zyxy;
		intswizzle<3, Int4, Bool4, 2, 1, 0, 2> zyxz;
		intswizzle<3, Int4, Bool4, 2, 1, 1, 0> zyyx;
		intswizzle<3, Int4, Bool4, 2, 1, 1, 1> zyyy;
		intswizzle<3, Int4, Bool4, 2, 1, 1, 2> zyyz;
		intswizzle<3, Int4, Bool4, 2, 1, 2, 0> zyzx;
		intswizzle<3, Int4, Bool4, 2, 1, 2, 1> zyzy;
		intswizzle<3, Int4, Bool4, 2, 1, 2, 2> zyzz;
		intswizzle<3, Int4, Bool4, 2, 2, 0, 0> zzxx;
		intswizzle<3, Int4, Bool4, 2, 2, 0, 1> zzxy;
		intswizzle<3, Int4, Bool4, 2, 2, 0, 2> zzxz;
		intswizzle<3, Int4, Bool4, 2, 2, 1, 0> zzyx;
		intswizzle<3, Int4, Bool4, 2, 2, 1, 1> zzyy;
		intswizzle<3, Int4, Bool4, 2, 2, 1, 2> zzyz;
		intswizzle<3, Int4, Bool4, 2, 2, 2, 0> zzzx;
		intswizzle<3, Int4, Bool4, 2, 2, 2, 1> zzzy;
		intswizzle<3, Int4, Bool4, 2, 2, 2, 2> zzzz;

	};

	Int3():x(0),y(0),z(0){}

	Int3(int i):x(i),y(i),z(i){}

	Int3(int x, int y, int z):x(x),y(y),z(z){}

	Int3(int x, int y, int z, int w):x(x),y(y),z(z){w;}

	Int3(int x, Int2 yz):x(x),y(yz.x),z(yz.y){}

	Int3(Int2 xy, int z):x(xy.x),y(xy.y),z(z){}

	Int3(Bool3 b):x(b.x),y(b.y),z(b.z){}

	Int3& operator+=(const Int3& o)
	{
		x += o.x;
		y += o.y;
		z += o.z;
		return *this;
	}

	Int3& operator-=(const Int3& o)
	{
		x -= o.x;
		y -= o.y;
		z -= o.z;
		return *this;
	}

	Int3& operator*=(const Int3& o)
	{
		x *= o.x;
		y *= o.y;
		z *= o.z;
		return *this;
	}

	Int3& operator/=(const Int3& o)
	{
		x /= o.x;
		y /= o.y;
		z /= o.z;
		return *this;
	}

	Int3& operator%=(const Int3& o)
	{
		x %= o.x;
		y %= o.y;
		z %= o.z;
		return *this;
	}

	Int3& operator>>=(const Int3& o)
	{
		x >>= o.x;
		y >>= o.y;
		z >>= o.z;
		return *this;
	}

	Int3& operator<<=(const Int3& o)
	{
		x <<= o.x;
		y <<= o.y;
		z <<= o.z;
		return *this;
	}

	Int3& operator&=(const Int3& o)
	{
		x &= o.x;
		y &= o.y;
		z &= o.z;
		return *this;
	}

	Int3& operator|=(const Int3& o)
	{
		x |= o.x;
		y |= o.y;
		z |= o.z;
		return *this;
	}

	Int3 operator&(const Int3& o) const
	{
		return Int3(x & o.x, y & o.y, z & o.z);
	}

	Int3 operator&&(const Int3& o) const
	{
		return Int3(x && o.x, y && o.y, z && o.z);
	}

	Int3 operator|	(const Int3& o) const
	{
		return Int3(x | o.x, y | o.y, z | o.z);
	}

	Int3 operator||(const Int3& o) const
	{
		return Int3(x || o.x, y || o.y, z || o.z);
	}

	Bool3 operator==(const Int3& o) const
	{
		return Bool3(x == o.x, y == o.y, z == o.z);
	}

	Bool3 operator!=(const Int3& o) const
	{
		return Bool3(x != o.x, y != o.y, z != o.z);
	}

	Bool3 operator<(const Int3& o) const
	{
		return Bool3(x < o.x, y < o.y, z < o.z);
	}

	Bool3 operator>(const Int3& o) const
	{
		return Bool3(x > o.x, y > o.y, z > o.z);
	}

	Bool3 operator<=(const Int3& o) const
	{
		return Bool3(x <= o.x, y <= o.y, z <= o.z);
	}

	Bool3 operator>=(const Int3& o) const
	{
		return Bool3(x >= o.x, y >= o.y, z >= o.z);
	}

	Int3 operator<<(const Int3& o) const
	{
		return Int3(x << o.x, y << o.y, z << o.z);
	}

	Int3 operator>>(const Int3& o) const
	{
		return Int3(x >> o.x, y >> o.y, z >> o.z);
	}

	Int3 operator+(const Int3& o) const
	{
		return Int3(x + o.x, y + o.y, z + o.z);
	}

	Int3 operator-(const Int3& o) const
	{
		return Int3(x - o.x, y - o.y, z - o.z);
	}

	Int3 operator*(const Int3& o) const
	{
		return Int3(x * o.x, y * o.y, z * o.z);
	}

	Int3 operator/(const Int3& o) const
	{
		return Int3(x / o.x, y / o.y, z / o.z);
	}

	Int3 operator%(const Int3& o) const
	{
		return Int3(x % o.x, y % o.y, z % o.z);
	}

	Int3 operator+() const
	{
		return Int3(+x, +y, +z);
	}

	Int3 operator-() const
	{
		return Int3(-x, -y, -z);
	}

	Int3 operator!() const
	{
		return Int3(!x, !y, !z);
	}

	Int3 operator~() const
	{
		return Int3(~x, ~y, ~z);
	}

	Int3 operator++()
	{
		return Int3(++x, ++y, ++z);
	}

	Int3 operator--()
	{
		return Int3(--x, --y, --z);
	}


	Int3 operator++(int)
	{
		return Int3(x++, y++, z++);
	}
	
	Int3 operator--(int)
	{
		return Int3(x++, y++, z++);
	}


	int operator[](unsigned int i) const
	{
		if(i < 0 || i > 2)
			throw std::range_error("Int3 index out of range.");
		return v[i];
	}

	int& operator[](unsigned int i)
	{
		if(i < 0 || i > 2)
			throw std::range_error("Int3 index out of range.");
		return v[i];
	}

	Int3 max(const Int3& o) const
	{
		return Int3( (x>o.x)?x:o.x, (y>o.y)?y:o.y, (z>o.z)?z:o.z );
	}

	Int3 min(const Int3& o) const
	{
		return Int3( (x<o.x)?x:o.x, (y<o.y)?y:o.y, (z<o.z)?z:o.z );
	}

	static Int3 random(int lower=0, int upper=6)
	{
		int range = upper - lower + 1;
		return Int3(
			rand() % range + lower,
			rand() % range + lower,
			rand() % range + lower);
	}

	static const Int3 zero;
	static const Int3 xUnit;
	static const Int3 yUnit;
	static const Int3 zUnit;
	static const Int3 one;
};
