#ifndef COMPUTER_HPP
#define COMPUTER_HPP

namespace kovshikov
{
  struct Computer
  {
    int income, minutes, currentMinutes, exitMinutes;
    Computer(): income(0), minutes(0), currentMinutes(0), exitMinutes(0) {};

    void increaseMinutes();
    void increaseIncome();
    void zeroing();
    void update();
  };
}

#endif
