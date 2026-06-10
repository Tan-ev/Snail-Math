#include "primary.h"
#include "defs/using.hpp"
#include <vector>

namespace alg
{
  inline Num abs(Num val) noexcept
  {
    switch (val.type)
    {
    case Num_Signed:
      if (val.i < 0)
      { val.i = -val.i; }

      break;

    case Num_Float:
      if (val.f < 0.0) 
      { val.f = -val.f; }

      break;

    case Num_Unsigned:
      /* already non-negative */
      break;
    }

    return val;
  }

  inline Num neg(Num val) noexcept 
  {
    switch (val.type)
    {
    case Num_Signed:
      val.i = -val.i;
      /* dont check for signed num type */
      break;

    case Num_Unsigned:
      val.u = -(i64)val.u;
      /* plus negative alway be minus */
      val.type = Num_Signed;
      break;
    case Num_Float:
      val.f = -val.f;
      /* float can store both minus, plus val */
      break;
    }

    return val;
  }
  
  inline i8 sign(Num val) noexcept
  {
    if ((i64)val.i < 0) 
    { return SM_MINUS; }
    if ((i64)val.i > 0)
    { return SM_PLUS; }

    return SM_ZERO;
  }

  inline Num ceil(i16 place, Num val) noexcept
  {
    f64 multi = 1.0;
    if (place > 0)
    {
      for (i16 i = 0; i < place; i++)
      { multi *= 10.0; }
    }
    else if (place < 0)
    {
      for (i16 i = 0; i > place; i--)
      { multi /= 10.0; }
    }

    f64 float_num;
    if (val.type == Num_Float)
    { float_num = val.f; }
    else if (val.type == Num_Unsigned)
    { float_num = static_cast<f64>(val.u); }
    else
    { float_num = static_cast<f64>(val.i); }

    /* move comma in digit */
    float_num *= multi;

    i64 int_val = static_cast<i64>(float_num);
    f64 ceiled_val;

    if (float_num > static_cast<f64>(int_val))
    { ceiled_val = static_cast<i64>(int_val+1); }
    else 
    { ceiled_val = static_cast<i64>(int_val); }

    /* move comma back */
    f64 result = ceiled_val / multi;
    return NUM(result);
  }

  inline Num floor(i16 place, Num val) noexcept
  {
    f64 multi = 1.0;
    if (place > 0)
    {
      for (i16 i = 0; i < place; i++)
      { multi *= 10.0; }
    }
    else if (place < 0)
    {
      for (i16 i = 0; i > place; i--)
      { multi /= 10.0; }
    }

    f64 float_num;
    if (val.type == Num_Float)
    { float_num = val.f; }
    else if (val.type == Num_Unsigned)
    { float_num = static_cast<f64>(val.u); }
    else
    { float_num = static_cast<f64>(val.i); }

    /* move comma */
    float_num *= multi;

    i64 int_val = static_cast<i64>(float_num);
    f64 floored_val;

    if (float_num < static_cast<f64>(int_val))
    { floored_val = static_cast<i64>(int_val+1); }
    else 
    { floored_val = static_cast<i64>(int_val); }

    /* move comma back */
    f64 result = floored_val / multi;

    return NUM(result);
  }

  inline Num round(i16 place, Num val) noexcept
  {
    f64 float_num;
    if (val.type == Num_Float)
    { float_num = static_cast<f64>(val.f); }
    else if (val.type == Num_Unsigned)
    { float_num = static_cast<f64>(val.u); }
    else
    { float_num = static_cast<f64>(val.i); }

    Num result;
    if (float_num >= 0.0)
    {
      f64 rounded_val = float_num + 0.5;
      result = floor(place, NUM(rounded_val));
    }
    else
    {
      f64 rounded_val = float_num - 0.5;
      result = ceil(place, NUM(rounded_val));
    }

    return result;
  }

  inline i8 cmp_ii(i64 left, i64 right) noexcept
  {
    if (left < right)
    { return SM_LT; }
    if (left > right)
    { return SM_GT; }
    return SM_EQ;
  }

  inline i8 cmp_uu(u64 left, u64 right) noexcept
  {
    if (left < right)
    { return SM_LT; }
    if (left > right)
    { return SM_GT; }
    return SM_EQ;
  }

  inline i8 cmp_ff(f64 left, f64 right) noexcept
  {
    if (left < right)
    { return SM_LT; }
    if (left > right)
    { return SM_GT; }
    return SM_EQ;
  }

