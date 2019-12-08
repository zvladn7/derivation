#define BOOST_TEST_MODULE DERIVATIVE
#include <boost/test/included/unit_test.hpp>
#include <boost/test/auto_unit_test.hpp>
#include <string>
#include <iostream>

#include <../../polynomialchecker.hpp>
#include <../../parsepolynomial.hpp>

const double FAULT = 0.00001;

BOOST_AUTO_TEST_SUITE(PolynomialCheckerTest)

BOOST_AUTO_TEST_CASE(TestSimpleIntExp)
{
  PolynomialChecker pc("1");
  BOOST_CHECK(pc.isCorrect());
  pc.setNextExp("x");
  BOOST_CHECK(pc.isCorrect());
  pc.setNextExp("3*x");
  BOOST_CHECK(pc.isCorrect());
  pc.setNextExp("2+x");
  BOOST_CHECK(pc.isCorrect());
  pc.setNextExp("2-x");
  BOOST_CHECK(pc.isCorrect());
  pc.setNextExp("x*3");
  BOOST_CHECK(pc.isCorrect());
  pc.setNextExp("x+2");
  BOOST_CHECK(pc.isCorrect());
  pc.setNextExp("x^2");
  BOOST_CHECK(pc.isCorrect());
  pc.setNextExp("2-x");
  BOOST_CHECK(pc.isCorrect());
  pc.setNextExp("3-2");
  BOOST_CHECK(pc.isCorrect());
  pc.setNextExp("3+2");
  BOOST_CHECK(pc.isCorrect());
}

BOOST_AUTO_TEST_CASE(TestSimpleDoubleExp)
{
  PolynomialChecker pc("1.2");
  BOOST_CHECK(pc.isCorrect());
  pc.setNextExp("1.123");
  BOOST_CHECK(pc.isCorrect());
  pc.setNextExp("0.00001");
  BOOST_CHECK(pc.isCorrect());
  pc.setNextExp("3.123*x");
  BOOST_CHECK(pc.isCorrect());
  pc.setNextExp("2.123+x");
  BOOST_CHECK(pc.isCorrect());
  pc.setNextExp("2.3123-x");
  BOOST_CHECK(pc.isCorrect());
  pc.setNextExp("x*3.213");
  BOOST_CHECK(pc.isCorrect());
  pc.setNextExp("x+2.123");
  BOOST_CHECK(pc.isCorrect());
  pc.setNextExp("x^0.312");
  BOOST_CHECK(pc.isCorrect());
  pc.setNextExp("2.312-x");
  BOOST_CHECK(pc.isCorrect());
  pc.setNextExp("3.12-2.312");
  BOOST_CHECK(pc.isCorrect());
  pc.setNextExp("3.3120+2.9210");
  BOOST_CHECK(pc.isCorrect());
}

BOOST_AUTO_TEST_CASE(TestLastCharIsCorrect)
{
  PolynomialChecker pc("1.");
  BOOST_CHECK(!pc.isCorrect());
  pc.setNextExp("1+");
  BOOST_CHECK(!pc.isCorrect());
  pc.setNextExp("1-");
  BOOST_CHECK(!pc.isCorrect());
  pc.setNextExp("1*");
  BOOST_CHECK(!pc.isCorrect());
  pc.setNextExp("1^");
  BOOST_CHECK(!pc.isCorrect());
}

BOOST_AUTO_TEST_CASE(TestFirstCharIsCorrect)
{
  PolynomialChecker pc(".1");
  BOOST_CHECK(!pc.isCorrect());
  pc.setNextExp("+1");
  BOOST_CHECK(!pc.isCorrect());
  pc.setNextExp("-1");
  BOOST_CHECK(!pc.isCorrect());
  pc.setNextExp("*1");
  BOOST_CHECK(!pc.isCorrect());
  pc.setNextExp("^1");
  BOOST_CHECK(!pc.isCorrect());
}

BOOST_AUTO_TEST_CASE(TestInvalidOnlyOneChar)
{
  PolynomialChecker pc(".");
  BOOST_CHECK(!pc.isCorrect());
  pc.setNextExp("+");
  BOOST_CHECK(!pc.isCorrect());
  pc.setNextExp("-");
  BOOST_CHECK(!pc.isCorrect());
  pc.setNextExp("*");
  BOOST_CHECK(!pc.isCorrect());
  pc.setNextExp("^");
  BOOST_CHECK(!pc.isCorrect());
}

