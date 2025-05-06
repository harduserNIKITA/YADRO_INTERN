#ifndef CLOCK_HPP
#define CLOCK_HPP
#include <string>
#include <iostream>

namespace kovshikov
{
  struct Clock
  {
    int hours = 0, minutes = 0;

    Clock() = default;
    Clock(int h, int m): hours(h), minutes(m) {};

    int getInMinutes() const;
    std::string createStringTime() const;
  };

  bool isDigit(char ch);
  int twoCharToNumber(char tens, char units);

  std::ostream& operator<<(std::ostream& out, const Clock& clock);
  std::istream& operator>>(std::istream& input, Clock& clock);
  bool operator>(const Clock& left, const Clock& right);
  bool operator<(const Clock& left, const Clock& right);
}

#endif