  inline i8 cmp_iu(i64 left, u64 right) noexcept
  {
    if (left < 0)
    { return SM_LT; }

    return cmp_uu(
      static_cast<u64>(left), 
      right
    );
  }

  inline i8 cmp_ui(u64 left, i64 right) noexcept
  {
    if (right < 0)
    { return SM_GT; }

    return cmp_uu(
      static_cast<u64>(right), 
      left
    );
  }

  inline i8 cmp_uf(u64 left, f64 right) noexcept
  {
    long double casted_lval = static_cast<long double>(left);
    long double casted_rval = static_cast<long double>(right);

    if (casted_lval < casted_rval)
    { return SM_LT; }
    if (casted_lval > casted_rval)
    { return SM_GT; }

    return SM_EQ;
  }  
  
  inline i8 cmp_fu(f64 left, u64 right) noexcept
  {
    long double casted_lval = static_cast<long double>(left);
    long double casted_rval = static_cast<long double>(right);

    if (casted_lval < casted_rval)
    { return SM_LT; }
    if (casted_lval > casted_rval)
    { return SM_GT; }

    return SM_EQ;
  }


  inline i8 cmp_if(i64 left, f64 right) noexcept
  {
    long double casted_lval = static_cast<long double>(left);
    long double casted_rval = static_cast<long double>(right);

    if (casted_lval < casted_rval)
    { return SM_LT; }
    if (casted_lval > casted_rval)
    { return SM_GT; }

    return SM_EQ;
  }

  inline i8 cmp_fi(f64 left, i64 right) noexcept
  {
    long double casted_lval = static_cast<long double>(left);
    long double casted_rval = static_cast<long double>(right);

    if (casted_lval < casted_rval)
    { return SM_LT; }
    if (casted_lval > casted_rval)
    { return SM_GT; }

    return SM_EQ;
  }

  inline i8 cmp(Num lval, Num rval) noexcept
  {
    switch (lval.type)
    {
    case Num_Signed:
      switch (rval.type)
      {
      case Num_Signed:
        return cmp_ii(lval.i, rval.i);

      case Num_Unsigned:
        return cmp_iu(lval.i, rval.u);

      case Num_Float:
        return cmp_if(lval.i, rval.f);
      }
      break;

    case Num_Unsigned:
      switch (rval.type)
      {
      case Num_Signed:
        return cmp_ui(lval.u, rval.i);

      case Num_Unsigned:
        return cmp_uu(lval.u, rval.u);

      case Num_Float:
        return cmp_uf(lval.u, rval.f);
      }
      break;

    case Num_Float:
      switch (rval.type)
      {
      case Num_Signed:
        return cmp_fi(lval.f, rval.i);

      case Num_Unsigned:
        return cmp_fu(lval.f, rval.u);

      case Num_Float:
        return cmp_ff(lval.f, rval.f);
      }
      break;
    }

    return SM_EQ;
  }

  inline Num min(Num lval, Num rval) noexcept 
  {
    if (cmp(lval, rval) == SM_LT) 
    { return lval; }
    return rval;
  }

  inline Num max(Num lval, Num rval) noexcept 
  {
    if (cmp(lval, rval) == SM_GT) 
    { return lval; }
    return rval;
  }

  inline Num clamp(Num val, Num min_val, Num max_val) noexcept
  { return min(max_val, max(min_val, val)); }

  inline Num avr(Num lval, Num rval) noexcept
  {
    if (cmp(lval, rval) == SM_EQ)
    { return lval; }

    Num result = rval;

    SUB(&result, lval); 
    DIV(&result, NUM(2)); 
    ADD(&result, lval); 

    return result;
  }

  inline f64 fmod(f64 left, f64 right) noexcept
  {
    if (right == 0.0)
    { return left; }
    i64 int_div = static_cast<i64>(left / right);
    return left - static_cast<f64>(int_div) * right;
  }

  Num mod(Num lval, Num rval) noexcept
  {
    if (lval.type == Num_Float || rval.type == Num_Float)
    { return Num_f(fmod(Num_asf(lval),Num_asf(rval))); }
    
    if (lval.type == Num_Unsigned || rval.type == Num_Unsigned)
    { return Num_u(Num_asu(lval) % Num_asu(rval)); }

    return Num_i( Num_asi(lval) % Num_asi(rval));
  }
}
