#ifndef SMATH_TYPES_H
#define SMATH_TYPES_H

typedef signed int i;
typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long long i64;

typedef unsigned int u;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef float f32;
typedef double f64;

typedef enum
{
  Num_Signed,
  Num_Unsigned,
  Num_Float
} NumType;

typedef struct 
{
  NumType type;
  union
  {
    i64 i;
    u64 u;
    f64 f;
  };
} Num;

inline static Num Num_i(i64 val)
{
  Num new_Num;
  new_Num.type = Num_Signed;
  new_Num.i = val;
  return new_Num;
}

inline static Num Num_u(u64 val)
{
  Num new_Num;
  new_Num.type = Num_Unsigned;
  new_Num.u = val;
  return new_Num;
}

inline static Num Num_f(f64 val)
{
  Num new_Num;
  new_Num.type = Num_Float;
  new_Num.f = val;
  return new_Num;
}

inline static void Num_set(Num *obj, Num other)
{
  if (!obj)
  { return; }

  obj->type = other.type;
  obj->i = other.i;
}

inline static constexpr i64 Num_asi(Num obj)
{
  if (obj.type == Num_Float)
  { return (i64)obj.f; }
  if (obj.type == Num_Unsigned)
  { return (i64)obj.u; }
  return (i64)obj.i;
}

inline static constexpr u64 Num_asu(Num obj)
{
  if (obj.type == Num_Float)
  { return (u64)obj.f; }
  if (obj.type == Num_Unsigned)
  { return (u64)obj.u; }
  return (u64)obj.i;
}

inline static constexpr f64 Num_asf(Num obj)
{
  if (obj.type == Num_Float)
  { return (f64)obj.f; }
  if (obj.type == Num_Unsigned)
  { return (f64)obj.u; }
  return (f64)obj.i;
}

inline static constexpr void Num_add(Num *obj, Num other)
{
  if (!obj)
  { return; }

  if (obj->type == Num_Float || other.type == Num_Float)
  {
    obj->f = Num_asf(*obj) + Num_asf(other);
    obj->type = Num_Float;
  }
  else if (obj->type == Num_Unsigned || other.type == Num_Unsigned)
  {
    obj->u = Num_asu(*obj) + Num_asu(other);
    obj->type = Num_Unsigned;
  }
  else
  {
    obj->i += other.i;
    obj->type = Num_Signed;
  }
}

inline static constexpr void Num_sub(Num *obj, Num other)
{
  if (!obj)
  { return; }

  if (obj->type == Num_Float || other.type == Num_Float)
  {
    obj->f = Num_asf(*obj) - Num_asf(other);
    obj->type = Num_Float;
  }
  else if (obj->type == Num_Unsigned || other.type == Num_Unsigned)
  {
    obj->u = Num_asu(*obj) - Num_asu(other);
    obj->type = Num_Unsigned;
  }
  else
  {
    obj->i -= other.i;
    obj->type = Num_Signed;
  }
}

inline static constexpr void Num_mul(Num *obj, Num other)
{
  if (!obj)
  { return; }

  if (obj->type == Num_Float || other.type == Num_Float)
  {
    obj->f = Num_asf(*obj) * Num_asf(other);
    obj->type = Num_Float;
  }
  else if (obj->type == Num_Unsigned || other.type == Num_Unsigned)
  {
    obj->u = Num_asu(*obj) * Num_asu(other);
    obj->type = Num_Unsigned;
  }
  else
  {
    obj->i *= other.i;
    obj->type = Num_Signed;
  }
}

inline static constexpr void Num_div(Num *obj, Num other)
{
  if (!obj)
  { return; }

  if (other.type != Num_Float && other.i == 0)
  {
    return;
  }

  if (obj->type == Num_Float || other.type == Num_Float)
  {
    obj->f = Num_asf(*obj) / Num_asf(other);
    obj->type = Num_Float;
  }
  else if (obj->type == Num_Unsigned || other.type == Num_Unsigned)
  {
    obj->u = Num_asu(*obj) / Num_asu(other);
    obj->type = Num_Unsigned;
  }
  else
  {
    obj->i /= other.i;
    obj->type = Num_Signed;
  }
}

#ifndef __cplusplus

#define NUM(data) _Generic((data), \
  i8: Num_i,                     \
  i16: Num_i,                    \
  i32: Num_i,                    \
  i64: Num_i,                    \
  u8: Num_u,                     \
  u16: Num_u,                    \
  u32: Num_u,                    \
  u64: Num_u,                    \
  f32: Num_f,                    \
  f64: Num_f)(data)
#define AS(type, data) _Generic((type)0, \
  i8: (i8)Num_asi(data),               \
  i16: (i16)Num_asi(data),             \
  i32: (i32)Num_asi(data),             \
  i64: (i64)Num_asi(data),             \
  u8: (u8)Num_asu(data),               \
  u16: (u16)Num_asu(data),             \
  u32: (u32)Num_asu(data),             \
  u64: (u64)Num_asu(data),             \
  f32: (f32)Num_asf(data),             \
  f64: (f64)Num_asf(data), )
  
#endif

#define SET(obj, other) Num_set(obj, other)
#define ADD(obj, other) Num_add(obj, other)
#define SUB(obj, other) Num_sub(obj, other)
#define MUL(obj, other) Num_mul(obj, other)
#define DIV(obj, other) Num_div(obj, other)

#endif
