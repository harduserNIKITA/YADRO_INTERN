#ifndef INPUTEVENT_HPP
#define INPUTEVENT_HPP
#include <string>
#include <queue>

namespace kovshikov
{
  using cl_com = std::unordered_set<std::string, int>;
  using com_cl = std::unordered_map<int, std::string>;
  void clientCome(const Clock& currentClock, const std::string& clientName, u_set& clients, const Clock& start, const Clock& finish);
  void clientSitDown(const Clock& currentClock, const std::string& clientName, const u_set& clients, u_map& whoBusy, std::map<int, Computer>& computer2, int numComputer);
  void clientWait(const Clock& currentClock, const std::string& clientName, u_set& clients, const whoBusy&, int countComputer, std::dequeu<std::string>& waitingQueue);
}






#endif
