#ifndef PARSEPOLYNOMIAL_HPP
#define PARSEPOLYNOMIAL_HPP
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <stack>
#include "basefunctions.hpp"

class ParsePolynomial
{
public:
  ParsePolynomial(std::istream &input);
  ParsePolynomial(const std::string &input);
  double getResult(double value);
private:
  std::vector<char> vector_;
  std::queue<std::string> queue_;
  bool checker_;

  void pushExpressionToQueue();
  bool isMorePriority(const std::string & oper1, const std::string & oper2);
  int getPriority(const std::string &oper);
  double convertToDouble(const char *line);
  double popStack(std::stack<std::string> &operators, std::stack<std::string> &operands, double value);
  void popStack(std::queue<std::string> &componentsOperation, std::stack<double> &componentsResults);
};

#endif // PARSEPOLYNOMIAL_HPP
