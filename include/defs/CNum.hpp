#ifndef SMATH_TYPES_HPP
#define SMATH_TYPES_HPP

#include "defs/Num.h"

using i8  = signed char;
using i16 = signed short;
using i32 = signed int;
using i64 = signed long long;

using u   = unsigned int;
using u8  = unsigned char;
using u16 = unsigned short;
using u32 = unsigned int;
using u64 = unsigned long long;

using f32 = float;
using f64 = double;

/* define number type */
class CNum : Num
{
public:
  /* constructor method */
  inline CNum(i64 value) noexcept 
  { Num_i(value); }
  inline CNum(u64 value) noexcept 
  { Num_u(value); }
  inline CNum(f64 value) noexcept 
  { Num_f(value); }
  inline CNum() noexcept 
  { *static_cast<Num*>(this) = Num_i(0); }
  ~CNum() = default;

  /* cast to normal C/C++ number types */
  inline constexpr operator i64() const noexcept 
  { return static_cast<i64>(this->i); }
  inline constexpr operator i32() const noexcept 
  { return static_cast<i32>(this->i); }
  inline constexpr operator i16() const noexcept 
  { return static_cast<i16>(this->i); }
  inline constexpr operator i8 () const noexcept 
  { return static_cast<i8>(this->i); }

  inline constexpr operator u64() const noexcept 
  { return static_cast<u64>(this->u); }
  inline constexpr operator u32() const noexcept 
  { return static_cast<u32>(this->u); }
  inline constexpr operator u16() const noexcept 
  { return static_cast<u16>(this->u); }
  inline constexpr operator u8 () const noexcept 
  { return static_cast<u8>(this->u); }

  inline constexpr operator f64() const noexcept 
  { return static_cast<f64>(this->f); }
  inline constexpr operator f32() const noexcept 
  { return static_cast<f32>(this->f); }

  /* calculate function */
  inline void set(Num other) noexcept 
  { *this = other; }
  inline void add(Num other) noexcept 
  { Num_add(this, other); }
  inline void sub(Num other) noexcept 
  { Num_sub(this, other); }
  inline void mul(Num other) noexcept 
  { Num_mul(this, other); }
  inline void div(Num other) noexcept 
  { Num_div(this, other); }

  /* operation function */
  inline constexpr CNum &operator=(Num other) noexcept
  {
    *this = other;
    return *this;
  }

  inline CNum operator+(Num other) const noexcept
  {
    CNum result = *this;
    Num_add(&result, other);
    return result;
  }

  inline CNum operator-(Num other) const noexcept
  {
    CNum result = *this;
    Num_sub(&result, other);
    return result;
  }

  inline CNum operator*(Num other) const noexcept
  {
    CNum result = *this;
    Num_mul(&result, other);
    return result;
  }

  inline CNum operator/(Num other) const noexcept
  {
    CNum result = *this;
    Num_div(&result, other);
    return result;
  }

  inline constexpr bool operator==(Num other) const noexcept
  { return this->i == other.i && this->type == other.type; }

  inline constexpr bool operator!=(Num other) const noexcept
  { return !(this->i == other.i && this->type == other.type); }

  inline constexpr bool operator<=(Num other) const noexcept
  { return this->i < other.i || *this == other; }

  inline constexpr bool operator>=(Num other) const noexcept 
  { return this->i > other.i || *this == other; }

  inline constexpr bool operator<(Num other) const noexcept 
  { return this->i < other.i; }

  inline constexpr bool operator>(Num other) const noexcept 
  { return this->i > other.i; }
};

#endif
