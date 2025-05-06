#include "clock.hpp"
#include <stdexcept>

int kovshikov::Clock::getInMinutes()
{
  return hours * 60 + minutes;
}

std::string kovshikov::Clock::createStringTime()
{
  std::string strTime;
  if(hours < 10)
  {
    strTime += "0";
  }
  strTime += std::to_string(hours) + ":";
  if(minutes < 10)
  {
    strTime += "0";
  }
  strTime += std::to_string(minutes);
  return strTime;
}

bool kovshikov::isDigit(char ch)
{
  int asii = (int) ch;
  if(ascii > 47 && ascii < 58)
  {
    return true;
  }
  return false;
}

int kovshikov::twoCharToNumber(char tens, char units)
{
  return (tens - '0') * 10 + (units - '0');
}

std::istream& kovshikov::operator>>(std::istream& input, Clock& clock)
{
  std::string clockStr;
  input >> clockStr;
  bool isCorrectNum = IsDigit(clockStr[0]) && IsDigit(clockStr[1]) && IsDigit(clockStr[3]) && IsDigit(clockStr[4]);
  if(clockStr.length() == 5 && isCorrectNum && clockStr[2] == ':')
  {
    clock.hours = twoCharToNumber(clockStr[0], clockStr[1]);
    clock.minutes = twoCharToNumber(clockStr[3], clockStr[4]);
  }
  else
  {
    throw std::invalid_argument(clockStr);
  }
   return input;
}

std::ostream& kovshikov::operator<<(std::ostream& out, const Clock& clock)
{
  out << clock.createStringTime();
}

bool kovshikov::operator>(const Clock& left, const Clock& right)
{
  return (left.hours, left.minutes) > (right.hours, right.minutes);
}

bool kovshikov::operator<(const Clock& left, const Clock& right)
{
  return !(left > right);
}
