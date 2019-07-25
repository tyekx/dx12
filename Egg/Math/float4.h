#pragma once

#include <math.h>

		class Float2;
		class Float3;
		class Float4;

		class Float4
		{
		public:
			union {
				struct {
					float x;
					float y;
					float z;
					float w;
				};

				float v[4];

				Float2swizzle<4, Float2, 0, 0> xx;
				Float2swizzle<4, Float2, 0, 1> xy;
				Float2swizzle<4, Float2, 0, 2> xz;
				Float2swizzle<4, Float2, 0, 3> xw;
				Float2swizzle<4, Float2, 1, 0> yx;
				Float2swizzle<4, Float2, 1, 1> yy;
				Float2swizzle<4, Float2, 1, 2> yz;
				Float2swizzle<4, Float2, 1, 3> yw;
				Float2swizzle<4, Float2, 2, 0> zx;
				Float2swizzle<4, Float2, 2, 1> zy;
				Float2swizzle<4, Float2, 2, 2> zz;
				Float2swizzle<4, Float2, 2, 3> zw;
				Float2swizzle<4, Float2, 3, 0> wx;
				Float2swizzle<4, Float2, 3, 1> wy;
				Float2swizzle<4, Float2, 3, 2> wz;
				Float2swizzle<4, Float2, 3, 3> ww;

				Float3swizzle<4, Float3, 0, 0, 0> xxx;
				Float3swizzle<4, Float3, 0, 0, 1> xxy;
				Float3swizzle<4, Float3, 0, 0, 2> xxz;
				Float3swizzle<4, Float3, 0, 0, 3> xxw;
				Float3swizzle<4, Float3, 0, 1, 0> xyx;
				Float3swizzle<4, Float3, 0, 1, 1> xyy;
				Float3swizzle<4, Float3, 0, 1, 2> xyz;
				Float3swizzle<4, Float3, 0, 1, 3> xyw;
				Float3swizzle<4, Float3, 0, 2, 0> xzx;
				Float3swizzle<4, Float3, 0, 2, 1> xzy;
				Float3swizzle<4, Float3, 0, 2, 2> xzz;
				Float3swizzle<4, Float3, 0, 2, 3> xzw;
				Float3swizzle<4, Float3, 0, 3, 0> xwx;
				Float3swizzle<4, Float3, 0, 3, 1> xwy;
				Float3swizzle<4, Float3, 0, 3, 2> xwz;
				Float3swizzle<4, Float3, 0, 3, 3> xww;

				Float3swizzle<4, Float3, 1, 0, 0> yxx;
				Float3swizzle<4, Float3, 1, 0, 1> yxy;
				Float3swizzle<4, Float3, 1, 0, 2> yxz;
				Float3swizzle<4, Float3, 1, 0, 3> yxw;
				Float3swizzle<4, Float3, 1, 1, 0> yyx;
				Float3swizzle<4, Float3, 1, 1, 1> yyy;
				Float3swizzle<4, Float3, 1, 1, 2> yyz;
				Float3swizzle<4, Float3, 1, 1, 3> yyw;
				Float3swizzle<4, Float3, 1, 2, 0> yzx;
				Float3swizzle<4, Float3, 1, 2, 1> yzy;
				Float3swizzle<4, Float3, 1, 2, 2> yzz;
				Float3swizzle<4, Float3, 1, 2, 3> yzw;
				Float3swizzle<4, Float3, 1, 3, 0> ywx;
				Float3swizzle<4, Float3, 1, 3, 1> ywy;
				Float3swizzle<4, Float3, 1, 3, 2> ywz;
				Float3swizzle<4, Float3, 1, 3, 3> yww;

				Float3swizzle<4, Float3, 2, 0, 0> zxx;
				Float3swizzle<4, Float3, 2, 0, 1> zxy;
				Float3swizzle<4, Float3, 2, 0, 2> zxz;
				Float3swizzle<4, Float3, 2, 0, 3> zxw;
				Float3swizzle<4, Float3, 2, 1, 0> zyx;
				Float3swizzle<4, Float3, 2, 1, 1> zyy;
				Float3swizzle<4, Float3, 2, 1, 2> zyz;
				Float3swizzle<4, Float3, 2, 1, 3> zyw;
				Float3swizzle<4, Float3, 2, 2, 0> zzx;
				Float3swizzle<4, Float3, 2, 2, 1> zzy;
				Float3swizzle<4, Float3, 2, 2, 2> zzz;
				Float3swizzle<4, Float3, 2, 2, 3> zzw;
				Float3swizzle<4, Float3, 2, 3, 0> zwx;
				Float3swizzle<4, Float3, 2, 3, 1> zwy;
				Float3swizzle<4, Float3, 2, 3, 2> zwz;
				Float3swizzle<4, Float3, 2, 3, 3> zww;

				Float3swizzle<4, Float3, 3, 0, 0> wxx;
				Float3swizzle<4, Float3, 3, 0, 1> wxy;
				Float3swizzle<4, Float3, 3, 0, 2> wxz;
				Float3swizzle<4, Float3, 3, 0, 3> wxw;
				Float3swizzle<4, Float3, 3, 1, 0> wyx;
				Float3swizzle<4, Float3, 3, 1, 1> wyy;
				Float3swizzle<4, Float3, 3, 1, 2> wyz;
				Float3swizzle<4, Float3, 3, 1, 3> wyw;
				Float3swizzle<4, Float3, 3, 2, 0> wzx;
				Float3swizzle<4, Float3, 3, 2, 1> wzy;
				Float3swizzle<4, Float3, 3, 2, 2> wzz;
				Float3swizzle<4, Float3, 3, 2, 3> wzw;
				Float3swizzle<4, Float3, 3, 3, 0> wwx;
				Float3swizzle<4, Float3, 3, 3, 1> wwy;
				Float3swizzle<4, Float3, 3, 3, 2> wwz;
				Float3swizzle<4, Float3, 3, 3, 3> www;

				Float4swizzle<4, Float4, 0, 0, 0, 0> xxxx;
				Float4swizzle<4, Float4, 0, 0, 0, 1> xxxy;
				Float4swizzle<4, Float4, 0, 0, 0, 2> xxxz;
				Float4swizzle<4, Float4, 0, 0, 0, 3> xxxw;
				Float4swizzle<4, Float4, 0, 0, 1, 0> xxyx;
				Float4swizzle<4, Float4, 0, 0, 1, 1> xxyy;
				Float4swizzle<4, Float4, 0, 0, 1, 2> xxyz;
				Float4swizzle<4, Float4, 0, 0, 1, 3> xxyw;
				Float4swizzle<4, Float4, 0, 0, 2, 0> xxzx;
				Float4swizzle<4, Float4, 0, 0, 2, 1> xxzy;
				Float4swizzle<4, Float4, 0, 0, 2, 2> xxzz;
				Float4swizzle<4, Float4, 0, 0, 2, 3> xxzw;
				Float4swizzle<4, Float4, 0, 0, 3, 0> xxwx;
				Float4swizzle<4, Float4, 0, 0, 3, 1> xxwy;
				Float4swizzle<4, Float4, 0, 0, 3, 2> xxwz;
				Float4swizzle<4, Float4, 0, 0, 3, 3> xxww;
				Float4swizzle<4, Float4, 0, 1, 0, 0> xyxx;
				Float4swizzle<4, Float4, 0, 1, 0, 1> xyxy;
				Float4swizzle<4, Float4, 0, 1, 0, 2> xyxz;
				Float4swizzle<4, Float4, 0, 1, 0, 3> xyxw;
				Float4swizzle<4, Float4, 0, 1, 1, 0> xyyx;
				Float4swizzle<4, Float4, 0, 1, 1, 1> xyyy;
				Float4swizzle<4, Float4, 0, 1, 1, 2> xyyz;
				Float4swizzle<4, Float4, 0, 1, 1, 3> xyyw;
				Float4swizzle<4, Float4, 0, 1, 2, 0> xyzx;
				Float4swizzle<4, Float4, 0, 1, 2, 1> xyzy;
				Float4swizzle<4, Float4, 0, 1, 2, 2> xyzz;
				Float4swizzle<4, Float4, 0, 1, 2, 3> xyzw;
				Float4swizzle<4, Float4, 0, 1, 3, 0> xywx;
				Float4swizzle<4, Float4, 0, 1, 3, 1> xywy;
				Float4swizzle<4, Float4, 0, 1, 3, 2> xywz;
				Float4swizzle<4, Float4, 0, 1, 3, 3> xyww;
				Float4swizzle<4, Float4, 0, 2, 0, 0> xzxx;
				Float4swizzle<4, Float4, 0, 2, 0, 1> xzxy;
				Float4swizzle<4, Float4, 0, 2, 0, 2> xzxz;
				Float4swizzle<4, Float4, 0, 2, 0, 3> xzxw;
				Float4swizzle<4, Float4, 0, 2, 1, 0> xzyx;
				Float4swizzle<4, Float4, 0, 2, 1, 1> xzyy;
				Float4swizzle<4, Float4, 0, 2, 1, 2> xzyz;
				Float4swizzle<4, Float4, 0, 2, 1, 3> xzyw;
				Float4swizzle<4, Float4, 0, 2, 2, 0> xzzx;
				Float4swizzle<4, Float4, 0, 2, 2, 1> xzzy;
				Float4swizzle<4, Float4, 0, 2, 2, 2> xzzz;
				Float4swizzle<4, Float4, 0, 2, 2, 3> xzzw;
				Float4swizzle<4, Float4, 0, 2, 3, 0> xzwx;
				Float4swizzle<4, Float4, 0, 2, 3, 1> xzwy;
				Float4swizzle<4, Float4, 0, 2, 3, 2> xzwz;
				Float4swizzle<4, Float4, 0, 2, 3, 3> xzww;
				Float4swizzle<4, Float4, 0, 3, 0, 0> xwxx;
				Float4swizzle<4, Float4, 0, 3, 0, 1> xwxy;
				Float4swizzle<4, Float4, 0, 3, 0, 2> xwxz;
				Float4swizzle<4, Float4, 0, 3, 0, 3> xwxw;
				Float4swizzle<4, Float4, 0, 3, 1, 0> xwyx;
				Float4swizzle<4, Float4, 0, 3, 1, 1> xwyy;
				Float4swizzle<4, Float4, 0, 3, 1, 2> xwyz;
				Float4swizzle<4, Float4, 0, 3, 1, 3> xwyw;
				Float4swizzle<4, Float4, 0, 3, 2, 0> xwzx;
				Float4swizzle<4, Float4, 0, 3, 2, 1> xwzy;
				Float4swizzle<4, Float4, 0, 3, 2, 2> xwzz;
				Float4swizzle<4, Float4, 0, 3, 2, 3> xwzw;
				Float4swizzle<4, Float4, 0, 3, 3, 0> xwwx;
				Float4swizzle<4, Float4, 0, 3, 3, 1> xwwy;
				Float4swizzle<4, Float4, 0, 3, 3, 2> xwwz;
				Float4swizzle<4, Float4, 0, 3, 3, 3> xwww;

				Float4swizzle<4, Float4, 1, 0, 0, 0> yxxx;
				Float4swizzle<4, Float4, 1, 0, 0, 1> yxxy;
				Float4swizzle<4, Float4, 1, 0, 0, 2> yxxz;
				Float4swizzle<4, Float4, 1, 0, 0, 3> yxxw;
				Float4swizzle<4, Float4, 1, 0, 1, 0> yxyx;
				Float4swizzle<4, Float4, 1, 0, 1, 1> yxyy;
				Float4swizzle<4, Float4, 1, 0, 1, 2> yxyz;
				Float4swizzle<4, Float4, 1, 0, 1, 3> yxyw;
				Float4swizzle<4, Float4, 1, 0, 2, 0> yxzx;
				Float4swizzle<4, Float4, 1, 0, 2, 1> yxzy;
				Float4swizzle<4, Float4, 1, 0, 2, 2> yxzz;
				Float4swizzle<4, Float4, 1, 0, 2, 3> yxzw;
				Float4swizzle<4, Float4, 1, 0, 3, 0> yxwx;
				Float4swizzle<4, Float4, 1, 0, 3, 1> yxwy;
				Float4swizzle<4, Float4, 1, 0, 3, 2> yxwz;
				Float4swizzle<4, Float4, 1, 0, 3, 3> yxww;
				Float4swizzle<4, Float4, 1, 1, 0, 0> yyxx;
				Float4swizzle<4, Float4, 1, 1, 0, 1> yyxy;
				Float4swizzle<4, Float4, 1, 1, 0, 2> yyxz;
				Float4swizzle<4, Float4, 1, 1, 0, 3> yyxw;
				Float4swizzle<4, Float4, 1, 1, 1, 0> yyyx;
				Float4swizzle<4, Float4, 1, 1, 1, 1> yyyy;
				Float4swizzle<4, Float4, 1, 1, 1, 2> yyyz;
				Float4swizzle<4, Float4, 1, 1, 1, 3> yyyw;
				Float4swizzle<4, Float4, 1, 1, 2, 0> yyzx;
				Float4swizzle<4, Float4, 1, 1, 2, 1> yyzy;
				Float4swizzle<4, Float4, 1, 1, 2, 2> yyzz;
				Float4swizzle<4, Float4, 1, 1, 2, 3> yyzw;
				Float4swizzle<4, Float4, 1, 1, 3, 0> yywx;
				Float4swizzle<4, Float4, 1, 1, 3, 1> yywy;
				Float4swizzle<4, Float4, 1, 1, 3, 2> yywz;
				Float4swizzle<4, Float4, 1, 1, 3, 3> yyww;
				Float4swizzle<4, Float4, 1, 2, 0, 0> yzxx;
				Float4swizzle<4, Float4, 1, 2, 0, 1> yzxy;
				Float4swizzle<4, Float4, 1, 2, 0, 2> yzxz;
				Float4swizzle<4, Float4, 1, 2, 0, 3> yzxw;
				Float4swizzle<4, Float4, 1, 2, 1, 0> yzyx;
				Float4swizzle<4, Float4, 1, 2, 1, 1> yzyy;
				Float4swizzle<4, Float4, 1, 2, 1, 2> yzyz;
				Float4swizzle<4, Float4, 1, 2, 1, 3> yzyw;
				Float4swizzle<4, Float4, 1, 2, 2, 0> yzzx;
				Float4swizzle<4, Float4, 1, 2, 2, 1> yzzy;
				Float4swizzle<4, Float4, 1, 2, 2, 2> yzzz;
				Float4swizzle<4, Float4, 1, 2, 2, 3> yzzw;
				Float4swizzle<4, Float4, 1, 2, 3, 0> yzwx;
				Float4swizzle<4, Float4, 1, 2, 3, 1> yzwy;
				Float4swizzle<4, Float4, 1, 2, 3, 2> yzwz;
				Float4swizzle<4, Float4, 1, 2, 3, 3> yzww;
				Float4swizzle<4, Float4, 1, 3, 0, 0> ywxx;
				Float4swizzle<4, Float4, 1, 3, 0, 1> ywxy;
				Float4swizzle<4, Float4, 1, 3, 0, 2> ywxz;
				Float4swizzle<4, Float4, 1, 3, 0, 3> ywxw;
				Float4swizzle<4, Float4, 1, 3, 1, 0> ywyx;
				Float4swizzle<4, Float4, 1, 3, 1, 1> ywyy;
				Float4swizzle<4, Float4, 1, 3, 1, 2> ywyz;
				Float4swizzle<4, Float4, 1, 3, 1, 3> ywyw;
				Float4swizzle<4, Float4, 1, 3, 2, 0> ywzx;
				Float4swizzle<4, Float4, 1, 3, 2, 1> ywzy;
				Float4swizzle<4, Float4, 1, 3, 2, 2> ywzz;
				Float4swizzle<4, Float4, 1, 3, 2, 3> ywzw;
				Float4swizzle<4, Float4, 1, 3, 3, 0> ywwx;
				Float4swizzle<4, Float4, 1, 3, 3, 1> ywwy;
				Float4swizzle<4, Float4, 1, 3, 3, 2> ywwz;
				Float4swizzle<4, Float4, 1, 3, 3, 3> ywww;

				Float4swizzle<4, Float4, 2, 0, 0, 0> zxxx;
				Float4swizzle<4, Float4, 2, 0, 0, 1> zxxy;
				Float4swizzle<4, Float4, 2, 0, 0, 2> zxxz;
				Float4swizzle<4, Float4, 2, 0, 0, 3> zxxw;
				Float4swizzle<4, Float4, 2, 0, 1, 0> zxyx;
				Float4swizzle<4, Float4, 2, 0, 1, 1> zxyy;
				Float4swizzle<4, Float4, 2, 0, 1, 2> zxyz;
				Float4swizzle<4, Float4, 2, 0, 1, 3> zxyw;
				Float4swizzle<4, Float4, 2, 0, 2, 0> zxzx;
				Float4swizzle<4, Float4, 2, 0, 2, 1> zxzy;
				Float4swizzle<4, Float4, 2, 0, 2, 2> zxzz;
				Float4swizzle<4, Float4, 2, 0, 2, 3> zxzw;
				Float4swizzle<4, Float4, 2, 0, 3, 0> zxwx;
				Float4swizzle<4, Float4, 2, 0, 3, 1> zxwy;
				Float4swizzle<4, Float4, 2, 0, 3, 2> zxwz;
				Float4swizzle<4, Float4, 2, 0, 3, 3> zxww;
				Float4swizzle<4, Float4, 2, 1, 0, 0> zyxx;
				Float4swizzle<4, Float4, 2, 1, 0, 1> zyxy;
				Float4swizzle<4, Float4, 2, 1, 0, 2> zyxz;
				Float4swizzle<4, Float4, 2, 1, 0, 3> zyxw;
				Float4swizzle<4, Float4, 2, 1, 1, 0> zyyx;
				Float4swizzle<4, Float4, 2, 1, 1, 1> zyyy;
				Float4swizzle<4, Float4, 2, 1, 1, 2> zyyz;
				Float4swizzle<4, Float4, 2, 1, 1, 3> zyyw;
				Float4swizzle<4, Float4, 2, 1, 2, 0> zyzx;
				Float4swizzle<4, Float4, 2, 1, 2, 1> zyzy;
				Float4swizzle<4, Float4, 2, 1, 2, 2> zyzz;
				Float4swizzle<4, Float4, 2, 1, 2, 3> zyzw;
				Float4swizzle<4, Float4, 2, 1, 3, 0> zywx;
				Float4swizzle<4, Float4, 2, 1, 3, 1> zywy;
				Float4swizzle<4, Float4, 2, 1, 3, 2> zywz;
				Float4swizzle<4, Float4, 2, 1, 3, 3> zyww;
				Float4swizzle<4, Float4, 2, 2, 0, 0> zzxx;
				Float4swizzle<4, Float4, 2, 2, 0, 1> zzxy;
				Float4swizzle<4, Float4, 2, 2, 0, 2> zzxz;
				Float4swizzle<4, Float4, 2, 2, 0, 3> zzxw;
				Float4swizzle<4, Float4, 2, 2, 1, 0> zzyx;
				Float4swizzle<4, Float4, 2, 2, 1, 1> zzyy;
				Float4swizzle<4, Float4, 2, 2, 1, 2> zzyz;
				Float4swizzle<4, Float4, 2, 2, 1, 3> zzyw;
				Float4swizzle<4, Float4, 2, 2, 2, 0> zzzx;
				Float4swizzle<4, Float4, 2, 2, 2, 1> zzzy;
				Float4swizzle<4, Float4, 2, 2, 2, 2> zzzz;
				Float4swizzle<4, Float4, 2, 2, 2, 3> zzzw;
				Float4swizzle<4, Float4, 2, 2, 3, 0> zzwx;
				Float4swizzle<4, Float4, 2, 2, 3, 1> zzwy;
				Float4swizzle<4, Float4, 2, 2, 3, 2> zzwz;
				Float4swizzle<4, Float4, 2, 2, 3, 3> zzww;
				Float4swizzle<4, Float4, 2, 3, 0, 0> zwxx;
				Float4swizzle<4, Float4, 2, 3, 0, 1> zwxy;
				Float4swizzle<4, Float4, 2, 3, 0, 2> zwxz;
				Float4swizzle<4, Float4, 2, 3, 0, 3> zwxw;
				Float4swizzle<4, Float4, 2, 3, 1, 0> zwyx;
				Float4swizzle<4, Float4, 2, 3, 1, 1> zwyy;
				Float4swizzle<4, Float4, 2, 3, 1, 2> zwyz;
				Float4swizzle<4, Float4, 2, 3, 1, 3> zwyw;
				Float4swizzle<4, Float4, 2, 3, 2, 0> zwzx;
				Float4swizzle<4, Float4, 2, 3, 2, 1> zwzy;
				Float4swizzle<4, Float4, 2, 3, 2, 2> zwzz;
				Float4swizzle<4, Float4, 2, 3, 2, 3> zwzw;
				Float4swizzle<4, Float4, 2, 3, 3, 0> zwwx;
				Float4swizzle<4, Float4, 2, 3, 3, 1> zwwy;
				Float4swizzle<4, Float4, 2, 3, 3, 2> zwwz;
				Float4swizzle<4, Float4, 2, 3, 3, 3> zwww;

				Float4swizzle<4, Float4, 3, 0, 0, 0> wxxx;
				Float4swizzle<4, Float4, 3, 0, 0, 1> wxxy;
				Float4swizzle<4, Float4, 3, 0, 0, 2> wxxz;
				Float4swizzle<4, Float4, 3, 0, 0, 3> wxxw;
				Float4swizzle<4, Float4, 3, 0, 1, 0> wxyx;
				Float4swizzle<4, Float4, 3, 0, 1, 1> wxyy;
				Float4swizzle<4, Float4, 3, 0, 1, 2> wxyz;
				Float4swizzle<4, Float4, 3, 0, 1, 3> wxyw;
				Float4swizzle<4, Float4, 3, 0, 2, 0> wxzx;
				Float4swizzle<4, Float4, 3, 0, 2, 1> wxzy;
				Float4swizzle<4, Float4, 3, 0, 2, 2> wxzz;
				Float4swizzle<4, Float4, 3, 0, 2, 3> wxzw;
				Float4swizzle<4, Float4, 3, 0, 3, 0> wxwx;
				Float4swizzle<4, Float4, 3, 0, 3, 1> wxwy;
				Float4swizzle<4, Float4, 3, 0, 3, 2> wxwz;
				Float4swizzle<4, Float4, 3, 0, 3, 3> wxww;
				Float4swizzle<4, Float4, 3, 1, 0, 0> wyxx;
				Float4swizzle<4, Float4, 3, 1, 0, 1> wyxy;
				Float4swizzle<4, Float4, 3, 1, 0, 2> wyxz;
				Float4swizzle<4, Float4, 3, 1, 0, 3> wyxw;
				Float4swizzle<4, Float4, 3, 1, 1, 0> wyyx;
				Float4swizzle<4, Float4, 3, 1, 1, 1> wyyy;
				Float4swizzle<4, Float4, 3, 1, 1, 2> wyyz;
				Float4swizzle<4, Float4, 3, 1, 1, 3> wyyw;
				Float4swizzle<4, Float4, 3, 1, 2, 0> wyzx;
				Float4swizzle<4, Float4, 3, 1, 2, 1> wyzy;
				Float4swizzle<4, Float4, 3, 1, 2, 2> wyzz;
				Float4swizzle<4, Float4, 3, 1, 2, 3> wyzw;
				Float4swizzle<4, Float4, 3, 1, 3, 0> wywx;
				Float4swizzle<4, Float4, 3, 1, 3, 1> wywy;
				Float4swizzle<4, Float4, 3, 1, 3, 2> wywz;
				Float4swizzle<4, Float4, 3, 1, 3, 3> wyww;
				Float4swizzle<4, Float4, 3, 2, 0, 0> wzxx;
				Float4swizzle<4, Float4, 3, 2, 0, 1> wzxy;
				Float4swizzle<4, Float4, 3, 2, 0, 2> wzxz;
				Float4swizzle<4, Float4, 3, 2, 0, 3> wzxw;
				Float4swizzle<4, Float4, 3, 2, 1, 0> wzyx;
				Float4swizzle<4, Float4, 3, 2, 1, 1> wzyy;
				Float4swizzle<4, Float4, 3, 2, 1, 2> wzyz;
				Float4swizzle<4, Float4, 3, 2, 1, 3> wzyw;
				Float4swizzle<4, Float4, 3, 2, 2, 0> wzzx;
				Float4swizzle<4, Float4, 3, 2, 2, 1> wzzy;
				Float4swizzle<4, Float4, 3, 2, 2, 2> wzzz;
				Float4swizzle<4, Float4, 3, 2, 2, 3> wzzw;
				Float4swizzle<4, Float4, 3, 2, 3, 0> wzwx;
				Float4swizzle<4, Float4, 3, 2, 3, 1> wzwy;
				Float4swizzle<4, Float4, 3, 2, 3, 2> wzwz;
				Float4swizzle<4, Float4, 3, 2, 3, 3> wzww;
				Float4swizzle<4, Float4, 3, 3, 0, 0> wwxx;
				Float4swizzle<4, Float4, 3, 3, 0, 1> wwxy;
				Float4swizzle<4, Float4, 3, 3, 0, 2> wwxz;
				Float4swizzle<4, Float4, 3, 3, 0, 3> wwxw;
				Float4swizzle<4, Float4, 3, 3, 1, 0> wwyx;
				Float4swizzle<4, Float4, 3, 3, 1, 1> wwyy;
				Float4swizzle<4, Float4, 3, 3, 1, 2> wwyz;
				Float4swizzle<4, Float4, 3, 3, 1, 3> wwyw;
				Float4swizzle<4, Float4, 3, 3, 2, 0> wwzx;
				Float4swizzle<4, Float4, 3, 3, 2, 1> wwzy;
				Float4swizzle<4, Float4, 3, 3, 2, 2> wwzz;
				Float4swizzle<4, Float4, 3, 3, 2, 3> wwzw;
				Float4swizzle<4, Float4, 3, 3, 3, 0> wwwx;
				Float4swizzle<4, Float4, 3, 3, 3, 1> wwwy;
				Float4swizzle<4, Float4, 3, 3, 3, 2> wwwz;
				Float4swizzle<4, Float4, 3, 3, 3, 3> wwww;


			};

			Float4() :x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}

			Float4(float f) :x(f), y(f), z(f), w(f) {}

			Float4(float x, float y, float z, float w) :x(x), y(y), z(z), w(w) {}

			Float4(Float2 xy, float z, float w) :x(xy.x), y(xy.y), z(z), w(w) {}

			Float4(float x, Float2 yz, float w) :x(x), y(yz.x), z(yz.y), w(w) {}

			Float4(float x, float y, Float2 zw) :x(x), y(y), z(zw.x), w(zw.y) {}

			Float4(Float2 xy, Float2 zw) :x(xy.x), y(xy.y), z(zw.x), w(zw.y) {}

			Float4(Float3 xyz, float w) :x(xyz.x), y(xyz.y), z(xyz.z), w(w) {}

			Float4(float x, Float3 yzw) :x(x), y(yzw.x), z(yzw.y), w(yzw.z) {}

			Float4(Int4 i) :x((float)i.x), y((float)i.y), z((float)i.z), w((float)i.w) {}

			Float4& operator+=(const Float4& o)
			{
				x += o.x;
				y += o.y;
				z += o.z;
				w += o.w;
				return *this;
			}

			Float4& operator-=(const Float4& o)
			{
				x -= o.x;
				y -= o.y;
				z -= o.z;
				w -= o.w;
				return *this;
			}

			Float4& operator*=(const Float4& o)
			{
				x *= o.x;
				y *= o.y;
				z *= o.z;
				w *= o.w;
				return *this;
			}

			Float4& operator/=(const Float4& o)
			{
				x /= o.x;
				y /= o.y;
				z /= o.z;
				w /= o.w;
				return *this;
			}

			Float4& operator%=(const Float4& o)
			{
				x = fmodf(x, o.x);
				y = fmodf(y, o.y);
				z = fmodf(z, o.z);
				w = fmodf(w, o.w);
				return *this;
			}

			Bool4 operator==(const Float4& o) const
			{
				return Bool4(x == o.x, y == o.y, z == o.z, w == o.w);
			}

			Bool4 operator!=(const Float4& o) const
			{
				return Bool4(x != o.x, y != o.y, z != o.z, w != o.w);
			}

			Bool4 operator<(const Float4& o) const
			{
				return Bool4(x < o.x, y < o.y, z < o.z, w < o.w);
			}

			Bool4 operator<=(const Float4& o) const
			{
				return Bool4(x <= o.x, y <= o.y, z <= o.z, w <= o.w);
			}

			Bool4 operator>(const Float4& o) const
			{
				return Bool4(x > o.x, y > o.y, z > o.z, w > o.w);
			}

			Bool4 operator>=(const Float4& o) const
			{
				return Bool4(x >= o.x, y >= o.y, z >= o.z, w >= o.w);
			}

			Float4 operator+(const Float4& o) const
			{
				return Float4(x + o.x, y + o.y, z + o.z, w + o.w);
			}

			Float4 operator-(const Float4& o) const
			{
				return Float4(x - o.x, y - o.y, z - o.z, w - o.w);
			}

			Float4 operator*(const Float4& o) const
			{
				return Float4(x * o.x, y * o.y, z * o.z, w * o.w);
			}

			Float4 operator/(const Float4& o) const
			{
				return Float4(x / o.x, y / o.y, z / o.z, w / o.w);
			}

			Float4 operator%(const Float4& o) const
			{
				return Float4(fmodf(x, o.x), fmodf(y, o.y), fmodf(z, o.z), fmodf(w, o.w));
			}


			Float4 operator+() const
			{
				return Float4(+x, +y, +z, +w);
			}

			Float4 operator-() const
			{
				return Float4(-x, -y, -z, -w);
			}

			Float4 operator!() const
			{
				return Float4(-x, -y, -z, +w);
			}

			float operator[](unsigned int i) const
			{
				if (i < 0 || i > 3)
					throw std::range_error("Float4 index out of range.");
				return v[i];
			}

			float& operator[](unsigned int i)
			{
				if (i < 0 || i > 3)
					throw std::range_error("Float4 index out of range.");
				return v[i];
			}


			Float4 abs() const {
				return Float4(::abs(x), ::abs(y), ::abs(z), ::abs(w));
			}

			Float4 acos() const {
				return Float4(::acos(x), ::acos(y), ::acos(z), ::acos(w));
			}

			Float4 asin() const {
				return Float4(::asin(x), ::asin(y), ::asin(z), ::asin(w));
			}

			Float4 atan() const {
				return Float4(::atan(x), ::atan(y), ::atan(z), ::atan(w));
			}

			Int4 ceil() const {
				return Int4((int)::ceil(x), (int)::ceil(y), (int)::ceil(z), (int)::ceil(w));
			}

			Float4 cos() const {
				return Float4(::cos(x), ::cos(y), ::cos(z), ::cos(w));
			}

			Float4 cosh() const {
				return Float4(::cosh(x), ::cosh(y), ::cosh(z), ::cosh(w));
			}

			Float4 exp() const {
				return Float4(::exp(x), ::exp(y), ::exp(z), ::exp(w));
			}

			Int4 floor() const {
				return Int4((int)::floor(x), (int)::floor(y), (int)::floor(z), (int)::floor(w));
			}

			Float4 log() const {
				return Float4(::log(x), ::log(y), ::log(z), ::log(w));
			}

			Float4 log10() const {
				return Float4(::log10(x), ::log10(y), ::log10(z), ::log10(w));
			}

			Float4 sin() const {
				return Float4(::sin(x), ::sin(y), ::sin(z), ::sin(w));
			}
			
			Float4 sinh() const {
				return Float4(::sinh(x), ::sinh(y), ::sinh(z), ::sinh(w));
			}

			Float4 tan() const {
				return Float4(::tan(x), ::tan(y), ::tan(z), ::tan(w));
			}

			Float4 exp2() const
			{
				return Float4(::pow(2.0f, x), ::pow(2.0f, y), ::pow(2.0f, z), ::pow(2.0f, w));
			}

			float distance(const Float4& o) const
			{
				return (*this - o).length();
			}

			float dot(const Float4& o) const
			{
				return x * o.x + y * o.y + z * o.z + w * o.w;
			}

			Float4 frac() const
			{
				return *this - trunc();
			}

			Bool4 isfinite() const
			{
				return Bool4(::_finite(x), ::_finite(y), ::_finite(z), ::_finite(w));
			}

			Bool4 isinf() const
			{
				return Bool4(!::_finite(x), !::_finite(y), !::_finite(z), !::_finite(w));
			}

			Bool4 isnan() const
			{
				return Bool4(::_isnan(x), ::_isnan(y), ::_isnan(z), ::_isnan(w));
			}

			float length() const
			{
				return sqrtf(this->dot(*this));
			}

			float lengthSquared() const
			{
				return this->dot(*this);
			}

			Float4 lerp(const Float4& a, const Float4& b) const
			{
				return a * (Float4(1, 1, 1, 1) - *this) + b * *this;
			}


			Float4 atan2(const Float4& o) const
			{
				return Float4(::atan2(x, o.x), ::atan2(y, o.y), ::atan2(z, o.z), ::atan2(w, o.w));
			}

			Float4 fmod(const Float4& o) const
			{
				return Float4(::fmod(x, o.x), ::fmod(y, o.y), ::fmod(z, o.z), ::fmod(w, o.w));
			}

			Float4 pow(const Float4& o) const
			{
				return Float4(::pow(x, o.x), ::pow(y, o.y), ::pow(z, o.z), ::pow(w, o.w));
			}

			Float4 log2() const
			{
				return Float4(::log(x) / ::log(2.0f), ::log(y) / ::log(2.0f), ::log(z) / ::log(2.0f), ::log(w) / ::log(2.0f));
			}

			Float4 max(const Float4& o) const
			{
				return Float4((x > o.x) ? x : o.x, (y > o.y) ? y : o.y, (z > o.z) ? z : o.z, (w > o.w) ? w : o.w);
			}

			Float4 min(const Float4& o) const
			{
				return Float4((x < o.x) ? x : o.x, (y < o.y) ? y : o.y, (z < o.z) ? z : o.z, (w < o.w) ? w : o.w);
			}

			Float4 normalize() const
			{
				return *this / length();
			}

			Int4 round() const
			{
				return Int4((int)(x + 0.5f), (int)(y + 0.5f), (int)(z + 0.5f), (int)(w + 0.5f));
			}

			Float4 rsqrt() const
			{
				return Float4(1.0f / ::sqrtf(x), 1.0f / ::sqrtf(y), 1.0f / ::sqrtf(z), 1.0f / ::sqrtf(w));
			}

			Float4 saturate() const
			{
				return clamp(Float4(0, 0, 0, 0), Float4(1, 1, 1, 1));
			}

			Float4 sign() const
			{
				return Float4((x > 0.0f) ? 1.0f : ((x < 0.0f) ? -1.0f : 0.0f), (y > 0.0f) ? 1.0f : ((y < 0.0f) ? -1.0f : 0.0f), (z > 0.0f) ? 1.0f : ((z < 0.0f) ? -1.0f : 0.0f), (w > 0.0f) ? 1.0f : ((w < 0.0f) ? -1.0f : 0.0f));
			}

			Float4 smoothstep(const Float4& a, const Float4& b) const
			{
				Float4 r = ((*this - a) / (b - a)).saturate();
				return r*r*(Float4(3.0f, 3.0f, 3.0f, 3.0f) - r*2.0f);
			}

			Float4 sqrt() const
			{
				return Float4(::sqrtf(x), ::sqrtf(y), ::sqrtf(z), ::sqrtf(w));
			}

			Float4 step(const Float4& o) const
			{
				return Float4((x >= o.x) ? 1.0f : 0.0f, (y >= o.y) ? 1.0f : 0.0f, (z >= o.z) ? 1.0f : 0.0f, (w >= o.w) ? 1.0f : 0.0f);
			}

			Int4 trunc() const
			{
				return Int4((int)(x), (int)(y), (int)(z), (int)(w));
			}

			Float4 clamp(const Float4& low, const Float4& high) const
			{
				return Float4((x < low.x) ? low.x : ((x > high.x) ? high.x : x), (y < low.y) ? low.y : ((y > high.y) ? high.y : y), (z < low.z) ? low.z : ((z > high.z) ? high.z : z), (w < low.w) ? low.w : ((w > high.w) ? high.w : w));
			}

			Float4 quatMul(const Float4& o) const
			{
				return Float4(
					y*o.z - z*o.y + w*o.x + x*o.w,
					z*o.x - x*o.z + w*o.y + y*o.w,
					x*o.y - y*o.x + w*o.z + z*o.w,
					w*o.w - (x*o.x + y*o.y + z*o.z));
			}

			Float4 quatExp()
			{
				Float3 vv = xyz;
				float theta = vv.length();
				return Float4(vv * (sinf(theta) / theta), cosf(theta)) * ::exp(w);
			}

			Float4 quatLn()
			{
				float lq = length();
				Float3 vv = xyz;
				Float3 lv = vv.length();
				return Float4(vv / (lv * ::cosf(w / lq)), ::logf(lq));
			}

			static Float4 quatAxisAngle(Float3 axis, float angle)
			{
				return Float4(axis.normalize() * sinf(angle / 2), cosf(angle / 2));
			}

			static Float4 random(float lower = 0.0f, float upper = 1.0f)
			{
				float range = upper - lower;
				return Float4(
					rand() * range / RAND_MAX + lower,
					rand() * range / RAND_MAX + lower,
					rand() * range / RAND_MAX + lower,
					rand() * range / RAND_MAX + lower);
			}

			static const Float4 zero;
			static const Float4 xUnit;
			static const Float4 yUnit;
			static const Float4 zUnit;
			static const Float4 wUnit;
			static const Float4 one;

			static const Float4 identity;

		};
