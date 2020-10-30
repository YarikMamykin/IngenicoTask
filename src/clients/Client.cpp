#include "Client.hpp"

namespace clients {
  Client::Client(BYTE priority, DWORD id) {
    data.cPriority = priority;
    data.dwClientId = id;
  }

  void Client::send_data(ClientsDataQueue &data_queue) {
    using system_clock = std::chrono::system_clock;
    data.dwTicks = system_clock::to_time_t(system_clock::now());
    data_queue.add_data(data);
  }
}
