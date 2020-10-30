#include <iostream>
#include <fstream>
#include <thread>
#include <vector>

#include "ClientsDataQueue.hpp"
#include "Client.hpp"
#include "Server.hpp"

int main(int argc, char** argv) {
  clients::ClientsDataQueue data_queue;
  const std::vector<BYTE> client_ids = {1,2,3,7,4,5,6,8,9,10};
  std::string log_file_path = "kek.txt";

  std::thread client_thread([&data_queue, client_ids]() -> void {
    for(const auto i : client_ids) {
      clients::Client client(i, 10*i/3 + 2);
      client.send_data(data_queue);
    }
  });

  std::thread server_thread([&data_queue, log_file_path]() -> void {
      server::Server server(log_file_path);
      for(unsigned short int i = 0; i < 100; ++i) {
        if(data_queue.queue_size() != 0u) {
          server.process_client_data(data_queue.pop_data());
          i = 0;
          std::cout << "Client data processed!" << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
      }
  });


  client_thread.join();
  server_thread.join();
  return 0;
}
