#ifndef SMATH_TYPES_HPP
#define SMATH_TYPES_HPP

#include "defs/typedef.h"

using i8    = signed char;
using i16   = signed short;
using i32   = signed int;
using i64   = signed long long;

using uint  = unsigned int;
using u8    = unsigned char;
using u16   = unsigned short;
using u32   = unsigned int;
using u64   = unsigned long long;

using f32   = float;
using f64   = double;

/* define number type */
class CNum: Num {
public:
  /* constructor method */
  inline constexpr CNum(i64 value)  noexcept { Num_i(value); }
  inline constexpr CNum(u64 value)  noexcept { Num_u(value); }
  inline constexpr CNum(f64 value)  noexcept { Num_f(value); }
  inline constexpr CNum()           noexcept { Num_i(0);     }
  ~CNum() = default;

  /* cast to normal C/C++ number types */
  inline constexpr operator i64()   noexcept { return Num_asi(*this); }
  inline constexpr operator u64()   noexcept { return Num_asu(*this); }
  inline constexpr operator f64()   noexcept { return Num_asf(*this); }
  inline constexpr operator Num()   noexcept { return Num{ this->type, this->i }; }

  /* calculate function */
  inline constexpr void set(Num other) noexcept { Num_set(this, other); }
  inline constexpr void add(Num other) noexcept { Num_add(this, other); }
  inline constexpr void sub(Num other) noexcept { Num_sub(this, other); }
  inline constexpr void mul(Num other) noexcept { Num_mul(this, other); }
  inline constexpr void div(Num other) noexcept { Num_div(this, other); }

  /* operation function */
  inline constexpr CNum& operator=(Num other) noexcept { 
    Num_set(this, other); 
    return *this;
  }

  inline constexpr CNum operator+(Num other) const noexcept {
    CNum result = *this; Num_add(&result, other);
    return result;
  }

  inline constexpr CNum operator-(Num other) const noexcept {
    CNum result = *this; Num_sub(&result, other);
    return result;
  }  
  
  inline constexpr CNum operator*(Num other) const noexcept {
    CNum result = *this; Num_mul(&result, other);
    return result;
  }  
  
  inline constexpr CNum operator/(Num other) const noexcept {
    CNum result = *this; Num_div(&result, other);
    return result;
  }

  inline constexpr bool operator==(Num other) const noexcept { 
    return this->i == other.i && this->type == other.type; 
  }

  inline constexpr bool operator!=(Num other) const noexcept { 
    return !(this->i == other.i && this->type == other.type); 
  }

  inline constexpr bool operator<=(Num other)  const noexcept { 
    return this->i < other.i || *this == other; 
  }

  inline constexpr bool operator>=(Num other)  const noexcept { 
    return this->i > other.i || *this == other; 
  }

  inline constexpr bool operator<(Num other)  const noexcept { return this->i < other.i; }
  inline constexpr bool operator>(Num other)  const noexcept { return this->i > other.i; }
};

#endif
