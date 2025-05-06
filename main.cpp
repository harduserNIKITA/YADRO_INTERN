#include <dequeu>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include "clock.hpp"

namespace kovshikov
{
  int main()
  {
    size_t countComputers;
    int cost = 0;
    Clock start, finish;
    std::cin >> computers >> start >> finish >> cost;

    std::queu<std::string> consolOutput;

    std::unordered_map<std::string, int> clientsAndComputers; //база клиентов, находящихся в комп клубе

    std::unordered_map<int, std::string> computersAndClients; //карта из номеров столов и клиентов, которые заняли

    std::queue<std::string> waitingQueue; // очередь из клиентов
    //std::map<int, std::pair<int, Clock>> computers //карта из компьютеров и их показаелей
    std::map<int, Computer> computers; //карта из компьютеров
    while(std::cin.eof()) //до конца ввода
    {
      Clock currentClock;
      int task;
      std::string clientName;
      int numComputer = 0;
      std::cin >> currentClock >> task >> clientName;
      if(task == 2)
      {
        std::cin >> numComputer;
      }
      //тут должна быть диспетчирезация
    }
    clientForcibleLeave(finish, consoleOutput, clientsAndComputers, computers);
    endOfDay(start, finish, consoleOutput, computers);
  }
}
