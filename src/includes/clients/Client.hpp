#ifndef SRC_INCLUDES_CLIENTS_CLIENT_HPP
#define SRC_INCLUDES_CLIENTS_CLIENT_HPP

#include "ClientsDataQueue.hpp"

namespace clients {
  struct Client {
    TDATA data;
    Client(BYTE priority, DWORD id);
    void send_data(ClientsDataQueue& data_queue);
  };
}
#endif /* SRC_INCLUDES_CLIENTS_CLIENT_HPP */
