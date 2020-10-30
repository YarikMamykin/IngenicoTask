#include "ClientsDataQueue.hpp"

namespace clients {
  void ClientsDataQueue::add_data(const TDATA &data) {
    std::lock_guard<std::mutex> guard(data_queue_mutex);
    data_queue.insert(data);
  }

  TDATA ClientsDataQueue::pop_data() {
    std::lock_guard<std::mutex> guard(data_queue_mutex);

    if(data_queue.size() == 0u) {
      return TDATA();
    }

    auto client_data = *data_queue.begin();
    data_queue.erase(data_queue.begin());

    return client_data;
  }

  size_t ClientsDataQueue::queue_size() {
    std::lock_guard<std::mutex> guard(data_queue_mutex);
    return data_queue.size();
  }
}
