#ifndef CLOCK_HPP
#define CLOCK_HPP
#include <iostream>
#include <string>
//!!!
//???
//может быть какие то еще конструкторы нужны?
namespace kovshikov
{
  struct Clock
  {
    int hours = 0, minutes = 0;

    Clock() = default;
    Clock(int h, int m): hours(h), minutes(m) {};

    int getInMinutes();
    std::string createStringTime();
  }

  bool isDigit(char ch);
  int twoCharToNumber(char tens, char units);

  std::ostream& operator<<(std::ostream& out, Clock& clock);
  std::istream& operator>>(std::istream& input, const Clock& clock);
  bool operator>(const Clock& left, const Clock& right);
  bool operator<(const Clock& left, const Clock& right);
}

#endif
