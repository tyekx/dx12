#pragma once

#include "Float3.h"
#include "Float4.h"
#include <cmath>
#include <cfloat>

namespace Egg {
	namespace Math {

		class Float3;
		class Float4;

		class Float4x4
		{
		public:
			union
			{
				struct
				{
					float        _00, _01, _02, _03;
					float        _10, _11, _12, _13;
					float        _20, _21, _22, _23;
					float        _30, _31, _32, _33;
				};
				float m[4][4];
				float l[16];
			};

			Float4x4();

			Float4x4(
				float _00, float _01, float _02, float _03,
				float _10, float _11, float _12, float _13,
				float _20, float _21, float _22, float _23,
				float _30, float _31, float _32, float _33);

			static const Float4x4 Identity;

			Float4x4 elementwiseProduct(const Float4x4& o) const;

			Float4x4 operator+(const Float4x4& o) const;

			Float4x4 operator-(const Float4x4& o) const;

			Float4x4& assignElementwiseProduct(const Float4x4& o);

			Float4x4& operator*=(float s);

			Float4x4& operator/=(float s);

			Float4x4& operator+=(const Float4x4& o);

			Float4x4& operator-=(const Float4x4& o);

			Float4x4 mul(const Float4x4& o) const;

			Float4x4 operator<<(const Float4x4& o) const;

			Float4x4& operator <<=(const Float4x4& o);

			Float4x4 operator*(const Float4x4& o) const;

			Float4x4& operator*=(const Float4x4& o);

			Float4 mul(const Float4& v) const;

			Float4 transform(const Float4& v) const;

			Float4 operator*(const Float4& v) const;

			Float4x4 operator*(float s) const;

			static Float4x4 scaling(const Float3& factors);

			static Float4x4 translation(const Float3& offset);

			static Float4x4 rotation(const Float3& axis, float angle);

			static Float4x4 reflection(const Float4& plane);


			static Float4x4 view(const Float3& eye, const Float3& ahead, const Float3& up);

			static Float4x4 proj(float fovy, float aspect, float zn, float zf);

			Float4x4 transpose() const;

			Float4x4 _invert() const;

			Float4x4 invert() const;
		};

		inline Float4 operator*(const Float4& v, const Float4x4& m)
		{
			return m.transform(v);
		}

		inline const Float4& operator*=(Float4& v, const Float4x4& m)
		{
			v = m.transform(v);
			return v;
		}
	}
}


