#include "computer.hpp"

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
