//#include <functional>
#include <stdexcept>
#include "inputEvent.hpp"

namespace kovshikov
{
  bool checkingClientName(const std::string& name)
  {
    for(char ch : name)
    {
      int ascii = (int)ch;
      if(!((ascii > 47 && ascii < 58) || (ascii > 96 && ascii < 123)))
      {
        //std::cout << ascii << ch << "\n"; //
        return false;
      }
    }
    return true;
  }
}

int main()
{
  std::vector<std::string> error;
  size_t countComputers;
  int cost = 0;
  kovshikov::Clock start, finish;
  std::cin >> countComputers;
  try
  {
    std::cin >> start >> finish;
  }
  catch(const std::invalid_argument& e)
  {
    std::cerr << e.what();
    return 1;
  }
  std::cin >> cost;

  std::queue<std::string> consoleOutput;
  std::unordered_map<std::string, int> clientsAndComputers;
  std::unordered_map<int, std::string> computersAndClients;
  std::queue<std::string> waitingQueue;
  std::map<int, kovshikov::Computer> computers;

  bool isError = false;
  while(true) //до конца ввода
  {
    std::string errorClock = "";
    kovshikov::Clock currentClock;
    int task;
    std::string clientName;
    int numComputer = 0;
    try
    {
      std::cin >> currentClock;
    }
    catch(const std::invalid_argument& e)
    {
      //std::cout << "TIME_ERROR\n"; //
      errorClock = e.what();
      isError = true;
    }

    std::cin >> task;
    if(task == 52)
    {
      break;
    }
    if(task != 1 && task != 2 && task != 3 && task != 4 && task != 11 && task != 12 && task != 13)
    {
      //std::cout << task << "TASK_ERROR\n"; //
      isError = true;
    }

    std::cin >> clientName;
    if(kovshikov::checkingClientName(clientName) == false)
    {
      //std::cout << "ERROR_NAME\n"; //
      isError = true;
    }

    if(task == 2)
    {
      std::cin >> numComputer;
      if(static_cast<size_t>(numComputer) > countComputers)
      {
        isError = true;
      }
    }

    if(isError == true)
    {
      //std::cout << "ERROR\n"; //
      error.push_back(errorClock);
      error.push_back(std::to_string(task));
      error.push_back(clientName);
      if(task == 2)
      {
        error.push_back(std::to_string(numComputer));
      }
      break;
    }

    if(task == 1)
    {
      //std::cout << "TASK1\n"; //
      kovshikov::clientCome(currentClock, clientName, consoleOutput, clientsAndComputers, start, finish);
    }
    else if(task == 2)
    {
      kovshikov::clientSitDown(currentClock, clientName, consoleOutput, clientsAndComputers, computersAndClients, computers, numComputer);
    }
    else if(task == 3)
    {
      kovshikov::clientWait(currentClock, clientName, consoleOutput, clientsAndComputers, computersAndClients, countComputers, waitingQueue);
    }
    else if(task == 4)
    {
      kovshikov::clientLeave(currentClock, clientName, consoleOutput, clientsAndComputers, computersAndClients, computers,  waitingQueue);
    }

   //нужна по-хорошему диспетчеризация
  }
  if(isError)
  {
    for(const std::string& str : error)
    {
      std::cout << str << " ";
    }
    std::cout << "\n";
    return 1;
  }
  else
  {
    kovshikov::clientForciblyLeave(finish, consoleOutput, clientsAndComputers, computers);
    kovshikov::endOfDay(start, finish, consoleOutput, computers, cost);
  }
}
