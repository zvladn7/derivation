#define BOOST_TEST_MODULE CHECKER
#include <stdexcept>
#include <boost/test/included/unit_test.hpp>
#include <boost/test/auto_unit_test.hpp>

#include <../../polynomialchecker.hpp>


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
