#include <fstream>
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
        return false;
      }
    }
    return true;
  }
}

int main(int argc, char* argv[])
{
  if(argc != 2)
  {
    std::cerr << "Arquments NOT TWO\n";
    return 1;
  }

  std::ifstream inputFile(argv[1]);
  if (!inputFile.is_open())
  {
    std::cerr << "Can't OPEN FILE\n";
    return 1;
  }
  std::vector<std::string> error;
  size_t countComputers;
  int cost = 0;
  kovshikov::Clock start, finish;
  inputFile >> countComputers;
  try
  {
    inputFile >> start >> finish;
  }
  catch(const std::invalid_argument& e)
  {
    std::cerr << e.what();
    return 1;
  }
  inputFile >> cost;

  std::queue<std::string> consoleOutput;
  std::unordered_map<std::string, int> clientsAndComputers;
  std::unordered_map<int, std::string> computersAndClients;
  std::queue<std::string> waitingQueue;
  std::map<int, kovshikov::Computer> computers;

  bool isError = false;
  while(!inputFile.eof())
  {
    std::string errorClock = "";
    kovshikov::Clock currentClock;
    int task;
    std::string clientName;
    int numComputer = 0;
    try
    {
      inputFile >> currentClock;
    }
    catch(const std::invalid_argument& e)
    {
      if(inputFile.eof())
      {
        break;
      }
      errorClock = e.what();
      isError = true;
    }

    inputFile >> task;
    if(task != 1 && task != 2 && task != 3 && task != 4 && task != 11 && task != 12 && task != 13)
    {
      isError = true;
    }

    inputFile >> clientName;
    if(kovshikov::checkingClientName(clientName) == false)
    {
      isError = true;
    }

    if(task == 2)
    {
      inputFile >> numComputer;
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
