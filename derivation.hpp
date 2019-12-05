#ifndef DERIVATION_HPP
#define DERIVATION_HPP
#include <functional>
#include "operations.hpp"
#include "basefunctions.hpp"

extern Simple X;

template <class F>
class Derivative {
public:
  using Type = std::function<double (double)>;

  Derivative(const F& f, double dx = 1e-3) :
    f_(f),
    dx_(dx)
  {
  }

  double operator()(double x) const
  {
    return (f_(x + dx_) - f_(x)) / dx_;
  }

  Type calculation() const
  {
    return [this](double x) -> double
    {
      return (f_(x + dx_) - f_(x)) / dx_;
    };
  }
  F f_;
  double dx_;
};

template<>
class Derivative<Const> {
public:
  using Type = Const;

  Derivative<Const> (Const)
  {
  }

  double operator()(double) const
  {
    return 0;
  }
  Type calculation() const
  {
    return Const(0);
  }
};

template<>
class Derivative<Simple> {
public:
  using Type = Const;

  Derivative<Simple>(Simple)
  {
  }

  double operator()(double) const
  {
    return 1;
  }
  Type calculation() const
  {
    return Const(1);
  }
};

template <class F1, class F2>
class Derivative< Add<F1, F2> > {
public:
  using Type = Add<typename Derivative<F1>::Type, typename Derivative<F2>::Type>;

  Derivative<Add<F1, F2>> (const Add<F1, F2>& f) :
    df1_(f.fn1_),
    df2_(f.fn2_)
  {
  }

  double operator()(double x) const
  {
    return df1_(x) + df2_(x);
  }

  Type calculation() const
  {
    return df1_.calculation() + df2_.calculation();
  }
  Derivative<F1> df1_;
  Derivative<F2> df2_;
};

template <class F1, class F2>
class Derivative< Subtract<F1, F2> > {
public:
  using Type = Subtract<typename Derivative<F1>::Type, typename Derivative<F2>::Type>;

  Derivative< Subtract<F1, F2> > (const Subtract<F1, F2>& f) :
    df1_(f.fn1_),
    df2_(f.fn2_)
  {
  }

  double operator()(double x) const
  {
    return df1_(x) - df2_(x);
  }

  Type calculation() const
  {
    return df1_.calculation() - df2_.calculation();
  }
  Derivative<F1> df1_;
  Derivative<F2> df2_;
};


template <class F1, class F2>
class Derivative< Multiply<F1, F2> > {
public:
  using Type = Add<Multiply<typename Derivative<F1>::Type, F2>, Multiply<F1, typename Derivative<F2>::Type> >;

  Derivative< Multiply<F1, F2> > (const Multiply<F1, F2>& f) :
    fn1_(f.fn1_),
    fn2_(f.fn2_),
    df1_(f.fn1_),
    df2_(f.fn2_)
  {
  }
  double operator()(double x) const
  {
    return df1_(x) * fn2_(x) + fn1_(x) * df2_(x);
  }

  Type calculation() const
  {
    return df1_.calculation() * fn2_ + fn1_ * df2_.calculation();
  }
  F1 fn1_;
  F2 fn2_;
  Derivative<F1> df1_;
  Derivative<F2> df2_;
};

template <class F1>
class Derivative< Multiply<F1, Const> > {
public:
  using Type = Multiply<Const, typename Derivative<F1>::Type>;


  Derivative< Multiply<F1, Const> > (const Multiply<F1, Const>& f)
    : df1_(f.fn1_), fn2_(f.fn2_)
  {
  }
  double operator()(double x) const
  {
    return df1_(x) * fn2_.const_;
  }

  Type calculation() const
  {
    return fn2_ * df1_.calculation();
  }
  Derivative<F1> df1_;
  Const fn2_;
};

template <class F2>
class Derivative< Multiply<Const, F2> > {
public:
  using Type = Multiply<Const, typename Derivative<F2>::Type>;

  Derivative< Multiply<Const, F2> > (const Multiply<Const, F2>& f) :
    fn1_(f.fn1_),
    df2_(f.fn2_)
  {
  }
  double operator()(double x) const
  {
    return fn1_.const_ * df2_(x);
  }

  Type calculation() const
  {
    return fn1_ * df2_.calculation();
  }
  Const fn1_;
  Derivative<F2> df2_;
};


template <class F>
class Derivative< Power<F> > {
public:
  using Type = Multiply<Multiply<Const, Power<F> >, typename Derivative<F>::Type>;

  Derivative< Power<F> > (const Power<F>& f)
    : f_(f.fn_), n_(f.n_), df_(f.fn_)
  {
  }
  double operator()(double x) const
  {
    return n_ * pow(f_(x), n_ - 1) * df_(x);
  }

  Type calculation() const
  {
    return (Const(n_) * Pow(f_, n_ - 1)) * df_.calculation();
  }
  F f_;
  double n_;
  Derivative<F> df_;
};


template <class F>
typename Derivative<F>::Type derivative(F f)
{
  return Derivative<F>(f).calculation();
}


#endif // DERIVATION_HPP
