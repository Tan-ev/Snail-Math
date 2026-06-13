#include "primary.h"
#include "defs/Num.h"
#include "defs/constdef.h"

#include "defs/CNum.hpp"

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

    case Num_Unsigned:
      /* already positive */
      break;

    case Num_Float:
      if (val.f < 0.0)
      { val.f = -val.f; }
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
      break;

    case Num_Unsigned:
      val.i = -static_cast<i64>(val.u);
      val.type = Num_Signed;
      break;

    case Num_Float:
      val.f = -val.f;
      break;
    }

    return val;
  }
  
  inline i8 sign(Num val) noexcept
  {
    switch (val.type)
    {
    case Num_Signed:
      if (val.i < 0)
      { return SM_MINUS; }
      if (val.i > 0)
      { return SM_PLUS; }
      break;

    case Num_Unsigned:
      if (val.u > 0)
      { return SM_PLUS; }
      break;

    case Num_Float:
      if (val.f < 0.0)
      { return SM_MINUS; }
      if (val.f > 0.0)
      { return SM_PLUS; }
      break;
    }

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
    return Num_f(result);
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
    { floored_val = static_cast<i64>(int_val-1); }
    else 
    { floored_val = static_cast<i64>(int_val); }

    /* move comma back */
    f64 result = floored_val / multi;

    return Num_f(result);
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
      result = floor(place, Num_f(rounded_val));
    }
    else
    {
      f64 rounded_val = float_num - 0.5;
      result = ceil(place, Num_f(rounded_val));
    }

    return result;
  }

  inline i8 cmp_ii(Num left, Num right) noexcept
  {
    if (left.i < right.i)
    { return SM_LT; }
    if (left.i > right.i)
    { return SM_GT; }
    return SM_EQ;
  }

  inline i8 cmp_iu(Num left, Num right) noexcept
  {
    if (left.i < 0)
    { return SM_LT; }

    u64 converted = static_cast<u64>(left.i);
    if (converted < right.u)
    { return SM_LT; }
    if (converted > right.u)
    { return SM_GT; }
    return SM_EQ;
  }

  inline i8 cmp_if(Num left, Num right) noexcept
  {
    long double casted_lval = static_cast<long double>(left.i);
    long double casted_rval = static_cast<long double>(right.f);

    if (casted_lval < casted_rval)
    { return SM_LT; }
    if (casted_lval > casted_rval)
    { return SM_GT; }
    return SM_EQ;
  }

  inline i8 cmp_ui(Num left, Num right) noexcept
  {
    if (right.i < 0)
    { return SM_GT; }

    u64 converted = static_cast<u64>(right.i);
    if (left.u < converted)
    { return SM_LT; }
    if (left.u > converted)
    { return SM_GT; }
    return SM_EQ;
  }

  inline i8 cmp_uu(Num left, Num right) noexcept
  {
    if (left.u < right.u)
    { return SM_LT; }
    if (left.u > right.u)
    { return SM_GT; }
    return SM_EQ;
  }

  inline i8 cmp_uf(Num left, Num right) noexcept
  {
    long double casted_lval = static_cast<long double>(left.u);
    long double casted_rval = static_cast<long double>(right.f);

    if (casted_lval < casted_rval)
    { return SM_LT; }
    if (casted_lval > casted_rval)
    { return SM_GT; }
    return SM_EQ;
  }  

  inline i8 cmp_fi(Num left, Num right) noexcept
  {
    long double casted_lval = static_cast<long double>(left.f);
    long double casted_rval = static_cast<long double>(right.i);

    if (casted_lval < casted_rval)
    { return SM_LT; }
    if (casted_lval > casted_rval)
    { return SM_GT; }
    return SM_EQ;
  }
  
  inline i8 cmp_fu(Num left, Num right) noexcept
  {
    long double casted_lval = static_cast<long double>(left.f);
    long double casted_rval = static_cast<long double>(right.u);

    if (casted_lval < casted_rval)
    { return SM_LT; }
    if (casted_lval > casted_rval)
    { return SM_GT; }
    return SM_EQ;
  }

  inline i8 cmp_ff(Num left, Num right) noexcept
  {
    if (left.f < right.f)
    { return SM_LT; }
    if (left.f > right.f)
    { return SM_GT; }
    return SM_EQ;
  }

  inline i8 cmp(Num lval, Num rval) noexcept
  {
    switch (lval.type)
    {
    case Num_Signed: switch (rval.type)
      {
      case Num_Signed:    return cmp_ii(lval, rval);
      case Num_Unsigned:  return cmp_iu(lval, rval);
      case Num_Float:     return cmp_if(lval, rval);
      }
      break;

    case Num_Unsigned: switch (rval.type)
      {
      case Num_Signed:    return cmp_ui(lval, rval);
      case Num_Unsigned:  return cmp_uu(lval, rval);
      case Num_Float:     return cmp_uf(lval, rval);
      }
      break;

    case Num_Float: switch (rval.type)
      {
      case Num_Signed:    return cmp_fi(lval, rval);
      case Num_Unsigned:  return cmp_fu(lval, rval);
      case Num_Float:     return cmp_ff(lval, rval);
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
    DIV(&result, Num_i(2)); 
    ADD(&result, lval); 

    return result;
  }

  inline Num fmod(Num left, Num right) noexcept
  {
    f64 lval = Num_asf(left);
    f64 rval = Num_asf(right);

    if (rval == 0.0)
    { return left; }

    i64 q = static_cast<i64>(lval / rval);

    return Num_f(
      lval - static_cast<f64>(q) * rval
    );
  }

  Num mod(Num lval, Num rval) noexcept
  {
    if (lval.type == Num_Float || rval.type == Num_Float)
    { return fmod(lval, rval); }

    if (lval.type == Num_Unsigned || rval.type == Num_Unsigned)
    {
      u64 divisor = Num_asu(rval);

      if (divisor == 0)
      { return lval; }

      return Num_u(Num_asu(lval) % divisor);
    }

    i64 divisor = Num_asi(rval);

    if (divisor == 0)
    { return lval; }

    return Num_i(Num_asi(lval) % divisor);
  }
}

extern "C" 
{
  Num sm_abs(Num val) noexcept
  { return alg::abs(val); }
  Num sm_neg(Num val) noexcept
  { return alg::neg(val); }
  i8 sm_sign(Num val) noexcept
  { return alg::sign(val); }

  Num sm_ceil(i16 place, Num val) noexcept
  { return alg::ceil(place, val); }
  Num sm_floor(i16 place, Num val) noexcept
  { return alg::floor(place, val); }
  Num sm_round(i16 place, Num val) noexcept
  { return alg::round(place, val); }

  i8 sm_cmpii(Num lval, Num rval) noexcept
  { return alg::cmp_ii(lval, rval); }
  i8 sm_cmpiu(Num lval, Num rval) noexcept
  { return alg::cmp_iu(lval, rval); }
  i8 sm_cmpif(Num lval, Num rval) noexcept
  { return alg::cmp_if(lval, rval); }

  i8 sm_cmpui(Num lval, Num rval) noexcept
  { return alg::cmp_ui(lval, rval); }
  i8 sm_cmpuu(Num lval, Num rval) noexcept
  { return alg::cmp_uu(lval, rval); }
  i8 sm_cmpuf(Num lval, Num rval) noexcept
  { return alg::cmp_uf(lval, rval); }

  i8 sm_cmpfi(Num lval, Num rval) noexcept
  { return alg::cmp_fi(lval, rval); }
  i8 sm_cmpfu(Num lval, Num rval) noexcept
  { return alg::cmp_fu(lval, rval); }
  i8 sm_cmpff(Num lval, Num rval) noexcept
  { return alg::cmp_ff(lval, rval); }

  i8 sm_cmp(Num lval, Num rval) noexcept
  { return alg::cmp(lval, rval); }

  Num sm_min(Num lval, Num rval) noexcept
  { return alg::min(lval, rval); }
  Num sm_max(Num lval, Num rval) noexcept
  { return alg::max(lval, rval); }
  Num sm_clamp(Num val, Num min_val, Num max_val) noexcept
  { return alg::clamp(val, min_val, max_val); }
  Num sm_avr(Num lval, Num rval) noexcept
  { return alg::avr(lval, rval); }
  Num sm_fmod(Num lval, Num rval) noexcept
  { return alg::fmod(lval, rval); }
  Num sm_mod(Num lval, Num rval) noexcept
  { return alg::mod(lval, rval); }
}
