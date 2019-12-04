#include "parsepolynomial.hpp"
#include <algorithm>
#include <iterator>
#include <functions.hpp>
#include <stack>
#include <basefunctions.hpp>
#include <operations.hpp>
#include <derivation.hpp>

Simple X;

ParsePolynomial::ParsePolynomial(std::istream &input) :
  checker_(true)
{
  std::for_each(std::istream_iterator<char>(input), std::istream_iterator<char>(), [&](char next) {
    vector_.push_back(next);
  });

  if (!std::cin.eof())
  {
    checker_ = false;
  }
}

void ParsePolynomial::pushExpressionToQueue()
{
  //for (auto i = vector_.begin(); i != vector_.end() ; ++i)
  std::size_t j = 0;
  for (std::size_t i = j; i < vector_.size();)
  {
    if (isdigit(vector_[i]))
    {
      //auto it = std::find_if(&i, std::end(vector_), [](char next) {
      //  return isRightOperation(next) || isDegree(next);
      //});
      for (j = i + 1; j < vector_.size(); ++j)
      {
        if (isRightOperation(vector_[j]) || isDegree(vector_[j]))
          break;
      }
      std::string number = "";
      for (std::size_t k = i; k < j; ++k)
        number += vector_[k];
      queue_.push(number);
      i = j;
    }
    else
    {
      std::string charToString(1, vector_[i]);
      queue_.push(charToString);
      i = ++j;
    }
  }
}

int ParsePolynomial::getPriority(const std::string &oper)
{
  if ((oper == "+") || (oper == "-"))
    return 1;
  if (oper == "*")
    return 2;
  if (oper == "^")
    return 3;
  return -1;
}

bool ParsePolynomial::isMorePriority(const std::string &oper1, const std::string &oper2)
{
  return getPriority(oper1) < getPriority(oper2);
}

//bool isOperation(const std::string &str)
//{
//  return ((str == "+") || (str == "-") || (str == "*") || str[]);
//}

double ParsePolynomial::getResult(double value)
{
  pushExpressionToQueue();
  std::stack<std::string> operands;
  std::stack<std::string> operators;
  std::queue<std::string> componentsOperation;
  std::stack<double> componentsResults;
  double result = 0.0;
  while (!queue_.empty())
  {
    std::string front = queue_.front();
    if (std::isdigit(front[0]) || (front == "x"))
    {
      operands.push(front);
    }
    else
    {
      if (getPriority(front) == 1)
      {
        componentsOperation.push(front);
      }
      if (operators.empty() || isMorePriority(operators.top(), front))
      {
        operators.push(front);
      }
      else
      {
        componentsResults.push(popStack(operators, operands, value));
        popStack(componentsOperation, componentsResults);
      }
    }
    queue_.pop();
  }
  componentsResults.push(popStack(operators, operands, value));
  popStack(componentsOperation, componentsResults);
  return componentsResults.top();;
}

double ParsePolynomial::popStack(std::stack<std::string> &operators, std::stack<std::string> &operands, double value)
{
  auto fun1 = Pow(X, 1);
  bool check1 = false;
  double result = 0.0;
  if (operators.empty() && !operands.empty())
  {
    if (operands.top() == "x")
      return 1;
    else
      return 0;
  }
  while (!operators.empty())
  {
    std::string oper = operators.top();
    operators.pop();
    if (oper == "^")
    {
      std::string op1 = operands.top();
      operands.pop();
      operands.pop();
      double num1 = atof(op1.c_str());
      fun1 = Pow(X, num1);
      check1 = true;
      auto df = derivative(fun1);
      result = df(value);
    }
    else if (operands.top() == "x")
    {
      check1 = true;
      operands.pop();
      auto df = derivative(fun1);
      result = df(value);
    }
    if (oper == "*")
    {
      std::string op = operands.top();
      operands.pop();
      double num = atof(op.c_str());
      if (check1)
      {
        auto fun2 = fun1 * num;
        auto df = derivative(fun2);
        result = df(value);
      }
    }
  }

  return result;
}

void ParsePolynomial::popStack(std::queue<std::string> &componentsOperation, std::stack<double> &componentsResults)
{
  if (!componentsOperation.empty() && (componentsResults.size() > 1))
  {
    double result;
    double op1 = componentsResults.top();
    componentsResults.pop();
    double op2 = componentsResults.top();
    componentsResults.pop();
    if (componentsOperation.front() == "+")
      result = op2 + op1;
    else
      result = op2 - op1;
    componentsOperation.pop();
    componentsResults.push(result);
  }
}