BOOST_AUTO_TEST_CASE(TestNotSimpleExpressions)
{
  PolynomialChecker pc("1.2*x^5-x^4+5+x^2+x^7");
  BOOST_CHECK(pc.isCorrect());
  pc.setNextExp("1.2*x^11.23+56.213*x^91+x^41");
  BOOST_CHECK(pc.isCorrect());
  pc.setNextExp("3*x^5-2*x^4+x^3-10*x^2+5*x+2");
  BOOST_CHECK(pc.isCorrect());
  pc.setNextExp("3*x^5/2*x^4+x^3-10*x^2+5*x+2");
  BOOST_CHECK(!pc.isCorrect());
  pc.setNextExp(".3*x^5/2*x^4+x^3-10*x^2+5*x+2");
  BOOST_CHECK(!pc.isCorrect());
  pc.setNextExp("3*x^5+2*x^4+x^3-10.*x^2+5*x+2");
  BOOST_CHECK(!pc.isCorrect());
  pc.setNextExp("3*x^5+2*x^4+x^3-10.*x^2+5*x++2");
  BOOST_CHECK(!pc.isCorrect());
  pc.setNextExp("3*x^5+2*x^4+x^3--10.*x^2+5*x+2");
  BOOST_CHECK(!pc.isCorrect());
  pc.setNextExp("3*x^5+2*x^4+x^3-10.*x^2+5*x+2+");
  BOOST_CHECK(!pc.isCorrect());
  pc.setNextExp("3*x^5+2*x^4+x^3-10.*x^2+5*x+2*");
  BOOST_CHECK(!pc.isCorrect());
  pc.setNextExp("3*x^5+2*x^4+x^3-10.*x^2+5*x+2^");
  BOOST_CHECK(!pc.isCorrect());
  pc.setNextExp("3*x^5+2*x^4+x^3-10.*x^2+5*x+2-");
  BOOST_CHECK(!pc.isCorrect());
  pc.setNextExp("3*x^5-2*x^.4+x^3-10*x^2+5*x+2");
  BOOST_CHECK(!pc.isCorrect());
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(ParsePolynomialTest)

BOOST_AUTO_TEST_CASE(TestNotSimpleExp)
{
  const std::string exp = "5*x+2";
  ParsePolynomial parsePolynomial(exp);
  const double res = parsePolynomial.getResult(0);
  BOOST_CHECK_CLOSE(res, 5.0, FAULT);

  const std::string exp1 = "3*x^3-3*x^2+2";
  ParsePolynomial parsePolynomial1(exp1);
  const double res1 = parsePolynomial1.getResult(0);
  BOOST_CHECK_CLOSE(res1, 0, FAULT);
  const double res2 = parsePolynomial1.getResult(1);
  BOOST_CHECK_CLOSE(res2, 3, FAULT);
  const double res3 = parsePolynomial1.getResult(-1);
  BOOST_CHECK_CLOSE(res3, 15, FAULT);
  const double res4 = parsePolynomial1.getResult(100);
  BOOST_CHECK_CLOSE(res4, 89400, FAULT);
  const double res5 = parsePolynomial1.getResult(-100);
  BOOST_CHECK_CLOSE(res5, 90600, FAULT);
}

BOOST_AUTO_TEST_CASE(TestComplicatedExp)
{
  const std::string exp = "x+2";
  ParsePolynomial parsePolynomial(exp);
  const double res = parsePolynomial.getResult(2);
  BOOST_CHECK_CLOSE(res, 1, FAULT);

  const std::string exp1 = "2*x^3+2*x^2+2*x+2";
  ParsePolynomial parsePolynomial1(exp1);
  const double res1 = parsePolynomial1.getResult(0);
  BOOST_CHECK_CLOSE(res1, 2, FAULT);
  const double res2 = parsePolynomial1.getResult(1);
  BOOST_CHECK_CLOSE(res2, 12, FAULT);
  const double res3 = parsePolynomial1.getResult(-1);
  BOOST_CHECK_CLOSE(res3, 4, FAULT);
  const double res4 = parsePolynomial1.getResult(2);
  BOOST_CHECK_CLOSE(res4, 34, FAULT);
  const double res5 = parsePolynomial1.getResult(-2);
  BOOST_CHECK_CLOSE(res5, 18, FAULT);
}

BOOST_AUTO_TEST_CASE(TestSimpleIntExp)
{
  std::string exp = "2*x^2";
  ParsePolynomial parsePolynomial(exp);
  double res = parsePolynomial.getResult(2);
  BOOST_CHECK_CLOSE(res, 8, FAULT);

  exp = "1";
  ParsePolynomial parsePolynomial1(exp);
  res = parsePolynomial1.getResult(2);
  BOOST_CHECK_CLOSE(res, 0, FAULT);

  exp = "x";
  ParsePolynomial parsePolynomial2(exp);
  res = parsePolynomial2.getResult(2);
  BOOST_CHECK_CLOSE(res, 1, FAULT);

  exp = "x+x";
  ParsePolynomial parsePolynomial3(exp);
  res = parsePolynomial3.getResult(2);
  BOOST_CHECK_CLOSE(res, 2, FAULT);

  exp = "x-x";
  ParsePolynomial parsePolynomial4(exp);
  res = parsePolynomial4.getResult(2);
  BOOST_CHECK_CLOSE(res, 0, FAULT);
}

BOOST_AUTO_TEST_CASE(TestFirstNumberIntExp)
{
  std::string exp = "2-x";
  ParsePolynomial parsePolynomial(exp);
  double res = parsePolynomial.getResult(2);
  BOOST_CHECK_CLOSE(res, -1, FAULT);

  exp = "2*x";
  ParsePolynomial parsePolynomial1(exp);
  res = parsePolynomial1.getResult(2);
  BOOST_CHECK_CLOSE(res, 2, FAULT);

  exp = "1+2*x";
  ParsePolynomial parsePolynomial4(exp);
  res = parsePolynomial4.getResult(2);
  BOOST_CHECK_CLOSE(res, 2, FAULT);
}


BOOST_AUTO_TEST_SUITE_END()
