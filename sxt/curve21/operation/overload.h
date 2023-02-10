#pragma once

#include <cstdint>

namespace sxt::s25t {
class element;
}

namespace sxt::c21t {
struct element_p3;

//--------------------------------------------------------------------------------------------------
// operator+
//--------------------------------------------------------------------------------------------------
element_p3 operator+(const element_p3& lhs, const element_p3& rhs) noexcept;

//--------------------------------------------------------------------------------------------------
// operator-
//--------------------------------------------------------------------------------------------------
element_p3 operator-(const element_p3& lhs, const element_p3& rhs) noexcept;

element_p3 operator-(const element_p3& p) noexcept;

//--------------------------------------------------------------------------------------------------
// operator*
//--------------------------------------------------------------------------------------------------
element_p3 operator*(const s25t::element& lhs, const element_p3& rhs) noexcept;

element_p3 operator*(uint64_t lhs, const element_p3& rhs) noexcept;

//--------------------------------------------------------------------------------------------------
// operator+=
//--------------------------------------------------------------------------------------------------
element_p3& operator+=(element_p3& lhs, const element_p3& rhs) noexcept;

//--------------------------------------------------------------------------------------------------
// operator-=
//--------------------------------------------------------------------------------------------------
element_p3& operator-=(element_p3& lhs, const element_p3& rhs) noexcept;
} // namespace sxt::c21t