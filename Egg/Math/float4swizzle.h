#pragma once


class Float4;

template<int nBase, class T, int s0=0, int s1=1, int s2=2, int s3=3>
class Float4swizzle : public floatswizzle<nBase, T, Int4, Bool4, s0, s1, s2, s3> 
{

};
