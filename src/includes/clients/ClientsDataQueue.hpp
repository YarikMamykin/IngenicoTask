#ifndef SRC_INCLUDES_CLIENTS_CLIENTSDATAQUEUE_HPP
#define SRC_INCLUDES_CLIENTS_CLIENTSDATAQUEUE_HPP

#include "ClientData.hpp"
#include <set>
#include <mutex>

namespace clients {
  struct ClientsDataQueue {
    std::multiset<TDATA, TDATA_Compare> data_queue;
    std::mutex data_queue_mutex;
    void add_data(const TDATA& data);
    TDATA pop_data();
    size_t queue_size();
  };
}
#endif /* SRC_INCLUDES_CLIENTS_CLIENTSDATAQUEUE_HPP */
