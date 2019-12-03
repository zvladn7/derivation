#ifndef BASEFUNCTIONS_HPP
#define BASEFUNCTIONS_HPP
#include <cmath>

class Const {
public:
  using Type = Const;

  Const(double x) :
    const_(x)
  {
  }

  double operator()(double) const
  {
    return const_;
  }
  operator double()
  {
    return const_;
  }
  double const_;
};

class Simple {
public:
  using Type = Simple;

  double operator()(double x) const
  {
    return x;
  }
};

template <class F1, class F2>
class Add {
public:
  using Type = Add<F1, F2>;

  Add(const F1& f1, const F2& f2) :
    fn1_(f1),
    fn2_(f2)
  {
  }

  double operator()(double x) const
  {
    return fn1_(x) + fn2_(x);
  }
  F1 fn1_;
  F2 fn2_;
};

template <class F1, class F2>
class Subtract {
public:
  using Type = Subtract<F1, F2>;
  Subtract(const F1& f1, const F2& f2) :
    fn1_(f1),
    fn2_(f2)
  {
  }

  double operator()(double x) const
  {
    return fn1_(x) - fn2_(x);
  }
  F1 fn1_;
  F2 fn2_;
};

template <class F1, class F2>
class Multiply {
public:
  using Type = Multiply<F1, F2>;

  Multiply(const F1& f1, const F2& f2) :
    fn1_(f1),
    fn2_(f2)
  {
  }

  double operator()(double x) const
  {
    return fn1_(x) * fn2_(x);
  }
  F1 fn1_;
  F2 fn2_;
};

template <class F>
class Power {
public:
  using Type = Power<F>;

  Power(const F& f, double n)
    : fn_(f), n_(n)
  {
  }

  double operator()(double x) const
  {
    return pow(fn_(x), n_);
  }
  F fn_;
  double n_;
};
#endif // BASEFUNCTIONS_HPP
