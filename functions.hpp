#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

inline bool isRightOperation(char c)
{
  return ((c == '+') || (c == '-') || (c == '*'));
}

inline bool isX(char c)
{
  return c == 'x';
}

inline bool isDegree(char c)
{
  return c == '^';
}

inline bool isPoint(char c)
{
  return c == '.';
}

#endif // FUNCTIONS_HPP
