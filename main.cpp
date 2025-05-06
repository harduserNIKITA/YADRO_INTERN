//#include <functional>
#include "inputEvent.hpp"

namespace kovshikov
{
  bool checkingClientName(const std::string& name)
  {

    for(char ch : name)
    {
      int ascii = (int)ch
      if(!(asii > 47 && ascii < 58) && (ascii > 96 && ascii < 123))
      {
        return false;
      }
    }
    return true;
  }

  int main()
  {
    std::vector<std::string> error;
    size_t countComputers;
    int cost = 0;
    Clock start, finish;
    std::cin >> computers;
    try
    {
      std::cin >> start >> finish;
    }
    catch(const std::invalid_exception& e)
    {
      std::err << e.what();
      return 1;
    }
    std::cin >> cost;

    std::queu<std::string> consolOutput;
    std::unordered_map<std::string, int> clientsAndComputers;
    std::unordered_map<int, std::string> computersAndClients;
    std::queue<std::string> waitingQueue;
    std::map<int, Computer> computers;

    std::map<int, std::function< void()>>

    bool isError = false;
    while(std::cin.eof()) //до конца ввода
    {
      std::string errorClock = "";
      Clock currentClock;
      int task;
      std::string clientName;
      int numComputer = 0;
      try
      {
        std::cin >> currentClock;
      }
      catch(const std::invalid_exception& e)
      {
        errorClock = e.what();
        isError = true;
      }

      std::cin >> task;
      if(task != 1 && task != 2 && task != 3 && task != 4 && task != 11 && task != 12 && task != 13)
      {
        isError = true;
      }

      std::cin >> clientName;
      if(checkingClientName == false)
      {
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
        clientCome(currentClock, clientName, consoleOutput, clientsAndComputers, start, finish);
      }
      else if(task == 2)
      {
        clientSitDown(currentClock, clientName, consoleOutput, clientsAndComputers, computersAndClients, computers, numComputer);
      }
      else if(task == 3)
      {
        clientWait(currentClock, clientName, consoleOutput, clientsAndComputers, computersAndClients, countComputers, waitingQueue);
      }
      else if(task == 4)
      {
        clientLeave(currentClock, clientName, consoleOutput, clientsAndComputers, computersAndClients, computers,  waitingQueue);
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
      clientForcibleLeave(finish, consoleOutput, clientsAndComputers, computers);
      endOfDay(start, finish, consoleOutput, computers);
    }
  }
}
