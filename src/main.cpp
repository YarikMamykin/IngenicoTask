#include <iostream>
#include <thread>
#include <vector>
#include <cstdlib>

#include "ClientsDataQueue.hpp"
#include "Client.hpp"
#include "Server.hpp"

namespace {
  const std::string default_log_file_path = "log.txt";
  const BYTE min_number_of_clients = 1;
  const BYTE max_number_of_clients = 10;

  void show_help() {
    std::cout << "Invalid number of arguments received! No more than 2 arguments can be specified." << std::endl
              << "Integer number from 1 to 10 as argument specifies number of clients." << std::endl
              << "A string as an argument specifies the path to log file. Default path is 'log.txt'." << std::endl
              << "Order of arguments doesn't matter." << std::endl;
  }

  void generate_client_priorities(std::vector<BYTE>& client_priorities) {
    for(auto i = 0; i < client_priorities.size(); ++i) {
      client_priorities[i] = rand() % (max_number_of_clients + min_number_of_clients);
    }
  }

  bool process_args(int argc, char** argv, std::vector<BYTE>& client_priorities, std::string& log_file_path) {
    if(argc > 2 || argc < 1) {
      return false;
    }

    for(auto i = 1; i <= argc; ++i) {
      auto&& param = std::string(argv[i]);
      try {
        auto number_of_clients = std::stoi(param);
        if(number_of_clients < min_number_of_clients || number_of_clients > max_number_of_clients) {
          return false;
        }
        for(auto i = 0; i < number_of_clients; ++i) {
          client_priorities.push_back(0);
        }
        generate_client_priorities(client_priorities);
      } catch(...) {
        log_file_path = param;
      }
    }

    if(client_priorities.size() == 0u) {
      return false;
    }

    log_file_path = log_file_path.empty() ? default_log_file_path : log_file_path;
    return true;
  }

  constexpr DWORD generate_client_id(BYTE client_priority) {
    return 10 * client_priority / 3 + 2;
  } 
}

int main(int argc, char** argv) {
  clients::ClientsDataQueue data_queue;
  std::vector<BYTE> client_priorities;
  std::string log_file_path;

  // passing argc-1 because first argument is the name of program
  if(!process_args(argc-1, argv, client_priorities, log_file_path)) {
    show_help();
    return 1;
  }

  std::thread client_thread([&data_queue, client_priorities]() -> void {
    for(const auto i : client_priorities) {
      clients::Client client(i, generate_client_id(i));
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
        // 10 milliseconds for 100 times = 1000 milliseconds = 1 second
        // of idle state of server terminates its work.
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
      }
  });


  client_thread.join();
  server_thread.join();
  return 0;
}
