#ifndef INPUTEVENT_HPP
#define INPUTEVENT_HPP
#include <unordered_map>
#include <map>
#include <queue>
#include "clock.hpp"
#include "computer.hpp"

namespace kovshikov
{
  using cl_com = std::unordered_map<std::string, int>;
  using com_cl = std::unordered_map<int, std::string>;
  void addLineOutput(const Clock& currentClock, const std::string& num, const std::string& str, std::queue<std::string>& consoleOutput, const std::string& optionalStr = "");
  void getError(const Clock& currentClock, const std::string& smsError, std::queue<std::string>& consoleOutput);
  void clientCome(const Clock& currentClock, const std::string& clientName, std::queue<std::string>& consoleOutput, cl_com& clientsAndComputers, const Clock& start, const Clock& finish);
  void clientSitDown(const Clock& currentClock, const std::string& clientName, std::queue<std::string>& consoleOutput,
                                          cl_com& clientsAndComputers, com_cl& computersAndClients, std::map<int, Computer>& computers, int numComputer);
  void clientWait(const Clock& currentClock, const std::string& clientName, std::queue<std::string>& consoleOutput,
                                                  cl_com& clientsAndComputers, const com_cl& computersAndClients, size_t countComputers, std::queue<std::string>& waitingQueue);
  void clientLeave(const Clock& currentClock, const std::string& clientName, std::queue<std::string>& consoleOutput, cl_com& clientsAndComputers,
                                            com_cl& computersAndClients, std::map<int, Computer>& computers, std::queue<std::string>& waitingQueue);
  void clientForciblyLeave(const Clock& finish, std::queue<std::string>& consoleOutput, const cl_com& clientsAndComputers, std::map<int, Computer>& computers);
  void clientForciblySit(const Clock& currentClock, std::queue<std::string>& consoleOutput, int freeingComp, cl_com& clientsAndComputers,
                                              com_cl& computersAndClients, std::map<int, Computer>& computers, std::queue<std::string>& waitingQueue);
  void endOfDay(const Clock& start, const Clock& finish, std::queue<std::string>& consoleOutput, std::map<int, Computer> computers, int cost);
}

#endif
