#include "polynomialchecker.hpp"
#include <algorithm>
#include <iostream>
#include "functions.hpp"

PolynomialChecker::PolynomialChecker(const std::string &forCheck) :
  forCheck_(forCheck)
{
}

void PolynomialChecker::setNextExp(const std::string &forCheck)
{
  forCheck_ = forCheck;
}


bool PolynomialChecker::isCorrect() {
  bool isCorrect = true;
  if (!isdigit(forCheck_[0]) && forCheck_[0] != 'x')
  {
    return false;
  }
  char previous = forCheck_[0];
  char lastChar = forCheck_[forCheck_.length() - 1];
  if (isPoint(lastChar) || isRightOperation(lastChar))
  {
    return false;
  }
  char prePrevious = previous;
  for (std::size_t i = 1; i < forCheck_.length(); ++i) {
    char current = forCheck_[i];
    if (isdigit(previous) && !(isdigit(current) || isRightOperation(current) || isPoint(current)))
    {
      isCorrect = false;
    }
    else if (isRightOperation(previous) && !(isdigit(current) || isX(current) || isPoint(current)))
    {
      isCorrect = false;
    }
    else if (isDegree(previous) && !isdigit(current))
    {
      isCorrect = false;
    }
    else if (isX(previous) && !(isRightOperation(current) || isDegree(current)))
    {
      isCorrect = false;
    }
    else if (isPoint(previous) && !isdigit(current))
    {
      isCorrect = false;
    }
    if (isX(prePrevious) && isX(current) && (previous == '*'))
    {
      isCorrect = false;
    }
    prePrevious = previous;
    previous = current;

  }

  return isCorrect;
}
