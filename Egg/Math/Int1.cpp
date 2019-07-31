#include "Int1.h"
#include <cmath>

namespace Egg {
    namespace Math {

        Int1::Int1(int x) : x { x }{ }

        Int1 & Int1::operator=(const Int1 & rhs) noexcept {
            this->x = rhs.x;
            return *this;
        }

        Int1 & Int1::operator+=(const Int1 & rhs) noexcept {
            this->x += rhs.x;
            return *this;
        }

        Int1 & Int1::operator-=(const Int1 & rhs) noexcept {
            this->x -= rhs.x;
            return *this;
        }

        Int1 & Int1::operator/=(const Int1 & rhs) noexcept {
            this->x /= rhs.x;
            return *this;
        }

        Int1 & Int1::operator*=(const Int1 & rhs) noexcept {
            this->x *= rhs.x;
            return *this;
        }

        Int1 & Int1::operator%=(const Int1 & rhs) noexcept {
            this->x %= rhs.x;
            return *this;
        }

        Int1 & Int1::operator|=(const Int1 & rhs) noexcept {
            this->x |= rhs.x;
            return *this;
        }

        Int1 & Int1::operator&=(const Int1 & rhs) noexcept {
            this->x &= rhs.x;
            return *this;
        }

        Int1 & Int1::operator^=(const Int1 & rhs) noexcept {
            this->x ^= rhs.x;
            return *this;
        }

        Int1 & Int1::operator<<=(const Int1 & rhs) noexcept {
            this->x <<= rhs.x;
            return *this;
        }

        Int1 & Int1::operator>>=(const Int1 & rhs) noexcept {
            this->x >>= rhs.x;
            return *this;
        }

        Int1 Int1::operator*(const Int1 & rhs) const noexcept {
            return Int1 { this->x * rhs.x };
        }

        Int1 Int1::operator/(const Int1 & rhs) const noexcept {
            return Int1 { this->x / rhs.x };
        }

        Int1 Int1::operator+(const Int1 & rhs) const noexcept {
            return Int1 { this->x + rhs.x };
        }

        Int1 Int1::operator-(const Int1 & rhs) const noexcept {
            return Int1 { this->x - rhs.x };
        }

        Int1 Int1::operator%(const Int1 & rhs) const noexcept {
            return Int1 { this->x % rhs.x };
        }

        Int1 Int1::operator|(const Int1 & rhs) const noexcept {
            return Int1 { this->x | rhs.x };
        }

        Int1 Int1::operator&(const Int1 & rhs) const noexcept {
            return Int1 { this->x & rhs.x };
        }

        Int1 Int1::operator^(const Int1 & rhs) const noexcept {
            return Int1 { this->x ^ rhs.x };
        }

        Int1 Int1::operator<<(const Int1 & rhs) const noexcept {
            return Int1 { this->x << rhs.x };
        }

        Int1 Int1::operator>>(const Int1 & rhs) const noexcept {
            return Int1 { this->x >> rhs.x };
        }

        Int1 Int1::operator||(const Int1 & rhs) const noexcept {
            return Int1 { this->x || rhs.x };
        }

        Int1 Int1::operator&&(const Int1 & rhs) const noexcept {
            return Int1 { this->x && rhs.x };
        }

        Bool1 Int1::operator<(const Int1 & rhs) const noexcept {
            return Bool1 { x < rhs.x };
        }

        Bool1 Int1::operator>(const Int1 & rhs) const noexcept {
            return Bool1 { x > rhs.x };
        }

        Bool1 Int1::operator!=(const Int1 & rhs) const noexcept {
            return Bool1 { x != rhs.x };
        }

        Bool1 Int1::operator==(const Int1 & rhs) const noexcept {
            return Bool1 { x == rhs.x };
        }

        Bool1 Int1::operator>=(const Int1 & rhs) const noexcept {
            return Bool1 { x >= rhs.x };
        }

        Bool1 Int1::operator<=(const Int1 & rhs) const noexcept {
            return Bool1 { x <= rhs.x };
        }

        Int1 Int1::operator~() const noexcept {
            return Int1 { ~x };
        }

        Int1 Int1::operator!() const noexcept {
            return Int1 { !x };
        }

        Int1 Int1::operator++() noexcept {
            return Int1 { ++x };
        }

        Int1 Int1::operator++(int) noexcept {
            return Int1 { x++ };
        }

        Int1 Int1::operator--() noexcept {
            return Int1 { --x };
        }

        Int1 Int1::operator--(int) noexcept {
            return Int1 { x-- };
        }

        Int1 Int1::operator-() const noexcept {
            return Int1 { -x };
        }

    }
}

