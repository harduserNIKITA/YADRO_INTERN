#ifndef COMPUTER_HPP
#define COMPUTER_HPP

namespace kovshikov //наверное стоит сделать поле clock и просто усовершенствовать класс clock!!!
{
  struct Computer
  {
    int income, minutes, currentMinutes, exitMinutes;
    Computer(): income(0), minutes(0), currentMinutes(0), exitMinutes(0);

    void increaseMinutes();
    void increaseIncome();
    void zeroing();
    void update()

  }
}

void kovshikov::Computer::increaseMinutes()
{
  minutes += exitMinutes - currentMinutes;
}

void kovshikov::Computer::increaseIncome()
{
  int usingComputer = exitMinutes - currentMinutes;
  int costSession = usingComputer/60;
  if(usingComputer % 60 != 0)
  {
    costSession += 1;
  }
  income += costSession;
}

void kovshikov::Computer::zeroing()
{
  currentMinutes = 0;
  exitMinutes = 0;
}

void kovshikov::Computer::update()
{
  increaseMinutes();
  increaseIncome();
  zeroing();
}

#endif
