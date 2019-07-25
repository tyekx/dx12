#pragma once

#include <math.h>
#include <stdexcept>


class Int3;
class Int4;

class Int2
{
public:
	union{
		struct {
			int x;
			int y;
		};

		int v[2];

		intswizzle<2, Int2, Bool2, 0, 0> xx;
		intswizzle<2, Int2, Bool2, 0, 1> xy;
		intswizzle<2, Int2, Bool2, 1, 0> yx;
		intswizzle<2, Int2, Bool2, 1, 1> yy;

		intswizzle<2, Int3, Bool3, 0, 0, 0> xxx;
		intswizzle<2, Int3, Bool3, 0, 0, 1> xxy;
		intswizzle<2, Int3, Bool3, 0, 1, 0> xyx;
		intswizzle<2, Int3, Bool3, 0, 1, 1> xyy;
		intswizzle<2, Int3, Bool3, 1, 0, 0> yxx;
		intswizzle<2, Int3, Bool3, 1, 0, 1> yxy;
		intswizzle<2, Int3, Bool3, 1, 1, 0> yyx;
		intswizzle<2, Int3, Bool3, 1, 1, 1> yyy;

		intswizzle<2, Int4, Bool4, 0, 0, 0, 0> xxxx;
		intswizzle<2, Int4, Bool4, 0, 0, 0, 1> xxxy;
		intswizzle<2, Int4, Bool4, 0, 0, 1, 0> xxyx;
		intswizzle<2, Int4, Bool4, 0, 0, 1, 1> xxyy;
		intswizzle<2, Int4, Bool4, 0, 1, 0, 0> xyxx;
		intswizzle<2, Int4, Bool4, 0, 1, 0, 1> xyxy;
		intswizzle<2, Int4, Bool4, 0, 1, 1, 0> xyyx;
		intswizzle<2, Int4, Bool4, 0, 1, 1, 1> xyyy;
		intswizzle<2, Int4, Bool4, 1, 0, 0, 0> yxxx;
		intswizzle<2, Int4, Bool4, 1, 0, 0, 1> yxxy;
		intswizzle<2, Int4, Bool4, 1, 0, 1, 0> yxyx;
		intswizzle<2, Int4, Bool4, 1, 0, 1, 1> yxyy;
		intswizzle<2, Int4, Bool4, 1, 1, 0, 0> yyxx;
		intswizzle<2, Int4, Bool4, 1, 1, 0, 1> yyxy;
		intswizzle<2, Int4, Bool4, 1, 1, 1, 0> yyyx;
		intswizzle<2, Int4, Bool4, 1, 1, 1, 1> yyyy;

	};

	Int2():x(0),y(0){}

	Int2(int i):x(i),y(i){}

	Int2(int x, int y):x(x),y(y){}

	Int2(int x, int y, int z, int w):x(x),y(y){z; w;}

	Int2(Bool2 b):x(b.x),y(b.y){}

	Int2& operator+=(const Int2& o)
	{
		x += o.x;
		y += o.y;
		return *this;
	}

	Int2& operator-=(const Int2& o)
	{
		x -= o.x;
		y -= o.y;
		return *this;
	}

	Int2& operator*=(const Int2& o)
	{
		x *= o.x;
		y *= o.y;
		return *this;
	}

	Int2& operator/=(const Int2& o)
	{
		x /= o.x;
		y /= o.y;
		return *this;
	}

	Int2& operator%=(const Int2& o)
	{
		x %= o.x;
		y %= o.y;
		return *this;
	}

	Int2& operator>>=(const Int2& o)
	{
		x >>= o.x;
		y >>= o.y;
		return *this;
	}

	Int2& operator<<=(const Int2& o)
	{
		x <<= o.x;
		y <<= o.y;
		return *this;
	}

	Int2& operator&=(const Int2& o)
	{
		x &= o.x;
		y &= o.y;
		return *this;
	}

	Int2& operator|=(const Int2& o)
	{
		x |= o.x;
		y |= o.y;
		return *this;
	}

	Int2 operator&(const Int2& o) const
	{
		return Int2(x & o.x, y & o.y);
	}

	Int2 operator&&(const Int2& o) const
	{
		return Int2(x && o.x, y && o.y);
	}

	Int2 operator|	(const Int2& o) const
	{
		return Int2(x | o.x, y | o.y);
	}

	Int2 operator||(const Int2& o) const
	{
		return Int2(x || o.x, y || o.y);
	}

	Bool2 operator==(const Int2& o) const
	{
		return Bool2(x == o.x, y == o.y);
	}

	Bool2 operator!=(const Int2& o) const
	{
		return Bool2(x != o.x, y != o.y);
	}

	Bool2 operator<(const Int2& o) const
	{
		return Bool2(x < o.x, y < o.y);
	}

	Bool2 operator>(const Int2& o) const
	{
		return Bool2(x > o.x, y > o.y);
	}

	Bool2 operator<=(const Int2& o) const
	{
		return Bool2(x <= o.x, y <= o.y);
	}

	Bool2 operator>=(const Int2& o) const
	{
		return Bool2(x >= o.x, y >= o.y);
	}

	Int2 operator<<(const Int2& o) const
	{
		return Int2(x << o.x, y << o.y);
	}

	Int2 operator>>(const Int2& o) const
	{
		return Int2(x >> o.x, y >> o.y);
	}

	Int2 operator+(const Int2& o) const
	{
		return Int2(x + o.x, y + o.y);
	}

	Int2 operator-(const Int2& o) const
	{
		return Int2(x - o.x, y - o.y);
	}

	Int2 operator*(const Int2& o) const
	{
		return Int2(x * o.x, y * o.y);
	}

	Int2 operator/(const Int2& o) const
	{
		return Int2(x / o.x, y / o.y);
	}

	Int2 operator%(const Int2& o) const
	{
		return Int2(x % o.x, y % o.y);
	}

	Int2 operator+() const
	{
		return Int2(+x, +y);
	}

	Int2 operator-() const
	{
		return Int2(-x, -y);
	}

	Int2 operator!() const
	{
		return Int2(!x, !y);
	}

	Int2 operator~() const
	{
		return Int2(~x, ~y);
	}

	Int2 operator++()
	{
		return Int2(++x, ++y);
	}

	Int2 operator--()
	{
		return Int2(--x, --y);
	}


	Int2 operator++(int)
	{
		return Int2(x++, y++);
	}
	
	Int2 operator--(int)
	{
		return Int2(x++, y++);
	}


	int operator[](unsigned int i) const
	{
		if(i < 0 || i > 1)
			throw std::range_error("Int2 index out of range.");
		return v[i];
	}

	int& operator[](unsigned int i)
	{
		if(i < 0 || i > 1)
			throw std::range_error("Int2 index out of range.");
		return v[i];
	}

	Int2 max(const Int2& o) const
	{
		return Int2( (x>o.x)?x:o.x, (y>o.y)?y:o.y );
	}

	Int2 min(const Int2& o) const
	{
		return Int2( (x<o.x)?x:o.x, (y<o.y)?y:o.y );
	}

	static Int2 random(int lower=0, int upper=6)
	{
		int range = upper - lower + 1;
		return Int2(
			rand() % range + lower,
			rand() % range + lower);
	}

	static const Int2 zero;
	static const Int2 xUnit;
	static const Int2 yUnit;
	static const Int2 one;

};
