#pragma once

#include <math.h>

class Bool2;
class Bool3;
class Bool4;

class Bool1
{
public:
	union{
		struct {
			bool x;
		};

		bool v[1];

		boolswizzle<1, Bool2, 0, 0> xx;
		boolswizzle<1, Bool3, 0, 0, 0> xxx;
		boolswizzle<1, Bool4, 0, 0, 0, 0> xxxx;
	};

	operator bool() const
	{
		return x;
	}

	Bool1():x(false){}

	Bool1(bool b):x(b){}

	Bool1(bool x, bool y, bool z, bool w):x(x){y; z; w;}

	Bool1& operator&=(const Bool1& o)
	{
		x = x && o.x;
		return *this;
	}

	Bool1& operator|=(const Bool1& o)
	{
		x = x || o.x;
		return *this;
	}

	Bool1 operator&	(const Bool1& o) const
	{
		return Bool1(x && o.x);
	}

	Bool1 operator&&(const Bool1& o) const
	{
		return Bool1(x && o.x);
	}

	Bool1 operator|	(const Bool1& o) const
	{
		return Bool1(x || o.x);
	}

	Bool1 operator||(const Bool1& o) const
	{
		return Bool1(x || o.x);
	}

	Bool1 operator==(const Bool1& o) const
	{
		return Bool1(x == o.x);
	}

	Bool1 operator!=(const Bool1& o) const
	{
		return Bool1(x != o.x);
	}

	Bool1 operator<=(const Bool1& o) const
	{
		return Bool1(x <= o.x);
	}

	Bool1 operator>=(const Bool1& o) const
	{
		return Bool1(x >= o.x);
	}

	Bool1 operator!() const
	{
		return Bool1(!x);
	}

	bool operator[](unsigned int i) const
	{
		if(i < 0 || i > 0)
			throw std::range_error("Bool1 index out of range.");
		return v[i];
	}

	bool& operator[](unsigned int i)
	{
		if(i < 0 || i > 0)
			throw std::range_error("Bool1 index out of range.");
		return v[i];
	}

	bool any() const
	{
		return x;
	}

	bool all() const
	{
		return x;
	}

	static Bool1 random()
	{
		return Bool1(rand()%2==0);
	}

	static const Bool1 zero;
	static const Bool1 xUnit;
	static const Bool1 one;
};
