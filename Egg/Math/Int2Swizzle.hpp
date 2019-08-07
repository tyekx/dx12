#pragma once
namespace Egg {
    namespace Math {

        template<typename I, typename B, int nBase, int s0 = 0, int s1 = 0>
        class Int2Swizzle {
            int v[nBase];
        public:
            operator I () const noexcept {
                return I {
                    (s0 >= 0) ? v[s0] : ((s0 == -1) ? 0.0f : 1.0f),
                    (s1 >= 0) ? v[s1] : ((s1 == -1) ? 0.0f : 1.0f)
                };
            }
        I operator*(const I & rhs) const noexcept {
            I t = *this;
            return t * rhs;
        }

        I operator/(const I & rhs) const noexcept {
            I t = *this;
            return t / rhs;
        }

        I operator+(const I & rhs) const noexcept {
            I t = *this;
            return t + rhs;
        }

        I operator-(const I & rhs) const noexcept {
            I t = *this;
            return t - rhs;
        }

        I operator%(const I & rhs) const noexcept {
            I t = *this;
            return t % rhs;
        }

        I operator|(const I & rhs) const noexcept {
            I t = *this;
            return t | rhs;
        }

        I operator&(const I & rhs) const noexcept {
            I t = *this;
            return t & rhs;
        }

        I operator^(const I & rhs) const noexcept {
            I t = *this;
            return t ^ rhs;
        }

        I operator<<(const I & rhs) const noexcept {
            I t = *this;
            return t << rhs;
        }

        I operator>>(const I & rhs) const noexcept {
            I t = *this;
            return t >> rhs;
        }

        I operator||(const I & rhs) const noexcept {
            I t = *this;
            return t || rhs;
        }

        I operator&&(const I & rhs) const noexcept {
            I t = *this;
            return t && rhs;
        }

        B operator<(const I & rhs) const noexcept {
            I t = *this;
            return B { t.x < rhs.x, t.y < rhs.y };
        }

        B operator>(const I & rhs) const noexcept {
            I t = *this;
            return B { t.x > rhs.x, t.y > rhs.y };
        }

        B operator!=(const I & rhs) const noexcept {
            I t = *this;
            return B { t.x != rhs.x, t.y != rhs.y };
        }

        B operator==(const I & rhs) const noexcept {
            I t = *this;
            return B { t.x == rhs.x, t.y == rhs.y };
        }

        B operator>=(const I & rhs) const noexcept {
            I t = *this;
            return B { t.x >= rhs.x, t.y >= rhs.y };
        }

        B operator<=(const I & rhs) const noexcept {
            I t = *this;
            return B { t.x <= rhs.x, t.y <= rhs.y };
        }

        I operator~() const noexcept {
            I t = *this;
            return I { ~t.x, ~t.y };
        }

        I operator!() const noexcept {
            I t = *this;
            return I { !t.x, !t.y };
        }

        I operator++() noexcept {
            I t = *this;
            return I { ++t.x, ++t.y };
        }

        I operator++(int) noexcept {
            I t = *this;
            return I { t.x++, t.y++ };
        }

        I operator--() noexcept {
            I t = *this;
            return I { --t.x, --t.y };
        }

        I operator--(int) noexcept {
            I t = *this;
            return I { t.x--, t.y-- };
        }


        I operator-() const noexcept {
            I t = *this;
            return I { -t.x, -t.y };
        }

        };
    }
}

