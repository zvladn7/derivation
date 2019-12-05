#ifndef POLYNOMIALCHECKER_HPP
#define POLYNOMIALCHECKER_HPP
#include <string>

class PolynomialChecker
{
public:
  PolynomialChecker(const std::string &forCheck);
  bool isCorrect();
  void setNextExp(const std::string &forCheck);
private:
  std::string forCheck_;
};

#endif // POLYNOMIALCHECKER_HPP
