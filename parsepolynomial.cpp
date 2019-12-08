#include "parsepolynomial.hpp"
#include <algorithm>
#include <iterator>
#include "functions.hpp"
#include <stack>
#include "basefunctions.hpp"
#include "operations.hpp"
#include "derivation.hpp"
#include <cstring>

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

ParsePolynomial::ParsePolynomial(const std::string & input) :
  checker_(true)
{
  std::for_each(input.begin(), input.end(), [&](char next) {
    vector_.push_back(next);
  });
}

void ParsePolynomial::pushExpressionToQueue()
{
  std::size_t j = 0;
  for (std::size_t i = j; i < vector_.size();)
  {
    if (isdigit(vector_[i]))
    {
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

double ParsePolynomial::getResult(double value)
{
  pushExpressionToQueue();
  std::stack<std::string> operands;
  std::stack<std::string> operators;
  std::queue<std::string> componentsOperation;
  std::stack<double> componentsResults;
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
        componentsResults.push(popStack(operators, operands, value));
        popStack(componentsOperation, componentsResults);
      }
      if (operators.empty() || isMorePriority(operators.top(), front))
      {
        operators.push(front);
      }
    }
    queue_.pop();
  }
  componentsResults.push(popStack(operators, operands, value));
  popStack(componentsOperation, componentsResults);
  return componentsResults.top();;
}

//this functions was added because all standart functions getting
//the wrong converting to double(rounding to int)
double ParsePolynomial::convertToDouble(const char *line)
{
  int length = strlen(line);
  int k=1;
  double r = 0.0;
  double p = 1.0;
  for (int i = 0; i < length; ++i)
  {
    if (k < 0)
      p = p * 10;
    if ('.' == line[i])
      k=-k;
    else
      r = r * 10 + (line[i] - '0');
  }
  return r / p;
}

double ParsePolynomial::popStack(std::stack<std::string> &operators, std::stack<std::string> &operands, double value)
{
  auto fun1 = Pow(X, 1);
  bool check1 = false;
  double result = 0.0;
  if (operators.empty() && !operands.empty())
  {
    if (operands.top() == "x")
      return 1.0;
    else
      return 0.0;
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
        double num1 = convertToDouble(op1.c_str());
        fun1 = Pow(X, num1);
        check1 = true;
        auto df = derivative(fun1);
        result = df(value);
      }
      else if (oper == "*")
      {
        if (check1)
        {
          std::string op = operands.top();
          operands.pop();
          double num = atof(op.c_str());
          auto fun2 = fun1 * num;
          auto df = derivative(fun2);
          result = df(value);
        }
        else
        {
          std::string op1 = operands.top();
          operands.pop();
          std::string op2 = operands.top();
          operands.pop();
          if (("x" == op1) || ("x" == op2))
          {
            if ("x" == op1)
            {
              op1.swap(op2);
            }
            double num = convertToDouble(op1.c_str());
            auto f = num * X;
            auto df = derivative(f);
            result = df(value);
          }
          else
          {
            result = 0.0;
          }
        }
      }
      else if (operands.top() == "x")
      {
        check1 = true;
        operands.pop();
        auto df = derivative(fun1);
        result = df(value);
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
