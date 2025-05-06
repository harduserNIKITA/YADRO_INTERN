#include "inputEvent.hpp"
#include <tuple>

void kovshikov::addLineOutput(const Clock& currentClock, const std::string& num, const std::string& str, std::queue<std::string>& consoleOutput, const std::string& optionalStr)
{
  std::string lineOutput;
  lineOutput += currentClock.createStringTime() + " " + num + " " + str + " " + optionalStr;
  consoleOutput.push(lineOutput);
}

void kovshikov::getError(const Clock& currentClock, const std::string& smsError, std::queue<std::string>& consoleOutput)
{
  addLineOutput(currentClock, "13", smsError, consoleOutput);
}

void kovshikov::clientCome(const Clock& currentClock, const std::string& clientName, std::queue<std::string>& consoleOutput, cl_com& clientsAndComputers, const Clock& start, const Clock& finish)
{
  addLineOutput(currentClock, "1", clientName, consoleOutput);
  if(currentClock < start || currentClock > finish)
  {
    std::string smsError = "NotOpenYet";
    getError(currentClock, smsError, consoleOutput);
  }
  else if(clientsAndComputers.find(clientName) != clientsAndComputers.end())
  {
    std::string smsError = "YouShallNotPass";
    getError(currentClock, smsError, consoleOutput);
  }
  else
  {
    clientsAndComputers[clientName] = 0;
  }
}

void kovshikov::clientSitDown(const Clock& currentClock, const std::string& clientName, std::queue<std::string>& consoleOutput,
                                         cl_com& clientsAndComputers, com_cl& computersAndClients, std::map<int, Computer>& computers, int numComputer)
{
  addLineOutput(currentClock, "2", clientName, consoleOutput, std::to_string(numComputer));
  if(clientsAndComputers.find(clientName) == clientsAndComputers.end())
  {
    std::string smsError = "ClientUnknown";
    getError(currentClock, smsError, consoleOutput);
  }
  else if(computersAndClients.find(numComputer) == computersAndClients.end())//может для computersAndClients вообще хватило бы set?
  {
    computersAndClients[numComputer] = clientName;
    clientsAndComputers[clientName] = numComputer;
    computers[numComputer].currentMinutes = currentClock.getInMinutes();
  }
  else
  {
     std::string smsError = "PlaceIsBusy";
     getError(currentClock, smsError, consoleOutput);
  }
}

void kovshikov::clientWait(const Clock& currentClock, const std::string& clientName, std::queue<std::string>& consoleOutput,
                                                 cl_com& clientsAndComputers, const com_cl& computersAndClients, size_t countComputers, std::queue<std::string>& waitingQueue)
{
  addLineOutput(currentClock, "3", clientName, consoleOutput);
  if(computersAndClients.size() < countComputers)
  {
    std::string smsError = "ICanWaitNoLonger";
    getError(currentClock, smsError, consoleOutput);
  }
  else if(countComputers <= waitingQueue.size())
  {
    addLineOutput(currentClock, "11", clientName, consoleOutput);
    clientsAndComputers.erase(clientName);
  }
  else
  {
    waitingQueue.push(clientName);
  }
}

void kovshikov::clientLeave(const Clock& currentClock, const std::string& clientName, std::queue<std::string>& consoleOutput, cl_com& clientsAndComputers,
                                          com_cl& computersAndClients, std::map<int, Computer>& computers, std::queue<std::string>& waitingQueue)
{
  addLineOutput(currentClock, "4", clientName, consoleOutput);
  if(clientsAndComputers.find(clientName) == clientsAndComputers.end())
  {
    std::string smsError = "ClientUnknown";
    getError(currentClock, smsError, consoleOutput);
  }
  else
  {
    int freeingComp = clientsAndComputers[clientName];
    clientsAndComputers.erase(clientName);
    computersAndClients.erase(freeingComp);
    computers[freeingComp].exitMinutes = currentClock.getInMinutes();
    computers[freeingComp].update();
    clientForciblySit(currentClock, consoleOutput, freeingComp, clientsAndComputers, computersAndClients, computers, waitingQueue);
  }
}


void kovshikov::clientForciblyLeave(const Clock& finish, std::queue<std::string>& consoleOutput, const cl_com& clientsAndComputers, std::map<int, Computer>& computers)
{
  for(const auto& element : clientsAndComputers)
  {
    addLineOutput(finish, "11", element.first, consoleOutput);
    computers[element.second].exitMinutes = finish.getInMinutes();
    computers[element.second].update();
  }
}

void kovshikov::clientForciblySit(const Clock& currentClock, std::queue<std::string>& consoleOutput, int freeingComp, cl_com& clientsAndComputers,
                                             com_cl& computersAndClients, std::map<int, Computer>& computers, std::queue<std::string>& waitingQueue)
{
  if(!waitingQueue.empty())
  {
    std::string waitingClient = waitingQueue.front();
    waitingQueue.pop();
    addLineOutput(currentClock, "12", waitingClient, consoleOutput, std::to_string(freeingComp));
    clientsAndComputers[waitingClient] = freeingComp;
    computersAndClients[freeingComp] = waitingClient;
    computers[freeingComp].currentMinutes = currentClock.getInMinutes();
  }
}

void kovshikov::endOfDay(const Clock& start, const Clock& finish, std::queue<std::string>& consoleOutput, std::map<int, Computer> computers, int cost)
{
  std::cout << start << "\n";
  while(!consoleOutput.empty())
  {
    std::cout << consoleOutput.front() << "\n";
    consoleOutput.pop();
  }
  std::cout << finish << "\n";
  for(const auto& element : computers)
  {
    int minutes = element.second.minutes;
    int hour = minutes / 60;
    int min = minutes - hour * 60;
    Clock clock(hour, min);
    std::cout << element.first << " " << element.second.income * cost << " " << clock << "\n";
  }
}
