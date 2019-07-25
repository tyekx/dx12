#pragma once

#include "boolswizzle.h"

class Bool3;
class Bool4;

class Bool2
{
public:
	union {
		struct {
			bool x;
			bool y;
		};

		bool v[2];

		boolswizzle<2, Bool2, 0, 0> xx;
		boolswizzle<2, Bool2, 0, 1> xy;
		boolswizzle<2, Bool2, 1, 0> yx;
		boolswizzle<2, Bool2, 1, 1> yy;

		boolswizzle<2, Bool3, 0, 0, 0> xxx;
		boolswizzle<2, Bool3, 0, 0, 1> xxy;
		boolswizzle<2, Bool3, 0, 1, 0> xyx;
		boolswizzle<2, Bool3, 0, 1, 1> xyy;
		boolswizzle<2, Bool3, 1, 0, 0> yxx;
		boolswizzle<2, Bool3, 1, 0, 1> yxy;
		boolswizzle<2, Bool3, 1, 1, 0> yyx;
		boolswizzle<2, Bool3, 1, 1, 1> yyy;

		boolswizzle<2, Bool4, 0, 0, 0, 0> xxxx;
		boolswizzle<2, Bool4, 0, 0, 0, 1> xxxy;
		boolswizzle<2, Bool4, 0, 0, 1, 0> xxyx;
		boolswizzle<2, Bool4, 0, 0, 1, 1> xxyy;
		boolswizzle<2, Bool4, 0, 1, 0, 0> xyxx;
		boolswizzle<2, Bool4, 0, 1, 0, 1> xyxy;
		boolswizzle<2, Bool4, 0, 1, 1, 0> xyyx;
		boolswizzle<2, Bool4, 0, 1, 1, 1> xyyy;
		boolswizzle<2, Bool4, 1, 0, 0, 0> yxxx;
		boolswizzle<2, Bool4, 1, 0, 0, 1> yxxy;
		boolswizzle<2, Bool4, 1, 0, 1, 0> yxyx;
		boolswizzle<2, Bool4, 1, 0, 1, 1> yxyy;
		boolswizzle<2, Bool4, 1, 1, 0, 0> yyxx;
		boolswizzle<2, Bool4, 1, 1, 0, 1> yyxy;
		boolswizzle<2, Bool4, 1, 1, 1, 0> yyyx;
		boolswizzle<2, Bool4, 1, 1, 1, 1> yyyy;
	};

	Bool2() :x(false), y(false) {}

	Bool2(bool x, bool y) :x{ x }, y{ y } {}

	Bool2(bool x, bool y, bool z, bool w) : x{ x }, y{ y } { }

	Bool2& operator&=(const Bool2& o)
	{
		x &= o.x;
		y &= o.y;
		return *this;
	}

	Bool2& operator|=(const Bool2& o)
	{
		x |= o.x;
		y |= o.y;
		return *this;
	}

	Bool2 operator&&(const Bool2& o) const
	{
		return Bool2(x && o.x, y && o.y);
	}

	Bool2 operator||(const Bool2& o) const
	{
		return Bool2(x || o.x, y || o.y);
	}

	Bool2 operator==(const Bool2& o) const
	{
		return Bool2(x == o.x, y == o.y);
	}

	Bool2 operator!=(const Bool2& o) const
	{
		return Bool2(x != o.x, y != o.y);
	}

	Bool2 operator<=(const Bool2& o) const
	{
		return Bool2(x <= o.x, y <= o.y);
	}

	Bool2 operator>=(const Bool2& o) const
	{
		return Bool2(x >= o.x, y >= o.y);
	}

	Bool2 operator!() const
	{
		return Bool2(!x, !y);
	}

	bool operator[](unsigned int i) const
	{
		if(i < 0 || i > 1) {
			throw std::range_error("Bool2 index out of range.");
		}
		return v[i];
	}

	bool& operator[](unsigned int i)
	{
		if(i < 0 || i > 1) {
			throw std::range_error("Bool2 index out of range.");
		}
		return v[i];
	}

	bool any() const
	{
		return x || y;
	}

	bool all() const
	{
		return x && y;
	}

	static const Bool2 zero;
	static const Bool2 xUnit;
	static const Bool2 yUnit;
	static const Bool2 one;
};
