#include <polynomialchecker.hpp>
#include <algorithm>
#include <iostream>
#include <functions.hpp>

PolynomialChecker::PolynomialChecker(const std::string &forCheck) :
  forCheck_(forCheck)
{
}

bool PolynomialChecker::isCorrect() {
  bool isCorrect = true;
  if (!isdigit(forCheck_[0]) && forCheck_[0] != 'x')
  {
    return false;
  }
  char previous = forCheck_[0];
  //std::for_each(++std::begin(forCheck_), std::end(forCheck_), [&](char current) {
  for (std::size_t i = 1; i < forCheck_.length(); ++i) {
    char current = forCheck_[i];
    if (isdigit(previous) && !(isdigit(current) || isRightOperation(current) || isPoint(current)))
    {
      isCorrect = false;
    }
    else if (isRightOperation(previous) && !(isdigit(current) || isX(current)))
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
    previous = current;
  }

  return isCorrect;
}
