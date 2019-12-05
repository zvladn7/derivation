#ifndef OPERATIONS_HPP
#define OPERATIONS_HPP
#include <type_traits>
#include "basefunctions.hpp"

template <class F1, class F2>
Add<F1, F2> operator+(const F1& f1, const F2& f2)
{
  return Add<F1, F2>(f1, f2);
}

template <class F>
typename std::enable_if<!std::is_arithmetic<F>::value, Add<F, Const>>::type operator+(double value, const F& f)
{
  return Add<F, Const>(f, Const(value));
}

template <class F>
typename std::enable_if<!std::is_arithmetic<F>::value, Add<F, Const>>::type operator+(const F& f, int value)
{
  return Add<F, Const>(f, Const(value));
}

template <class F>
typename std::enable_if<!std::is_arithmetic<F>::value, Add<F, Const>>::type operator+(int value, const F& f)
{
  return Add<F, Const>(f, Const(value));
}

template <class F>
typename std::enable_if<!std::is_arithmetic<F>::value, Add<F, Const>>::type operator+(const F& f, double value)
{
  return Add<F, Const>(f, Const(value));
}

template <class F1, class F2>
Subtract<F1, F2> operator-(const F1& f1, const F2& f2)
{
  return Subtract<F1, F2>(f1, f2);
}

template <class F>
typename std::enable_if<!std::is_arithmetic<F>::value, Subtract<F, Const>>::type operator-(const F& f, double value)
{
  return Subtract<F, Const>(f, Const(value));
}

template <class F>
typename std::enable_if<!std::is_arithmetic<F>::value, Subtract<Const, F>>::type operator-(double value, const F& f)
{
  return Subtract<Const, F>(Const(value), f);
}

template <class F>
typename std::enable_if<!std::is_arithmetic<F>::value, Subtract<F, Const>>::type operator-(const F& f, int value)
{
  return Subtract<F, Const>(f, Const(value));
}

template <class F>
typename std::enable_if<!std::is_arithmetic<F>::value, Subtract<Const, F>>::type operator-(int value, const F& f)
{
  return Subtract<Const, F>(Const(value), f);
}

template <class F1, class F2>
Multiply<F1, F2> operator*(const F1& f1, const F2& f2)
{
  return Multiply<F1, F2>(f1, f2);
}

template <class F>
typename std::enable_if<!std::is_arithmetic<F>::value, Multiply<F, Const>>::type operator*(const F& f, double value)
{
  return Multiply<F, Const>(f, Const(value));
}

template <class F>
typename std::enable_if<!std::is_arithmetic<F>::value, Multiply<F, Const>>::type operator*(double value, const F& f)
{
  return Multiply<F, Const>(f, Const(value));
}

template <class F>
typename std::enable_if<!std::is_arithmetic<F>::value, Multiply<F, Const>>::type operator*(const F& f, int value)
{
  return Multiply<F, Const>(f, Const(value));
}

template <class F>
typename std::enable_if<!std::is_arithmetic<F>::value, Multiply<F, Const>>::type operator*(int value, const F& f)
{
  return Multiply<F, Const>(f, Const(value));
}

template <class F, class Numeric>
Power<F> Pow(const F& f, Numeric n)
{
  return Power<F>(f, n);
}

inline double Pow(double x, double y)
{
  return pow(x, y);
}

extern Simple X;


#endif // OPERATIONS_HPP
