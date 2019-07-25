#pragma once

#define DEFINE_Float3SWIZZLE_METHOD( Float3SWIZZLE_METHOD_NAME, Float3SWIZZLE_METHOD_RETURN_TYPE )	\
	Float3SWIZZLE_METHOD_RETURN_TYPE Float3SWIZZLE_METHOD_NAME () const	\
	{	\
		T t = *this;	\
		return t. Float3SWIZZLE_METHOD_NAME ();	\
	}

#define DEFINE_Float3SWIZZLE_METHOD_DIADIC( Float3SWIZZLE_METHOD_NAME, Float3SWIZZLE_METHOD_RETURN_TYPE )	\
	Float3SWIZZLE_METHOD_RETURN_TYPE Float3SWIZZLE_METHOD_NAME (const T& o) const	\
	{	\
		T t = *this;	\
		return t. Float3SWIZZLE_METHOD_NAME (o);	\
	}


template<int nBase, class T, int s0=0, int s1=0, int s2=0, int s3=0>
class Float3swizzle : public floatswizzle<nBase, T, Int3, Bool3, s0, s1, s2, s3> 
{
	DEFINE_Float3SWIZZLE_METHOD_DIADIC(cross, T)

};
