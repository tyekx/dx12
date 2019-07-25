#pragma once

#include <math.h>
#include <stdexcept>


class Int2;
class Int3;
class Int4;

class Int1
{
public:
	union{
		struct {
			int x;
		};

		int v[1];

		intswizzle<1, Int2, Bool2, 0, 0> xx;
		intswizzle<1, Int3, Bool3, 0, 0, 0> xxx;
		intswizzle<1, Int4, Bool4, 0, 0, 0, 0> xxxx;

	};

	operator int() const
	{
		return x;
	}

	Int1():x(0){}

	Int1(int i):x(i){}

	Int1(int x, int y, int z, int w):x(x){y; z; w;}

	Int1(Bool1 b):x(b.x){}

	Int1& operator+=(const Int1& o)
	{
		x += o.x;
		return *this;
	}

	Int1& operator-=(const Int1& o)
	{
		x -= o.x;
		return *this;
	}

	Int1& operator*=(const Int1& o)
	{
		x *= o.x;
		return *this;
	}

	Int1& operator/=(const Int1& o)
	{
		x /= o.x;
		return *this;
	}

	Int1& operator%=(const Int1& o)
	{
		x %= o.x;
		return *this;
	}

	Int1& operator>>=(const Int1& o)
	{
		x >>= o.x;
		return *this;
	}

	Int1& operator<<=(const Int1& o)
	{
		x <<= o.x;
		return *this;
	}

	Int1& operator&=(const Int1& o)
	{
		x &= o.x;
		return *this;
	}

	Int1& operator|=(const Int1& o)
	{
		x |= o.x;
		return *this;
	}

	Int1 operator&(const Int1& o) const
	{
		return Int1(x & o.x);
	}

	Int1 operator&&(const Int1& o) const
	{
		return Int1(x && o.x);
	}

	Int1 operator|	(const Int1& o) const
	{
		return Int1(x | o.x);
	}

	Int1 operator||(const Int1& o) const
	{
		return Int1(x || o.x);
	}

	bool operator==(const Int1& o) const
	{
		return x == o.x;
	}

	bool operator!=(const Int1& o) const
	{
		return x != o.x;
	}

	bool operator<(const Int1& o) const
	{
		return x < o.x;
	}

	bool operator>(const Int1& o) const
	{
		return (x > o.x);
	}

	bool operator<=(const Int1& o) const
	{
		return (x <= o.x);
	}

	bool operator>=(const Int1& o) const
	{
		return (x >= o.x);
	}

	Int1 operator<<(const Int1& o) const
	{
		return Int1(x << o.x);
	}

	Int1 operator>>(const Int1& o) const
	{
		return Int1(x >> o.x);
	}

	Int1 operator+(const Int1& o) const
	{
		return Int1(x + o.x);
	}

	Int1 operator-(const Int1& o) const
	{
		return Int1(x - o.x);
	}

	Int1 operator*(const Int1& o) const
	{
		return Int1(x * o.x);
	}

	Int1 operator/(const Int1& o) const
	{
		return Int1(x / o.x);
	}

	Int1 operator%(const Int1& o) const
	{
		return Int1(x % o.x);
	}

	Int1 operator+() const
	{
		return Int1(+x);
	}

	Int1 operator-() const
	{
		return Int1(-x);
	}

	Int1 operator!() const
	{
		return Int1(!x);
	}

	Int1 operator~() const
	{
		return Int1(~x);
	}

	Int1 operator++()
	{
		return Int1(++x);
	}

	Int1 operator--()
	{
		return Int1(--x);
	}


	Int1 operator++(int)
	{
		return Int1(x++);
	}
	
	Int1 operator--(int)
	{
		return Int1(x++);
	}


	int operator[](unsigned int i) const
	{
		if(i < 0 || i > 0)
			throw std::range_error("Int1 index out of range.");
		return v[i];
	}

	int& operator[](unsigned int i)
	{
		if(i < 0 || i > 0)
			throw std::range_error("Int1 index out of range.");
		return v[i];
	}

	Int1 max(const Int1& o) const
	{
		return Int1( (x>o.x)?x:o.x );
	}

	Int1 min(const Int1& o) const
	{
		return Int1( (x<o.x)?x:o.x );
	}

	static Int1 random(int lower=0, int upper=6)
	{
		int range = upper - lower + 1;
		return Int1(
			rand() % range + lower);
	}

	static const Int1 zero;
	static const Int1 xUnit;
	static const Int1 one;

};
