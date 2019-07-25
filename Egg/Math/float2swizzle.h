#pragma once

#define DEFINE_Float2SWIZZLE_METHOD( Float2SWIZZLE_METHOD_NAME, Float2SWIZZLE_METHOD_RETURN_TYPE )	\
	Float2SWIZZLE_METHOD_RETURN_TYPE Float2SWIZZLE_METHOD_NAME () const	\
	{	\
		T t = *this;	\
		return t. Float2SWIZZLE_METHOD_NAME ();	\
	}

#define DEFINE_Float2SWIZZLE_METHOD_DIADIC( Float2SWIZZLE_METHOD_NAME, Float2SWIZZLE_METHOD_RETURN_TYPE )	\
	Float2SWIZZLE_METHOD_RETURN_TYPE Float2SWIZZLE_METHOD_NAME (const T& o) const	\
	{	\
		T t = *this;	\
		return t. Float2SWIZZLE_METHOD_NAME (o);	\
	}

template<int nBase, class T, int s0=0, int s1=1, int s2=2, int s3=3>
class Float2swizzle : public floatswizzle<nBase, T, Int2, Bool2, s0, s1, s2, s3> 
{
	DEFINE_Float2SWIZZLE_METHOD(arg, float)
	DEFINE_Float2SWIZZLE_METHOD_DIADIC(complexmul, T)
	DEFINE_Float2SWIZZLE_METHOD(polar, T)
	DEFINE_Float2SWIZZLE_METHOD(cartesian, T)

	T rotate(float angle) const
	{
		T t = *this;
		return t.rotate(angle);
	}
};
