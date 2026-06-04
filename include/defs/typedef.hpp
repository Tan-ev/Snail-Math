#ifndef SMATH_TYPES_HPP
#define SMATH_TYPES_HPP

namespace smath {
  using i     = signed int;
  using i8    = signed char;
  using i16   = signed short;
  using i32   = signed int;
  using i64   = signed long long;

  using u     = unsigned int;
  using u8    = unsigned char;
  using u16   = unsigned short;
  using u32   = unsigned int;
  using u64   = unsigned long long;

  using f32   = float;
  using f64   = double;

  class num {
  public:
    enum class Type { Signed, Unsigned, Float };

    Type type;
    union { i64 i; u64 u; f64 f; };

    constexpr num(i64 val)  noexcept : type(Type::Signed), i(val) {}
    constexpr num(u64 val)  noexcept : type(Type::Unsigned), u(val) {}
    constexpr num(f64 val)  noexcept : type(Type::Float), f(val) {}
    constexpr num()         noexcept : type(Type::Signed), i(0) {}

    /* cast to C/C++ number type */
    constexpr operator i64() const noexcept {
      if (type == Type::Signed)   return (i64)i;
      if (type == Type::Unsigned) return (i64)u;
      return (i64)f;
    }

    constexpr operator u64() const noexcept {
      if (type == Type::Signed)   return (u64)i;
      if (type == Type::Unsigned) return (u64)u;
      return (u64)f;
    }

    constexpr operator f64() const noexcept {
      if (type == Type::Signed)   return (f64)i;
      if (type == Type::Unsigned) return (f64)u;
      return (f64)f;
    }

    /* assign operation */
    constexpr num& operator=(i64 val) noexcept {
      type = Type::Signed; i = val;
      return *this; 
    }

    constexpr num& operator=(u64 val) noexcept {
      type = Type::Unsigned; u = val;
      return *this;
    }

    constexpr num& operator=(f64 val) noexcept {
      type = Type::Float; f = val;
      return *this;
    }

    /* calculate operation */
    constexpr num operator+(num other) const noexcept {
      if (this->type == Type::Float || other.type == Type::Float) {
        return (f64)*this + (f64)other;
      }

      if (this->type == Type::Unsigned || other.type == Type::Unsigned) {
        return (u64)*this + (u64)other;
      }

      return (i64)*this + (i64)other;
    }

    constexpr num operator-(num other) const noexcept {
      if (this->type == Type::Float || other.type == Type::Float) {
        return (f64)*this - (f64)other;
      }

      if (this->type == Type::Unsigned || other.type == Type::Unsigned) {
        return (u64)*this - (u64)other;
      }

      return (i64)*this - (i64)other;
    }

    constexpr num operator*(num other) const noexcept {
      if (this->type == Type::Float || other.type == Type::Float) {
        return (f64)*this * (f64)other;
      }

      if (this->type == Type::Unsigned || other.type == Type::Unsigned) {
        return (u64)*this * (u64)other;
      }

      return (i64)*this * (i64)other;
    }

    constexpr num operator/(num other) const noexcept {
      /* can't divide with 0 */
      if ((f64)other == 0.0) return num((i64)0);

      if (this->type == Type::Float || other.type == Type::Float) {
        return (f64)*this / (f64)other;
      }

      if (this->type == Type::Unsigned || other.type == Type::Unsigned) {
        return (u64)*this / (u64)other;
      }

      return (i64)*this / (i64)other;
    }
  };
} 

#endif
